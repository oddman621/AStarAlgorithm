#include "node.h"

//map 클래스 외부에서 맵데이터에 접근시 이 매크로를 이용한다.
//(x, y) 좌표값을 배열참조에 알맞게 변환해준다.
//반환값은 해당 노드의 주소이다.
#define NODEMAP(PTR, X, Y)			( *( (PTR->mapdata) + (Y-1) ) + (X-1) )
#define NODEMAP_ISVALID(PTR, X, Y)	( X>=1 && X<=(PTR->SizeX()) && Y>=1 && Y<=(PTR->SizeY()) )

//이동이 가능한 지 검증한 뒤 해당 노드주소를 리턴한다. 아닐 경우 nullptr을 리턴한다.
#define NODEMAP_LEFT(PTR, X, Y)			NODEMAP_ISVALID(PTR, X-1, Y) ? NODEMAP(PTR, X-1, Y) : nullptr
#define NODEMAP_RIGHT(PTR, X, Y)		NODEMAP_ISVALID(PTR, X+1, Y) ? NODEMAP(PTR, X+1, Y) : nullptr
#define NODEMAP_UP(PTR, X, Y)			NODEMAP_ISVALID(PTR, X, Y-1) ? NODEMAP(PTR, X, Y-1) : nullptr
#define NODEMAP_DOWN(PTR, X, Y)			NODEMAP_ISVALID(PTR, X, Y+1) ? NODEMAP(PTR, X, Y+1) : nullptr
//대각선 이동은 특수하게 처리해야 하는데, 가령 왼쪽 상단으로 이동할 경우 왼쪽과 윗쪽 중 하나는 PASSABLE이어야 한다.
//수정중인 부분.
#define NODEMAP_DOWNLEFT(PTR, X, Y)		NODEMAP_ISVALID(PTR, X-1, Y+1) && ( NODEMAP_LEFT(PTR, X, Y) ? NODEMAP_LEFT(PTR, X, Y)->type == NODETYPE::PASSABLE : false || NODEMAP_DOWN(PTR, X, Y) ? NODEMAP_DOWN(PTR, X, Y)->type == NODETYPE::PASSABLE : false ) ? NODEMAP(PTR, X-1, Y+1) : nullptr
#define NODEMAP_DOWNRIGHT(PTR, X, Y)	NODEMAP_ISVALID(PTR, X+1, Y+1) && ( NODEMAP_LEFT(PTR, X, Y)->type == NODETYPE::PASSABLE || NODEMAP_DOWN(PTR, X, Y)->type == NODETYPE::PASSABLE ) ? NODEMAP(PTR, X+1, Y+1) : nullptr
#define NODEMAP_UPLEFT(PTR, X, Y)		NODEMAP_ISVALID(PTR, X-1, Y-1) && ( NODEMAP_LEFT(PTR, X, Y)->type == NODETYPE::PASSABLE || NODEMAP_DOWN(PTR, X, Y)->type == NODETYPE::PASSABLE ) ? NODEMAP(PTR, X-1, Y-1) : nullptr
#define NODEMAP_UPRIGHT(PTR, X, Y)		NODEMAP_ISVALID(PTR, X+1, Y-1) && ( NODEMAP_LEFT(PTR, X, Y)->type == NODETYPE::PASSABLE || NODEMAP_DOWN(PTR, X, Y)->type == NODETYPE::PASSABLE ) ? NODEMAP(PTR, X+1, Y-1) : nullptr

//각 노드의 f, g, h값은 CreateMap() 함수에 의해 자동 입력된다.
//nodemap(int, int, int, int, int, int, const int) 생성자는 내부에서 CreateMap()을 호출한다.
//여기서 x, y값은 맵의 크기를 의미한다.
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