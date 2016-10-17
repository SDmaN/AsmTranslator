#ifndef ERRORSOUT_H
#define ERRORSOUT_H

#include <vector>
#include <ostream>

#include "../Commands/Command.h"
#include "Error.h"

class ErrorsOut
{
public:
    void collectErrors(const std::vector<CommandPointer> &commands);
    bool empty() const;

    friend std::ostream &operator<<(std::ostream &stream, const ErrorsOut &eo);

private:
    std::vector<Error> m_errors;
};

#endif //ERRORSOUT_H
