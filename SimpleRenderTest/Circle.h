#ifndef __CIRCLE_H__
#define __CIRCLE_H__

#include<windows.h>
#include<cstdio>
#include<cstdlib>

#define RANDOMF(a) (a * ((float)rand()/RAND_MAX))

class CircleClass
{
public:
	CircleClass();
	~CircleClass();

	void Update();//Update logical data.
	void Render(HDC hdc);//Do the drawing work.
private:
	int size;
	unsigned char r,g,b;
	float x,y;
	float dx,dy;
};

#endif
