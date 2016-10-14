#include <sstream>

#include "Listing.h"
#include "../Commands/CommandData.h"

void Listing::clear()
{
    m_listingText.clear();
}

void Listing::appendLine(const CommandData &cmdData, Address commandAddress, const ByteArray &translatedBytes)
{
    if(!cmdData.empty())
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
}

const std::string &Listing::listingText() const
{
    return m_listingText;
}
