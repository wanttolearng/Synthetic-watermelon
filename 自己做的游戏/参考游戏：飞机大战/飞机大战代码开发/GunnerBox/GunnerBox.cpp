#include"GunnerBox.h"
#include"../GameConfig/GameConfig.h"
CGunnerBox::CGunnerBox()
{
	m_lstGunner.clear();//构造时将链表清空这个操作别忘了
}
CGunnerBox::~CGunnerBox()
{
	//删除时注意通过迭代器遍历所有节点，然后依次delete
	list<CGunner *>::iterator ite = m_lstGunner.begin();
	while (ite != m_lstGunner.end())
	{
		delete (*ite);
		(*ite) = NULL;

		ite++;
	}
	m_lstGunner.clear();//上面将炮弹空间delete之后，还要讲这个链表也删除才行
}
void CGunnerBox::ShowAllGunner(HDC hdc, HDC compHdc)
{
	//显示所有炮弹就是遍历链表，然后显示链表中的每一个炮弹
	list<CGunner *>::iterator ite = m_lstGunner.begin();
	while (ite != m_lstGunner.end())
	{
		(*ite)->ShowGunner(hdc,compHdc);
		ite++;
	}
}
void CGunnerBox::MoveAllGunner(int step){
	//移动所有炮弹就是遍历链表，然后移动链表中的每一个炮弹
	list<CGunner *>::iterator ite = m_lstGunner.begin();
	while (ite != m_lstGunner.end())
	{
		(*ite)->MoveGunner(step);
		//为了灵活，我们也可以把炮弹的步长做成一个配置
		//判断炮弹是否出界
		if ( (*ite)->m_ny  <= -MAPSIZE_GUUNER_HEIGH)//也是以图片最左上角的坐标作为判断
		{                                                                             //也就是说看不到炮弹就删除
			//删除这个节点，返回值为迭代器，用迭代器接之后自动变成下一个节点
			ite = m_lstGunner.erase(ite);
			continue;//跳出本次循环，不执行下面的语句了，转而继续执行下次循环
		}
		ite++;
	}
}