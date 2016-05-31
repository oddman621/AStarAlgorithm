#include "node.h"

//map Ŭ���� �ܺο��� �ʵ����Ϳ� ���ٽ� �� ��ũ�θ� �̿��Ѵ�.
//(x, y) ��ǥ���� �迭������ �˸°� ��ȯ���ش�.
//��ȯ���� �ش� ����� �ּ��̴�.
#define NODEMAP(PTR, X, Y)			( *( (PTR->mapdata) + (Y-1) ) + (X-1) )
#define NODEMAP_ISVALID(PTR, X, Y)	( X>=1 && X<=(PTR->SizeX()) && Y>=1 && Y<=(PTR->SizeY()) )

//�̵��� ������ �� ������ �� �ش� ����ּҸ� �����Ѵ�. �ƴ� ��� nullptr�� �����Ѵ�.
#define NODEMAP_LEFT(PTR, X, Y)			NODEMAP_ISVALID(PTR, X-1, Y) ? NODEMAP(PTR, X-1, Y) : nullptr
#define NODEMAP_RIGHT(PTR, X, Y)		NODEMAP_ISVALID(PTR, X+1, Y) ? NODEMAP(PTR, X+1, Y) : nullptr
#define NODEMAP_UP(PTR, X, Y)			NODEMAP_ISVALID(PTR, X, Y-1) ? NODEMAP(PTR, X, Y-1) : nullptr
#define NODEMAP_DOWN(PTR, X, Y)			NODEMAP_ISVALID(PTR, X, Y+1) ? NODEMAP(PTR, X, Y+1) : nullptr
//�밢�� �̵��� Ư���ϰ� ó���ؾ� �ϴµ�, ���� ���� ������� �̵��� ��� ���ʰ� ���� �� �ϳ��� PASSABLE�̾�� �Ѵ�.
//�������� �κ�.
#define NODEMAP_DOWNLEFT(PTR, X, Y)		NODEMAP_ISVALID(PTR, X-1, Y+1) && ( NODEMAP_LEFT(PTR, X, Y) ? NODEMAP_LEFT(PTR, X, Y)->type == NODETYPE::PASSABLE : false || NODEMAP_DOWN(PTR, X, Y) ? NODEMAP_DOWN(PTR, X, Y)->type == NODETYPE::PASSABLE : false ) ? NODEMAP(PTR, X-1, Y+1) : nullptr
#define NODEMAP_DOWNRIGHT(PTR, X, Y)	NODEMAP_ISVALID(PTR, X+1, Y+1) && ( NODEMAP_LEFT(PTR, X, Y)->type == NODETYPE::PASSABLE || NODEMAP_DOWN(PTR, X, Y)->type == NODETYPE::PASSABLE ) ? NODEMAP(PTR, X+1, Y+1) : nullptr
#define NODEMAP_UPLEFT(PTR, X, Y)		NODEMAP_ISVALID(PTR, X-1, Y-1) && ( NODEMAP_LEFT(PTR, X, Y)->type == NODETYPE::PASSABLE || NODEMAP_DOWN(PTR, X, Y)->type == NODETYPE::PASSABLE ) ? NODEMAP(PTR, X-1, Y-1) : nullptr
#define NODEMAP_UPRIGHT(PTR, X, Y)		NODEMAP_ISVALID(PTR, X+1, Y-1) && ( NODEMAP_LEFT(PTR, X, Y)->type == NODETYPE::PASSABLE || NODEMAP_DOWN(PTR, X, Y)->type == NODETYPE::PASSABLE ) ? NODEMAP(PTR, X+1, Y-1) : nullptr

//�� ����� f, g, h���� CreateMap() �Լ��� ���� �ڵ� �Էµȴ�.
//nodemap(int, int, int, int, int, int, const int) �����ڴ� ���ο��� CreateMap()�� ȣ���Ѵ�.
//���⼭ x, y���� ���� ũ�⸦ �ǹ��Ѵ�.
class nodemap
{
private:
	int x = 0; int y = 0;
public:
	node **mapdata = nullptr;
	int SizeX(void){ return x; }
	int SizeY(void){ return y; }
	nodemap(){}
	nodemap(int x, int y, int start_x, int start_y, int dest_x, int dest_y, const int obstacles[][2]) { CreateMap(x, y, start_x, start_y, dest_x, dest_y, obstacles); }
	virtual ~nodemap(){ DeleteMap(); }
	void CreateMap(int x, int y, int start_x, int start_y, int dest_x, int dest_y, const int obstacles[][2]);
	void DeleteMap();
};