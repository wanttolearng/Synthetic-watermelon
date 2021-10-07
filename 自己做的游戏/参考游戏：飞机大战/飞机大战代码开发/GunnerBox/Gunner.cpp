#include"Gunner.h"
#include"../resource.h"
#include"../GameConfig/GameConfig.h"
CGunner::CGunner()
{
	m_hGun = NULL;
	m_nx = 0;
	m_ny = 0;
}
CGunner::~CGunner()
{
	::DeleteObject(m_hGun);
	m_nx = 0;
	m_ny = 0;
}
void CGunner::InitGunner(int x, int y, HINSTANCE hIns)
{
	m_nx = x;
	m_ny = y;
	m_hGun = ::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_GUNNER));
}
void CGunner::ShowGunner(HDC hdc, HDC compHdc){
	::SelectObject(compHdc,m_hGun);
	::BitBlt(hdc,m_nx,m_ny,MAPSIZE_GUUNER_WIDTH,MAPSIZE_GUUNER_HEIGH,
		compHdc,0,0,SRCAND);
}
void CGunner::MoveGunner(int step){
	m_ny-=step;
}