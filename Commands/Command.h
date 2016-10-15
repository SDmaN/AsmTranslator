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
class ErrorsContainer;

// Абстрактный класс команды процессора или ассемблера
class Command
{
public:
    Command(const CommandData &data, Address commandAddress, LabelContainer *labelContainer);

    const CommandData &data() const; // Возвращает данные команды
    CommandData &data();
    Address address() const;

    bool hasError() const; // Проверяет, содержит ли команда ошибку
    ByteArray translatedBytes() const; // Возвращает результат трансляции в байтах

    virtual std::size_t size() const = 0; // Вычисляет размер команды
    virtual void translate(VmExecutable &vmExec) = 0; // Транслирует в машинный код

protected:
    LabelContainer *labelContainer() const;
    void handleError(CompillerError error);
    void setTranslatedBytes(const ByteArray &translatedBytes);

private:
    CommandData m_data; // Данные команды
    Address m_address; // Адрес команды
    LabelContainer *m_labelContainer; // Хранилище меток
    bool m_hasError; // Имеет ли команда ошибку
    ByteArray m_translatedBytes; // Оттранслированные байты команды
};

#endif //COMMAND_H
