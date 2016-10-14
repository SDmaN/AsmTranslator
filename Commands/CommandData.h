#ifndef COMMANDDATA_H
#define COMMANDDATA_H

#include <string>

// Содержит разобранную команду ассемблера
struct CommandData
{
    std::string sourceLine;
    std::size_t lineIndex;
    std::string label;
    std::string code;
    std::string arg;
    std::string comment;

    CommandData();

    bool empty() const;
};

#endif //COMMANDDATA_H
