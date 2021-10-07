#pragma once
#include<Windows.h>
#include"../PlayerPlane/PlayerPlane.h"
class CFoePlane
{
public:
	HBITMAP m_foePlane;
	int			m_nBlood;
	int			m_nx;
	int			m_ny;
	int			m_showId;
public:
	CFoePlane();
	virtual ~CFoePlane();
public:	
	virtual void InitFoePlane( HINSTANCE hIns)=0;
	void MoveFoePlane(int step);
	virtual void ShowFoePlane(HDC hdc, HDC compHdc)=0;
	virtual BOOL IsHitGunner(CGunner *pGun)=0;
	virtual BOOL IsHitPlayer(CPlayerPlane &player)=0;
};

