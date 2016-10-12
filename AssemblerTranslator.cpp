#include "AssemblerTranslator.h"
#include "ErrorsHandling/ErrorContainer.h"

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

CommandPointer AssemblerTranslator::createCommand(const CommandData &cmdData) const
{
    return m_commandsCreator.create(cmdData, const_cast<LabelContainer *>(&m_labels), m_errorContainer);
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

        CommandPointer command = createCommand(cmdData);

        if(command)
        {
            currentCommandAddress += command->size();
            hasError = command->hasError(); // Сама ошибка обработана командой
            m_commands.push_back(command);
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
    Address currentCommandAddress = 0;

    for(CommandPointer &command : m_commands)
    {
        if(command)
        {
            command->translate(vmExec, currentCommandAddress);
            currentCommandAddress += command->size();

            hasError = command->hasError();
        }
    }

    return hasError;
}