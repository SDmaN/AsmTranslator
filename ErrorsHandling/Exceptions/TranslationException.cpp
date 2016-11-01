#include <sstream>
#include "TranslationException.h"

TranslationException::TranslationException(const Error &translationError)
    : m_translationError(translationError)
{
}

TranslationException::TranslationException(size_t lineIndex, const std::string &sourceLine, CompillerError errorCode)
    : TranslationException(Error(lineIndex, sourceLine, errorCode))
{
}

const Error &TranslationException::translationError() const
{
    return m_translationError;
}

const char *TranslationException::what() const throw()
{
    std::stringstream ss; // Поток для формирования текста ошибки
    ss << m_translationError; // Формируем текст

    return ss.str().c_str();
}
