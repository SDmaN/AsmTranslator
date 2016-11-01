#ifndef ERRORCONTAINER_H
#define ERRORCONTAINER_H

#include <vector>
#include <string>
#include "Error.h"

class CommandData;

// Класс, собирающий ошибки транслятора.
// Используется как данные команды
class ErrorsContainer
{
public:
    ErrorsContainer();

    // Добавляет ошибку в контейнер
    void add(const Error &error);

    // Добавляет ошибку в данной строке с данным кодом
    void add(std::size_t lineIndex, const std::string &sourceLine, CompillerError errorCode);

    // Добавляет ошибку, вытаскивая строку из данных команды
    void add(const CommandData &cmdData, CompillerError errorCode);

    // Очищает контейнер
    void clear();

    // Проверяет, пусь ди контейнер
    bool empty() const;

    // Возвращает вектор ошибок, которые содержатся в контейнере
    const std::vector<Error> &errors() const;

private:
    std::vector<Error> m_errors; // Вектор ошибок контейнера
};

#endif //ERRORCONTAINER_H