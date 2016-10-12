#include <regex>

#include "LongProcessorCommand.h"
#include "../LabelContainer.h"
#include "../../Utils/Utils.h"

LongProcessorCommand::LongProcessorCommand(const CommandData &data, LabelContainer *labelContainer,
                                           ErrorContainer *errorContainer)
        : ProcessorCommand(data, labelContainer, errorContainer)
{
}

size_t LongProcessorCommand::size() const
{
    return LongCommandSize;
}

void LongProcessorCommand::translate(VmExecutable &vmExec, Address commandAddress)
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
            ByteArray addressBytes = addressToBytes(argAddress);

            vmExec.appendProgramByte(static_cast<Byte>(code()));
            vmExec.appendProgramBytes(addressBytes);
            vmExec.appendRelativeAdress(commandAddress + sizeof(code())); // Адрес аргумента сразу после кода
        }
    }
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
