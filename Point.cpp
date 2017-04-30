/*
 * wb: 1 true;
 *     0 false;
 */

class Qitem;

class Point
{
    public:
        int  x = 0;
        int  y = 0;
        int  z = 0;
        int  value = 0;
        int  wb[10];
        Qitem *q;

        Point(int,int,int);
        void setValue(int);
        int  getValue();
        int  comput();
        int  check(int);
};

Point::Point(int x, int y, int v)
{
    memset(wb, 0, sizeof(wb));
    setValue(v);
    this->x = x;
    this->y = y;
    this->z = x/3*3 + y/3;
}

void Point::setValue(int v)
{
    value = v;
}

int Point::getValue()
{
    return value;
}
