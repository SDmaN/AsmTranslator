#include "ShortProcessorCommand.h"

ShortProcessorCommand::ShortProcessorCommand(const CommandData &data, Address commandAddress, LabelContainer *labelContainer)
        : ProcessorCommand(data, commandAddress, labelContainer)
{
}

size_t ShortProcessorCommand::size() const
{
    return ShortCommandSize;
}

void ShortProcessorCommand::translate(VmExecutable &vmExec)
{
    ByteArray result; // Результат трансляции в байтах

    // Если нет ошибки, то записываем байт команды
    if(!hasError())
    {
        result = { static_cast<Byte>(code()) };
        vmExec.appendBytes(result);
    }

    // Нужно, чтобы потом транслируемые байты можно было получить из команды (для листинга)
    setTranslatedBytes(result);
}
