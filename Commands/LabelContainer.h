#ifndef LABELCONTAINER_H
#define LABELCONTAINER_H

#include <string>
#include <map>

#include "../TypeDefines.h"

// Контейнер для меток (собирается при первом проходе)
class LabelContainer
{
public:
    bool contains(const std::string &label) const; // Проверяет, содержится ли метка
    void add(const std::pair<std::string, Address> &element); // Добавляет метку и адрес
    Address address(const std::string &label) const; // Возвращает адрес метки
    void clear(); // Очищает контейнер

private:
    std::map<std::string, Address> m_container; // Содержит метки и соответствующие адреса
};

#endif //LABELCONTAINER_H
