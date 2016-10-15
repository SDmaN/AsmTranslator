#ifndef LABELCOMMAND_H
#define LABELCOMMAND_H

#include "Command.h"

class LabelCommand : public Command
{
public:
    LabelCommand(const CommandData &data, Address commandAddress, LabelContainer *labelContainer);

    virtual size_t size() const override;
    virtual void translate(VmExecutable &vmExec) override;

private:
    const std::size_t LabelCommandSize = 0;

    void addLabel(const CommandData &data);

};

#endif //LABELCOMMAND_H
