#ifndef SHORTPROCESSORCOMMAND_H
#define SHORTPROCESSORCOMMAND_H

#include "ProcessorCommand.h"

// Короткая команда процессора
class ShortProcessorCommand : public ProcessorCommand
{
public:
    ShortProcessorCommand(const CommandData &data, LabelContainer *labelContainer, ErrorContainer *errorContainer,
                          Listing *listing);

    virtual size_t size() const override; // Возвращает размер

protected:
    virtual ByteArray writeExecutable(VmExecutable &vmExec, Address) override; // Транлирует в машинный код

private:
    const std::size_t ShortCommandSize = 1; // Размер в байтах
};

#endif //SHORTPROCESSORCOMMAND_H
