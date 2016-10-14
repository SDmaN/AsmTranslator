#include "UnknownCommand.h"

UnknownCommand::UnknownCommand(const CommandData &data, Address commandAddress, LabelContainer *labelContainer,
                               ErrorContainer *errorContainer)
        : Command(data, commandAddress, labelContainer, errorContainer),
          m_labelCommand(data, commandAddress, labelContainer, errorContainer)
{
}

size_t UnknownCommand::size() const
{
    return UnknownCommandSize;
}

void UnknownCommand::translate(VmExecutable &vmExec)
{
    m_labelCommand.translate(vmExec);
    handleError(CompillerError::CommandNotFound);
    setTranslatedBytes(ByteArray());
}
