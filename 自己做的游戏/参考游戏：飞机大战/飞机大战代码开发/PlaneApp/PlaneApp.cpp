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
//case WM_CREATE: //窗口创建消息
void CPlaneApp::OnCreate(){

	srand((unsigned int)time(NULL));

	//创建定时器
	SetTimmer();

	//初始化背景，this->  写不写都行，没区别
	m_back.InitBackGround(0,0,this->m_hInstance);
	//初始化玩家飞机，this->  写不写都行，没区别，xy为窗口下方居中的位置为我方飞机出现的位置
	m_player.InitPlayerPlane((MAPSIZE_BACKGROUND_WIDTH-MAPSIZE_PLAYERPLANE_WIDTH)/2,
		MAPSIZE_BACKGROUND_HEIGH-MAPSIZE_PLAYERPLANE_HEIGH,this->m_hInstance);
}
//case WM_PAINT:  //重绘消息
void CPlaneApp::OnDraw(){
	//获取窗口DC
	PAINTSTRUCT ps = {0};
	HDC hdc = ::BeginPaint(this->m_hWnd,&ps);
	//创建缓冲的DC
	HDC cacheDC = ::CreateCompatibleDC(hdc);
	HBITMAP map = ::CreateCompatibleBitmap(hdc,MAPSIZE_BACKGROUND_WIDTH,MAPSIZE_BACKGROUND_HEIGH);
	::SelectObject(cacheDC,map);

	//创建兼容性DC
	HDC compDC = ::CreateCompatibleDC(cacheDC);
	
	//----------------------------------------------
	m_back.ShowBackGround(cacheDC,compDC);

	m_player.ShowPlayerPlane(cacheDC,compDC);

	m_gunBox.ShowAllGunner(cacheDC,compDC);

	m_foePlaneBox.ShowAllFoePlane(cacheDC,compDC);

	m_foePlaneBox.ShowAllBoomPlane(cacheDC,compDC);

	//----------------------------------------------

	//现在所有的图都放到cacheDC中了，接着就是把cacheDC中的所有图一次性传输到hdc中
	//不写  ::   的原因是参数本函数就有，不用在外面找
	BitBlt(hdc,0,0,MAPSIZE_BACKGROUND_WIDTH,MAPSIZE_BACKGROUND_HEIGH,cacheDC,0,0,SRCCOPY);

	DeleteDC(compDC);
	compDC = NULL;
	//删除位图专用函数
	::DeleteObject(map);
	map = NULL;
	//删除兼容性DC专用函数
	DeleteDC(cacheDC);
	cacheDC = NULL;

	::EndPaint(this->m_hWnd,&ps);
}

#define CREATE_FOEPLANE(FOEPLANE_CLASS)\
			CFoePlane *pFoe = new FOEPLANE_CLASS;\
			pFoe->InitFoePlane(this->m_hInstance);\
			m_foePlaneBox.m_lstFoe.push_back(pFoe);


//case WM_TIMER:   //定时器，需要我们在子类中手动添加定时器并设置触发间隔
void CPlaneApp::OnGameRun(WPARAM wParam){
	switch (wParam)
	{
	case TIMER_BACKGROUND_MOVE_TIMERID://背景移动
		{
			//背景的移动通过定时器在游戏启动时自主进行就行，而飞机的移动是通过按键进行了，所以飞机移动的实现写在键盘按下的消息里
			m_back.MoveBackGround(4);
		}
		break;
	case TIMER_PLAYERPLANE_MOVE_TIMERID: //玩家飞机移动
		{
				//判断是否按下了方向键
				if (::GetAsyncKeyState(VK_LEFT))
				{
					m_player.MovePlayerPlane(VK_LEFT,PLAYERPLANE_MOVE_STEP);//方向，键盘按下检测是在wParam里，所以写wParam就行了
				}

				if (::GetAsyncKeyState(VK_RIGHT))
				{
					m_player.MovePlayerPlane(VK_RIGHT,PLAYERPLANE_MOVE_STEP);//方向，键盘按下检测是在wParam里，所以写wParam就行了
				}

				if (::GetAsyncKeyState(VK_UP))
				{
				m_player.MovePlayerPlane(VK_UP,PLAYERPLANE_MOVE_STEP);//方向，键盘按下检测是在wParam里，所以写wParam就行了
				}

				if (::GetAsyncKeyState(VK_DOWN))
				{
				m_player.MovePlayerPlane(VK_DOWN,PLAYERPLANE_MOVE_STEP);//方向，键盘按下检测是在wParam里，所以写wParam就行了
				}
		}
		break;
	case TIMER_GUNNER_MOVE_TIMERID://炮弹移动
		{
			m_gunBox.MoveAllGunner(GUNNER_MOVE_STEP);
		}
		break;
	case TIMER_SEND_GUNNER_MOVE_TIMERID://定时发射炮弹
		{
			CGunner *pGun = m_player.SendGunner(this->m_hInstance);
			//发射完炮弹，炮弹离开了玩家飞机，所以玩家飞机管不了了，此时由炮弹盒子统一管理
			m_gunBox.m_lstGunner.push_back(pGun);//把炮弹放到炮弹盒子里
		}
		break;
	case TIMER_FOEBIG_CREATE_TIMERID://创建大飞机
		{
			//CFoePlane *pFoe = new CFoePlaneBig;
			//pFoe->InitFoePlane(this->m_hInstance);
			////添加到飞机盒子里
			//m_foePlaneBox.m_lstFoe.push_back(pFoe);
			CREATE_FOEPLANE(CFoePlaneBig)
		}
		break;
	case TIMER_FOEMID_CREATE_TIMERID://创建中飞机
		{
			//CFoePlane *pFoe = new CFoePlaneMid;
			//pFoe->InitFoePlane(this->m_hInstance);
			////添加到飞机盒子里
			//m_foePlaneBox.m_lstFoe.push_back(pFoe);
			CREATE_FOEPLANE(CFoePlaneMid)
		}
		break;
	case TIMER_FOESMA_CREATE_TIMERID://创建小飞机
		{
			//CFoePlane *pFoe = new CFoePlaneSma;
			//pFoe->InitFoePlane(this->m_hInstance);
			////添加到飞机盒子里
			//m_foePlaneBox.m_lstFoe.push_back(pFoe);
			CREATE_FOEPLANE(CFoePlaneSma)
		}
		break;
	case TIMER_FOEPLANE_MOVE_TIMERID:   //敌人飞机移动
		{
			m_foePlaneBox.MoveAllFoePlane();
		}
		break;
	case TIMER_CHECK_FOEPLANE_HIT_TIMERID:   //定时检查是否撞击
		{
			bool isboom = false;
			list<CFoePlane *>::iterator iteFoe = m_foePlaneBox.m_lstFoe.begin();
			while (iteFoe != m_foePlaneBox.m_lstFoe.end() )
			{
				//---------------------遍历所有敌人飞机-------------

				//判断是否撞击玩家飞机
				if (  (*iteFoe)->IsHitPlayer(m_player)  )
				{
					//游戏结束
					GameOver();
					return;
				}

				//判断是否撞击到炮弹
				list<CGunner *>::iterator iteGun = m_gunBox.m_lstGunner.begin();
				while (iteGun != m_gunBox.m_lstGunner.end() )
				{
					if (  (*iteFoe)->IsHitGunner(*iteGun)    )  //判断敌人飞机是否撞击到了炮弹
					{
						//炮弹消失
						iteGun = m_gunBox.m_lstGunner.erase(iteGun);

						//敌人飞机血量减少
						(*iteFoe)->m_nBlood-=GUNNER_HURT;

						//判断血量是否为0
						if ((*iteFoe)->m_nBlood <= 0 )
						{
							isboom = true;
							//移动敌人飞机到爆炸链表
							m_foePlaneBox.m_BoomFoe.push_back(*iteFoe);
							//上面把敌机放到了爆炸链表，在正常链表留下了一个节点，要删除
							iteFoe = m_foePlaneBox.m_lstFoe.erase(iteFoe);
						}
						break;
					}
					iteGun++;
				}

				//---------------------遍历所有敌人飞机-------------
				if (isboom)
				{
					//这里不能写break，否则跳出大循环while，也就跳出这个消息了，
					//后面的敌机就没遍历到。就不能判断有的敌机能不能撞击炮弹了，就不对了。
					isboom = false;
				}else
				{
					iteFoe++;
				}				
			}
		}
		break;
	case TIMER_CHANGE_FOEPLANE_BOOM_TIMERID:   //定时切换爆炸效果
		{
			list<CFoePlane *>::iterator ite = m_foePlaneBox.m_BoomFoe.begin();
			while (  ite != m_foePlaneBox.m_BoomFoe.end() )
			{
				(*ite)->m_showId--;

				if ((*ite)->m_showId   <   0)//确实爆炸了，这里不能等于0，否则最后一张爆炸效果就没了
				{
					delete (*ite);//删除我们new出来的CFoePlane *指向的这片空间
					(*ite) = NULL;

					ite = m_foePlaneBox.m_BoomFoe.erase(ite);
					continue;
				}
				ite++;
			}
		}
		break;
	}
	//这个00指的是客户端的00，也就是上面我们讨论的两个红线的交点。
	RECT rect = {0,0,MAPSIZE_BACKGROUND_WIDTH,MAPSIZE_BACKGROUND_HEIGH};//设置这些数值来将窗口中背景区域都变成无效区域。
	::InvalidateRect(this->m_hWnd,&rect,FALSE);
}
//case WM_KEYDOWN:  //键盘按下触发消息
void CPlaneApp::OnKeyDown(WPARAM wParam){
	//背景的移动通过定时器在游戏启动时自主进行就行，而飞机的移动是通过按键进行了，所以飞机移动的实现写在键盘按下的消息里
	//m_player.MovePlayerPlane(wParam,PLAYERPLANE_MOVE_STEP);//方向，键盘按下检测是在wParam里，所以写wParam就行了
}
void CPlaneApp::SetTimmer()
{
	//设置背景移动的定时器
	::SetTimer(this->m_hWnd,TIMER_BACKGROUND_MOVE_TIMERID,TIMER_BACKGROUND_MOVE_INTERVAL,NULL);

	//设置我方飞机移动持续检测的定时器
	::SetTimer(this->m_hWnd,TIMER_PLAYERPLANE_MOVE_TIMERID,TIMER_PLAYERPLANE_MOVE_INTERVAL,NULL);

	//炮弹移动的定时器
	::SetTimer(this->m_hWnd,TIMER_GUNNER_MOVE_TIMERID,TIMER_GUNNER_MOVE_INTERVAL,NULL);

	//发射炮弹的定时器
	::SetTimer(this->m_hWnd,TIMER_SEND_GUNNER_MOVE_TIMERID,TIMER_SEND_GUNNER_INTERVAL,NULL);

	//创建敌人大飞机
	::SetTimer(this->m_hWnd,TIMER_FOEBIG_CREATE_TIMERID,TIMER_FOEBIG_CREATE_INTERVAL,NULL);
	//创建敌人中飞机
	::SetTimer(this->m_hWnd,TIMER_FOEMID_CREATE_TIMERID,TIMER_FOEMID_CREATE_INTERVAL,NULL);
	//创建敌人小飞机
	::SetTimer(this->m_hWnd,TIMER_FOESMA_CREATE_TIMERID,TIMER_FOESMA_CREATE_INTERVAL,NULL);

	//敌人飞机移动定时器
	::SetTimer(this->m_hWnd,TIMER_FOEPLANE_MOVE_TIMERID,TIMER_FOEPLANE_MOVE_INTERVAL,NULL);

	//定时检查是否撞击
	::SetTimer(this->m_hWnd,TIMER_CHECK_FOEPLANE_HIT_TIMERID,TIMER_CHECK_FOEPLANE_HIT_INTERVAL,NULL);

	//切换爆炸效果定时器
	::SetTimer(this->m_hWnd,TIMER_CHANGE_FOEPLANE_BOOM_TIMERID,TIMER_CHANGE_FOEPLANE_BOOM_INTERVAL,NULL);	
}
void CPlaneApp::GameOver()
{
	//杀死所有定时器

	//设置背景移动的定时器
	::KillTimer(this->m_hWnd,TIMER_BACKGROUND_MOVE_TIMERID);

	//设置我方飞机移动持续检测的定时器
	::KillTimer(this->m_hWnd,TIMER_PLAYERPLANE_MOVE_TIMERID);

	//炮弹移动的定时器
	::KillTimer(this->m_hWnd,TIMER_GUNNER_MOVE_TIMERID);

	//发射炮弹的定时器
	::KillTimer(this->m_hWnd,TIMER_SEND_GUNNER_MOVE_TIMERID);

	//创建敌人大飞机
	::KillTimer(this->m_hWnd,TIMER_FOEBIG_CREATE_TIMERID);
	//创建敌人中飞机
	::KillTimer(this->m_hWnd,TIMER_FOEMID_CREATE_TIMERID);
	//创建敌人小飞机
	::KillTimer(this->m_hWnd,TIMER_FOESMA_CREATE_TIMERID);

	//敌人飞机移动定时器
	::KillTimer(this->m_hWnd,TIMER_FOEPLANE_MOVE_TIMERID);

	//定时检查是否撞击
	::KillTimer(this->m_hWnd,TIMER_CHECK_FOEPLANE_HIT_TIMERID);

	//切换爆炸效果定时器
	::KillTimer(this->m_hWnd,TIMER_CHANGE_FOEPLANE_BOOM_TIMERID);	

	//提示GameOver

	::MessageBox(this->m_hWnd,"GameOver~~","提示",MB_OK);

	//发送程序退出消息
	PostMessage(this->m_hWnd,WM_DESTROY,0,0);//相当于执行WM_DESTROY这个消息
}