#include "Command.h"
#include "../ErrorsHandling/ErrorContainer.h"
#include "../Listing/Listing.h"

Command::Command(const CommandData &data, Address commandAddress, LabelContainer *labelContainer,
                 ErrorContainer *errorContainer)
        : m_data(data), m_address(commandAddress), m_labelContainer(labelContainer), m_errorContainer(errorContainer)
{
}

const CommandData &Command::data() const
{
    return m_data;
}

Address Command::address() const
{
    return m_address;
}

bool Command::hasError() const
{
    return m_hasError;
}

ByteArray Command::translatedBytes() const
{
    return m_translatedBytes;
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

void Command::setTranslatedBytes(const ByteArray &translatedBytes)
{
    m_translatedBytes = translatedBytes;
}
