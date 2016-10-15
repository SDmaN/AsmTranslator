#include "ErrorsContainer.h"
#include "../Commands/CommandData.h"

ErrorsContainer::ErrorsContainer()
{
    clear();
}

void ErrorsContainer::add(const Error &error)
{
    m_errors.push_back(error);
}

void ErrorsContainer::add(std::size_t lineIndex, const std::string &sourceLine, CompillerError errorCode)
{
    add(Error(lineIndex, sourceLine, errorCode));
}

void ErrorsContainer::add(const CommandData &cmdData, CompillerError errorCode)
{
    add(cmdData.lineIndex, cmdData.sourceLine, errorCode);
}

void ErrorsContainer::clear()
{
    m_errors.clear();
}

const std::vector<Error> &ErrorsContainer::errors() const
{
    return m_errors;
}
