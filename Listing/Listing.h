#ifndef LISTINGMAKER_H
#define LISTINGMAKER_H

#include <string>
#include "../TypeDefines.h"

class CommandData;

class Listing
{
public:
    void clear();
    void appendLine(const CommandData &cmdData, Address commandAddress, const ByteArray &translatedBytes);

    const std::string &listingText() const;

private:
    std::string m_listingText;
};

#endif //LISTINGMAKER_H
