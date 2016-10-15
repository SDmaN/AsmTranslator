#include "UnknownCommand.h"

UnknownCommand::UnknownCommand(const CommandData &data, Address commandAddress, LabelContainer *labelContainer)
        : Command(data, commandAddress, labelContainer),
          m_labelCommand(data, commandAddress, labelContainer)
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
