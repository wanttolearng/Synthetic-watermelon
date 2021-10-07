#include"FoePlaneBig.h"
#include"../resource.h"
#include"../GameConfig/GameConfig.h"
CFoePlaneBig::CFoePlaneBig(){}
 CFoePlaneBig::~CFoePlaneBig(){}

void CFoePlaneBig::InitFoePlane( HINSTANCE hIns)
{
	//��Planeapp.cpp�еĴ�����Ϣ����Ѿ�д����rand�����ӣ�srand((unsigned int)time(NULL));
	m_foePlane = ::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_FOEPLANEBIG));
	m_nBlood = BLOOD_FOEPLANEBIG;//��Ѫ��Ҳ��������
	m_nx = rand()%(MAPSIZE_BACKGROUND_WIDTH-MAPSIZE_FOEPLANEBIG_WIDTH);
	m_ny =-MAPSIZE_FOEPLANEBIG_HEIGH;
	m_showId = 3;//С�д�ɻ��ֱ���1 2 3
}
void CFoePlaneBig::ShowFoePlane(HDC hdc, HDC compHdc)
{
	::SelectObject(compHdc,m_foePlane);//��ͼ����
	//���ﴫ��hdc������ʵ�ǻ���DC��,��ͼҲ�Ǵ�ͼƬ���Ͻǿ�ʼ��ģ���
	::BitBlt(hdc,m_nx,m_ny,MAPSIZE_BACKGROUND_WIDTH,MAPSIZE_FOEPLANEBIG_HEIGH,
		compHdc,0,(3-m_showId)*MAPSIZE_FOEPLANEBIG_HEIGH,SRCAND);
}
BOOL CFoePlaneBig::IsHitGunner(CGunner *pGun)
{
	//���ڵ�����һ���㣬�����λ���ӵ�ͷ��λ�ã���������������ɻ��������ľ��η�Χ�ڣ�
	//�ͷ���ture��Ҳ���ǵл����ײ�������ӵ���ע�������m_nx��m_ny���ǵл���xy��pGun->m_ny�Ȳ����ӵ���

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
	//�������м��Ǹ����ڵл�������η�Χ�ڵĻ�������ture
	int x1 = player.m_nx + MAPSIZE_PLAYERPLANE_WIDTH/2;
	if (m_nx<=x1    &&   x1<= m_nx+MAPSIZE_FOEPLANEBIG_WIDTH    &&   
		m_ny<=player.m_ny   &&   player.m_ny <=m_ny+MAPSIZE_FOEPLANEBIG_HEIGH)
	{
		return TRUE;
	}
	//���������½��Ǹ����ڵл�������η�Χ�ڵĻ�������ture
	//���½ǵĵ㣬x���䣬y��Ϊy+2/3�ҷ��ɻ��߶ȣ���Ϊ������y����
	int y1 = player.m_ny + MAPSIZE_PLAYERPLANE_HEIGH*2/3;
	if (m_nx<=player.m_nx    &&   player.m_nx<= m_nx+MAPSIZE_FOEPLANEBIG_WIDTH    &&   
		m_ny<=y1   &&   y1 <=m_ny+MAPSIZE_FOEPLANEBIG_HEIGH)
	{
		return TRUE;
	}
	//���������½��Ǹ����ڵл�������η�Χ�ڵĻ�������ture
	//���½ǵĵ㣬y����������������y1��x��Ϊm_nx+�ҷ��ɻ��������
	int x2 = player.m_nx+MAPSIZE_PLAYERPLANE_WIDTH;
	if (m_nx<=x2    &&   x2<= m_nx+MAPSIZE_FOEPLANEBIG_WIDTH    &&   
		m_ny<=y1   &&   y1 <=m_ny+MAPSIZE_FOEPLANEBIG_HEIGH)
	{
		return TRUE;
	}
	return FALSE;
}