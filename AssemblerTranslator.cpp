#include "AssemblerTranslator.h"
#include "Listing/Listing.h"
#include <iostream>

AssemblerTranslator::AssemblerTranslator()
{
}

VmExecutable AssemblerTranslator::translate(const std::vector<CommandData> &cmdsData)
{
    m_labels.clear();

    VmExecutable result;

    // Первый проход
    bool hasError = firstPass(cmdsData);

    // Если не было ошибок, второй проход
    if(!hasError)
        hasError = secondPass(result);

    // Если были ошибки, vmExec должен быть пустой
    return hasError ? VmExecutable() : result;
}

const std::vector<CommandPointer> &AssemblerTranslator::translatedCommands() const
{
    return m_translatedCommands;
}

CommandPointer AssemblerTranslator::createCommand(const CommandData &cmdData, Address commandAddress) const
{
    return m_commandsCreator.create(cmdData, commandAddress, const_cast<LabelContainer *>(&m_labels));
}

void AssemblerTranslator::handleError(CommandData &cmdData, CompillerError errorCode)
{
    cmdData.errors.add(cmdData, errorCode);
}

bool AssemblerTranslator::firstPass(const std::vector<CommandData> &cmdsData)
{
    bool hasError = false;
    Address currentCommandAddress = 0;

    for(const auto &cmdData : cmdsData)
    {
        CommandPointer command = createCommand(cmdData, currentCommandAddress);

        currentCommandAddress += command->size();
        hasError |= command->hasError(); // Сама ошибка обработана командой
        m_translatedCommands.push_back(command);
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
        auto c = command.get();
        command->translate(vmExec);
        hasError |= command->hasError();

        // Последней должна быть директива End и установлен IP
        if(it == lastIt)
        {
            hasError |= !vmExec.ipIsSet();

            if(!vmExec.ipIsSet())
                handleError(command->data(), CompillerError::IpNotSet);
        }

        ++it;
    }

    return hasError;
}