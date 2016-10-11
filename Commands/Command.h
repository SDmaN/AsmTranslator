#ifndef COMMAND_H
#define COMMAND_H

#include <memory>

#include "CommandData.h"
#include "../TypeDefines.h"
#include "../VmExecutable.h"
#include "ProcessorCommandCode.h"
#include "../ErrorsHandling/CompillerError.h"

class Command;

typedef std::shared_ptr<Command> CommandPointer;

class LabelContainer;
class ErrorContainer;

// Абстрактный класс команды процессора или ассемблера
class Command
{
public:
    Command(const CommandData &data, LabelContainer *labelContainer, ErrorContainer *errorContainer);

    const CommandData &data() const; // Возвращает данные команды

    virtual bool hasError() const; // Проверяет, содержит ли команда ошибку
    virtual std::size_t size() const = 0; // Вычисляет размер команды
    virtual ByteArray translate() = 0; // Транслирует команду в машинный код

protected:
    LabelContainer *labelContainer() const;
    void handleError(CompillerError error);

private:
    CommandData m_data; // Данные команды
    LabelContainer *m_labelContainer; // Хранилище меток
    ErrorContainer *m_errorContainer; // Хранилище ошибок
    bool m_hasError; // Имеет ли команда ошибку
};

#endif //COMMAND_H
