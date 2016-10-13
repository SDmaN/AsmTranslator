#include <regex>

#include "LongProcessorCommand.h"
#include "../LabelContainer.h"
#include "../../Utils/Utils.h"

LongProcessorCommand::LongProcessorCommand(const CommandData &data, LabelContainer *labelContainer,
                                           ErrorContainer *errorContainer, Listing *listing)
        : ProcessorCommand(data, labelContainer, errorContainer, listing)
{
}

size_t LongProcessorCommand::size() const
{
    return LongCommandSize;
}

ByteArray LongProcessorCommand::writeExecutable(VmExecutable &vmExec, Address commandAddress)
{
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

            ByteArray result(LongCommandSize);
            result.push_back(static_cast<Byte>(code())); // Байт кода операции
            result.insert(std::end(result), std::begin(addressBytes), std::end(addressBytes)); // Дописываем 2 байта адреса

            vmExec.appendBytes(result);
            vmExec.appendRelativeAddress(commandAddress + sizeof(code())); // Адрес аргумента сразу после кода

            return result;
        }
    }

    return ByteArray();
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
