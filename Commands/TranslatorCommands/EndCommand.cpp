#include <regex>
#include "EndCommand.h"
#include "../LabelContainer.h"

EndCommand::EndCommand(const CommandData &data, Address commandAddress, LabelContainer *labelContainer)
        : Command(data, commandAddress, labelContainer),
          m_labelCommand(data, commandAddress, labelContainer)
{
    parseArg();
}

size_t EndCommand::size() const
{
    return m_commandSize;
}

void EndCommand::translate(VmExecutable &vmExec)
{
    m_labelCommand.translate(vmExec);
    ByteArray result;

    if(!hasError())
    {
        result = { static_cast<Byte>(m_stopCommandCode) };

        vmExec.setIp(m_ip);
        vmExec.appendBytes(result);
        vmExec.appendRelativeAddress(address() + sizeof(m_stopCommandCode));
    }

    setTranslatedBytes(result);
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
