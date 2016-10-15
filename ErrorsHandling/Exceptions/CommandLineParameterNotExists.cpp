#include "CommandLineParameterNotExists.h"

CommandLineParameterNotExists::CommandLineParameterNotExists(const std::string &message)
        : m_message(message)
{
}

const char *CommandLineParameterNotExists::what() const throw()
{
    return m_message.c_str();
}
