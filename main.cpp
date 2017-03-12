#include <iostream>
#include <fstream>
#include "AssemblerParser.h"
#include "AssemblerTranslator.h"
#include "ErrorsHandling/ErrorsOut.h"
#include "Listing/Listing.h"
#include "ErrorsHandling/Exceptions/FileNotFoundException.h"

using namespace std;

const string execExtension = "vmexec";

string
getExecFileName(const string &sourceFileName); // На основе исходного файла, составляет выходной (заменяет расширение)

int main(int argc, char *argv[])
{
    if(argc >= 2)
    {
        string inFilename = argv[1];

        try
        {
            AssemblerParser parser;

            auto cmdsData = parser.parse(inFilename);

            AssemblerTranslator translator;
            VmExecutable vmExec = translator.translate(cmdsData);

            if(!vmExec.empty())
            {
                string execFilename = getExecFileName(inFilename);
                vmExec.write(execFilename);
            }

            Listing listing;
            listing.generate(translator.translatedCommands());

            ofstream listtingFile("listing.txt");

            if(!listtingFile.is_open())
            {
                throw FileNotFoundException("Не удалось открыть файл листинга");
            }

            listtingFile << listing;
            listtingFile.close();

        }
        catch(exception &ex)
        {
            cout << ex.what() << endl;
        }
    }
    else
    {
        cout << "Command argument no exist.";
    }

    return 0;
}

string getExecFileName(const string &sourceFileName)
{
    std::size_t pos = sourceFileName.find('.');

    if(pos != string::npos)
    {
        return sourceFileName.substr(0, pos) + '.' + execExtension;
    }

    return sourceFileName + '.' + execExtension;
}