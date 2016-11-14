#ifndef LISTINGMAKER_H
#define LISTINGMAKER_H

#include <string>
#include <ostream>

#include "../Commands/Command.h"
#include "../TypeDefines.h"

class CommandData;

// Класс листинга программы
class Listing
{
public:
    void clear(); // Очищает листинг
    void generate(const std::vector<CommandPointer> &commands); // Формирует листинг на основе команд

    // Вывод листинга в поток
    friend std::ostream &operator<<(std::ostream &stream, const Listing &listing);

private:
    std::string m_listingText; // Текст листинга
    void appendLine(const CommandPointer &command); // Добавляет очередную строку (команду) к листингу
};

#endif //LISTINGMAKER_H
