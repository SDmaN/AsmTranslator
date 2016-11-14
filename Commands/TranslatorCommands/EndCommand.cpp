#include <regex>
#include "EndCommand.h"
#include "../LabelContainer.h"
#include "../../ErrorsHandling/Exceptions/ArgumentIncorrectException.h"
#include "../../ErrorsHandling/Exceptions/LabelNotExistsException.h"
#include "../../Utils/Utils.h"

EndCommand::EndCommand(const CommandData &data, Address commandAddress, LabelContainer *labelContainer)
        : Command(data, commandAddress, labelContainer)
{
    parseArg();
}

size_t EndCommand::size() const
{
    return EndComandSize;
}

void EndCommand::translate(VmExecutable &vmExec)
{
    // Если нет ошибок, устанавливаем ip
    if(!hasError())
        vmExec.setIp(m_ip); // Директива устанавливает ip

    // Результат трансляции - пустой
    setTranslatedBytes(ByteArray());
}

void EndCommand::parseArg()
{
    // Если не было ошибки
    if(!hasError())
    {
        try
        {
            checkArgCorrectness(); // Проверили корректность аргумента. Есть вариант перехватить исключение
            Address argAddres = getArgAddress(); // Получили адрес. Есть вариант перехватить исключение
            m_ip = argAddres; // Сохранили ip
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
}

void EndCommand::checkArgCorrectness() const
{
    const std::regex regEx("[a-zA-Z_]\\w+\\s*"); // Образец для аргумента

    // Если аргумент не подходит по образцу, бросаем исключение
    if(!std::regex_match(data().arg, regEx))
        throw ArgumentIncorrectException(data().arg);
}

Address EndCommand::getArgAddress() const
{
    std::string arg = data().arg;
    removeSpaces(arg); // Удаляем пробелы

    // Если метка указывает на адрес, выбрасываем ArgumentIncorrect
    // Если в данном месте, метка не будет найдена, будет выброшено LabelNotExists
    if(labelContainer()->labelPurpose(arg) != LabelData::AddressConstant)
        throw ArgumentIncorrectException(arg);

    // Если метку нашли и она указывает на адрес, то возвращаем адрес
    return labelContainer()->address(arg);
}
