#include "CommandNotFoundException.h"

CommandNotFoundException::CommandNotFoundException(const std::string &commandName)
    : m_commandName(commandName)
{
}

const char *CommandNotFoundException::what() const throw()
{
    return m_commandName.c_str();
}
