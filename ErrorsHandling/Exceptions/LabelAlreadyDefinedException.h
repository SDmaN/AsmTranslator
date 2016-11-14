#ifndef LABELALREADYDEFINED_H
#define LABELALREADYDEFINED_H

#include <exception>
#include <string>

// Исключение, выбрасываемое при добавлении метки в контейнер, если метка уже определена
class LabelAlreadyDefinedException : public std::exception
{
public:
    explicit LabelAlreadyDefinedException(const std::string &label = std::string());
    virtual const char *what() const throw() override; // Возвращает метку

private:
    std::string m_label; // Метка
};

#endif //LABELALREADYDEFINED_H
