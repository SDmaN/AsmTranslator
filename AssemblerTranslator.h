#ifndef ASSEMBLERTRANSLATOR_H
#define ASSEMBLERTRANSLATOR_H

#include "VmExecutable.h"
#include "Commands/LabelContainer.h"
#include "Commands/Command.h"

// Двупроходной транслятор с ассемблера
class AssemblerTranslator
{
public:
    AssemblerTranslator();
    VmExecutable translate(std::vector<CommandData> &operators); // Транслирует операторы в модуль

private:
    //CommandCreator m_commandCreator;

    LabelContainer m_labels; // Хранилище меток
    std::vector<CommandPointer> m_commands;

    CommandPointer createCommand(const CommandData &opData, Address address) const; // Создает команду

    bool firstPass(const std::vector<CommandData> &operators); // Первый проход
    VmExecutable secondPass(); // Второй проход
};

#endif //ASSEMBLERTRANSLATOR_H
