#pragma once
#include<Windows.h>
class CGunner
{
public:
	HBITMAP m_hGun;
	int			m_nx;
	int			m_ny;

public:
	CGunner();
	~CGunner();
public:
	 void InitGunner(int x, int y, HINSTANCE hIns);
	 void ShowGunner(HDC hdc, HDC compHdc);
	 void MoveGunner(int step);
};

