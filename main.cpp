#include <iostream>
#include <fstream>

#include "AssemblerParser.h"
#include "AssemblerTranslator.h"
#include "Listing/Listing.h"
#include "ErrorsHandling/ErrorsOut.h"
#include "ErrorsHandling/Exceptions/FileNotFoundException.h"
#include "ErrorsHandling/Exceptions/CommandLineParameterNotExists.h"

using namespace std;

// Строки
const string fileNotFound = "Не удалось открыть файл:";
const string execExtension = "vmexec";
const string errorsFileName = "errors.txt";
const string listingFileName = "listing.txt";

// Преобразует массив аргументов cmd к вектору
template<typename IteratorType>
vector<string> getCommandLineArguments(IteratorType begin, IteratorType end);
string getSourceFileName(const vector<string> &commandLineArgs); // Вытаскивает из аргументов исходный файл
string getExecFileName(const string &sourceFileName); // На основе исходного файла, составляет выходной (заменяет расширение)
bool listingArgExists(const vector<string> &commandLineArgs); // Проверяет, есть ли среди аргментов листинг

int main(int argc, char *argv[])
{
    ofstream errorsFile;
    vector<string> commandLineArgs = getCommandLineArguments(argv, argv + argc);

    try
    {
        if(commandLineArgs.size() < 2)
            throw CommandLineParameterNotExists("Недостаточно параметров.");

        string sourceFileName = getSourceFileName(commandLineArgs);
        AssemblerParser parser;
        vector<CommandData> cmdsData = parser.parse(sourceFileName);
        AssemblerTranslator translator;
        VmExecutable vmExec = translator.translate(cmdsData);

        if(!vmExec.empty())
        {
            string execFileName = getExecFileName(sourceFileName);
            vmExec.write(execFileName);
        }

        ErrorsOut eo;
        eo.collectErrors(translator.translatedCommands());

        if(!eo.empty())
        {
            errorsFile.open(errorsFileName);
            errorsFile << eo;
        }

        if(listingArgExists(commandLineArgs))
        {
            Listing listing;
            listing.generate(translator.translatedCommands());

            ofstream listingFile(listingFileName);

            if(!listingFile.is_open())
                throw FileNotFoundException("Не удалось открыть файл листинга");

            listingFile << listing;
        }
    }
    catch(exception &ex)
    {
        errorsFile.open(errorsFileName);
        errorsFile << ex.what() << endl;
    }

    return 0;
}

template<typename IteratorType>
vector<string> getCommandLineArguments(IteratorType begin, IteratorType end)
{
    return vector<string>(begin, end);
}

string getSourceFileName(const vector<string> &commandLineArgs)
{
    return commandLineArgs[1];
}

string getExecFileName(const string &sourceFileName)
{
    std::size_t pos = sourceFileName.find('.');

    if(pos != string::npos)
        return sourceFileName.substr(0, pos) + '.' + execExtension;

    return sourceFileName + '.' + execExtension;
}

bool listingArgExists(const vector<string> &commandLineArgs)
{
    for(int i = 2; i < commandLineArgs.size(); ++i)
    {
        if(commandLineArgs[i] == "-l")
            return true;
    }

    return false;
}