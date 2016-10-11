#include "AssemblerTranslator.h"

AssemblerTranslator::AssemblerTranslator()
{
}

VmExecutable AssemblerTranslator::translate(std::vector<CommandData> &operators)
{
    return VmExecutable();
}

CommandPointer AssemblerTranslator::createCommand(const CommandData &opData, Address address) const
{
    return CommandPointer();
}

bool AssemblerTranslator::firstPass(const std::vector<CommandData> &operators)
{
    return false;
}

VmExecutable AssemblerTranslator::secondPass()
{
    return VmExecutable();
}
