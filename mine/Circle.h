#ifndef __CIRCLE_H__
#define __CIRCLE_H__

#include<windows.h>
#include<cstdio>
#include<cstdlib>

#define RANDOMF(a) (a * ((float)rand()/RAND_MAX))

class CircleClass()
{
public:
    CircleClass();
    ~CircleClass();

    Update();
    Render(HDC hdc);
private:
    int num;
    int basicarea;
    double x,y;
    unsigned char r,g,b;
};


#endif
