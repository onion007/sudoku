/**
 * Sudoku
 *
 * author: heconghua
 */
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>

#include "Qizz.cpp"

using namespace std;

void usage()
{
    cout << "sudoku -i <inputfile> -o <outputfile>" << endl;
    exit(255);
}

int main(int argc, char *argv[])
{
    const char *inputFile = NULL;
    const char *outputFile = NULL;

    int ch;
    while(( ch = getopt(argc, argv, "i:o:")) != -1 )
    {
        switch(ch)
        {
            case 'i':
                inputFile = optarg;
                break;
            case 'o':
                outputFile = optarg;
                break;
            default:
                usage();
        }
    }
    if( NULL == inputFile || NULL == outputFile )
    {
        usage();
    }

    Qizz q(inputFile);
    q.Run();
    q.Submit(outputFile);

    return 0;
}
