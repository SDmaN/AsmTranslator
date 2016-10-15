#include "EmptyCommand.h"

EmptyCommand::EmptyCommand(const CommandData &data, Address commandAddress, LabelContainer *labelContainer)
        : Command(data, commandAddress, labelContainer)
{
}

size_t EmptyCommand::size() const
{
    return 0;
}

void EmptyCommand::translate(VmExecutable &vmExec)
{
}
