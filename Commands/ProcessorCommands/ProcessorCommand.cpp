#include "ProcessorCommand.h"
#include "../../ErrorsHandling/Exceptions/CommandNotFoundException.h"

// "Текстовый код - числовой код короткой команды"
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

// "Текстовый код - числовой код длинной команды"
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

ProcessorCommand::ProcessorCommand(const CommandData &data, Address commandAddress, LabelContainer *labelContainer)
        : Command(data, commandAddress, labelContainer)
{
    extractCode(data); // При создании команды сразу можем определить ее код
}

ProcessorCommandCode ProcessorCommand::code() const
{
    return m_code;
}

void ProcessorCommand::extractCode(const CommandData &cmdData)
{
    try
    {
        findCommand(cmdData, m_shortCodes); // Сперва ищем среди коротких
    }
    catch(CommandNotFoundException &ex)
    {
        try
        {
            // Если не найшли, пытаемся искать среди длинных
            findCommand(cmdData, m_longCodes);
        }
        catch(CommandNotFoundException &ex)
        {
            // Если опять не нашли, то ошибка
            handleError(CompillerError::CommandNotFound);
        }
    }
}

void
ProcessorCommand::findCommand(const CommandData &cmdData, std::map<std::string, ProcessorCommandCode> &whereToSearch)
{
    auto it = whereToSearch.find(cmdData.code); // Ищем код

    // Если не нашли, выбрасываем исключение
    if(it == std::end(whereToSearch))
        throw CommandNotFoundException(cmdData.code);

    // Иначе устанавливаем код
    m_code = it->second;
}
