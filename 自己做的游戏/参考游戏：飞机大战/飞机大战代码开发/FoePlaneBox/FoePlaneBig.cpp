#include"FoePlaneBig.h"
#include"../resource.h"
#include"../GameConfig/GameConfig.h"
CFoePlaneBig::CFoePlaneBig(){}
 CFoePlaneBig::~CFoePlaneBig(){}

void CFoePlaneBig::InitFoePlane( HINSTANCE hIns)
{
	//在Planeapp.cpp中的创建消息里就已经写好了rand的种子：srand((unsigned int)time(NULL));
	m_foePlane = ::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_FOEPLANEBIG));
	m_nBlood = BLOOD_FOEPLANEBIG;//把血量也做成配置
	m_nx = rand()%(MAPSIZE_BACKGROUND_WIDTH-MAPSIZE_FOEPLANEBIG_WIDTH);
	m_ny =-MAPSIZE_FOEPLANEBIG_HEIGH;
	m_showId = 3;//小中大飞机分别是1 2 3
}
void CFoePlaneBig::ShowFoePlane(HDC hdc, HDC compHdc)
{
	::SelectObject(compHdc,m_foePlane);//贴图！！
	//这里传的hdc参数其实是缓冲DC了,贴图也是从图片左上角开始算的！！
	::BitBlt(hdc,m_nx,m_ny,MAPSIZE_BACKGROUND_WIDTH,MAPSIZE_FOEPLANEBIG_HEIGH,
		compHdc,0,(3-m_showId)*MAPSIZE_FOEPLANEBIG_HEIGH,SRCAND);
}
BOOL CFoePlaneBig::IsHitGunner(CGunner *pGun)
{
	//把炮弹当成一个点，这个点位于子弹头的位置，如果这个点在这个飞机所包含的矩形范围内，
	//就返回ture，也就是敌机真的撞击到了子弹，注意下面的m_nx、m_ny都是敌机的xy，pGun->m_ny等才是子弹的

	int x = pGun->m_nx + MAPSIZE_GUUNER_WIDTH/2;
	if (m_nx<=x    &&   x<= m_nx+MAPSIZE_FOEPLANEBIG_WIDTH    &&   
		m_ny<=pGun->m_ny   &&   pGun->m_ny <=m_ny+MAPSIZE_FOEPLANEBIG_HEIGH)
	{
		return TRUE;
	}
	return FALSE;
}
BOOL CFoePlaneBig::IsHitPlayer(CPlayerPlane &player)
{
	//三角形中间那个点在敌机这个矩形范围内的话，返回ture
	int x1 = player.m_nx + MAPSIZE_PLAYERPLANE_WIDTH/2;
	if (m_nx<=x1    &&   x1<= m_nx+MAPSIZE_FOEPLANEBIG_WIDTH    &&   
		m_ny<=player.m_ny   &&   player.m_ny <=m_ny+MAPSIZE_FOEPLANEBIG_HEIGH)
	{
		return TRUE;
	}
	//三角形左下角那个点在敌机这个矩形范围内的话，返回ture
	//左下角的点，x不变，y变为y+2/3我方飞机高度；因为往下是y增加
	int y1 = player.m_ny + MAPSIZE_PLAYERPLANE_HEIGH*2/3;
	if (m_nx<=player.m_nx    &&   player.m_nx<= m_nx+MAPSIZE_FOEPLANEBIG_WIDTH    &&   
		m_ny<=y1   &&   y1 <=m_ny+MAPSIZE_FOEPLANEBIG_HEIGH)
	{
		return TRUE;
	}
	//三角形右下角那个点在敌机这个矩形范围内的话，返回ture
	//右下角的点，y就是上面计算出来的y1，x变为m_nx+我方飞机整个宽度
	int x2 = player.m_nx+MAPSIZE_PLAYERPLANE_WIDTH;
	if (m_nx<=x2    &&   x2<= m_nx+MAPSIZE_FOEPLANEBIG_WIDTH    &&   
		m_ny<=y1   &&   y1 <=m_ny+MAPSIZE_FOEPLANEBIG_HEIGH)
	{
		return TRUE;
	}
	return FALSE;
}