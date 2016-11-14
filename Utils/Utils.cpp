#include "Utils.h"

void removeSpaces(std::string &s)
{
    s.erase(std::remove(std::begin(s), std::end(s), ' '), std::end(s));
}