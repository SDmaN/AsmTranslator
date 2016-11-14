#include "Command.h"
#include "../Listing/Listing.h"
#include "LabelContainer.h"
#include "../ErrorsHandling/Exceptions/LabelAlreadyDefinedException.h"

Command::Command(const CommandData &data, Address commandAddress, LabelContainer *labelContainer)
        : m_data(data), m_address(commandAddress), m_labelContainer(labelContainer), m_hasError(false)
{
    // При создании сразу проверяем наличие метки и, если есть, добавляем в таблицу
    addLabelToContainer();
}

const CommandData &Command::data() const
{
    return m_data;
}

CommandData &Command::data()
{
    return m_data;
}

Address Command::address() const
{
    return m_address;
}

bool Command::hasError() const
{
    return m_hasError;
}

ByteArray Command::translatedBytes() const
{
    return m_translatedBytes;
}

LabelContainer *Command::labelContainer() const
{
    return m_labelContainer;
}

void Command::handleError(CompillerError error)
{
    // При обработке ошибки:
    m_hasError = true; // Говорим, что ошибка есть
    m_data.errors.add(m_data, error); // Запоминаем ошибку
}

void Command::setTranslatedBytes(const ByteArray &translatedBytes)
{
    m_translatedBytes = translatedBytes;
}

void Command::addLabelToContainer()
{
    // Обрабатываем метку, только если она есть
    if(!m_data.label.empty())
    {
        try
        {
            // Пытаемся добавить метку-адрес в таблицу
            // Для директивы Equ адрес будет заменен на константу в самой команде Equ
            labelContainer()->addAddress(data().label, address());
        }
        catch(LabelAlreadyDefinedException &ex)
        {
            handleError(CompillerError::LabelAlreadyDefined);
        }
    }
}
