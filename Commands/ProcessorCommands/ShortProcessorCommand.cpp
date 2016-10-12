#include "ShortProcessorCommand.h"

ShortProcessorCommand::ShortProcessorCommand(const CommandData &data, LabelContainer *labelContainer, ErrorContainer *errorContainer)
        : ProcessorCommand(data, labelContainer, errorContainer)
{
}

size_t ShortProcessorCommand::size() const
{
    return ShortCommandSize;
}

void ShortProcessorCommand::translate(VmExecutable &vmExec)
{
    if(!hasError())
        vmExec.appendProgramByte(static_cast<Byte>(code()));
}
