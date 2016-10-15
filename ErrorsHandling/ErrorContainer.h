#ifndef ERRORCONTAINER_H
#define ERRORCONTAINER_H

#include <vector>
#include <string>
#include "Error.h"

// Класс, собирающий ошибки транслятора
class ErrorContainer
{
public:
    ErrorContainer();

    void add(const Error &error);
    void add(std::size_t lineIndex, const std::string &sourceLine, CompillerError errorCode);
    void clear();

    const std::vector<Error> &errors() const;

private:
    std::vector<Error> m_errors;
};

#endif //ERRORCONTAINER_H