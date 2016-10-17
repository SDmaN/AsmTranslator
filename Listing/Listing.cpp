#include <sstream>
#include <iomanip>

#include "Listing.h"
#include "../Commands/CommandData.h"

void Listing::clear()
{
    m_listingText.clear();
}

void Listing::generate(const std::vector<CommandPointer> &commands)
{
    for(auto &command : commands)
        appendLine(command);
}

void Listing::appendLine(const CommandPointer &command)
{
    std::stringstream ss;

    CommandData cmdData = command->data();

    ss << cmdData.lineIndex << ": ";

    auto oldFlags = ss.flags();

    ss << std::hex << command->address() << '\t';

    for(auto b : command->translatedBytes())
        ss << static_cast<short>(b);

    ss.flags(oldFlags);

    ss << "\t\t";
    ss << cmdData.sourceLine << std::endl;

    for(auto &error : cmdData.errors.errors())
        ss << error << std::endl;

    m_listingText += ss.str();
}

std::ostream &operator<<(std::ostream &stream, const Listing &listing)
{
    stream << listing.m_listingText;
    return stream;
}
