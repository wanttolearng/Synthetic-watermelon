#pragma once
#include"FoePlane.h"
class CFoePlaneMid:public CFoePlane
{
public:
	CFoePlaneMid();
	~CFoePlaneMid();
public:
	virtual void InitFoePlane( HINSTANCE hIns);
	virtual void ShowFoePlane(HDC hdc, HDC compHdc);
	virtual BOOL IsHitGunner(CGunner *pGun);
	virtual BOOL IsHitPlayer(CPlayerPlane &player);
};