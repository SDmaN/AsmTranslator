#include "LabelContainer.h"
#include "../ErrorsHandling/Exceptions/LabelAlreadyDefinedException.h"
#include "../ErrorsHandling/Exceptions/LabelNotExistsException.h"

bool LabelContainer::contains(const std::string &label) const
{
    auto it = m_container.find(label);
    return it != m_container.end();
}

void LabelContainer::add(const std::pair<std::string, Address> &element)
{
    addAddress(element.first, element.second);
}

void LabelContainer::addAddress(const std::string &label, Address address)
{
    checkNotDefined(label); // Проверяем на наличие

    // Метка не определена
    // Данные метки
    LabelData insertingData;
    insertingData.purpose = LabelData::AddressConstant;
    insertingData.taggedData.address = address;

    insertLabelData(label, insertingData); // Вставляем
}

Address LabelContainer::address(const std::string &label) const
{
    checkExists(label); // Проверяем на наличие

    // Метка есть
    LabelData ld = m_container.at(label);

    if(ld.purpose != LabelData::AddressConstant)
        throwNotExistsException(label);

    return ld.taggedData.address;
}

void LabelContainer::addWord(const std::string &label, Word word)
{
    checkNotDefined(label); // Проверяем на наличие

    // Метка не определена
    // Данные метки
    LabelData insertingData;
    insertingData.purpose = LabelData::WordConstant;
    insertingData.taggedData.w = word;

    insertLabelData(label, insertingData); // Вставляем метку
}

Word LabelContainer::word(const std::string &label) const
{
    checkExists(label); // Проверяем наличие метки

    LabelData ld = m_container.at(label);

    if(ld.purpose != LabelData::WordConstant)
        throwNotExistsException(label);

    return ld.taggedData.w;
}

LabelData::Purpose LabelContainer::labelPurpose(const std::string &label)
{
    checkExists(label); // Проверяем наличие

    LabelData ld = m_container.at(label);
    return ld.purpose; // Возвращаем назначение
}

void LabelContainer::updateLabel(const std::string &label, LabelData::Purpose newPurpose)
{
    checkExists(label); // Проверяем наличие

    //Метка есть, можем менять
    m_container[label].purpose = newPurpose;
}

void LabelContainer::updateLabel(const std::string &label, LabelData::Purpose newPurpose, unsigned short newValue)
{
    checkExists(label);

    // Метка есть, можем менять
    m_container[label].purpose = newPurpose;

    switch(newPurpose)
    {
        case LabelData::Purpose::AddressConstant:
            m_container[label].taggedData.address = newValue;
            break;

        case LabelData::Purpose::WordConstant:
            m_container[label].taggedData.w = newValue;
            break;
    }
}

void LabelContainer::clear()
{
    m_container.clear();
}

void LabelContainer::insertLabelData(const std::string &label, const LabelData &labelData)
{
    m_container.insert(std::make_pair(label, labelData));
}

void LabelContainer::throwAlreadyDefinedException(const std::string &label) const
{
    throw LabelAlreadyDefinedException(label);
}

void LabelContainer::throwNotExistsException(const std::string &label) const
{
    throw LabelNotExistsException(label);
}

void LabelContainer::checkNotDefined(const std::string &label) const
{
    if(contains(label))
        throwAlreadyDefinedException(label);
}

void LabelContainer::checkExists(const std::string &label) const
{
    if(!contains(label))
        throwNotExistsException(label);
}
