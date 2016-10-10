#include "FileNotFoundException.h"

FileNotFoundException::FileNotFoundException(const std::string &message)
        : m_message(message)
{
}

const char *FileNotFoundException::what() const throw()
{
    return m_message.c_str();
}
