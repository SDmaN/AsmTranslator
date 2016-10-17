#ifndef ERRORCONTAINER_H
#define ERRORCONTAINER_H

#include <vector>
#include <string>
#include "Error.h"

class CommandData;

// Класс, собирающий ошибки транслятора
class ErrorsContainer
{
public:
    ErrorsContainer();

    void add(const Error &error);
    void add(std::size_t lineIndex, const std::string &sourceLine, CompillerError errorCode);
    void add(const CommandData &cmdData, CompillerError errorCode);
    void clear();
    bool empty() const; // Проверяет, пусь ди контейнер

    const std::vector<Error> &errors() const;

private:
    std::vector<Error> m_errors;
};

#endif //ERRORCONTAINER_H