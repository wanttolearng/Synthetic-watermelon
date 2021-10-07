#include"BackGround.h"
#include"../resource.h"
#include"../GameConfig/GameConfig.h"
CBackGround::CBackGround()
{
	m_backDown = NULL;
	m_backUp = NULL;
	m_nx = 0;
	m_ny = 0;
}
CBackGround::~CBackGround()
{
	m_nx = 0;
	m_ny = 0;

	::DeleteObject(m_backDown);
	::DeleteObject(m_backUp);
	m_backDown = NULL;
	m_backUp = NULL;
}
void CBackGround::InitBackGround(int x, int y, HINSTANCE hIns)
{
	m_nx = x;
	m_ny = y;

	m_backDown = ::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_BACKGROUND));
	m_backUp =	  ::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_BACKGROUND));
}
void CBackGround::ShowBackGround(HDC hdc, HDC compHdc)
{
	::SelectObject(compHdc,m_backDown);
	::BitBlt(hdc,m_nx,m_ny,MAPSIZE_BACKGROUND_WIDTH,MAPSIZE_BACKGROUND_HEIGH,
		compHdc,0,0,SRCCOPY);

	::SelectObject(compHdc,m_backUp);
	::BitBlt(hdc,m_nx,m_ny-MAPSIZE_BACKGROUND_HEIGH,MAPSIZE_BACKGROUND_WIDTH,MAPSIZE_BACKGROUND_HEIGH,
		compHdc,0,0,SRCCOPY);
}

void CBackGround::MoveBackGround(int step)
{
	if (m_ny + step  >= 550)
	{
		m_ny =0;
	}
	else
	{
		m_ny+=step;
	}
}
