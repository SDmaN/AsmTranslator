#include "Error.h"

Error::Error(size_t lineIndex, const std::string &sourceLine, CompillerError errorCode)
        : m_lineIndex(lineIndex), m_sourceLine(sourceLine), m_errorCode(errorCode)
{
}

size_t Error::lineIndex() const
{
    return m_lineIndex;
}

void Error::setLineIndex(size_t lineIndex)
{
    m_lineIndex = lineIndex;
}

const std::string &Error::sourceLine() const
{
    return m_sourceLine;
}

void Error::setSourceLine(const std::string &sourceLine)
{
    m_sourceLine = sourceLine;
}

CompillerError Error::errorCode() const
{
    return m_errorCode;
}

void Error::setErrorCode(CompillerError errorCode)
{
    m_errorCode = errorCode;
}
