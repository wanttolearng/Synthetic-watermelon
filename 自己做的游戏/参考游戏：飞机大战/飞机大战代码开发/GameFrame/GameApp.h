#pragma once
#include<Windows.h>
class CGameApp{
public:
	HINSTANCE m_hInstance;//h�Ǿ������˼  ʵ�����
	HWND         m_hWnd;//���ھ��
public:
	CGameApp(){}
	virtual ~CGameApp(){}   //ע������������������
public:
	void SetHandle(HINSTANCE hIns,HWND hWnd)
	{
		m_hInstance = hIns;
		m_hWnd       = hWnd;
	}
public:
	//case WM_CREATE: //���ڴ�����Ϣ
	virtual void OnCreate(){}

	//case WM_PAINT:  //�ػ���Ϣ
	virtual void OnDraw(){}

	//case WM_TIMER:   //��ʱ������Ҫ�������������ֶ���Ӷ�ʱ�������ô������
	virtual void OnGameRun(WPARAM wParam){}

	//case WM_KEYDOWN:  //���̰��´�����Ϣ
	virtual void OnKeyDown(WPARAM wParam){}

	//case WM_KEYUP:    //����̧�𴥷���Ϣ
	virtual void OnKeyUp(WPARAM wParam){}

	//case WM_LBUTTONDOWN: //���������´�����Ϣ
	virtual void OnLButtonDown(POINT &po){}

	//case WM_LBUTTONUP:  //������̧�𴥷���Ϣ
	virtual void OnLButtonUp(POINT &po){}

	//case WM_MOUSEMOVE: //����ƶ�
	virtual void OnMouseMove(POINT &po){}
};
CGameApp *GetChildObject();

#define GET_OBJECT(CHILD_CLASS)\
	CGameApp *GetChildObject(){\
		return new CHILD_CLASS;\
	}

#define CLASS_CONFIG(PARAM_X,PARAM_Y,PARAM_WIDTH,PARAM_HEIGH,PARAM_TITLE)\
	int nx=PARAM_X;\
	int ny=PARAM_Y;\
	int nwidth=PARAM_WIDTH;\
	int nheigh=PARAM_HEIGH;\
	CHAR * strTitle=PARAM_TITLE;//����ֱ�Ӵ��ַ���PARAM_TITLE

