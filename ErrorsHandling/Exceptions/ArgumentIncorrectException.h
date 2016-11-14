#ifndef ARGUMENTINCORRECTEXCEPTION_H
#define ARGUMENTINCORRECTEXCEPTION_H

#include <exception>
#include <string>

// Выбрасывается, когда команда имеет неверный аргумент (например
class ArgumentIncorrectException : public std::exception
{
public:
    explicit ArgumentIncorrectException(const std::string &wrongArgmunent);
    virtual const char *what() const throw() override; // Возвращает неверный аргумент

private:
    std::string m_wrongArgument; // Ошибочный аргумент
};

#endif //ARGUMENTINCORRECTEXCEPTION_H
