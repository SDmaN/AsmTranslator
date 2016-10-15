#include <sstream>

#include "Listing.h"
#include "../Commands/CommandData.h"

void Listing::clear()
{
    m_listingText.clear();
}

void Listing::generate(const std::vector<CommandPointer> &commands)
{
    for(auto &command : commands)
        appendLine(command->data(), command->address(), command->translatedBytes());
}

void Listing::appendLine(const CommandData &cmdData, Address commandAddress, const ByteArray &translatedBytes)
{
    std::stringstream ss;

    ss << cmdData.lineIndex << ":\t";
    ss << std::hex << commandAddress << '\t';

    for(auto b : translatedBytes)
        ss << std::hex << static_cast<short>(b);

    ss << '\t';
    ss << cmdData.sourceLine << std::endl;

    m_listingText += ss.str();
}

std::ostream &operator<<(std::ostream &stream, const Listing &listing)
{
    stream << listing.m_listingText;
    return stream;
}
