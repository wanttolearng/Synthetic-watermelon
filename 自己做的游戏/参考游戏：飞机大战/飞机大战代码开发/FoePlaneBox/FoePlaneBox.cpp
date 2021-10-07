#include"FoePlaneBox.h"
#include<typeinfo>
#include"FoePlaneBig.h"
#include"FoePlaneMid.h"
#include"FoePlaneSma.h"
#include"../GameConfig/GameConfig.h"
CFoePlaneBox::CFoePlaneBox()
{
	m_BoomFoe.clear();
	m_lstFoe.clear();
}
#define RANGE_DELETE_FOELPLANE(FOEPLANE_LIST)\
	list<CFoePlane *>::iterator ite##FOEPLANE_LIST = FOEPLANE_LIST.begin();\
	while (ite##FOEPLANE_LIST != FOEPLANE_LIST.end() )\
	{\
		delete *ite##FOEPLANE_LIST;\
		*ite##FOEPLANE_LIST = NULL;\
		ite##FOEPLANE_LIST++;\
	}\
	FOEPLANE_LIST.clear();


CFoePlaneBox::~CFoePlaneBox()
{
	RANGE_DELETE_FOELPLANE(m_lstFoe)

	RANGE_DELETE_FOELPLANE(m_BoomFoe)
}

void CFoePlaneBox::ShowAllFoePlane(HDC hdc, HDC compHdc)
{
	list<CFoePlane *>::iterator ite = m_lstFoe.begin();
	while (ite != m_lstFoe.end() )
	{
		//��ʾ���еĵ��˷ɻ�
		(*ite)->ShowFoePlane(hdc,compHdc);
		ite++;
	}
}
void CFoePlaneBox::MoveAllFoePlane()
{
	list<CFoePlane *>::iterator ite = m_lstFoe.begin();
	while (ite != m_lstFoe.end() )
	{
		//�ƶ����еĵ��˷ɻ�
		//typeid(*(*ite)) == *(CFoePlane *) ==> big mid sma

		//--------------------------------------------------------

		const type_info &ti = typeid(CFoePlaneSma);
		const char*pName = ti.name();

		//--------------------------------------------------------

		if ( typeid(*(*ite)) == typeid(CFoePlaneSma) )     //С�ɻ�
		{
			(*ite)->MoveFoePlane(FOESMA_MOVE_STEP);
		}
		else if ( typeid(*(*ite)) == typeid(CFoePlaneMid) )   //�зɻ�
		{
			(*ite)->MoveFoePlane(FOEMID_MOVE_STEP);
		}
		else if ( typeid(*(*ite)) == typeid(CFoePlaneBig) )   //��ɻ�
		{
			(*ite)->MoveFoePlane(FOEBIG_MOVE_STEP);
		}

		//�ж��Ƿ����,�����ɾ��
		if ((*ite)->m_ny > MAPSIZE_BACKGROUND_HEIGH)
		{
			ite = m_lstFoe.erase(ite);
			continue;//ɾ��������ѭ������ִ�������ite++;
		}
		ite++;
	}
}
void CFoePlaneBox::ShowAllBoomPlane(HDC hdc, HDC compHdc)
{
	list<CFoePlane *>::iterator ite = m_BoomFoe.begin();
	while (ite != m_BoomFoe.end() )
	{
		//��ʾ���еı�ը�ɻ�
		(*ite)->ShowFoePlane(hdc,compHdc);
		ite++;
	}
}