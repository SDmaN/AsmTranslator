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
    AssemblerTranslator(ErrorContainer *errorContainer);
    VmExecutable translate(const std::vector<CommandData> &cmdsData); // Транслирует операторы в модуль

private:
    CommandsCreator m_commandsCreator; // Создатель команд

    LabelContainer m_labels; // Хранилище меток
    ErrorContainer *m_errorContainer; // Хранилище ошибок

    std::vector<CommandPointer> m_commands; // Команды, собранные в первом проходе

    CommandPointer createCommand(const CommandData &cmdData) const; // Создает команду

    bool hasLabel(const CommandData &cmdData) const; // Проверяет наличие метки
    void addLabel(const std::string &label, Address address); // Добавляет метку в хранилище

    void handleError(const CommandData &cmdData, CompillerError error);

    bool firstPass(const std::vector<CommandData> &cmdsData); // Первый проход
    bool secondPass(VmExecutable &vmExec); // Второй проход
};

#endif //ASSEMBLERTRANSLATOR_H
