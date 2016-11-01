#ifndef UTILS_H
#define UTILS_H

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

#endif //UTILS_H
