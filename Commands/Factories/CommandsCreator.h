#ifndef COMMANDSCREATOR_H
#define COMMANDSCREATOR_H

#include "../Command.h"

// Класс создателя команд (обращается к фабрикам)
class CommandsCreator
{
public:
    CommandPointer create(const CommandData &cmdData, LabelContainer *labelContainer, ErrorContainer *errorContainer) const;

private:
};

#endif //COMMANDSCREATOR_H
