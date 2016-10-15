#ifndef PROCESSORCOMMAND_H
#define PROCESSORCOMMAND_H

#include <map>
#include "../Command.h"

// Базовый класс для команд процессора
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
};

#endif //PROCESSORCOMMAND_H
