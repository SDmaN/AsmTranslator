#include <regex>
#include <algorithm>

#include "LongProcessorCommand.h"
#include "../LabelContainer.h"
#include "../../ErrorsHandling/Exceptions/ArgumentIncorrectException.h"
#include "../../ErrorsHandling/Exceptions/LabelNotExistsException.h"
#include "../../Utils/Utils.h"

LongProcessorCommand::LongProcessorCommand(const CommandData &data, Address commandAddress, LabelContainer *labelContainer)
        : ProcessorCommand(data, commandAddress, labelContainer)
{
}

size_t LongProcessorCommand::size() const
{
    return LongCommandSize;
}

void LongProcessorCommand::translate(VmExecutable &vmExec)
{
    ByteArray result; // Результат трансляции

    // Если нет ошибок
    if(!hasError())
    {
        try
        {
            checkArgCorrectness(); // Проверили корректность аргумента. Есть вариант перехватить исключение
            Address argAddres = getArgAddress(); // Получили адрес. Есть вариант перехватить исключение
            ByteArray addressBytes = toBytes(argAddres); // Байты адреса

            result.reserve(LongCommandSize);
            result.push_back(static_cast<Byte>(code())); // Байт кода операции
            result.insert(std::end(result), std::begin(addressBytes), std::end(addressBytes)); // Дописываем 2 байта адреса

            vmExec.appendBytes(result); // Дописали байта к executable
            vmExec.appendRelativeAddress(address() + sizeof(code())); // Занесли адрес в таблицу
        }
        catch(ArgumentIncorrectException &ex) // Некорректность аргумента
        {
            handleError(CompillerError::ArgumentIncorrect);
        }
        catch(LabelNotExistsException &ex) // Не найдена метка, переданная в аргумент
        {
            handleError(CompillerError::LabelNotFound);
        }
    }

    setTranslatedBytes(result);
}

void LongProcessorCommand::checkArgCorrectness() const
{
    const std::regex regEx("[a-zA-Z_]\\w+\\s*"); // Образец для аргумента

    // Если аргумент не подходит по образцу, бросаем исключение
    if(!std::regex_match(data().arg, regEx))
        throw ArgumentIncorrectException(data().arg);
}

Address LongProcessorCommand::getArgAddress() const
{
    std::string arg = data().arg;
    removeSpaces(arg); // Удаляем пробелы из строки

    // Если метка указывает на адрес, выбрасываем ArgumentIncorrect
    // Если в данном месте, метка не будет найдена, будет выброшено LabelNotExists
    if(labelContainer()->labelPurpose(arg) != LabelData::AddressConstant)
        throw ArgumentIncorrectException(arg);

    // Если метку нашли и она указывает на адрес, то возвращаем адрес
    return labelContainer()->address(arg);
}
