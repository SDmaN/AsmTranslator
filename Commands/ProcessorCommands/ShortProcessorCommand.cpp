#include "ShortProcessorCommand.h"

ShortProcessorCommand::ShortProcessorCommand(const CommandData &data, Address address, LabelContainer *labelContainer,
                                             ErrorContainer *errorContainer)
        : ProcessorCommand(data, address, labelContainer, errorContainer)
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
