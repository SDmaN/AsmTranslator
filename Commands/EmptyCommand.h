#ifndef EMPTYCOMMAND_H
#define EMPTYCOMMAND_H

#include "Command.h"

// Пустая команда. Не транслируется. Используется для формирования листинга
class EmptyCommand : public Command
{
public:
    EmptyCommand(const CommandData &data, Address commandAddress, LabelContainer *labelContainer);

    virtual size_t size() const override;
    virtual void translate(VmExecutable &vmExec) override;
};

#endif //EMPTYCOMMAND_H
