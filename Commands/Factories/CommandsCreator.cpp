#include "CommandsCreator.h"
#include "../../ErrorsHandling/ErrorContainer.h"

CommandFactory<ShortProcessorCommand> CommandsCreator::m_shortProcessorCommandFactory;
CommandFactory<LongProcessorCommand> CommandsCreator::m_longProcessorCommandFactory;

std::map<std::string, CommandFactoryBase *> CommandsCreator::m_commandFactories = {
        { "Nop",  &m_shortProcessorCommandFactory },
        { "Stop", &m_shortProcessorCommandFactory },
        { "ItF",  &m_shortProcessorCommandFactory },
        { "FtI",  &m_shortProcessorCommandFactory },
        { "InI",  &m_shortProcessorCommandFactory },
        { "OutI",  &m_shortProcessorCommandFactory },
        { "InF",  &m_shortProcessorCommandFactory },
        { "OutF",  &m_shortProcessorCommandFactory },
        { "Ret",  &m_shortProcessorCommandFactory },

        { "AddI",  &m_longProcessorCommandFactory },
        { "AddIR",  &m_longProcessorCommandFactory },
        { "SubI",  &m_longProcessorCommandFactory },
        { "SubIR",  &m_longProcessorCommandFactory },
        { "MulI",  &m_longProcessorCommandFactory },
        { "MulIR",  &m_longProcessorCommandFactory },
        { "DivI",  &m_longProcessorCommandFactory },
        { "DivIR",  &m_longProcessorCommandFactory },
        { "ModI",  &m_longProcessorCommandFactory },
        { "ModIR",  &m_longProcessorCommandFactory },
        { "AddF",  &m_longProcessorCommandFactory },
        { "AddFR",  &m_longProcessorCommandFactory },
        { "SubF",  &m_longProcessorCommandFactory },
        { "SubFR",  &m_longProcessorCommandFactory },
        { "MulF",  &m_longProcessorCommandFactory },
        { "MulFR",  &m_longProcessorCommandFactory },
        { "DivF",  &m_longProcessorCommandFactory },
        { "DivFR",  &m_longProcessorCommandFactory },
        { "LoadS",  &m_longProcessorCommandFactory },
        { "LoadSR",  &m_longProcessorCommandFactory },
        { "UnloadS",  &m_longProcessorCommandFactory },
        { "UnloadSR",  &m_longProcessorCommandFactory },
        { "LoadA",  &m_longProcessorCommandFactory },
        { "LoadAR",  &m_longProcessorCommandFactory },
        { "UnloadA",  &m_longProcessorCommandFactory },
        { "UnloadAR",  &m_longProcessorCommandFactory },
        { "CmpI",  &m_longProcessorCommandFactory },
        { "CmpIR",  &m_longProcessorCommandFactory },
        { "CmpF",  &m_longProcessorCommandFactory },
        { "CmpFR",  &m_longProcessorCommandFactory },
        { "Jmp",  &m_longProcessorCommandFactory },
        { "JmpR",  &m_longProcessorCommandFactory },
        { "Je",  &m_longProcessorCommandFactory },
        { "JeR",  &m_longProcessorCommandFactory },
        { "Jne",  &m_longProcessorCommandFactory },
        { "JneR",  &m_longProcessorCommandFactory },
        { "Jl",  &m_longProcessorCommandFactory },
        { "JlR",  &m_longProcessorCommandFactory },
        { "Jg",  &m_longProcessorCommandFactory },
        { "JgR",  &m_longProcessorCommandFactory },
        { "Jle",  &m_longProcessorCommandFactory },
        { "JleR",  &m_longProcessorCommandFactory },
        { "Jge",  &m_longProcessorCommandFactory },
        { "JgeR",  &m_longProcessorCommandFactory },
        { "Call",  &m_longProcessorCommandFactory }
};

// ============================================

CommandPointer CommandsCreator::create(const CommandData &cmdData, LabelContainer *labelContainer, ErrorContainer *errorContainer) const
{
    auto factoriesIt = m_commandFactories.find(cmdData.code);

    if(factoriesIt == std::end(m_commandFactories))
    {
        errorContainer->add(cmdData.lineIndex, cmdData.sourceLine, CompillerError::CommandNotFound);
        return CommandPointer();
    }

    return factoriesIt->second->create(cmdData, labelContainer, errorContainer);
}
