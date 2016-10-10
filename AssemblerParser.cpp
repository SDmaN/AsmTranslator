#include <fstream>

#include "AssemblerParser.h"
#include "ErrorsHandling/ErrorContainer.h"
#include "ErrorsHandling/Exceptions/FileNotFoundException.h"

const std::string FileNotFoundMessage = "Файл не найден";

AssemblerParser::AssemblerParser(ErrorContainer *errorContainer)
        : m_errorContainer(errorContainer)
{
    initHandlers();
}

std::vector<CommandData> AssemblerParser::parse(std::istream &stream, bool &hasErrors)
{
    std::vector<CommandData> result;
    std::string line;
    m_currentLineIndex = 0;

    do
    {
        std::getline(stream, line);

        if(!line.empty())
        {
            CommandData cmdData = parseLine(line, hasErrors);
            cmdData.lineIndex = m_currentLineIndex;
            cmdData.sourceLine = line;

            if(!(cmdData.code.empty() && cmdData.label.empty() && cmdData.comment.empty() && hasErrors))
                result.push_back(cmdData);

            ++m_currentLineIndex;
        }

    } while(!line.empty());

    return result;
}

std::vector<CommandData> AssemblerParser::parse(const std::string &fileName, bool &hasErrors)
{
    std::fstream sourceFile(fileName);

    if(sourceFile.is_open())
        return parse(sourceFile, hasErrors);

    hasErrors = true;
    throw FileNotFoundException(FileNotFoundMessage);
}

void AssemblerParser::initHandlers()
{
    m_stateHandlers.resize(StatesCount);

    m_stateHandlers[Start] = std::bind(handleStart, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    m_stateHandlers[Id] = std::bind(handleId, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    m_stateHandlers[IdEnding] = std::bind(handleIdEnding, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    m_stateHandlers[Code] = std::bind(handleCode, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    m_stateHandlers[CodeWaiting] = std::bind(handleCodeWaiting, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    m_stateHandlers[ArgWaiting] = std::bind(handleArgWaiting, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    m_stateHandlers[Arg] = std::bind(handleArg, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    m_stateHandlers[Comment] = std::bind(handleComment, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
}

CommandData AssemblerParser::parseLine(const std::string &line, bool &hasError)
{
    CommandData result;
    result.lineIndex = m_currentLineIndex;

    m_currentState = Start;
    m_currentSymbolIndex = 0;

    while(m_currentSymbolIndex < line.size() + 1 && m_currentState != End)
    {
        char symbol = line[m_currentSymbolIndex];
        m_currentState = m_stateHandlers[m_currentState](symbol, result, hasError);

        ++m_currentSymbolIndex;
    }

    return result;
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

AssemblerParser::State AssemblerParser::handleStart(char symbol, CommandData &opData, bool &hasError) const
{
    SymbolType symbolType = getSymbolType(symbol);

    switch(symbolType)
    {
        case Unknown: // Первый символ неверен
        case Colon:
        case Digit:
            hasError = true;
            saveErrorData(opData, CompillerError::IncorrectSymbol);
            return End;

        case CommentSeparator: // Строка начинается с комментария. Переходим к сбору комментария
            return Comment;

        case LineEnd: // Строка пуста
            return End;

        case Space: // Пропускаем пробелы
            return m_currentState;

        case Alpha: // Нашли метку или код оерации
        case Underline:
            opData.label = symbol; // Начинаем формировать метку
            return Id;
    }

    hasError = true;
    saveErrorData(opData, CompillerError::Unknown);
    return End;
}

AssemblerParser::State AssemblerParser::handleId(char symbol, CommandData &opData, bool &hasError) const
{
    SymbolType symbolType = getSymbolType(symbol);

    switch(symbolType)
    {
        case Alpha: // Продолжаются символы метки или кода
        case Underline:
        case Digit:
            opData.label += symbol; // Продолжаем формирование
            return m_currentState; // Остаемся сдесь же

        case Colon: // Закончилась МЕТКА
            return CodeWaiting; // Ожидаем код

        case Space: // Название идентификатора кончилось
            return IdEnding; // Переходим к состоянию, в котором можно понять, была ли метка или код

        case CommentSeparator: // Увидели комментарий, значит был код
            opData.code = opData.label;
            opData.label.clear();
            return Comment; // Переходим к сбору комментария

        case Unknown: // Встретили символ, который не может быть в названии идентификатора
            hasError = true;
            saveErrorData(opData, CompillerError::IncorrectSymbol);

        case LineEnd: // Конец строки, значит собрали код
            opData.code = opData.label;
            opData.label.clear();
            return End;
    }

    hasError = true;
    saveErrorData(opData, CompillerError::Unknown);
    return End;
}

AssemblerParser::State AssemblerParser::handleIdEnding(char symbol, CommandData &opData, bool &hasError) const
{
    SymbolType symbolType = getSymbolType(symbol);

    switch(symbolType)
    {
        case Unknown: // Встретили начало аргумента, значит собрали код
        case Digit: // Также начинаем собирать аргумент
        case Alpha:
        case Underline:
            opData.code = opData.label;
            opData.arg = symbol;
            opData.label.clear();
            return Arg;

        case Space: // Пропускаем пробелы, пока не встретим другой символ
            return m_currentState;

        case Colon: // Собрали метку, переходим к ожиданию кода
            return CodeWaiting;

        case CommentSeparator: // Встретили комментарий, значит собрали код.
            opData.code = opData.label;
            opData.label.clear();
            return Comment; // Переходим к сбору комментария

        case LineEnd: // Встретили конец строки, значит собрали код
            opData.code = opData.label;
            opData.label.clear();
            return End;
    }

    hasError = true;
    saveErrorData(opData, CompillerError::Unknown);
    return End;
}

AssemblerParser::State AssemblerParser::handleCodeWaiting(char symbol, CommandData &opData, bool &hasError) const
{
    SymbolType symbolType = getSymbolType(symbol);

    switch(symbolType)
    {
        case Unknown: // Встретили символ, который не может содержаться в коде
        case Colon:
        case Digit:
            hasError = true;
            saveErrorData(opData, CompillerError::IncorrectSymbol);

        case LineEnd: // Встретили конец строки. На строке была только метка
            return End;

        case Alpha: // Встретили начало кода
        case Underline:
            opData.code = symbol; // Начинаем собирать код
            return Code;

        case CommentSeparator: // Встретили комментарий. После метки стоял комментарий
            return Comment; // Переходим к сбору комментария

        case Space: // Пропускаем пробелы
            return m_currentState;
    }

    hasError = true;
    saveErrorData(opData, CompillerError::Unknown);
    return End;
}

AssemblerParser::State AssemblerParser::handleCode(char symbol, CommandData &opData, bool &hasError) const
{
    SymbolType symbolType = getSymbolType(symbol);

    switch(symbolType)
    {
        case Unknown: // Встретили символ, который не может содержаться в коде
        case Colon:
            hasError = true;
            saveErrorData(opData, CompillerError::IncorrectSymbol);

        case LineEnd: // Встретили конец строки, собрали код
            return End;

        case Digit: // Встретили символ кода
        case Alpha:
        case Underline:
            opData.code += symbol; // Формируем код
            return m_currentState;

        case CommentSeparator: // Встретили комментарий
            return Comment; // Начинаем собирать комментарий

        case Space: // Встретили пробел, переходим к ожиданию аргумента
            return ArgWaiting;
    }

    hasError = true;
    saveErrorData(opData, CompillerError::Unknown);
    return End;
}

AssemblerParser::State AssemblerParser::handleArgWaiting(char symbol, CommandData &opData, bool &hasError) const
{
    SymbolType symbolType = getSymbolType(symbol);

    switch(symbolType)
    {
        case Unknown: // Нашли непробельный символ и не ":". Переходим к сбору аргумента
        case Digit:
        case Alpha:
        case Underline:
            opData.arg = symbol; // Начинаем сбор
            return Arg;

        case Space: // Пропускаем пробелы
            return m_currentState;

        case Colon: // Символ ":" не может содержаться в аргументе
            hasError = true;
            saveErrorData(opData, CompillerError::IncorrectSymbol);

        case LineEnd: // Конец строки. Команда без аргумента
            return End;

        case CommentSeparator: // Комментарий. Команда без аргумента
            return Comment; // Переходим к сбору аргумента
    }

    hasError = true;
    saveErrorData(opData, CompillerError::Unknown);
    return End;
}

AssemblerParser::State AssemblerParser::handleArg(char symbol, CommandData &opData, bool &hasError) const
{
    SymbolType symbolType = getSymbolType(symbol);

    switch(symbolType)
    {
        case Unknown: // Встретили символ аргумента.
        case Digit:
        case Alpha:
        case Underline:
        case Space:
            opData.arg += symbol; // Продолжаем сбор
            return m_currentState;

        case CommentSeparator: // Встретили комментарий. Закончили сбор аргумента
            return Comment; // Переходм к сбору комментария

        case Colon: // Встретили недопустимый для аргумента символ ":".
            hasError = true;
            saveErrorData(opData, CompillerError::IncorrectSymbol);

        case LineEnd: // Встретили конец строки. Закончили сбор аргмента
            return End;
    }

    hasError = true;
    saveErrorData(opData, CompillerError::Unknown);
    return End;
}

AssemblerParser::State AssemblerParser::handleComment(char symbol, CommandData &opData, bool &hasError) const
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
            opData.comment += symbol;
            return m_currentState;

        case LineEnd: // Конец комментария
            return End;
    }

    hasError = true;
    saveErrorData(opData, CompillerError::Unknown);
    return End;
}

void AssemblerParser::saveErrorData(CommandData &opData, CompillerError error) const
{
    if(m_errorContainer != nullptr)
        m_errorContainer->add(m_currentLineIndex, opData.sourceLine, error);
}
