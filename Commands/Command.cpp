#include "Command.h"
#include "../ErrorsHandling/ErrorContainer.h"

Command::Command(const CommandData &data, LabelContainer *labelContainer, ErrorContainer *errorContainer)
        : m_data(data), m_labelContainer(labelContainer), m_errorContainer(errorContainer)
{
}

const CommandData &Command::data() const
{
    return m_data;
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

    if(m_errorContainer != nullptr)
        m_errorContainer->add(m_data.lineIndex, m_data.sourceLine, error);
}
