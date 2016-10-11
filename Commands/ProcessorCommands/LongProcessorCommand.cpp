#include <regex>

#include "LongProcessorCommand.h"
#include "../LabelContainer.h"
#include "../../Utils/Utils.h"

LongProcessorCommand::LongProcessorCommand(const CommandData &data, LabelContainer *labelContainer,
                                           ErrorContainer *errorContainer)
        : ProcessorCommand(data, labelContainer, errorContainer)
{
}

size_t LongProcessorCommand::size() const
{
    return LongCommandSize;
}

ByteArray LongProcessorCommand::translate()
{
    if(!hasError())
    {
        if(!checkArgCorrectness())
            handleError(CompillerError::ArgumentIncorrect);

        else if(!labelExists())
            handleError(CompillerError::LabelNotFound);

        else
        {
            Address argAddress = getArgAddress();
            ByteArray addressBytes = addressToBytes(argAddress);

            ByteArray result = { static_cast<Byte> (code()), 0, 0 };

            for(Byte b : addressBytes)
                result.push_back(b);
        }
    }

    return ByteArray();
}

bool LongProcessorCommand::checkArgCorrectness() const
{
    const std::regex regEx("[a-zA-Z_]\\w+");
    return std::regex_match(data().arg, regEx);
}

bool LongProcessorCommand::labelExists() const
{
    return labelContainer()->contains(data().arg);
}

Address LongProcessorCommand::getArgAddress() const
{
    return labelContainer()->address(data().arg);
}
