#ifndef COMMANDSCREATOR_H
#define COMMANDSCREATOR_H

#include <map>

#include "../../TypeDefines.h"
#include "../Command.h"
#include "CommandFactory.h"
#include "../ProcessorCommands/ShortProcessorCommand.h"
#include "../ProcessorCommands/LongProcessorCommand.h"
#include "../TranslatorCommands/AllocateCommand.h"
#include "../TranslatorCommands/EndCommand.h"
#include "../UnknownCommand.h"
#include "../LabelCommand.h"
#include "../EmptyCommand.h"

// Класс создателя команд (обращается к фабрикам)
class CommandsCreator
{
public:
    // Создает команду
    CommandPointer create(const CommandData &cmdData, Address commandAddress, LabelContainer *labelContainer) const;

private:
    static CommandFactory<ShortProcessorCommand> m_shortProcessorCommandFactory; // Фабрика коротких команд
    static CommandFactory<LongProcessorCommand> m_longProcessorCommandFactory; // Фабрика длинных команд
    static CommandFactory<AllocateCommand<Dword>> m_dwAllocateCommandFactory; // Фабрика для директив выделения целых
    static CommandFactory<AllocateCommand<Float>> m_fltAllocateCommandFactory; // Фабрика для директив выделения дробных
    static CommandFactory<EndCommand> m_endCommandFactory; // Фабрика для End
    static CommandFactory<UnknownCommand> m_unknownCommandFactory; // Фабрика для ошибочных
    static CommandFactory<LabelCommand> m_labelCommandFactory; // Фабрика для команд лейблов
    static CommandFactory<EmptyCommand> m_emptyCommandFactory; // Фабрика для пустых команд (комментариев)
    static std::map<std::string, CommandFactoryBase *> m_commandFactories; // Код-фабрика
};

#endif //COMMANDSCREATOR_H
