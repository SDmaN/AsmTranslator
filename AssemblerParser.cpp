#include <fstream>

#include "AssemblerParser.h"
#include "ErrorsHandling/Exceptions/FileNotFoundException.h"
#include "ErrorsHandling/Exceptions/TranslationException.h"
#include "ErrorsHandling/Error.h"
#include <iostream>

const std::string FileNotFoundMessage = "Не удалось открыть исходный файл.";

AssemblerParser::AssemblerParser()
{

    initHandlers();
}

std::vector<CommandData> AssemblerParser::parse(std::istream &stream, bool *hasErrors)
{
    std::vector<CommandData> result; // Результирующий вектор с данными команд
    std::string line; // Считанная строка файла
    m_currentLineIndex = 0; // Номер текущей строки

    while(!stream.eof())
    {
        CommandData cmdData; // Разобранные данные команды из исходной строки

        try
        {
            std::getline(stream, line); // Считываем очередную строку
            parseLine(line, cmdData); // Разбиваем ее
        }
        catch(TranslationException &ex)
        {
            if(hasErrors != nullptr)
                *hasErrors = true;
        }

        result.push_back(cmdData); // Сохраняем результат независимо от ошибки
        ++m_currentLineIndex; // Переходим к следующей линии
    }

    return result;
}

std::vector<CommandData> AssemblerParser::parse(const std::string &fileName, bool *hasErrors)
{
    std::ifstream sourceFile(fileName); // Открываем файл из которого читать

    if(sourceFile.is_open())
        return parse(sourceFile, hasErrors);

    // По каким-то причинам не удалось открыть
    if(hasErrors != nullptr)
        *hasErrors = true;

    throw FileNotFoundException(FileNotFoundMessage);
}

void AssemblerParser::initHandlers()
{
    m_stateHandlers.resize(StatesCount);

    // Функциональные привязки к массиву, где номер состояния - индекс элемента массива
    // Предоставляет удобство при выборе очередного обработчика соятояния

    m_stateHandlers[Start] = std::bind(handleStart, this, std::placeholders::_1, std::placeholders::_2);
    m_stateHandlers[Id] = std::bind(handleId, this, std::placeholders::_1, std::placeholders::_2);
    m_stateHandlers[IdEnding] = std::bind(handleIdEnding, this, std::placeholders::_1, std::placeholders::_2);
    m_stateHandlers[Code] = std::bind(handleCode, this, std::placeholders::_1, std::placeholders::_2);
    m_stateHandlers[CodeWaiting] = std::bind(handleCodeWaiting, this, std::placeholders::_1, std::placeholders::_2);
    m_stateHandlers[ArgWaiting] = std::bind(handleArgWaiting, this, std::placeholders::_1, std::placeholders::_2);
    m_stateHandlers[Arg] = std::bind(handleArg, this, std::placeholders::_1, std::placeholders::_2);
    m_stateHandlers[Comment] = std::bind(handleComment, this, std::placeholders::_1, std::placeholders::_2);
}

void AssemblerParser::parseLine(const std::string &line, CommandData &cmdData)
{
    cmdData.lineIndex = m_currentLineIndex; // Сохраняем номер строки
    cmdData.sourceLine = line; // Сохрнаяем исходную строку

    m_currentState = Start; // Start - всегда первое состояние
    m_currentSymbolIndex = 0;

    // Читаем пока не конец строки и состояние не End
    while(m_currentSymbolIndex < line.size() + 1 && m_currentState != End)
    {
        try
        {
            char symbol = line[m_currentSymbolIndex]; // Берем очередной символ
            m_currentState = m_stateHandlers[m_currentState](symbol, cmdData); // Применяем нужные обработчик

            ++m_currentSymbolIndex;
        }
        catch(TranslationException &ex)
        {
            saveErrorData(cmdData, ex.translationError().errorCode()); // Сохраняем ошибку
            m_currentState = End; // После ошибки состояние в End

            throw; // Выбрасываем наверх
        }
    }
}

AssemblerParser::SymbolType AssemblerParser::getSymbolType(char symbol) const
{
    const char colon = ':';
    const char commentSeparator = ';';

    if(symbol == ' ' || symbol == '\t')
        return Space;

    if(symbol == colon)
        return Colon;

    if(symbol == commentSeparator)
        return CommentSeparator;

    if(symbol == '_')
        return Underline;

    if(isdigit(symbol))
        return Digit;

    if(isalpha(symbol))
        return Alpha;

    if(symbol == '\n' || symbol == '\0')
        return LineEnd;

    return Unknown;
}

AssemblerParser::State AssemblerParser::handleStart(char symbol, CommandData &cmdData) const
{
    SymbolType symbolType = getSymbolType(symbol);

    switch(symbolType)
    {
        case Unknown: // Первый символ неверен
        case Colon:
        case Digit:
            throwTranslationException(CompillerError::IncorrectSymbol);
            return End;

        case CommentSeparator: // Строка начинается с комментария. Переходим к сбору комментария
            return Comment;

        case LineEnd: // Строка пуста
            return End;

        case Space: // Пропускаем пробелы
            return m_currentState;

        case Alpha: // Нашли метку или код оерации
        case Underline:
            cmdData.label = symbol; // Начинаем формировать метку
            return Id;
    }

    throwTranslationException(CompillerError::Unknown);
    return End;
}

AssemblerParser::State AssemblerParser::handleId(char symbol, CommandData &cmdData) const
{
    SymbolType symbolType = getSymbolType(symbol);

    switch(symbolType)
    {
        case Alpha: // Продолжаются символы метки или кода
        case Underline:
        case Digit:
            cmdData.label += symbol; // Продолжаем формирование
            return m_currentState; // Остаемся сдесь же

        case Colon: // Закончилась МЕТКА
            return CodeWaiting; // Ожидаем код

        case Space: // Название идентификатора кончилось
            return IdEnding; // Переходим к состоянию, в котором можно понять, была ли метка или код

        case CommentSeparator: // Увидели комментарий, значит был код
            cmdData.code = cmdData.label;
            cmdData.label.clear();
            return Comment; // Переходим к сбору комментария

        case Unknown: // Встретили символ, который не может быть в названии идентификатора
            throwTranslationException(CompillerError::IncorrectSymbol);

        case LineEnd: // Конец строки, значит собрали код
            cmdData.code = cmdData.label;
            cmdData.label.clear();
            return End;
    }

    throwTranslationException(CompillerError::Unknown);
    return End;
}

AssemblerParser::State AssemblerParser::handleIdEnding(char symbol, CommandData &cmdData) const
{
    SymbolType symbolType = getSymbolType(symbol);

    switch(symbolType)
    {
        case Unknown: // Встретили начало аргумента, значит собрали код
        case Digit: // Также начинаем собирать аргумент
        case Alpha:
        case Underline:
            cmdData.code = cmdData.label;
            cmdData.arg = symbol;
            cmdData.label.clear();
            return Arg;

        case Space: // Пропускаем пробелы, пока не встретим другой символ
            return m_currentState;

        case Colon: // Собрали метку, переходим к ожиданию кода
            return CodeWaiting;

        case CommentSeparator: // Встретили комментарий, значит собрали код.
            cmdData.code = cmdData.label;
            cmdData.label.clear();
            return Comment; // Переходим к сбору комментария

        case LineEnd: // Встретили конец строки, значит собрали код
            cmdData.code = cmdData.label;
            cmdData.label.clear();
            return End;
    }

    throwTranslationException(CompillerError::Unknown);
    return End;
}

AssemblerParser::State AssemblerParser::handleCodeWaiting(char symbol, CommandData &cmdData) const
{
    SymbolType symbolType = getSymbolType(symbol);

    switch(symbolType)
    {
        case Unknown: // Встретили символ, который не может содержаться в коде
        case Colon:
        case Digit:
            throwTranslationException(CompillerError::IncorrectSymbol);

        case LineEnd: // Встретили конец строки. На строке была только метка
            return End;

        case Alpha: // Встретили начало кода
        case Underline:
            cmdData.code = symbol; // Начинаем собирать код
            return Code;

        case CommentSeparator: // Встретили комментарий. После метки стоял комментарий
            return Comment; // Переходим к сбору комментария

        case Space: // Пропускаем пробелы
            return m_currentState;
    }

    throwTranslationException(CompillerError::Unknown);
    return End;
}

AssemblerParser::State AssemblerParser::handleCode(char symbol, CommandData &cmdData) const
{
    SymbolType symbolType = getSymbolType(symbol);

    switch(symbolType)
    {
        case Unknown: // Встретили символ, который не может содержаться в коде
        case Colon:
            throwTranslationException(CompillerError::IncorrectSymbol);

        case LineEnd: // Встретили конец строки, собрали код
            return End;

        case Digit: // Встретили символ кода
        case Alpha:
        case Underline:
            cmdData.code += symbol; // Формируем код
            return m_currentState;

        case CommentSeparator: // Встретили комментарий
            return Comment; // Начинаем собирать комментарий

        case Space: // Встретили пробел, переходим к ожиданию аргумента
            return ArgWaiting;
    }

    throwTranslationException(CompillerError::Unknown);
    return End;
}

AssemblerParser::State AssemblerParser::handleArgWaiting(char symbol, CommandData &cmdData) const
{
    SymbolType symbolType = getSymbolType(symbol);

    switch(symbolType)
    {
        case Unknown: // Нашли непробельный символ и не ":". Переходим к сбору аргумента
        case Digit:
        case Alpha:
        case Underline:
            cmdData.arg = symbol; // Начинаем сбор
            return Arg;

        case Space: // Пропускаем пробелы
            return m_currentState;

        case Colon: // Символ ":" не может содержаться в аргументе
            throwTranslationException(CompillerError::IncorrectSymbol);

        case LineEnd: // Конец строки. Команда без аргумента
            return End;

        case CommentSeparator: // Комментарий. Команда без аргумента
            return Comment; // Переходим к сбору аргумента
    }

    throwTranslationException(CompillerError::Unknown);
    return End;
}

AssemblerParser::State AssemblerParser::handleArg(char symbol, CommandData &cmdData) const
{
    SymbolType symbolType = getSymbolType(symbol);

    switch(symbolType)
    {
        case Unknown: // Встретили символ аргумента.
        case Digit:
        case Alpha:
        case Underline:
        case Space:
            cmdData.arg += symbol; // Продолжаем сбор
            return m_currentState;

        case CommentSeparator: // Встретили комментарий. Закончили сбор аргумента
            return Comment; // Переходм к сбору комментария

        case Colon: // Встретили недопустимый для аргумента символ ":".
            throwTranslationException(CompillerError::IncorrectSymbol);

        case LineEnd: // Встретили конец строки. Закончили сбор аргмента
            return End;
    }

    throwTranslationException(CompillerError::Unknown);
    return End;
}

AssemblerParser::State AssemblerParser::handleComment(char symbol, CommandData &cmdData) const
{
    SymbolType symbolType = getSymbolType(symbol);

    switch(symbolType)
    {
        case Unknown: // Любой символ подходит для комментария
        case Space: // Кроме символа перехода к следующей строке
        case Colon:
        case CommentSeparator:
        case Digit:
        case Alpha:
        case Underline:
            cmdData.comment += symbol;
            return m_currentState;

        case LineEnd: // Конец комментария
            return End;
    }

    throwTranslationException(CompillerError::Unknown);
    return End;
}

void AssemblerParser::saveErrorData(CommandData &cmdData, CompillerError errorCode) const
{
    cmdData.errors.add(cmdData, errorCode);
}

void AssemblerParser::throwTranslationException(CompillerError errorCode) const
{
    throw TranslationException(0, std::string(), errorCode);
}
