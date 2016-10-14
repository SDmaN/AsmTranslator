#ifndef LONGPROCESSORCOMMAND_H
#define LONGPROCESSORCOMMAND_H

#include "ProcessorCommand.h"
#include "../LabelCommand.h"

// Класс длинной команды процессора
class LongProcessorCommand : public ProcessorCommand
{
public:
    LongProcessorCommand(const CommandData &data, Address commandAddress, LabelContainer *labelContainer,
                             ErrorContainer *errorContainer);

    virtual size_t size() const override; // Возвращает размер
    virtual void translate(VmExecutable &vmExec) override; // Транслирует в машинный код

private:
    const std::size_t LongCommandSize = 3; // Размер в байтах
    LabelCommand m_labelCommand;

    bool checkArgCorrectness() const; // Проверяет аргумент на правильность
    bool labelExists() const; // Проверяет, существует ли метка (из аргумента)
    Address getArgAddress() const; // Возвращает адрес метки
};

#endif //LONGPROCESSORCOMMAND_H
