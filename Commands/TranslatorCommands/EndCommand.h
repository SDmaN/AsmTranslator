#ifndef ENDCOMMAND_H
#define ENDCOMMAND_H

#include "../Command.h"
#include "../LabelCommand.h"

// Команда транслятора End
class EndCommand : public Command
{
public:
    EndCommand(const CommandData &data, Address commandAddress, LabelContainer *labelContainer,
                   ErrorContainer *errorContainer);

    virtual size_t size() const override; // Возвращает размер
    virtual void translate(VmExecutable &vmExec) override; // Транслирует команду (вставляет Stop)

private:
    const std::size_t m_commandSize = 1; // Размер Stop
    const ProcessorCommandCode m_stopCommandCode = ProcessorCommandCode::Stop;

    Address m_ip;

    LabelCommand m_labelCommand;

    void parseArg(); // Парсит аргумент

    bool checkArgCorrectness() const; // Проверяет аргумент на правильность
    bool labelExists() const; // Проверяет, существует ли метка (из аргумента)
    Address getArgAddress() const; // Возвращает адрес метки
};

#endif //ENDCOMMAND_H
