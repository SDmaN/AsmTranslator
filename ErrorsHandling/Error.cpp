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

std::ostream &operator<<(std::ostream &stream, const Error &error)
{
    stream << error.lineIndex() << ": ";
    stream << error.sourceLine() << std::endl;

    switch(error.errorCode())
    {
        case NoError:
            stream << "Нет ошибки";
            break;

        case Unknown:
            stream << "Неизвестная ошибка";
            break;

        case IncorrectSymbol:
            stream << "Неверный символ";
            break;

        case CommandNotFound:
            stream << "Неверный символ";
            break;

        case TooManyArguments:
            stream << "Лишний аргумент";
            break;

        case TooFewArguments:
            stream << "Не достаточно аргументов";
            break;

        case ArgumentIncorrect:
            stream << "Неверный аргумент";
            break;

        case LabelNotFound:
            stream << "Метка не найдена";
            break;

        case LabelAlreadyDefined:
            stream << "Метка уже определена";
            break;

        case IpNotSet:
            stream << "IP не установлен";
            break;
    }

    stream << " (" << error.errorCode() << ")";

    return stream;
}
