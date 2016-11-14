#ifndef ASMTRANSLATOR_LABELNOTEXISTS_H
#define ASMTRANSLATOR_LABELNOTEXISTS_H

#include <exception>
#include <string>

// Исключение, выбрасываемое при попытке вытащить метку, если ее нет в таблице
class LabelNotExistsException : public std::exception
{
public:
    explicit LabelNotExistsException(const std::string &label = std::string());
    virtual const char *what() const throw() override; // Возвращает название метки

private:
    std::string m_label; // Метка
};

#endif //LABELNOTEXISTS_H
