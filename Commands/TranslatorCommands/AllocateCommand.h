#ifndef ALLOCATECOMMAND_H
#define ALLOCATECOMMAND_H

#include <regex>
#include <iterator>

#include "../Command.h"
#include "../../Utils/Utils.h"

// Директива для выделения памяти
// AllocatingItemType - тип элемента выделения памяти
template<typename AllocatingItemType>
class AllocateCommand : public Command
{
public:
    AllocateCommand(const CommandData &data, Address commandAddress, LabelContainer *labelContainer)
            : Command(data, commandAddress, labelContainer)
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
    virtual void translate(VmExecutable &vmExec) override
    {
        if(hasError())
            return;

        ByteArray result;

        switch(m_argType)
        {
            case ArgType::Array:
                result = translateArray();
                break;

            case ArgType::Sequence:
                result = translateSequence();
                break;

            default:
                break;
        }

        vmExec.appendBytes(result);
        setTranslatedBytes(result);
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

        // Проверяем тип аргумента
        switch(m_argType)
        {
            case ArgType::Unknown: // Неизвестный - сохраняем ошибку
                handleError(CompillerError::ArgumentIncorrect);
                return;

            case ArgType::Empty: // Пустой - сохраняем ошибку
                handleError(CompillerError::TooFewArguments);
                return;

            case ArgType::Array: // В виде массива ([n])
                parseArray(arg); // Парсим как массив
                break;

            case ArgType::Sequence: // Последовательность (a, b, c, ...)
                parseSequence(arg); // Парсим как последовательность
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
        std::string np = numberPattern(); // Получаем образец для числа (для целого и дробного разные)
        std::string sequencePattern = "\\s*" + np + "\\s*(\\,\\s*" + np + ")*\\s*"; // Паттерн для последовательности
        std::regex sequenceRegex(sequencePattern);

        return std::regex_match(arg, sequenceRegex);
    }

    // Возвращает паттерн для элемента последовательности (для Float - отдельный)
    inline std::string numberPattern() const
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
            m_allocatingItemsCount = static_cast<std::size_t>(std::stof(match.begin()->str().c_str()));
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
            m_allocatingItems.push_back(static_cast<AllocatingItemType>(std::stof(match.begin()->str().c_str())));
            arg = match.suffix();
        }

        m_allocatingItemsCount = m_allocatingItems.size();
        m_commandSize = m_allocatingItemsCount * sizeof(AllocatingItemType);
    }

    // Транслирует аргумент как массив
    ByteArray translateArray()
    {
        ByteArray result(m_commandSize, 0);
        return result;
    }

    // Транслирует аргумент как последовательность
    ByteArray translateSequence()
    {
        ByteArray result;

        for(auto &item : m_allocatingItems)
        {
            ByteArray itemArray = toBytes(item);
            result.insert(std::end(result), std::begin(itemArray), std::end(itemArray));
        }

        return result;
    }
};

// Специализация для Float
template<>
inline std::string AllocateCommand<float>::numberPattern() const
{
    return "[-+]?\\d*\\.?\\d+([eE][-+]?\\d+)?";
}

#endif //ALLOCATECOMMAND_H