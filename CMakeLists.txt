cmake_minimum_required(VERSION 3.6)
project(AsmTranslator)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp ErrorsHandling/CompillerError.h ErrorsHandling/ErrorsContainer.cpp ErrorsHandling/ErrorsContainer.h ErrorsHandling/Error.cpp ErrorsHandling/Error.h ErrorsHandling/Exceptions/FileNotFoundException.cpp ErrorsHandling/Exceptions/FileNotFoundException.h AssemblerParser.h AssemblerParser.cpp Commands/CommandData.h Commands/CommandData.cpp TypeDefines.h Commands/ProcessorCommandCode.h Commands/Command.cpp Commands/Command.h Commands/LabelContainer.cpp Commands/LabelContainer.h AssemblerTranslator.cpp AssemblerTranslator.h VmExecutable.cpp VmExecutable.h Commands/Factories/CommandFactory.h Commands/Factories/CommandsCreator.cpp Commands/Factories/CommandsCreator.h Commands/ProcessorCommands/ShortProcessorCommand.cpp Commands/ProcessorCommands/ShortProcessorCommand.h Commands/ProcessorCommands/ProcessorCommand.cpp Commands/ProcessorCommands/ProcessorCommand.h Commands/ProcessorCommands/LongProcessorCommand.cpp Commands/ProcessorCommands/LongProcessorCommand.h Utils/Utils.h Commands/TranslatorCommands/AllocateCommand.h Commands/TranslatorCommands/EndCommand.cpp Commands/TranslatorCommands/EndCommand.h Listing/Listing.cpp Listing/Listing.h Commands/UnknownCommand.cpp Commands/UnknownCommand.h Commands/LabelCommand.cpp Commands/LabelCommand.h Commands/EmptyCommand.cpp Commands/EmptyCommand.h)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
add_executable(AsmTranslator ${SOURCE_FILES})