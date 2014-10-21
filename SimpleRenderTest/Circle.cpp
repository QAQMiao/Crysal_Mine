#include"Circle.h"

CircleClass::CircleClass()
{
    x = RANDOMF(300);
    y = RANDOMF(300);
    dx = (rand()%2 == 1 ? 1.0 : -1.0) * (RANDOMF(0.5) + .1);
    dy = (rand()%2 == 1 ? 1.0 : -1.0) * (RANDOMF(0.5) + .1);
    size = rand() % 20;
    r = rand() % 256;
    g = rand() % 256;
    b = rand() % 256;
}

CircleClass::~CircleClass()
{
    ;
}

void CircleClass::Update()
{
    //Update position
    x+=dx;
    y+=dy;
    //reflection
    if(x < size && dx < 0||((x + size > 500) && (dx > 0)))
    {
        dx = -dx;
    }
    if(y < size && dy < 0||((y + size > 500) && (dy > 0)))
    {
        dy = -dy;
    }
}

void CircleClass::Render(HDC hdc)
{
    HBRUSH brush = CreateSolidBrush(RGB(r,g,b));
    SelectObject(hdc,brush);
    Ellipse(hdc,(int)x - size,(int)y - size,(int)x + size,(int)y + size);
    DeleteObject(brush);
}
