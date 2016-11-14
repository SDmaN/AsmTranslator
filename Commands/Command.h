#ifndef COMMAND_H
#define COMMAND_H

#include <memory>

#include "CommandData.h"
#include "../TypeDefines.h"
#include "../VmExecutable.h"
#include "ProcessorCommandCode.h"
#include "../ErrorsHandling/CompillerError.h"

class LabelContainer;

// Абстрактный класс команды процессора или ассемблера
class Command
{
public:
    Command(const CommandData &data, Address commandAddress, LabelContainer *labelContainer);

    const CommandData &data() const; // Возвращает данные команды
    CommandData &data(); // Возвращает данные по ссылке
    Address address() const; // Возвращает адрес команды

    bool hasError() const; // Проверяет, содержит ли команда ошибку
    ByteArray translatedBytes() const; // Возвращает результат трансляции в байтах

    virtual std::size_t size() const = 0; // Вычисляет размер команды
    virtual void translate(VmExecutable &vmExec) = 0; // Транслирует в машинный код

protected:
    LabelContainer *labelContainer() const; // Возвращает указатель на контейнер меток
    void handleError(CompillerError error); // Обрабатывает и сохраняет ощибку
    void setTranslatedBytes(const ByteArray &translatedBytes); // Устанавливает оттранслированные байты

private:
    CommandData m_data; // Данные команды
    Address m_address; // Адрес команды
    LabelContainer *m_labelContainer; // Хранилище меток
    bool m_hasError; // Имеет ли команда ошибку
    ByteArray m_translatedBytes; // Оттранслированные байты команды

    void addLabelToContainer(); // Добавляет метку в контейнер
};

// Указатель для удобного удаления команд
typedef std::shared_ptr<Command> CommandPointer;

#endif //COMMAND_H
