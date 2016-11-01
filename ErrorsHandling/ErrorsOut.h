#ifndef ERRORSOUT_H
#define ERRORSOUT_H

#include <vector>
#include <ostream>

#include "../Commands/Command.h"
#include "Error.h"

// Собирает все ошибки транслятора и выводит их в поток
class ErrorsOut
{
public:
    void collectErrors(const std::vector<CommandPointer> &commands); // Сбор ошибок
    bool empty() const; // Проверка, есть ли ошибки

    // Вывод в поток
    friend std::ostream &operator<<(std::ostream &stream, const ErrorsOut &eo);

private:
    std::vector<Error> m_errors; // Собранные ошибки
};

#endif //ERRORSOUT_H
