#ifndef SHORTPROCESSORCOMMAND_H
#define SHORTPROCESSORCOMMAND_H

#include "ProcessorCommand.h"
#include "../LabelCommand.h"

// Короткая команда процессора
class ShortProcessorCommand : public ProcessorCommand
{
public:
    ShortProcessorCommand(const CommandData &data, Address commandAddress, LabelContainer *labelContainer,
                              ErrorContainer *errorContainer);

    virtual size_t size() const override; // Возвращает размер
    virtual void translate(VmExecutable &vmExec) override; // Транслирует в машинный код

private:
    const std::size_t ShortCommandSize = 1; // Размер в байтах
    LabelCommand m_labelCommand;
};

#endif //SHORTPROCESSORCOMMAND_H
