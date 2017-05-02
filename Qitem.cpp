#include <fstream>
#include <list>
#include <iostream>

#include "Point.cpp"

using namespace std;

class Qitem
{
    public:
        int   tag;
        Point *board[9][9];
        int   rx[9][10];
        int   ry[9][10];
        int   rz[9][10];
        Point *tbd[81];
        int   tbdc = 0;
        int   total = 0;
        list<string *> result;

        Qitem(int);
        void bset(int,int,int);
        void run();
        void showBoard();
        void hch1(int);
        void setRule(Point*,int,int);
        int  check(Point*,int);
        void showRule();
        void showTBD();
        void saveResult();
        void showResult();
        void flushResult(FILE *);
        //void flushResult(fstream);
};

void Qitem::showResult()
{
    list<string *>::iterator iter;
    string *s = NULL;
    for(iter = result.begin(); iter != result.end();)
    {
        list<string *>::iterator t = iter++;
        s = *t;
        cout << *s;
    }
}

//void Qitem::flushResult(fstream fin)
void Qitem::flushResult(FILE *fp)
{
    list<string *>::iterator iter;
    string *s = NULL;
    for(iter = result.begin(); iter != result.end();)
    {
        list<string *>::iterator t = iter++;
        s = *t;
        //cout << *s;
        fprintf(fp, "%s", s->c_str());
    }
}

void Qitem::saveResult()
{
    char s[20];
    sprintf(s, "[%d,%d]\n", tag, total+1);
    result.push_back(new string(s));
    for(int i=0;i<9;i++)
    {
        sprintf(s, "%d,%d,%d,%d,%d,%d,%d,%d,%d\n",
                board[i][0]->value,
                board[i][1]->value,
                board[i][2]->value,
                board[i][3]->value,
                board[i][4]->value,
                board[i][5]->value,
                board[i][6]->value,
                board[i][7]->value,
                board[i][8]->value);
        result.push_back(new string(s));
    }
    total++;
}

void Qitem::showTBD()
{
    for(int i=0;i<tbdc;i++)
    {
        cout << "#" << i << "  :";
        cout << "x=" << tbd[i]->x;
        cout << ", y=" << tbd[i]->y;
        cout << ", z=" << tbd[i]->z;
        cout << endl;
    }
}

void Qitem::showRule()
{
    cout << "======== rx ======= ";
    cout << "======== ry ======= ";
    cout << "======== rz ========" << endl;
    int f=0;
    for(int i=0;i<9;i++)
    {
        if(f==0)
        {
          for(int k=0;k<3;k++)
          {
            for(int j=1;j<10;j++)
                cout << "|" << j;
            if(f<3)
                cout << "| ";
            f++;
          }
          cout << endl;
          cout << "-----------------------------------------------------------"<<endl;
        }
        for(int j=1;j<10;j++)
            cout << "|" << rx[i][j];
        cout << "| ";
        for(int j=1;j<10;j++)
            cout << "|" << ry[i][j];
        cout << "| ";
        for(int j=1;j<10;j++)
            cout << "|" << rz[i][j];
        cout << "|" << endl;
    }
}

Qitem::Qitem(int tag)
{
    memset(rx, 0, sizeof(rx));
    memset(ry, 0, sizeof(ry));
    memset(rz, 0, sizeof(rz));
    this->tag = tag;
}

void Qitem::bset(int x, int y, int value)
{
    board[x][y] = new Point(x, y, value);
    board[x][y]->q = this;
    if(value)
    {
        setRule(board[x][y], value, 1);
    }
    else
    {
        tbd[tbdc] = board[x][y];
        tbdc++;
    }
}

void Qitem::setRule(Point *p, int num, int v)
{
    rx[p->x][num] = v;
    ry[p->y][num] = v;
    rz[p->z][num] = v;
}

int Qitem::check(Point *p, int v)
{
    if( rx[p->x][v] || ry[p->y][v] || rz[p->z][v] )
    {
        return 0;
    }
    return 1;
}

void Qitem::hch1(int c)
{
    if( c == tbdc )
    {
        saveResult();
        return;
    }
    for(int i=1;i<10;i++)
    {
        if(check(tbd[c], i))
        {
            tbd[c]->setValue(i);
            setRule(tbd[c], i, 1);

            hch1(c+1);

            tbd[c]->setValue(0);
            setRule(tbd[c], i, 0);
        }
    }
}

void Qitem::showBoard()
{
    cout << "============================" << endl;
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            cout << "|" << board[i][j]->value;
        }
        cout << "|" << endl;
    }
}

void Qitem::run(){
    //showBoard();
    hch1(0);
    //cout << "total=" << total << endl;
}
