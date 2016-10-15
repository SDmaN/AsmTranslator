#include "EmptyCommand.h"

EmptyCommand::EmptyCommand(const CommandData &data, Address commandAddress, LabelContainer *labelContainer,
                           ErrorContainer *errorContainer)
        : Command(data, commandAddress, labelContainer, errorContainer)
{
}

size_t EmptyCommand::size() const
{
    return 0;
}

void EmptyCommand::translate(VmExecutable &vmExec)
{
}
