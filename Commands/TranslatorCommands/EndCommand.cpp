#include <regex>
#include "EndCommand.h"
#include "../LabelContainer.h"

EndCommand::EndCommand(const CommandData &data, LabelContainer *labelContainer, ErrorContainer *errorContainer,
                       Listing *listing)
        : Command(data, labelContainer, errorContainer, listing)
{
    parseArg();
}

size_t EndCommand::size() const
{
    return m_commandSize;
}

ByteArray EndCommand::writeExecutable(VmExecutable &vmExec, Address)
{
    if(!hasError())
    {
        ByteArray result = { static_cast<Byte>(m_stopCommandCode) };

        vmExec.setIp(m_ip);
        vmExec.appendBytes(result);

        return result;
    }

    return ByteArray();
}

void EndCommand::parseArg()
{
    if(!checkArgCorrectness())
    {
        handleError(CompillerError::ArgumentIncorrect);
        return;
    }

    else if(!labelExists())
    {
        handleError(CompillerError::LabelNotFound);
        return;
    }

    m_ip = getArgAddress();
}

bool EndCommand::checkArgCorrectness() const
{
    const std::regex regEx("[a-zA-Z_]\\w+");
    return std::regex_match(data().arg, regEx);
}

bool EndCommand::labelExists() const
{
    return labelContainer()->contains(data().arg);
}

Address EndCommand::getArgAddress() const
{
    return labelContainer()->address(data().arg);
}
