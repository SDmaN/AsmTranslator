#include "CommandData.h"

CommandData::CommandData()
        : lineIndex(0)
{
}

CommandData::CommandData(const CommandData &other)
        : lineIndex(other.lineIndex), label(other.label), code(other.code), arg(other.arg), comment(other.comment)
{
}

CommandData::CommandData(CommandData &&other)
        : lineIndex(other.lineIndex), label(other.label), code(other.code), arg(other.arg), comment(other.comment)
{
}