#include "Command.h"

Command::Command(const CommandData &data, Address address, LabelContainer *labelContainer,
                 ErrorContainer *errorContainer)
        : m_data(data), m_address(address), m_labelContainer(labelContainer), m_errorContainer(errorContainer)
{
}

LabelContainer *Command::labelContainer() const
{
    return m_labelContainer;
}

ErrorContainer *Command::errorContainer() const
{
    return m_errorContainer;
}
