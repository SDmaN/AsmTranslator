#include "UnknownCommand.h"

UnknownCommand::UnknownCommand(const CommandData &data, Address commandAddress, LabelContainer *labelContainer)
        : Command(data, commandAddress, labelContainer)
{
}

size_t UnknownCommand::size() const
{
    return UnknownCommandSize;
}

void UnknownCommand::translate(VmExecutable &vmExec)
{
    handleError(CompillerError::CommandNotFound); // Сразу записываем ошибку
    setTranslatedBytes(ByteArray());
}
