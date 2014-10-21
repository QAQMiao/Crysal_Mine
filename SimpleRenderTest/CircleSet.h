#ifndef __CIRCLESET_H__
#define __CIRCLESET_H__

#include"Circle.h"

class CircleSet
{
public:
	//通过构造函数加参数设定粒子个数
	CircleSet(int num);
	~CircleSet();

	void Update();
	void Render(HDC hdc);
private:
	int particleCount;	//记录粒子个数
	CircleClass* p;
};

#endif
