#include "ShortProcessorCommand.h"

ShortProcessorCommand::ShortProcessorCommand(const CommandData &data, LabelContainer *labelContainer, ErrorContainer *errorContainer)
        : ProcessorCommand(data, labelContainer, errorContainer)
{
}

size_t ShortProcessorCommand::size() const
{
    return ShortCommandSize;
}

ByteArray ShortProcessorCommand::translate()
{
    if(!hasError())
        return { static_cast<Byte>(code()) };

    return ByteArray();
}
