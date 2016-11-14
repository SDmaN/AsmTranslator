#include "EmptyCommand.h"

EmptyCommand::EmptyCommand(const CommandData &data, Address commandAddress, LabelContainer *labelContainer)
        : Command(data, commandAddress, labelContainer)
{
}

std::size_t EmptyCommand::size() const
{
    return EmptyCommandSize;
}

void EmptyCommand::translate(VmExecutable &vmExec)
{
    // Устанавливаем пустые байты
    setTranslatedBytes(ByteArray());
}
