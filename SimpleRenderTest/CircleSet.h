#ifndef __CIRCLESET_H__
#define __CIRCLESET_H__

#include"Circle.h"

class CircleSet
{
public:
	//ͨ�����캯���Ӳ����趨���Ӹ���
	CircleSet(int num);
	~CircleSet();

	void Update();
	void Render(HDC hdc);
private:
	int particleCount;	//��¼���Ӹ���
	CircleClass* p;
};

#endif
