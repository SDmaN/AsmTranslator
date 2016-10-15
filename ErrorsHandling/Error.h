#ifndef ERROR_H
#define ERROR_H

#include <string>
#include <ostream>
#include "CompillerError.h"

// Представляет ошибку
class Error
{
public:
    Error(size_t lineIndex, const std::string &sourceLine, CompillerError errorCode);

    // Геттеры и сеттеры для полей
    size_t lineIndex() const;
    void setLineIndex(size_t lineIndex);

    const std::string &sourceLine() const;
    void setSourceLine(const std::string &sourceLine);

    CompillerError errorCode() const;
    void setErrorCode(CompillerError errorCode);

private:
    std::size_t m_lineIndex; // Номер строки, содержащей ошибку
    std::string m_sourceLine; // Исходная строка
    CompillerError m_errorCode; // Код ошибки
};

std::ostream &operator<<(std::ostream &stream, const Error &error);

#endif //ERROR_H
