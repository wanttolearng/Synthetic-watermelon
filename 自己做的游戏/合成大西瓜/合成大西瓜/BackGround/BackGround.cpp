#include"BackGround.h"
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

