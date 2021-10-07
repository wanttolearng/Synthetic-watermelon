#pragma once
#include"../GameFrame/GameApp.h"
#include"../BackGround/BackGround.h"
#include"../PlayerPlane/PlayerPlane.h"
#include"../GunnerBox/GunnerBox.h"
#include"../FoePlaneBox/FoePlaneBox.h"
class CPlaneApp:public CGameApp{
public:
	CBackGround m_back;
	CPlayerPlane m_player;
	CGunnerBox m_gunBox;
	CFoePlaneBox m_foePlaneBox;
public:
	CPlaneApp();
	~CPlaneApp();
public:
	//case WM_CREATE: //���ڴ�����Ϣ
	virtual void OnCreate();

	//case WM_PAINT:  //�ػ���Ϣ
	virtual void OnDraw();

	//case WM_TIMER:   //��ʱ������Ҫ�������������ֶ���Ӷ�ʱ�������ô������
	virtual void OnGameRun(WPARAM wParam);

	//case WM_KEYDOWN:  //���̰��´�����Ϣ
	virtual void OnKeyDown(WPARAM wParam);

	void SetTimmer();
	void GameOver();
};