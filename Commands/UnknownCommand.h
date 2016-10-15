#ifndef UNKNOWNCOMMAND_H
#define UNKNOWNCOMMAND_H

#include "Command.h"
#include "LabelCommand.h"

// Неизвестная команда (ошибка)
class UnknownCommand : public Command
{
public:
    UnknownCommand(const CommandData &data, Address commandAddress, LabelContainer *labelContainer);

    virtual size_t size() const override;
    virtual void translate(VmExecutable &vmExec) override;

private:
    const std::size_t UnknownCommandSize = 0;
    LabelCommand m_labelCommand;
};

#endif //UNKNOWNCOMMAND_H
