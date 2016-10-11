#ifndef COMMAND_H
#define COMMAND_H

#include <memory>
#include "CommandData.h"
#include "../TypeDefines.h"

class Command;

typedef std::shared_ptr<Command> CommandPointer;

class LabelContainer;
class ErrorContainer;
class VmExecutable;

// Абстрактный класс команды процессора или ассемблера
class Command
{
public:
    Command(const CommandData &data, Address address, LabelContainer *labelContainer, ErrorContainer *errorContainer);

    virtual std::size_t size() const = 0; // Вычисляет размер команды
    virtual bool translate(VmExecutable &vmExec) = 0; // Транслирует команду в машинный код

protected:
    LabelContainer *labelContainer() const;
    ErrorContainer *errorContainer() const;

private:
    CommandData m_data; // Данные команды
    Address m_address; // Адрес команды относительно начала
    LabelContainer *m_labelContainer; // Хранилище меток
    ErrorContainer *m_errorContainer; // Хранилище ошибок
};

#endif //COMMAND_H
