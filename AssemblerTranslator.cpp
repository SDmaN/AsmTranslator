#include "AssemblerTranslator.h"
#include "ErrorsHandling/ErrorContainer.h"

AssemblerTranslator::AssemblerTranslator(ErrorContainer *errorContainer)
{
}

VmExecutable AssemblerTranslator::translate(const std::vector<CommandData> &cmdsData)
{
    m_labels.clear();

    VmExecutable result;

    bool hasError = firstPass(cmdsData);

    if(!hasError)
        result = secondPass();

    return result;
}

CommandPointer AssemblerTranslator::createCommand(const CommandData &cmdData, Address address) const
{
    return m_commandsCreator.create(cmdData, address, &m_labels, m_errorContainer);
}

bool AssemblerTranslator::hasLabel(const CommandData &cmdData) const
{
    return !cmdData.label.empty();
}

void AssemblerTranslator::addLabel(const std::string &label, Address address)
{
    m_labels.add(std::make_pair(label, address));
}

void AssemblerTranslator::handleError(const CommandData &cmdData, CompillerError error)
{
    m_errorContainer->add(cmdData.lineIndex, cmdData.sourceLine, error);
}

bool AssemblerTranslator::firstPass(const std::vector<CommandData> &cmdsData)
{
    bool hasError = false;
    Address currentCommandAddress = 0;

    for(const auto &cmdData : cmdsData)
    {
        if(hasLabel(cmdData))
            addLabel(cmdData.label, currentCommandAddress);

        CommandPointer command = createCommand(cmdData, currentCommandAddress);

        if(command)
            currentCommandAddress += command->size();
        else
        {
            hasError = true;
            handleError(cmdData, CompillerError::CommandNotFound);
        }
    }

    return hasError;
}

VmExecutable AssemblerTranslator::secondPass()
{
    return VmExecutable();
}
