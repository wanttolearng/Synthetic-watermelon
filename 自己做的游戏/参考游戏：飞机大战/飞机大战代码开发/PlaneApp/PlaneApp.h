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
	//case WM_CREATE: //窗口创建消息
	virtual void OnCreate();

	//case WM_PAINT:  //重绘消息
	virtual void OnDraw();

	//case WM_TIMER:   //定时器，需要我们在子类中手动添加定时器并设置触发间隔
	virtual void OnGameRun(WPARAM wParam);

	//case WM_KEYDOWN:  //键盘按下触发消息
	virtual void OnKeyDown(WPARAM wParam);

	void SetTimmer();
	void GameOver();
};