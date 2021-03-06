#ifndef ASSEMBLERTRANSLATOR_H
#define ASSEMBLERTRANSLATOR_H

#include "VmExecutable.h"
#include "Commands/LabelContainer.h"
#include "Commands/Command.h"
#include "Commands/Factories/CommandsCreator.h"
#include "ErrorsHandling/CompillerError.h"

// Двупроходной транслятор с ассемблера
class AssemblerTranslator
{
public:
    AssemblerTranslator();
    VmExecutable translate(const std::vector<CommandData> &cmdsData); // Транслирует операторы в модуль
    const std::vector<CommandPointer> &translatedCommands() const;

private:
    CommandsCreator m_commandsCreator; // Создатель команд
    LabelContainer m_labels; // Хранилище меток

    std::vector<CommandPointer> m_translatedCommands; // Команды, собранные в первом проходе

    CommandPointer createCommand(const CommandData &cmdData, Address commandAddress) const; // Создает команду
    void handleError(CommandData &cmdData, CompillerError errorCode);

    bool firstPass(const std::vector<CommandData> &cmdsData); // Первый проход
    bool secondPass(VmExecutable &vmExec); // Второй проход
};

#endif //ASSEMBLERTRANSLATOR_H
