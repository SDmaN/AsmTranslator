cmake_minimum_required(VERSION 3.6)
project(AsmTranslator)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp ErrorsHandling/CompillerError.h ErrorsHandling/ErrorContainer.cpp ErrorsHandling/ErrorContainer.h ErrorsHandling/Error.cpp ErrorsHandling/Error.h ErrorsHandling/Exceptions/FileNotFoundException.cpp ErrorsHandling/Exceptions/FileNotFoundException.h AssemblerParser.h AssemblerParser.cpp Commands/CommandData.h Commands/CommandData.cpp)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
add_executable(AsmTranslator ${SOURCE_FILES})