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
    void generate(const std::vector<CommandPointer> &commands);

    friend std::ostream &operator<<(std::ostream &stream, const Listing &listing);

private:
    std::string m_listingText;
    void appendLine(const CommandData &cmdData, Address commandAddress, const ByteArray &translatedBytes);
};

#endif //LISTINGMAKER_H
