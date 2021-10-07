#include"PlaneApp.h"
#include"../GameConfig/GameConfig.h"
#include<time.h>
#include"../FoePlaneBox/FoePlane.h"
#include"../FoePlaneBox/FoePlaneBig.h"
#include"../FoePlaneBox/FoePlaneMid.h"
#include"../FoePlaneBox/FoePlaneSma.h"
GET_OBJECT(CPlaneApp)
CLASS_CONFIG(WND_PARAM_X,WND_PARAM_Y,WND_PARAM_WIDTH,WND_PARAM_HIGTH,WND_PARAM_TITLE)

CPlaneApp::CPlaneApp(){

}
CPlaneApp::~CPlaneApp(){

}
//case WM_CREATE: //���ڴ�����Ϣ
void CPlaneApp::OnCreate(){

	srand((unsigned int)time(NULL));

	//������ʱ��
	SetTimmer();

	//��ʼ��������this->  д��д���У�û����
	m_back.InitBackGround(0,0,this->m_hInstance);
	//��ʼ����ҷɻ���this->  д��д���У�û����xyΪ�����·����е�λ��Ϊ�ҷ��ɻ����ֵ�λ��
	m_player.InitPlayerPlane((MAPSIZE_BACKGROUND_WIDTH-MAPSIZE_PLAYERPLANE_WIDTH)/2,
		MAPSIZE_BACKGROUND_HEIGH-MAPSIZE_PLAYERPLANE_HEIGH,this->m_hInstance);
}
//case WM_PAINT:  //�ػ���Ϣ
void CPlaneApp::OnDraw(){
	//��ȡ����DC
	PAINTSTRUCT ps = {0};
	HDC hdc = ::BeginPaint(this->m_hWnd,&ps);
	//���������DC
	HDC cacheDC = ::CreateCompatibleDC(hdc);
	HBITMAP map = ::CreateCompatibleBitmap(hdc,MAPSIZE_BACKGROUND_WIDTH,MAPSIZE_BACKGROUND_HEIGH);
	::SelectObject(cacheDC,map);

	//����������DC
	HDC compDC = ::CreateCompatibleDC(cacheDC);
	
	//----------------------------------------------
	m_back.ShowBackGround(cacheDC,compDC);

	m_player.ShowPlayerPlane(cacheDC,compDC);

	m_gunBox.ShowAllGunner(cacheDC,compDC);

	m_foePlaneBox.ShowAllFoePlane(cacheDC,compDC);

	m_foePlaneBox.ShowAllBoomPlane(cacheDC,compDC);

	//----------------------------------------------

	//�������е�ͼ���ŵ�cacheDC���ˣ����ž��ǰ�cacheDC�е�����ͼһ���Դ��䵽hdc��
	//��д  ::   ��ԭ���ǲ������������У�������������
	BitBlt(hdc,0,0,MAPSIZE_BACKGROUND_WIDTH,MAPSIZE_BACKGROUND_HEIGH,cacheDC,0,0,SRCCOPY);

	DeleteDC(compDC);
	compDC = NULL;
	//ɾ��λͼר�ú���
	::DeleteObject(map);
	map = NULL;
	//ɾ��������DCר�ú���
	DeleteDC(cacheDC);
	cacheDC = NULL;

	::EndPaint(this->m_hWnd,&ps);
}

#define CREATE_FOEPLANE(FOEPLANE_CLASS)\
			CFoePlane *pFoe = new FOEPLANE_CLASS;\
			pFoe->InitFoePlane(this->m_hInstance);\
			m_foePlaneBox.m_lstFoe.push_back(pFoe);


//case WM_TIMER:   //��ʱ������Ҫ�������������ֶ���Ӷ�ʱ�������ô������
void CPlaneApp::OnGameRun(WPARAM wParam){
	switch (wParam)
	{
	case TIMER_BACKGROUND_MOVE_TIMERID://�����ƶ�
		{
			//�������ƶ�ͨ����ʱ������Ϸ����ʱ�������о��У����ɻ����ƶ���ͨ�����������ˣ����Էɻ��ƶ���ʵ��д�ڼ��̰��µ���Ϣ��
			m_back.MoveBackGround(4);
		}
		break;
	case TIMER_PLAYERPLANE_MOVE_TIMERID: //��ҷɻ��ƶ�
		{
				//�ж��Ƿ����˷����
				if (::GetAsyncKeyState(VK_LEFT))
				{
					m_player.MovePlayerPlane(VK_LEFT,PLAYERPLANE_MOVE_STEP);//���򣬼��̰��¼������wParam�����дwParam������
				}

				if (::GetAsyncKeyState(VK_RIGHT))
				{
					m_player.MovePlayerPlane(VK_RIGHT,PLAYERPLANE_MOVE_STEP);//���򣬼��̰��¼������wParam�����дwParam������
				}

				if (::GetAsyncKeyState(VK_UP))
				{
				m_player.MovePlayerPlane(VK_UP,PLAYERPLANE_MOVE_STEP);//���򣬼��̰��¼������wParam�����дwParam������
				}

				if (::GetAsyncKeyState(VK_DOWN))
				{
				m_player.MovePlayerPlane(VK_DOWN,PLAYERPLANE_MOVE_STEP);//���򣬼��̰��¼������wParam�����дwParam������
				}
		}
		break;
	case TIMER_GUNNER_MOVE_TIMERID://�ڵ��ƶ�
		{
			m_gunBox.MoveAllGunner(GUNNER_MOVE_STEP);
		}
		break;
	case TIMER_SEND_GUNNER_MOVE_TIMERID://��ʱ�����ڵ�
		{
			CGunner *pGun = m_player.SendGunner(this->m_hInstance);
			//�������ڵ����ڵ��뿪����ҷɻ���������ҷɻ��ܲ����ˣ���ʱ���ڵ�����ͳһ����
			m_gunBox.m_lstGunner.push_back(pGun);//���ڵ��ŵ��ڵ�������
		}
		break;
	case TIMER_FOEBIG_CREATE_TIMERID://������ɻ�
		{
			//CFoePlane *pFoe = new CFoePlaneBig;
			//pFoe->InitFoePlane(this->m_hInstance);
			////��ӵ��ɻ�������
			//m_foePlaneBox.m_lstFoe.push_back(pFoe);
			CREATE_FOEPLANE(CFoePlaneBig)
		}
		break;
	case TIMER_FOEMID_CREATE_TIMERID://�����зɻ�
		{
			//CFoePlane *pFoe = new CFoePlaneMid;
			//pFoe->InitFoePlane(this->m_hInstance);
			////��ӵ��ɻ�������
			//m_foePlaneBox.m_lstFoe.push_back(pFoe);
			CREATE_FOEPLANE(CFoePlaneMid)
		}
		break;
	case TIMER_FOESMA_CREATE_TIMERID://����С�ɻ�
		{
			//CFoePlane *pFoe = new CFoePlaneSma;
			//pFoe->InitFoePlane(this->m_hInstance);
			////��ӵ��ɻ�������
			//m_foePlaneBox.m_lstFoe.push_back(pFoe);
			CREATE_FOEPLANE(CFoePlaneSma)
		}
		break;
	case TIMER_FOEPLANE_MOVE_TIMERID:   //���˷ɻ��ƶ�
		{
			m_foePlaneBox.MoveAllFoePlane();
		}
		break;
	case TIMER_CHECK_FOEPLANE_HIT_TIMERID:   //��ʱ����Ƿ�ײ��
		{
			bool isboom = false;
			list<CFoePlane *>::iterator iteFoe = m_foePlaneBox.m_lstFoe.begin();
			while (iteFoe != m_foePlaneBox.m_lstFoe.end() )
			{
				//---------------------�������е��˷ɻ�-------------

				//�ж��Ƿ�ײ����ҷɻ�
				if (  (*iteFoe)->IsHitPlayer(m_player)  )
				{
					//��Ϸ����
					GameOver();
					return;
				}

				//�ж��Ƿ�ײ�����ڵ�
				list<CGunner *>::iterator iteGun = m_gunBox.m_lstGunner.begin();
				while (iteGun != m_gunBox.m_lstGunner.end() )
				{
					if (  (*iteFoe)->IsHitGunner(*iteGun)    )  //�жϵ��˷ɻ��Ƿ�ײ�������ڵ�
					{
						//�ڵ���ʧ
						iteGun = m_gunBox.m_lstGunner.erase(iteGun);

						//���˷ɻ�Ѫ������
						(*iteFoe)->m_nBlood-=GUNNER_HURT;

						//�ж�Ѫ���Ƿ�Ϊ0
						if ((*iteFoe)->m_nBlood <= 0 )
						{
							isboom = true;
							//�ƶ����˷ɻ�����ը����
							m_foePlaneBox.m_BoomFoe.push_back(*iteFoe);
							//����ѵл��ŵ��˱�ը��������������������һ���ڵ㣬Ҫɾ��
							iteFoe = m_foePlaneBox.m_lstFoe.erase(iteFoe);
						}
						break;
					}
					iteGun++;
				}

				//---------------------�������е��˷ɻ�-------------
				if (isboom)
				{
					//���ﲻ��дbreak������������ѭ��while��Ҳ�����������Ϣ�ˣ�
					//����ĵл���û���������Ͳ����ж��еĵл��ܲ���ײ���ڵ��ˣ��Ͳ����ˡ�
					isboom = false;
				}else
				{
					iteFoe++;
				}				
			}
		}
		break;
	case TIMER_CHANGE_FOEPLANE_BOOM_TIMERID:   //��ʱ�л���ըЧ��
		{
			list<CFoePlane *>::iterator ite = m_foePlaneBox.m_BoomFoe.begin();
			while (  ite != m_foePlaneBox.m_BoomFoe.end() )
			{
				(*ite)->m_showId--;

				if ((*ite)->m_showId   <   0)//ȷʵ��ը�ˣ����ﲻ�ܵ���0���������һ�ű�ըЧ����û��
				{
					delete (*ite);//ɾ������new������CFoePlane *ָ�����Ƭ�ռ�
					(*ite) = NULL;

					ite = m_foePlaneBox.m_BoomFoe.erase(ite);
					continue;
				}
				ite++;
			}
		}
		break;
	}
	//���00ָ���ǿͻ��˵�00��Ҳ���������������۵��������ߵĽ��㡣
	RECT rect = {0,0,MAPSIZE_BACKGROUND_WIDTH,MAPSIZE_BACKGROUND_HEIGH};//������Щ��ֵ���������б������򶼱����Ч����
	::InvalidateRect(this->m_hWnd,&rect,FALSE);
}
//case WM_KEYDOWN:  //���̰��´�����Ϣ
void CPlaneApp::OnKeyDown(WPARAM wParam){
	//�������ƶ�ͨ����ʱ������Ϸ����ʱ�������о��У����ɻ����ƶ���ͨ�����������ˣ����Էɻ��ƶ���ʵ��д�ڼ��̰��µ���Ϣ��
	//m_player.MovePlayerPlane(wParam,PLAYERPLANE_MOVE_STEP);//���򣬼��̰��¼������wParam�����дwParam������
}
void CPlaneApp::SetTimmer()
{
	//���ñ����ƶ��Ķ�ʱ��
	::SetTimer(this->m_hWnd,TIMER_BACKGROUND_MOVE_TIMERID,TIMER_BACKGROUND_MOVE_INTERVAL,NULL);

	//�����ҷ��ɻ��ƶ��������Ķ�ʱ��
	::SetTimer(this->m_hWnd,TIMER_PLAYERPLANE_MOVE_TIMERID,TIMER_PLAYERPLANE_MOVE_INTERVAL,NULL);

	//�ڵ��ƶ��Ķ�ʱ��
	::SetTimer(this->m_hWnd,TIMER_GUNNER_MOVE_TIMERID,TIMER_GUNNER_MOVE_INTERVAL,NULL);

	//�����ڵ��Ķ�ʱ��
	::SetTimer(this->m_hWnd,TIMER_SEND_GUNNER_MOVE_TIMERID,TIMER_SEND_GUNNER_INTERVAL,NULL);

	//�������˴�ɻ�
	::SetTimer(this->m_hWnd,TIMER_FOEBIG_CREATE_TIMERID,TIMER_FOEBIG_CREATE_INTERVAL,NULL);
	//���������зɻ�
	::SetTimer(this->m_hWnd,TIMER_FOEMID_CREATE_TIMERID,TIMER_FOEMID_CREATE_INTERVAL,NULL);
	//��������С�ɻ�
	::SetTimer(this->m_hWnd,TIMER_FOESMA_CREATE_TIMERID,TIMER_FOESMA_CREATE_INTERVAL,NULL);

	//���˷ɻ��ƶ���ʱ��
	::SetTimer(this->m_hWnd,TIMER_FOEPLANE_MOVE_TIMERID,TIMER_FOEPLANE_MOVE_INTERVAL,NULL);

	//��ʱ����Ƿ�ײ��
	::SetTimer(this->m_hWnd,TIMER_CHECK_FOEPLANE_HIT_TIMERID,TIMER_CHECK_FOEPLANE_HIT_INTERVAL,NULL);

	//�л���ըЧ����ʱ��
	::SetTimer(this->m_hWnd,TIMER_CHANGE_FOEPLANE_BOOM_TIMERID,TIMER_CHANGE_FOEPLANE_BOOM_INTERVAL,NULL);	
}
void CPlaneApp::GameOver()
{
	//ɱ�����ж�ʱ��

	//���ñ����ƶ��Ķ�ʱ��
	::KillTimer(this->m_hWnd,TIMER_BACKGROUND_MOVE_TIMERID);

	//�����ҷ��ɻ��ƶ��������Ķ�ʱ��
	::KillTimer(this->m_hWnd,TIMER_PLAYERPLANE_MOVE_TIMERID);

	//�ڵ��ƶ��Ķ�ʱ��
	::KillTimer(this->m_hWnd,TIMER_GUNNER_MOVE_TIMERID);

	//�����ڵ��Ķ�ʱ��
	::KillTimer(this->m_hWnd,TIMER_SEND_GUNNER_MOVE_TIMERID);

	//�������˴�ɻ�
	::KillTimer(this->m_hWnd,TIMER_FOEBIG_CREATE_TIMERID);
	//���������зɻ�
	::KillTimer(this->m_hWnd,TIMER_FOEMID_CREATE_TIMERID);
	//��������С�ɻ�
	::KillTimer(this->m_hWnd,TIMER_FOESMA_CREATE_TIMERID);

	//���˷ɻ��ƶ���ʱ��
	::KillTimer(this->m_hWnd,TIMER_FOEPLANE_MOVE_TIMERID);

	//��ʱ����Ƿ�ײ��
	::KillTimer(this->m_hWnd,TIMER_CHECK_FOEPLANE_HIT_TIMERID);

	//�л���ըЧ����ʱ��
	::KillTimer(this->m_hWnd,TIMER_CHANGE_FOEPLANE_BOOM_TIMERID);	

	//��ʾGameOver

	::MessageBox(this->m_hWnd,"GameOver~~","��ʾ",MB_OK);

	//���ͳ����˳���Ϣ
	PostMessage(this->m_hWnd,WM_DESTROY,0,0);//�൱��ִ��WM_DESTROY�����Ϣ
}