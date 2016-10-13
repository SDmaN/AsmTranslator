#ifndef ENDCOMMAND_H
#define ENDCOMMAND_H

#include "../Command.h"

// Команда транслятора End
class EndCommand : public Command
{
public:
    EndCommand(const CommandData &data, LabelContainer *labelContainer, ErrorContainer *errorContainer,
               Listing *listing);

    virtual size_t size() const override; // Возвращает размер

protected:
    virtual ByteArray writeExecutable(VmExecutable &vmExec, Address commandAddress) override; // Транслирует команду (вставляет Stop)

private:
    const std::size_t m_commandSize = 1; // Размер Stop
    const ProcessorCommandCode m_stopCommandCode = ProcessorCommandCode::Stop;

    Address m_ip;

    void parseArg(); // Парсит аргумент

    bool checkArgCorrectness() const; // Проверяет аргумент на правильность
    bool labelExists() const; // Проверяет, существует ли метка (из аргумента)
    Address getArgAddress() const; // Возвращает адрес метки
};

#endif //ENDCOMMAND_H
