#ifndef CONSOLEPARAMETERNOTEXISTS_H
#define CONSOLEPARAMETERNOTEXISTS_H

#include <exception>
#include <string>

// Ошибка параметра командной строки
class CommandLineParameterNotExistsException : public std::exception
{
public:
    CommandLineParameterNotExistsException(const std::string &message);
    virtual const char *what() const throw() override; // Сообщение ошибки

private:
    std::string m_message;
};

#endif //CONSOLEPARAMETERNOTEXISTS_H
