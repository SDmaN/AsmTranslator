#ifndef COMMANDFACTORY_H
#define COMMANDFACTORY_H

#include "../Command.h"

// Базовый класс для фабрик команд
class CommandFactoryBase
{
public:
    virtual CommandPointer
    create(const CommandData &cmdData, Address commandAddress, LabelContainer *labelContainer) const = 0; // Создает команду
};

// Шаблон класса фабрики для конкретной команды
template<typename CommandType> // CommandType - тип создаваемой команды
class CommandFactory : public CommandFactoryBase
{
public:
    virtual CommandPointer
    create(const CommandData &cmdData, Address commandAddress, LabelContainer *labelContainer) const override // Создает конкретную команду
    {
        CommandPointer result(new CommandType(cmdData, commandAddress, labelContainer));
        return result;
    }
};

#endif //COMMANDFACTORY_H
