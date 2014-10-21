#include"Circle.h"

CircleClass::CircleClass()
{
    x=random(1366);
    y=random(768);
    r=rand()%255;
    g=rand()%255;
    b=rand()%255;
    basicarea=rand()%3+3;
    num=rand()%200+300;
    for(int i=0; i<num; i++)
    {
        point pnow;
        pnow.x=x;
        pnow.y=y;
        pnow.r=r;
        pnow.g=g;
        pnow.b=b;
        pnow.time=5;
        if(i%2==1)
            pnow.area=basicarea+2;
        else
            pnow.area=basicarea-2;
        pnow.vx=rand()*11/(double)RAND_MAX-5;
        pnow.vy=rand()*11/(double)RAND_MAX-5;
        while((pnow.vx*pnow.vx+pnow.vy*pnow.vy)>25)
        {
            pnow.vx=rand()*11/(double)RAND_MAX-5;
            pnow.vy=rand()*11/(double)RAND_MAX-5;
        }
        pnow.ay=-0.2;
        vec1.push_back(pnow);
    }
}

CircleClass::~CircleClass()
{
    ;
}

CircleClass::Update()
{
    if(time)
    {
        beforex[time-1]=x;
        beforey[time-1]=y;
        time--;
    }
    else
    {
        for(int i=4;i>=0;i--)
        {
            beforex[i+1]=beforex[i];
            beforey[i+1]=beforey[i];
        }
        beforex[0]=x;
        beforey[0]=y;
    }
    x+=vx;
    vy+=ay;
    y+=vy;
}

void CircleClass::Render(HDC hdc)
{
    HBRUSH brush = CreateSolidBrush(RGB(r,g,b));
    SelectObject(hdc,brush);
    Ellipse(hdc,(x,y,x+area,y+area);
    DeleteObject(brush);
}
