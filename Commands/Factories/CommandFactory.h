#ifndef COMMANDFACTORY_H
#define COMMANDFACTORY_H

#include "../Command.h"

// Базовый класс для фабрик команд
class CommandFactoryBase
{
public:
    virtual CommandPointer
    create(const CommandData &cmdData, LabelContainer *labelContainer, ErrorContainer *errorContainer, Listing *listing) const = 0; // Создает команду
};

// Шаблон класса фабрики для конкретной команды
template<typename CommandType> // CommandType - тип создаваемой команды
class CommandFactory : public CommandFactoryBase
{
public:
    virtual CommandPointer
    create(const CommandData &cmdData, LabelContainer *labelContainer, ErrorContainer *errorContainer, Listing *listing) const override // Создает конкретную команду
    {
        CommandPointer result(new CommandType(cmdData, labelContainer, errorContainer, listing));
        return result;
    }
};

#endif //COMMANDFACTORY_H
