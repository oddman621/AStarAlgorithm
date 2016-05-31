#pragma once

#include <math.h>
enum NODETYPE{STARTPOINT, DESTINATION, IMPASSABLE, PASSABLE};

#define IS_PASSABLE(NODEPTR)	( NODEPTR->type != NODETYPE::IMPASSABLE )

//������ x,y,f,g,h���� �ݵ�� ä���� �Ѵ�.
struct node
{
	double f = 0, g = 0, h = 0;
	int x = 0, y = 0;
	NODETYPE type = NODETYPE::PASSABLE;
	node *direction[8] = { nullptr };
	node(void){};
	node(float x, float y, float startpos_x, float startpos_y, float destination_x, float destination_y)
	{
		this->x = x; this->y = y;
		g = sqrt(pow(x - startpos_x, 2) + pow(y - startpos_y, 2));
		h = sqrt(pow(x - destination_x, 2) + pow(y - destination_y, 2));
		f = g + h;
	}
	virtual ~node(void){ delete direction; }
};
struct linkednode
{
	node *dataptr = nullptr;
	linkednode *next = nullptr;
};
//�� Ŭ������ �������� �ּҰ��� �ٷ��,
//data�� ���� new���� �̿��ϴ� �����Ҵ��̳� delete�� �̿����� �ʴ´�.
class linkednodehead : public linkednode
{
private:
	//������ �߰��� �����ϰ� �̿��.
	//������ ��带 ����Ų��.
	linkednode *last = nullptr;
public:


	//��ũ�� ����Ʈ �� �ʿ��� �κи� �����Ѵ�.

	//Add�� ����Ʈ�� ���� �� �ڵ����� �������ش�.
	void Add(node *data);
	//Pop�� �����δ� Head�κк��� Pop�ȴ�.
	//linkednode�� ����. ���� �����ʹ� �ǵ帮�� ����.
	void Pop(node *data);
	//���� ���Ͽ� ã���� �� �� ��ũ����� �ּҰ���, ã�� ���ϸ� nullptr�� �����Ѵ�.
	//���� �񱳴� �ּҰ��� �ƴ� ������ x, y�� ��ġ���θ� �̿��Ѵ�.
	linkednode *Search(node *data);
	//f�� ���� ������������ �����Ѵ�. ���������� �̿��Ѵ�.
	//�������ķε� ����� ������, ������ ���� ����.
	//���� ���������̱⿡ ����Ʈ�� �ּ� 3�� �̻��̾�� �Ѵ�.
	void SortByFval(void);
};