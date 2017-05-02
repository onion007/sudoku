#include <fstream>
#include <list>
#include <iostream>

#include "Qitem.cpp"

using namespace std;

class Qizz
{
    public:
        list<Qitem *> qlist;

        Qizz(const char *inputFile);
        void Run();
        int Submit(const char *outputFile);
};

#define YGFORMAT "%d,%d,%d,%d,%d,%d,%d,%d,%d"
Qizz::Qizz(const char *inputFile)
{
    ifstream fin(inputFile);
    string s;
    int tag, i;
    Qitem *q = NULL;
    int t[9];
    while( getline(fin, s) )
    {
        if( sscanf(s.c_str(), "[%d]", &tag) )
        {
            if( q != NULL )
            {
                // add q into Queue
                qlist.push_back(q);
            }
            q = new Qitem(tag);
            i = 0;
        }
        if( sscanf(s.c_str(), YGFORMAT, &t[0],
                                        &t[1],
                                        &t[2],
                                        &t[3],
                                        &t[4],
                                        &t[5],
                                        &t[6],
                                        &t[7],
                                        &t[8]))
        {
            q->bset(i, 0, t[0]);
            q->bset(i, 1, t[1]);
            q->bset(i, 2, t[2]);
            q->bset(i, 3, t[3]);
            q->bset(i, 4, t[4]);
            q->bset(i, 5, t[5]);
            q->bset(i, 6, t[6]);
            q->bset(i, 7, t[7]);
            q->bset(i, 8, t[8]);
            i++;
        }
    }
    qlist.push_back(q);
}

void Qizz::Run()
{
    list<Qitem *>::iterator iter;
    Qitem *q = NULL;
    for(iter = qlist.begin(); iter != qlist.end();)
    {
        list<Qitem *>::iterator t = iter++;
        q = *t;
        q->run();
    }
}

int Qizz::Submit(const char *outputFile)
{
    FILE *fp;
    fp = fopen(outputFile, "w");
    list<Qitem *>::iterator iter;
    Qitem *q = NULL;
    for(iter = qlist.begin(); iter != qlist.end();)
    {
        list<Qitem *>::iterator t = iter++;
        q = *t;
        q->flushResult(fp);
    }
    fclose(fp);
}
