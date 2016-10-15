#include "LabelCommand.h"
#include "LabelContainer.h"

LabelCommand::LabelCommand(const CommandData &data, Address commandAddress, LabelContainer *labelContainer)
        : Command(data, commandAddress, labelContainer)
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
    if(!data.label.empty())
    {
        if(labelContainer()->contains(data.label))
        {
            handleError(CompillerError::LabelAlreadyDefined);
            return;
        }

        labelContainer()->add(std::make_pair(data.label, address()));
    }
}
