#ifndef EQUCOMMAND_H
#define EQUCOMMAND_H

#include "../Command.h"

// Представляет собой директиву Equ
class EquCommand : public Command
{
public:
    EquCommand(const CommandData &data, Address commandAddress, LabelContainer *labelContainer);

    virtual size_t size() const override; // Возвращает нулевой размер
    virtual void translate(VmExecutable &vmExec) override; // Не транслирует

private:
    const std::size_t EquSize = 0; // Размер команды
    void updateLabelPurpose(); // Обновляет назначение метки на Constant
};

#endif // EQUCOMMAND_H
