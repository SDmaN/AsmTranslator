#include "Command.h"
#include "../ErrorsHandling/ErrorContainer.h"

std::map<std::string, ProcessorCommandCode> Command::m_shortCodes = {
        { "Nop",  ProcessorCommandCode::Nop },
        { "Stop", ProcessorCommandCode::Stop },

        { "ItF",  ProcessorCommandCode::ItF },
        { "FtI",  ProcessorCommandCode::FtI },

        { "InI",  ProcessorCommandCode::InI },
        { "OutI", ProcessorCommandCode::OutI },
        { "InF",  ProcessorCommandCode::InF },
        { "OutF", ProcessorCommandCode::OutF },

        { "Ret",  ProcessorCommandCode::Ret }
};

std::map<std::string, ProcessorCommandCode> Command::m_longCodes = {
        { "AddI",     ProcessorCommandCode::AddI },
        { "AddIR",    ProcessorCommandCode::AddIR },
        { "SubI",     ProcessorCommandCode::SubI },
        { "SubIR",    ProcessorCommandCode::SubIR },
        { "MulI",     ProcessorCommandCode::MulI },
        { "MulIR",    ProcessorCommandCode::MulIR },
        { "DivI",     ProcessorCommandCode::DivI },
        { "DivIR",    ProcessorCommandCode::DivIR },
        { "ModI",     ProcessorCommandCode::ModI },
        { "ModIR",    ProcessorCommandCode::ModIR },

        { "AddF",     ProcessorCommandCode::AddF },
        { "AddFR",    ProcessorCommandCode::AddFR },
        { "SubF",     ProcessorCommandCode::SubF },
        { "SubFR",    ProcessorCommandCode::SubFR },
        { "MulF",     ProcessorCommandCode::MulF },
        { "MulFR",    ProcessorCommandCode::MulFR },
        { "DivF",     ProcessorCommandCode::DivF },
        { "DivFR",    ProcessorCommandCode::DivFR },

        { "LoadS",    ProcessorCommandCode::LoadS },
        { "LoadSR",   ProcessorCommandCode::LoadSR },
        { "UnloadS",  ProcessorCommandCode::UnloadS },
        { "UnloadSR", ProcessorCommandCode::UnloadSR },
        { "LoadA",    ProcessorCommandCode::LoadA },
        { "LoadAR",   ProcessorCommandCode::LoadAR },
        { "UnloadA",  ProcessorCommandCode::UnloadA },
        { "UnloadAR", ProcessorCommandCode::UnloadAR },

        { "CmpI",     ProcessorCommandCode::CmpI },
        { "CmpIR",    ProcessorCommandCode::CmpIR },
        { "CmpF",     ProcessorCommandCode::CmpF },
        { "CmpFR",    ProcessorCommandCode::CmpFR },

        { "Jmp",      ProcessorCommandCode::Jmp },
        { "JmpR",     ProcessorCommandCode::JmpR },
        { "Je",       ProcessorCommandCode::Je },
        { "JeR",      ProcessorCommandCode::JeR },
        { "Jne",      ProcessorCommandCode::Jne },
        { "JneR",     ProcessorCommandCode::JneR },
        { "Jl",       ProcessorCommandCode::Jl },
        { "JlR",      ProcessorCommandCode::JlR },
        { "Jg",       ProcessorCommandCode::Jg },
        { "JgR",      ProcessorCommandCode::JgR },
        { "Jle",      ProcessorCommandCode::Jle },
        { "JleR",     ProcessorCommandCode::JleR },
        { "Jge",      ProcessorCommandCode::Jge },
        { "JgeR",     ProcessorCommandCode::JgeR },
        { "Call",     ProcessorCommandCode::Call }
};

Command::Command(const CommandData &data, Address address, LabelContainer *labelContainer,
                 ErrorContainer *errorContainer)
        : m_data(data), m_address(address), m_labelContainer(labelContainer), m_errorContainer(errorContainer)
{
}

LabelContainer *Command::labelContainer() const
{
    return m_labelContainer;
}

void Command::handleError(CompillerError error)
{
    m_errorContainer->add(m_data.lineIndex, m_data.sourceLine, error);
}
