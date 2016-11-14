#include "ArgumentIncorrectException.h"

ArgumentIncorrectException::ArgumentIncorrectException(const std::string &wrongArgmunent)
    : m_wrongArgument(wrongArgmunent)
{
}

const char *ArgumentIncorrectException::what() const throw()
{
    return m_wrongArgument.c_str();
}
