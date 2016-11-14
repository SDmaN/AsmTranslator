#ifndef PROCESSORCOMMAND_H
#define PROCESSORCOMMAND_H

#include <map>
#include "../Command.h"

// Базовый класс для команд процессора (коротких и длинных)
class ProcessorCommand : public Command
{
public:
    ProcessorCommand(const CommandData &data, Address commandAddress, LabelContainer *labelContainer);

protected:
    ProcessorCommandCode code() const; // Возвращает код команды

private:
    static std::map<std::string, ProcessorCommandCode> m_shortCodes; // Коды коротких команд
    static std::map<std::string, ProcessorCommandCode> m_longCodes; // Коды длинных команд

    ProcessorCommandCode m_code; // Код команды

    void extractCode(const CommandData &cmdData); // Достает код команды из данных

    // Ищет команду в мапах m_shortCodes или m_longCodes. Если не найдена, выбрасывает CommandNotFoundException
    void findCommand(const CommandData &cmdData, std::map<std::string, ProcessorCommandCode> &whereToSearch);
};

#endif //PROCESSORCOMMAND_H
