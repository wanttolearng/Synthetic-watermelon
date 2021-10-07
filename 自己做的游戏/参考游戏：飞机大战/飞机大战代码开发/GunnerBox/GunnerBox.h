#pragma once
#include<list>
using namespace std;
#include"Gunner.h"
class CGunnerBox
{
public:
	list<CGunner *>m_lstGunner;
public:
	CGunnerBox();
	~CGunnerBox();
public:
	void ShowAllGunner(HDC hdc, HDC compHdc);
	void MoveAllGunner(int step);
};

