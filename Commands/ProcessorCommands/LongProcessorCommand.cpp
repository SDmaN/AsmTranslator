#include <regex>

#include "LongProcessorCommand.h"
#include "../LabelContainer.h"
#include "../../Utils/Utils.h"

LongProcessorCommand::LongProcessorCommand(const CommandData &data, Address commandAddress, LabelContainer *labelContainer)
        : ProcessorCommand(data, commandAddress, labelContainer),
          m_labelCommand(data, commandAddress, labelContainer)
{
}

size_t LongProcessorCommand::size() const
{
    return LongCommandSize;
}

void LongProcessorCommand::translate(VmExecutable &vmExec)
{
    m_labelCommand.translate(vmExec);
    ByteArray result;

    if(!hasError())
    {
        if(!checkArgCorrectness())
            handleError(CompillerError::ArgumentIncorrect);

        else if(!labelExists())
            handleError(CompillerError::LabelNotFound);

        else
        {
            Address argAddress = getArgAddress();
            ByteArray addressBytes = toBytes(argAddress);

            result.reserve(LongCommandSize);
            result.push_back(static_cast<Byte>(code())); // Байт кода операции
            result.insert(std::end(result), std::begin(addressBytes), std::end(addressBytes)); // Дописываем 2 байта адреса

            vmExec.appendBytes(result);
            vmExec.appendRelativeAddress(address() + sizeof(code())); // Адрес аргумента сразу после кода
        }
    }

    setTranslatedBytes(result);
}

bool LongProcessorCommand::checkArgCorrectness() const
{
    const std::regex regEx("[a-zA-Z_]\\w+");
    return std::regex_match(data().arg, regEx);
}

bool LongProcessorCommand::labelExists() const
{
    return labelContainer()->contains(data().arg);
}

Address LongProcessorCommand::getArgAddress() const
{
    return labelContainer()->address(data().arg);
}
