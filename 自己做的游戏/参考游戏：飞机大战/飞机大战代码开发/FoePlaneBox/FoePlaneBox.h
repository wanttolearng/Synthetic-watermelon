#pragma once
#include<Windows.h>
#include<list>
using namespace std;
#include"FoePlane.h"

class CFoePlaneBox
{
public:
	list<CFoePlane *>m_BoomFoe;
	list<CFoePlane *>m_lstFoe;
public:
	CFoePlaneBox();
	~CFoePlaneBox();
public:
	void ShowAllFoePlane(HDC hdc, HDC compHdc);
	void MoveAllFoePlane();
	void ShowAllBoomPlane(HDC hdc, HDC compHdc);
};

