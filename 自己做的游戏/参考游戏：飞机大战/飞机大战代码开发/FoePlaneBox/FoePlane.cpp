#include"FoePlane.h"

CFoePlane::CFoePlane()
{
	m_foePlane = NULL;
	m_nBlood = 0;
	m_nx = 0;
	m_ny = 0;
	m_showId = 0;
}

CFoePlane::~CFoePlane()
{
	::DeleteObject(m_foePlane);

	m_foePlane = NULL;
	m_nBlood = 0;
	m_nx = 0;
	m_ny = 0;
	m_showId = 0;
}
//�з��ɻ��ƶ�����̶���ֻ���·�
void CFoePlane::MoveFoePlane(int step)
{
	m_ny+=step;
}