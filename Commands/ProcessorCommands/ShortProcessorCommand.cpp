#include "ShortProcessorCommand.h"

ShortProcessorCommand::ShortProcessorCommand(const CommandData &data, Address commandAddress, LabelContainer *labelContainer,
                                             ErrorContainer *errorContainer)
        : ProcessorCommand(data, commandAddress, labelContainer, errorContainer),
          m_labelCommand(data, commandAddress, labelContainer, errorContainer)
{
}

size_t ShortProcessorCommand::size() const
{
    return ShortCommandSize;
}

void ShortProcessorCommand::translate(VmExecutable &vmExec)
{
    m_labelCommand.translate(vmExec);
    ByteArray result;

    if(!hasError())
    {
        result = { static_cast<Byte>(code()) };
        vmExec.appendBytes(result);
    }

    setTranslatedBytes(result);
}
