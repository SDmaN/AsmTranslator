#include "LabelCommand.h"
#include "LabelContainer.h"

LabelCommand::LabelCommand(const CommandData &data, Address commandAddress, LabelContainer *labelContainer,
                           ErrorContainer *errorContainer)
        : Command(data, commandAddress, labelContainer, errorContainer)
{
    addLabel(data);
}

size_t LabelCommand::size() const
{
    return LabelCommandSize;
}

void LabelCommand::translate(VmExecutable &vmExec)
{
    setTranslatedBytes(ByteArray());
}

void LabelCommand::addLabel(const CommandData &data)
{
    if(labelContainer()->contains(data.arg))
    {
        handleError(CompillerError::LabelAlreadyDefined);
        return;
    }

    labelContainer()->add(std::make_pair(data.arg, address()));
}
