#ifndef COMMANDSCREATOR_H
#define COMMANDSCREATOR_H

#include <map>

#include "../Command.h"
#include "CommandFactory.h"
#include "../ProcessorCommands/ShortProcessorCommand.h"
#include "../ProcessorCommands/LongProcessorCommand.h"

// Класс создателя команд (обращается к фабрикам)
class CommandsCreator
{
public:
    // Создает команду
    CommandPointer create(const CommandData &cmdData, LabelContainer *labelContainer, ErrorContainer *errorContainer) const;

private:
    static CommandFactory<ShortProcessorCommand> m_shortProcessorCommandFactory; // Фабрика коротких команд
    static CommandFactory<LongProcessorCommand> m_longProcessorCommandFactory; // Фабрика длинных команд
    static std::map<std::string, CommandFactoryBase *> m_commandFactories; // Код-фабрика
};

#endif //COMMANDSCREATOR_H
