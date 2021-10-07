#pragma once
#include<Windows.h>
class CBackGround{
public:

	 HBITMAP	m_backDown;
	 HBITMAP	m_backUp;
	 int				m_nx;
	 int				m_ny;
public:
	CBackGround();
	~CBackGround();
public:
	void InitBackGround(int x, int y, HINSTANCE hIns);
	void MoveBackGround(int step);
	void ShowBackGround(HDC hdc, HDC compHdc);
};