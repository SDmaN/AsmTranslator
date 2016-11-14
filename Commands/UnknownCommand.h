#ifndef UNKNOWNCOMMAND_H
#define UNKNOWNCOMMAND_H

#include "Command.h"

// Неизвестная команда (ошибка)
class UnknownCommand : public Command
{
public:
    UnknownCommand(const CommandData &data, Address commandAddress, LabelContainer *labelContainer);

    virtual size_t size() const override; // Возвращает размер команды
    virtual void translate(VmExecutable &vmExec) override; // Транслирует команду в машинный код

private:
    const std::size_t UnknownCommandSize = 0; // Размер ошибочной команды
};

#endif //UNKNOWNCOMMAND_H
