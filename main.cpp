#include <iostream>

#include "AssemblerParser.h"

using namespace std;


int main(int argc, char *argv[])
{
    return 0;



    bool hasErrors;

    AssemblerParser parser;
    auto parsed = parser.parse("123.txt", &hasErrors);

    cout << "has errors: " << hasErrors << endl << endl;

    for(auto &x : parsed)
    {
        cout << x.lineIndex << ":" << endl;
        cout << "source: " << x.sourceLine << endl;
        cout << "label: " << x.label << endl;
        cout << "code: " << x.code << endl;
        cout << "arg: " << x.arg << endl;
        cout << "comment: " << x.comment << endl;

        cout << "errors: " << endl;

        for(auto &e : x.errors.errors())
            cout << e << endl;

        cout << endl;
        cout << endl;
    }

    return 0;
}