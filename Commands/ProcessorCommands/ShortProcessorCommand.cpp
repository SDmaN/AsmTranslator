#include "ShortProcessorCommand.h"

ShortProcessorCommand::ShortProcessorCommand(const CommandData &data, LabelContainer *labelContainer,
                                             ErrorContainer *errorContainer, Listing *listing)
        : ProcessorCommand(data, labelContainer, errorContainer, listing)
{
}

size_t ShortProcessorCommand::size() const
{
    return ShortCommandSize;
}

ByteArray ShortProcessorCommand::writeExecutable(VmExecutable &vmExec, Address)
{
    if(!hasError())
    {
        ByteArray result = { static_cast<Byte>(code()) };
        vmExec.appendBytes(result);

        return result;
    }

    return ByteArray();
}
