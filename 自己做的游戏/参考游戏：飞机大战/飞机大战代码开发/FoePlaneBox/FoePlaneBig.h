#pragma once
#include"FoePlane.h"
class CFoePlaneBig:public CFoePlane
{
public:
	CFoePlaneBig();
	~CFoePlaneBig();
public:
	virtual void InitFoePlane( HINSTANCE hIns);
	virtual void ShowFoePlane(HDC hdc, HDC compHdc);
	virtual BOOL IsHitGunner(CGunner *pGun);
	virtual BOOL IsHitPlayer(CPlayerPlane &player);
};