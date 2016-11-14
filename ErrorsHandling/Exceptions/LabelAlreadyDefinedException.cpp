#include "LabelAlreadyDefinedException.h"

LabelAlreadyDefinedException::LabelAlreadyDefinedException(const std::string &label)
    : m_label(label)
{
}

const char *LabelAlreadyDefinedException::what() const throw()
{
    return m_label.c_str();
}
