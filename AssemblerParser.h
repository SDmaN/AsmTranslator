#ifndef ASSEMBLERPARSER_H
#define ASSEMBLERPARSER_H

#include <vector>
#include <functional>

#include "Commands/CommandData.h"
#include "ErrorsHandling/CompillerError.h"

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
        Start = 0,
        Id,
        IdEnding,
        CodeWaiting,
        Code,
        ArgWaiting,
        Arg,
        Comment,
        End
    };

    // Типы символа
    enum SymbolType
    {
        Unknown,
        Space,
        Colon,
        CommentSeparator,
        Digit,
        Alpha,
        Underline,
        LineEnd
    };

    // Тип функции-обработчика состояния
    typedef std::function<State(char,CommandData&,bool*)> StateHandler;

    const std::size_t StatesCount = 9; // Количество состояний
    std::vector<StateHandler> m_stateHandlers; // Обработчики состояний

    std::size_t m_currentLineIndex; // Номер разбираемой строки
    std::size_t m_currentSymbolIndex; // Индекс разбираемого символа в строке
    State m_currentState; // Текущее состояние

    void initHandlers(); // Инициализирует функции-обработчики
    CommandData parseLine(const std::string &line, bool *hasError); // Парсит исходную строку

    SymbolType getSymbolType(char symbol) const; // Возвращает тип символа

    // Функции-обработчики состояний
    State handleStart(char symbol, CommandData &cmdData, bool *hasError) const;
    State handleId(char symbol, CommandData &cmdData, bool *hasError) const;
    State handleIdEnding(char symbol, CommandData &cmdData, bool *hasError) const;
    State handleCodeWaiting(char symbol, CommandData &cmdData, bool *hasError) const;
    State handleCode(char symbol, CommandData &cmdData, bool *hasError) const;
    State handleArgWaiting(char symbol, CommandData &cmdData, bool *hasError) const;
    State handleArg(char symbol, CommandData &cmdData, bool *hasError) const;
    State handleComment(char symbol, CommandData &cmdData, bool *hasError) const;

    // Сохраняет информацию об ошибке в операторе (код ошибки, номер ошибочного символа)
    void saveErrorData(CommandData &cmdData, CompillerError errorCode) const;
};

#endif //ASSEMBLERPARSER_H
