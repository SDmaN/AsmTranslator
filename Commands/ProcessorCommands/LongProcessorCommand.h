#ifndef LONGPROCESSORCOMMAND_H
#define LONGPROCESSORCOMMAND_H

#include "ProcessorCommand.h"

// Класс длинной команды процессора
class LongProcessorCommand : public ProcessorCommand
{
public:
    LongProcessorCommand(const CommandData &data, Address commandAddress, LabelContainer *labelContainer);

    virtual size_t size() const override; // Возвращает размер
    virtual void translate(VmExecutable &vmExec) override; // Транслирует в машинный код

private:
    const std::size_t LongCommandSize = 3; // Размер в байтах

    void checkArgCorrectness() const; // Проверяет аргумент на правильность
    Address getArgAddress() const; // Возвращает адрес метки. Если метка указывает на константу, выбрасывает ArgumentIncorrect
};

#endif //LONGPROCESSORCOMMAND_H
