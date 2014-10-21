#include"CircleSet.h"

CircleSet::CircleSet(int num)
{
	p = nullptr;
	p = new CircleClass[num];
	particleCount = num;
}

CircleSet::~CircleSet()
{
	if(p != nullptr)
	{
		delete [] p;
		p = nullptr;
	}
}

void CircleSet::Update()
{
	for(int i=0;i<particleCount;i++)
	{
		p[i].Update();
	}
}

void CircleSet::Render(HDC hdc)
{
	for(int i=0;i<particleCount;i++)
	{
		p[i].Render(hdc);
	}
}
