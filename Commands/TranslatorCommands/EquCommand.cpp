#include "EquCommand.h"
#include "../LabelContainer.h"
#include "../../Utils/MathExpressionCalculator.h"
#include "../../ErrorsHandling/Exceptions/ArgumentIncorrectException.h"
#include "../../ErrorsHandling/Exceptions/LabelNotExistsException.h"

EquCommand::EquCommand(const CommandData &data, Address commandAddress, LabelContainer *labelContainer)
        : Command(data, commandAddress, labelContainer)
{
    updateLabelPurpose();
}

size_t EquCommand::size() const
{
    return EquSize;
}

void EquCommand::translate(VmExecutable &vmExec)
{
}

void EquCommand::updateLabelPurpose()
{
    // Вычислит константу
    MathExpressionCalculator exprCalculator(labelContainer(), address());

    try
    {
        CommandData cmdData = data();

        // Метка уже добавлена в таблицу базовым классом
        // Нужно изменить её назначение с Address на Constant
        labelContainer()->updateLabel(cmdData.label, LabelData::AddressConstant,
                                      static_cast<unsigned short>(exprCalculator.evaluate(cmdData.arg)));
    }
    catch(ArgumentIncorrectException &ex)
    {
        handleError(CompillerError::ArgumentIncorrect);
    }
    catch(LabelNotExistsException &ex)
    {
        handleError(CompillerError::LabelNotFound);
    }
}
