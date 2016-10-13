#ifndef ALLOCATECOMMAND_H
#define ALLOCATECOMMAND_H

#include <regex>
#include <iterator>
#include <cstdlib>

#include "../Command.h"
#include "../../Utils/Utils.h"

// Директива для выделения памяти
// AllocatingItemType - тип элемента выделения памяти
template<typename AllocatingItemType>
class AllocateCommand : public Command
{
public:
    AllocateCommand(const CommandData &data, LabelContainer *labelContainer, ErrorContainer *errorContainer)
            : Command(data, labelContainer, errorContainer), m_commandSize(0), m_allocatingItemsCount(0)
    {
        parseArg(data.arg);
    }

    // Возвращает размер выделенной области
    virtual size_t size() const override
    {
        return m_commandSize;
    }

    // Транслирует выделенную область в массив байт
    // Если выделяется массив, то он заполняется нулями
    virtual void translate(VmExecutable &vmExec, Address commandAddress) override
    {
        switch(m_argType)
        {
            case ArgType::Array:
                translateArray(vmExec);
                break;

            case ArgType::Sequence:
                parseSequence(vmExec);
                break;

            default:
                break;
        }
    }

private:
    // Тип аргумента
    enum ArgType
    {
        Unknown, // Неизвестен (ошибка)
        Empty, // Пуст (ошибка)
        Array, // Массив
        Sequence // Последовательность
    };

    const std::string m_arraySizePattern = "\\d+"; // Паттерн для поиска целых положительных чисел или нуля
    const std::string m_arrayCorrectnessPattern = "\\s*\\[\\s*\\d+\\s*\\]\\s*"; // Паттерн проверки на массив

    std::size_t m_commandSize; // Размер выделяемой памяти
    std::size_t m_allocatingItemsCount = 0; // Количество выделяемых элементов
    std::vector<AllocatingItemType> m_allocatingItems; // Выделяемые элементы (используется только для последовательности)
    ArgType m_argType; // Тип аргумента

    // Парсит аргумент, вычисляя го тип
    void parseArg(const std::string &arg)
    {
        m_argType = getArgType(arg);

        switch(m_argType)
        {
            case ArgType::Unknown:
                handleError(CompillerError::ArgumentIncorrect);
                return;

            case ArgType::Empty:
                handleError(CompillerError::TooFewArguments);
                return;

            case ArgType::Array:
                parseArray(arg);
                break;

            case ArgType::Sequence:
                parseSequence(arg);
                break;
        }
    }

    // Возвращает тип аргумента
    ArgType getArgType(const std::string &arg)
    {
        if(arg.empty())
            return ArgType::Empty;

        if(checkArray(arg))
            return ArgType::Array;

        if(checkSequence(arg))
            return ArgType::Sequence;

        return ArgType::Unknown;
    }

    // Проверяет аргумент на массив
    bool checkArray(const std::string &arg)
    {
        std::regex arrayRegex(m_arrayCorrectnessPattern);
        return std::regex_match(arg, arrayRegex);
    }

    // Проверяет аргумент на последовательность
    bool checkSequence(const std::string &arg)
    {
        std::string np = numberPattern();
        std::string sequencePattern = "\\s*" + np + "\\s*(\\,\\s*" + np + ")*\\s*";
        std::regex sequenceRegex(sequencePattern);

        return std::regex_match(arg, sequenceRegex);
    }

    // Возвращает паттерн для элемента последовательности (для Float - отдельный)
    std::string numberPattern() const
    {
        return "[+-]?\\d+";
    }

    // Парсит аргумент как массив
    void parseArray(const std::string &arg)
    {
        std::regex arraySizeRegex(m_arraySizePattern);
        std::smatch match;

        if(std::regex_search(arg, match, arraySizeRegex))
        {
            m_allocatingItemsCount = std::atoi(match.begin()->str().c_str());
            m_commandSize = m_allocatingItemsCount * sizeof(AllocatingItemType);
        }
    }

    // Парсит аргумент как последовательность
    void parseSequence(std::string arg)
    {
        std::regex numberRegex(numberPattern());
        std::smatch match;

        while(std::regex_search(arg, match, numberRegex))
        {
            m_allocatingItems.push_back(std::atof(match.begin()->str().c_str()));
            arg = match.suffix();
        }
    }

    // Транслирует аргумент как массив
    void translateArray(VmExecutable &vmExec)
    {
        vmExec.appendZeroBytes(m_commandSize);
    }

    // Транслирует аргумент как последовательность
    void parseSequence(VmExecutable &vmExec)
    {
        for(auto &item : m_allocatingItems)
            vmExec.appendBytes(toBytes(item));
    }
};

// Специализация для Float
template<>
std::string AllocateCommand<float>::numberPattern() const
{
    return "[-+]?\\d*\\.?\\d+([eE][-+]?\\d+)?";
}

#endif //ALLOCATECOMMAND_H