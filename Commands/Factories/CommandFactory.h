#ifndef COMMANDFACTORY_H
#define COMMANDFACTORY_H

#include "../Command.h"

// Базовый класс для фабрик команд
class CommandFactoryBase
{
public:
    virtual CommandPointer create(const CommandData &cmdData, Address address, LabelContainer *labelContainer,
                                  ErrorContainer *errorContainer) const = 0; // Создает команду
};

// Шаблон класса фабрики для конкретной команды
template<typename CommandType> // CommandType - тип создаваемой команды
class CommandFactory : public CommandFactoryBase
{
public:
    virtual CommandPointer create(const CommandData &cmdData, Address address, LabelContainer *labelContainer,
                                  ErrorContainer *errorContainer) const override // Создает конкретную команду
    {
        CommandPointer result(new CommandType(cmdData, address, labelContainer, errorContainer));
        return result;
    }
};

#endif //COMMANDFACTORY_H
