#include"PlayerPlane.h"
#include"../resource.h"
#include"../GameConfig/GameConfig.h"
CPlayerPlane::CPlayerPlane()
{
	 m_player = NULL;
	 m_nx = 0;
	 m_ny = 0;
}
CPlayerPlane::~CPlayerPlane()
{
	::DeleteObject(m_player);
	m_player = NULL;
	 m_nx = 0;
	 m_ny = 0;
}
void CPlayerPlane::InitPlayerPlane(int x, int y, HINSTANCE hIns)
{
	m_nx = x;
	m_ny = y;
	m_player = ::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_PLAYERPLANE));
}
void CPlayerPlane::ShowPlayerPlane(HDC hdc, HDC compHdc)
{
	::SelectObject(compHdc,m_player);
	::BitBlt(hdc,m_nx,m_ny,MAPSIZE_PLAYERPLANE_WIDTH,MAPSIZE_PLAYERPLANE_HEIGH,
		compHdc,0,0,SRCAND);
}
void CPlayerPlane::MovePlayerPlane(int direct, int step)
{
	switch (direct)
	{
	case VK_LEFT:
		{
			if(	m_nx - step <= 0)		
				m_nx =0;
			else
				m_nx-=step;
		}
		break;
	case VK_RIGHT:
		{
			//我们算的是飞机左上角的坐标点，这四个方向都是这样
			if(	m_nx + step >= (MAPSIZE_BACKGROUND_WIDTH-MAPSIZE_PLAYERPLANE_WIDTH))		
				m_nx =(MAPSIZE_BACKGROUND_WIDTH-MAPSIZE_PLAYERPLANE_WIDTH);
			else
				m_nx+=step;
		}
		break;
	case VK_UP:
		{
			if(	m_ny - step <= 0)		
				m_ny =0;
			else
				m_ny-=step;
		}
		break;
	case VK_DOWN:
		{
			if(	m_ny + step >= (MAPSIZE_BACKGROUND_HEIGH-MAPSIZE_PLAYERPLANE_HEIGH))		
				m_ny =(MAPSIZE_BACKGROUND_HEIGH-MAPSIZE_PLAYERPLANE_HEIGH);
			else
				m_ny+=step;
		}
		break;
	}
}
CGunner *CPlayerPlane::SendGunner(HINSTANCE hIns)
{
	CGunner *pGun = new CGunner;
	pGun->InitGunner(		(m_nx + (MAPSIZE_PLAYERPLANE_WIDTH - MAPSIZE_GUUNER_WIDTH)/2),
		m_ny - MAPSIZE_GUUNER_HEIGH,
		hIns);
	return pGun;//初始化后返回这个炮弹就可以了
}