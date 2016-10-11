#include "ProcessorCommand.h"

std::map<std::string, ProcessorCommandCode> ProcessorCommand::m_shortCodes = {
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

std::map<std::string, ProcessorCommandCode> ProcessorCommand::m_longCodes = {
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

ProcessorCommand::ProcessorCommand(const CommandData &data, LabelContainer *labelContainer, ErrorContainer *errorContainer)
        : Command(data, labelContainer, errorContainer)
{
    extractCode(data);
}

ProcessorCommandCode ProcessorCommand::code() const
{
    return m_code;
}

void ProcessorCommand::extractCode(const CommandData &cmdData)
{
    auto shortIt = m_shortCodes.find(cmdData.code);

    if(shortIt == std::end(m_shortCodes))
    {
        auto longIt = m_longCodes.find(cmdData.code);

        if(longIt == std::end(m_longCodes))
            handleError(CompillerError::CommandNotFound);
        else
            m_code = longIt->second;
    }
    else
        m_code = shortIt->second;
}
