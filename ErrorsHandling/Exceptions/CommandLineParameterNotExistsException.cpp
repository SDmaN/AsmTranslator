#include "CommandLineParameterNotExistsException.h"

CommandLineParameterNotExistsException::CommandLineParameterNotExistsException(const std::string &message)
        : m_message(message)
{
}

const char *CommandLineParameterNotExistsException::what() const throw()
{
    return m_message.c_str();
}
