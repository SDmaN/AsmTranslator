#ifndef COMMANDSCREATOR_H
#define COMMANDSCREATOR_H

#include "../Command.h"

class CommandsCreator
{
public:
    CommandPointer create(const CommandData &cmdData, Address address, LabelContainer *labelContainer,
                          ErrorContainer *errorContainer) const;

private:
};

#endif //COMMANDSCREATOR_H
