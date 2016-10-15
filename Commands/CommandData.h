#ifndef COMMANDDATA_H
#define COMMANDDATA_H

#include <string>
#include "../ErrorsHandling/ErrorsContainer.h"

// Содержит разобранную команду ассемблера
struct CommandData
{
    std::string sourceLine; // Исходная строка
    std::size_t lineIndex; // Номер строки
    std::string label; // Метка
    std::string code; // Код
    std::string arg; // Аргумент
    std::string comment; // Комментарий

    ErrorsContainer errors; // Ошибки

    CommandData();
};

#endif //COMMANDDATA_H
