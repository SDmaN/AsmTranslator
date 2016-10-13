#ifndef LONGPROCESSORCOMMAND_H
#define LONGPROCESSORCOMMAND_H

#include "ProcessorCommand.h"

// Класс длинной команды процессора
class LongProcessorCommand : public ProcessorCommand
{
public:
    LongProcessorCommand(const CommandData &data, LabelContainer *labelContainer, ErrorContainer *errorContainer,
                         Listing *listing);

    virtual size_t size() const override; // Возвращает размер

protected:
    virtual ByteArray writeExecutable(VmExecutable &vmExec, Address commandAddress) override; // Транслирует в машинный код

private:
    const std::size_t LongCommandSize = 3; // Размер в байтах

    bool checkArgCorrectness() const; // Проверяет аргумент на правильность
    bool labelExists() const; // Проверяет, существует ли метка (из аргумента)
    Address getArgAddress() const; // Возвращает адрес метки
};

#endif //LONGPROCESSORCOMMAND_H
