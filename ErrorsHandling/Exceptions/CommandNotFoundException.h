#ifndef COMMANDNOTFOUND_H
#define COMMANDNOTFOUND_H

#include <exception>
#include <string>

// Исключение, выбрасываемое, если команда не была найдена в мапе
class CommandNotFoundException : public std::exception
{
public:
    explicit CommandNotFoundException(const std::string &commandName);
    virtual const char *what() const throw() override; // Возвращает название ошибочной команды

private:
    std::string m_commandName; // Строковое название команды
};

#endif //COMMANDNOTFOUND_H
