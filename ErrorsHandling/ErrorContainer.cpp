#include "ErrorContainer.h"

ErrorContainer::ErrorContainer()
{
    clear();
}

void ErrorContainer::add(const Error &error)
{
    m_errors.push_back(error);
}

void ErrorContainer::add(std::size_t lineIndex, const std::string &sourceLine, CompillerError errorCode)
{
    add(Error(lineIndex, sourceLine, errorCode));
}

void ErrorContainer::clear()
{
    m_errors.clear();
}

const std::vector<Error> &ErrorContainer::errors() const
{
    return m_errors;
}
