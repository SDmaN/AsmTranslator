#include "ErrorsOut.h"

void ErrorsOut::collectErrors(const std::vector<CommandPointer> &commands)
{
    for(auto &c : commands)
    {
        CommandData cmdData = c->data();

        if(!cmdData.errors.empty())
        {
            m_errors.insert(std::begin(m_errors), std::begin(cmdData.errors.errors()),
                            std::end(cmdData.errors.errors()));
        }
    }
}

bool ErrorsOut::empty() const
{
    return m_errors.empty();
}

std::ostream &operator<<(std::ostream &stream, const ErrorsOut &eo)
{
    for(auto &error : eo.m_errors)
        stream << error << std::endl;

    return stream;
}
