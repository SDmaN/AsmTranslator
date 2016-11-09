#ifndef ASSEMBLERPARSER_H
#define ASSEMBLERPARSER_H

#include <vector>
#include <functional>

#include "Commands/CommandData.h"
#include "ErrorsHandling/CompillerError.h"

/*
 * Парсер основного текста программы
 * Разбивает на:
 * метку
 * код операции
 * аргументы
 *
 * Аргументы записываются как обычная срока.
 * Свои аргументы каждая команда разбирает сама.
 */
class AssemblerParser
{
public:
    explicit AssemblerParser();

    std::vector<CommandData> parse(std::istream &stream, bool *hasErrors = nullptr); // Парсит исходный текст из потока
    std::vector<CommandData> parse(const std::string &fileName, bool *hasErrors = nullptr); // Парсит исходный текст из файла

private:
    // Состояния
    enum State
    {
        Start = 0, // Начальное состояние
        Id, // Нашли метку или код команды
        IdEnding, // Метка или код закончился (тут определяется, что это было)
        CodeWaiting, // Id оказалась меткой, ждем код (пропускаем пробелы)
        Code, // Собираем код
        ArgWaiting, // Ждем аргументы (пропускаем пробелы)
        Arg, // Собираем аргумент
        Comment, // Собираем комментарий
        End // Конечное состояние
    };

    // Типы символа
    enum SymbolType
    {
        Unknown, // Неизвестный
        Space, // Пробел или табуляция
        Colon, // Двоеточие
        CommentSeparator, // Символ комментария ';'
        Digit, // Цифра
        Alpha, // Буква
        Underline, // Нижнее подчеркивание
        LineEnd // Конец строки
    };

    // Тип функции-обработчика состояния
    typedef std::function<State(char,CommandData&)> StateHandler;

    const std::size_t StatesCount = 9; // Количество состояний
    std::vector<StateHandler> m_stateHandlers; // Обработчики состояний

    std::size_t m_currentLineIndex; // Номер разбираемой строки
    std::size_t m_currentSymbolIndex; // Индекс разбираемого символа в строке
    State m_currentState; // Текущее состояние

    void initHandlers(); // Инициализирует функции-обработчики
    void parseLine(const std::string &line, CommandData &cmdData); // Парсит исходную строку

    SymbolType getSymbolType(char symbol) const; // Возвращает тип символа

    // Функции-обработчики состояний
    AssemblerParser::State handleStart(char symbol, CommandData &cmdData) const;
    AssemblerParser::State handleId(char symbol, CommandData &cmdData) const;
    AssemblerParser::State handleIdEnding(char symbol, CommandData &cmdData) const;
    AssemblerParser::State handleCodeWaiting(char symbol, CommandData &cmdData) const;
    AssemblerParser::State handleCode(char symbol, CommandData &cmdData) const;
    AssemblerParser::State handleArgWaiting(char symbol, CommandData &cmdData) const;
    AssemblerParser::State handleArg(char symbol, CommandData &cmdData) const;
    AssemblerParser::State handleComment(char symbol, CommandData &cmdData) const;

    // Сохраняет информацию об ошибке в операторе (код ошибки, номер ошибочного символа)
    void saveErrorData(CommandData &cmdData, CompillerError errorCode) const;

    // Выбрасывает исключение с ошибкой
    void throwTranslationException(CompillerError errorCode) const;
};

#endif //ASSEMBLERPARSER_H
