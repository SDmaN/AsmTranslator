#ifndef SHORTPROCESSORCOMMAND_H
#define SHORTPROCESSORCOMMAND_H

#include "ProcessorCommand.h"

// Короткая команда процессора (1 байт)
class ShortProcessorCommand : public ProcessorCommand
{
public:
    ShortProcessorCommand(const CommandData &data, Address commandAddress, LabelContainer *labelContainer);

    virtual size_t size() const override; // Возвращает размер
    virtual void translate(VmExecutable &vmExec) override; // Транслирует в машинный код

private:
    const std::size_t ShortCommandSize = 1; // Размер в байтах
};

#endif //SHORTPROCESSORCOMMAND_H
