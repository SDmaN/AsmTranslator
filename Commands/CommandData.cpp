#include "CommandData.h"

CommandData::CommandData()
        : lineIndex(0)
{
}

bool CommandData::empty() const
{
    return label.empty() && code.empty() && comment.empty();
}
