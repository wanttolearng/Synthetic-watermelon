#include"GunnerBox.h"
#include"../GameConfig/GameConfig.h"
CGunnerBox::CGunnerBox()
{
	m_lstGunner.clear();//����ʱ����������������������
}
CGunnerBox::~CGunnerBox()
{
	//ɾ��ʱע��ͨ���������������нڵ㣬Ȼ������delete
	list<CGunner *>::iterator ite = m_lstGunner.begin();
	while (ite != m_lstGunner.end())
	{
		delete (*ite);
		(*ite) = NULL;

		ite++;
	}
	m_lstGunner.clear();//���潫�ڵ��ռ�delete֮�󣬻�Ҫ���������Ҳɾ������
}
void CGunnerBox::ShowAllGunner(HDC hdc, HDC compHdc)
{
	//��ʾ�����ڵ����Ǳ�������Ȼ����ʾ�����е�ÿһ���ڵ�
	list<CGunner *>::iterator ite = m_lstGunner.begin();
	while (ite != m_lstGunner.end())
	{
		(*ite)->ShowGunner(hdc,compHdc);
		ite++;
	}
}
void CGunnerBox::MoveAllGunner(int step){
	//�ƶ������ڵ����Ǳ�������Ȼ���ƶ������е�ÿһ���ڵ�
	list<CGunner *>::iterator ite = m_lstGunner.begin();
	while (ite != m_lstGunner.end())
	{
		(*ite)->MoveGunner(step);
		//Ϊ��������Ҳ���԰��ڵ��Ĳ�������һ������
		//�ж��ڵ��Ƿ����
		if ( (*ite)->m_ny  <= -MAPSIZE_GUUNER_HEIGH)//Ҳ����ͼƬ�����Ͻǵ�������Ϊ�ж�
		{                                                                             //Ҳ����˵�������ڵ���ɾ��
			//ɾ������ڵ㣬����ֵΪ���������õ�������֮���Զ������һ���ڵ�
			ite = m_lstGunner.erase(ite);
			continue;//��������ѭ������ִ�����������ˣ�ת������ִ���´�ѭ��
		}
		ite++;
	}
}