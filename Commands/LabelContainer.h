#ifndef LABELCONTAINER_H
#define LABELCONTAINER_H

#include <string>
#include <map>

#include "../TypeDefines.h"

// Данные метки
// Контейнер меток содержит словарь этих данных: "название метки - данные"
struct LabelData
{
    // Назначение метки
    enum Purpose
    {
        AddressConstant, // Метка указывает на адрес в программе
        WordConstant, // Метка указывает на знаковую константу (напр. такие метки создаются для директивы Equ)
    };

    // Данные, помеченные меткой.
    union TaggedData
    {
        Word w; // Меткой помечена целая знаковая константа (напр. Equ)
        Address address; // Меткой помечен адрес (обычная метка перед командой)
    };

    Purpose purpose; // Назначение
    TaggedData taggedData; // Данные метки
};

// Контейнер для меток (собирается при первом проходе)
class LabelContainer
{
public:
    bool contains(const std::string &label) const; // Проверяет, содержится ли метка
    void add(const std::pair<std::string, Address> &element); // Добавляет метку и адрес

    void addAddress(const std::string &label, Address address); // Помечает адрес
    Address address(const std::string &label) const; // Возвращает адрес метки

    void addWord(const std::string &label, Word word); // Добавляет знаковую константу
    Word word(const std::string &label) const; // Возвращает знаковую константу

    // Изменяет назначение метки
    void updateLabel(const std::string &label, LabelData::Purpose newPurpose);

    void clear(); // Очищает контейнер

private:
    std::map<std::string, LabelData> m_container; // Содержит метки и соответствующие адреса

    void insertLabelData(const std::string &label, const LabelData &labelData); // Добавляет метку в таблицу

    void throwAlreadyDefinedException(const std::string &label) const; // Выбрасывает исключение LabelAlreadyDefined
    void throwNotExistsException(const std::string &label) const; // Выбрасывает иключение LabelNotExists

    void checkNotDefined(const std::string &label) const; // Выбрасывает исключение, если метка не определена
    void checkExists(const std::string &label) const; // Выбрасывает исключение, если метки нет в таблице
};

#endif //LABELCONTAINER_H
