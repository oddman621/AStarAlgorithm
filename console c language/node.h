#pragma once

#include <math.h>
enum NODETYPE{STARTPOINT, DESTINATION, IMPASSABLE, PASSABLE};

#define IS_PASSABLE(NODEPTR)	( NODEPTR->type != NODETYPE::IMPASSABLE )

//내부의 x,y,f,g,h값은 반드시 채워야 한다.
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
//이 클래스는 데이터의 주소값만 다루며,
//data에 대해 new등을 이용하는 동적할당이나 delete를 이용하지 않는다.
class linkednodehead : public linkednode
{
private:
	//데이터 추가에 유용하게 이용됨.
	//마지막 노드를 가리킨다.
	linkednode *last = nullptr;
public:


	//링크드 리스트 중 필요한 부분만 구현한다.

	//Add는 리스트가 없을 시 자동으로 생성해준다.
	void Add(node *data);
	//Pop은 실제로는 Head부분부터 Pop된다.
	//linkednode를 제거. 실제 데이터는 건드리지 않음.
	void Pop(node *data);
	//값을 비교하여 찾았을 시 그 링크노드의 주소값을, 찾지 못하면 nullptr를 리턴한다.
	//값의 비교는 주소값이 아닌 내부의 x, y의 일치여부를 이용한다.
	linkednode *Search(node *data);
	//f값 기준 오름차순으로 정렬한다. 버블정렬을 이용한다.
	//버블정렬로도 충분히 빠르며, 구현이 쉽기 때문.
	//또한 버블정렬이기에 리스트가 최소 3개 이상이어야 한다.
	void SortByFval(void);
};