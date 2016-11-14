#include "LabelNotExistsException.h"

LabelNotExistsException::LabelNotExistsException(const std::string &label)
    : m_label(label)
{
}

const char *LabelNotExistsException::what() const throw()
{
    return m_label.c_str();
}
