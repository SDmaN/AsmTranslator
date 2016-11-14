#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <algorithm>
#include "../TypeDefines.h"

// Преобразователь к массиву байт
// CastingItemType - тип преобразуемого объекта
template<typename CastingItemType>
union ByteConverter
{
    CastingItemType convertingItem; // Преобразуемый объект
    Byte bytes[sizeof(CastingItemType)]; // Байты объекта
};

// Преобразует объект к массиву байт
// CastingItemType - тип объекта
template<typename CastingItemType>
ByteArray toBytes(const CastingItemType &item)
{
    ByteConverter<CastingItemType> converter;
    converter.convertingItem = item;

    return ByteArray(std::begin(converter.bytes), std::end(converter.bytes));
}

// Удаляет пробелы из строки
void removeSpaces(std::string &s);

#endif //UTILS_H
