#pragma once


//노드에서 인접한 노드까지의 직선거리(혹은 그 기반값)
#define STRAIGHT_BASE	(1)
//노드에서 인접한 노드까지의 사선거리의 근사값(혹은 그 기반값) ≒ 1.41421356237
#define DIAGONAL_BASE	(1.4)
//노드간의 단위거리
#define DISTANCE_UNIT	(10)

struct Point2D
{
	int x = 0, y = 0;
	Point2D(){}
	Point2D(int x, int y){ this->x = x; this->y = y; }
	virtual ~Point2D(){}
};

enum NODETYPE{ NODETYPE_STARTPOINT, NODETYPE_DESTINATION, NODETYPE_IMPASSABLE, NODETYPE_PASSABLE, NODETYPE_CLOSED, NODETYPE_FINALROUTE };
//각 노드에 담긴 정보.
struct astarnode : public Point2D
{
public:
	float f = 0, g = 0, h = 0;
	NODETYPE type = NODETYPE_PASSABLE;
	astarnode *parent = nullptr;
};

//노드에 더블 링크드 요소가 추가됨.
struct linked_astarnode
{
	astarnode *dataptr = nullptr;
	linked_astarnode *prev = nullptr;
	linked_astarnode *next = nullptr;
};

//노드의 리스트를 만들어 관리한다.
//직접 노드를 만들지 않으며, linked_astarnode를 통해
//리스트 내 노드간 연결 및 해제를 제어한다.
//따라서 push, pop은 데이터를 넘겨주지 않고 그 데이터의 위치를 넘겨준다.
class list_astarnode : protected linked_astarnode
{
private:
	linked_astarnode *lastelem = nullptr;
	bool list_is_valid(void);
	void quick_sort_by_fval(linked_astarnode *head, linked_astarnode *left, linked_astarnode *right);
public:
	void push_front(astarnode *data);
	void push_back(astarnode *data);
	astarnode *pop_front(void);
	astarnode *pop_back(void);
	linked_astarnode *search(astarnode *data);
	void SortByFval(void);
};


class astarnode_map
{
protected:
	unsigned int size_x = 0, size_y = 0;
	astarnode **mapdata = nullptr;

public:
	astarnode_map(){}
	virtual ~astarnode_map(){ DeleteMap(); }

	astarnode *nodeptr(unsigned int pos_x, unsigned int pos_y);
	void CreateMap(unsigned int size_x, unsigned int size_y);
	void DeleteMap();
};

