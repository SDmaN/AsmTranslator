#include "AssemblerTranslator.h"
#include "ErrorsHandling/ErrorContainer.h"
#include "Listing/Listing.h"

AssemblerTranslator::AssemblerTranslator(ErrorContainer *errorContainer)
    : m_errorContainer(errorContainer)
{
}

VmExecutable AssemblerTranslator::translate(const std::vector<CommandData> &cmdsData)
{
    m_labels.clear();

    VmExecutable result;

    bool hasError = firstPass(cmdsData);

    if(!hasError)
        hasError = secondPass(result);

    return hasError ? VmExecutable() : result;
}

const std::vector<CommandPointer> &AssemblerTranslator::translatedCommands() const
{
    return m_translatedCommands;
}

CommandPointer AssemblerTranslator::createCommand(const CommandData &cmdData, Address commandAddress) const
{
    return m_commandsCreator.create(cmdData, commandAddress, const_cast<LabelContainer *>(&m_labels), m_errorContainer);
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
        CommandPointer command = createCommand(cmdData, currentCommandAddress);

        if(command)
        {
            currentCommandAddress += command->size();
            hasError |= command->hasError(); // Сама ошибка обработана командой
            m_translatedCommands.push_back(command);
        }
        else
        { // Нашли неверную команду
            hasError = true;
            handleError(cmdData, CompillerError::CommandNotFound);
        }
    }

    return hasError;
}

bool AssemblerTranslator::secondPass(VmExecutable &vmExec)
{
    bool hasError = false;

    auto it = std::begin(m_translatedCommands);
    auto end = std::end(m_translatedCommands);
    auto lastIt = end - 1;

    while(it != end)
    {
        CommandPointer command = *it;

        if(command)
        {
            command->translate(vmExec);
            hasError |= command->hasError();

            // Последней должна быть директива End и установлен IP
            if(it == lastIt)
            {
                hasError |= !vmExec.ipIsSet();

                if(!vmExec.ipIsSet())
                    handleError(command->data(), CompillerError::IpNotSet);
            }
        }

        ++it;
    }

    return hasError;
}