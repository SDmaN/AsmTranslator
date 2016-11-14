#ifndef EMPTYCOMMAND_H
#define EMPTYCOMMAND_H

#include "Command.h"

// Пустая команда. Не транслируется. Используется для формирования листинга
// Например, если в строке написана только метка
class EmptyCommand : public Command
{
public:
    EmptyCommand(const CommandData &data, Address commandAddress, LabelContainer *labelContainer);

    virtual size_t size() const override;
    virtual void translate(VmExecutable &vmExec) override;

private:
    const std::size_t EmptyCommandSize = 0; // Размер пустой команды
};

#endif //EMPTYCOMMAND_H
