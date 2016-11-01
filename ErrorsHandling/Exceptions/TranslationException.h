#ifndef TRANSLATIONEXCEPTION_H
#define TRANSLATIONEXCEPTION_H

#include <exception>
#include "../Error.h"

// Исключение, возникшие при попытке трансляции (парсинг или 2 прохода)
class TranslationException : public std::exception
{
public:
    // Конструкторы инициализации
    explicit TranslationException(const Error &translationError);
    TranslationException(size_t lineIndex, const std::string &sourceLine, CompillerError errorCode);

    // Возвращает ошибку трансляйии
    const Error &translationError() const;

    // Возвращает сообщение с текстом ошибки
    virtual const char *what() const throw() override;

private:
    Error m_translationError; // Возникшая ошибка трансляции
};

#endif //TRANSLATIONEXCEPTION_H
