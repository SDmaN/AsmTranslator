#ifndef ENDCOMMAND_H
#define ENDCOMMAND_H

#include "../Command.h"

// Команда транслятора End
class EndCommand : public Command
{
public:
    EndCommand(const CommandData &data, Address commandAddress, LabelContainer *labelContainer);

    virtual size_t size() const override; // Возвращает размер
    virtual void translate(VmExecutable &vmExec) override; // Транслирует команду (вставляет Stop)

private:
    const std::size_t EndComandSize = 0; // Размер директивы
    Address m_ip; // Адрес старта программы

    void parseArg(); // Парсит аргумент

    void checkArgCorrectness() const; // Проверяет аргумент на правильность
    Address getArgAddress() const; // Возвращает адрес метки. Если метка указывает на константу, выбрасывает ArgumentIncorrect
};

#endif //ENDCOMMAND_H
