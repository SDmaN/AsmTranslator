#include "Command.h"
#include "../ErrorsHandling/ErrorContainer.h"
#include "../Listing/Listing.h"

Command::Command(const CommandData &data, LabelContainer *labelContainer, ErrorContainer *errorContainer,
                 Listing *listing)
        : m_data(data), m_labelContainer(labelContainer), m_errorContainer(errorContainer), m_listing(listing)
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

void Command::translate(VmExecutable &vmExec, Address commandAddress)
{
    if(!hasError())
    {
        ByteArray translatedBytes = writeExecutable(vmExec, commandAddress);
        writeListing(commandAddress, translatedBytes);
    }
}

void Command::writeListing(Address commandAddress, const ByteArray &translatedBytes)
{
    if(m_listing != nullptr)
    {
        // TODO: запись в листинг
    }
}
