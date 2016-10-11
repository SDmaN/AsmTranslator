#include "Command.h"
#include "../ErrorsHandling/ErrorContainer.h"

Command::Command(const CommandData &data, Address address, LabelContainer *labelContainer,
                 ErrorContainer *errorContainer)
        : m_data(data), m_address(address), m_labelContainer(labelContainer), m_errorContainer(errorContainer)
{
}

bool Command::hasError() const
{
    return m_hasError;
}

LabelContainer *Command::labelContainer() const
{
    return m_labelContainer;
}

void Command::handleError(CompillerError error)
{
    m_hasError = true;
    m_errorContainer->add(m_data.lineIndex, m_data.sourceLine, error);
}
