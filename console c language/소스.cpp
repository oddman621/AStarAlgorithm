#include <stdio.h>
#include <math.h>

#define STARTPOINT_X	2
#define STARTPOINT_Y	3
#define DESTINATION_X	6
#define DESTINATION_Y	3

//두 점 사이의 거리를 리턴.
#define GET_DISTANCE(X1, Y1, X2, Y2) ( sqrt( pow(X1-X2, 2) + pow(Y1-Y2, 2) ) )
#define ARRAY(MAP, X, Y)			( MAP[Y-1][X-1] )
//타입. 그래픽 환경에서 이 값을 이용해 그래픽 표현이 가능함.
enum nodetype { STARTPOINT, DESTINATION, WALL, PASSABLE };

//해당 맵의 좌표가 PASSABLE인가?
#define IS_PASSABLE(MAP, X, Y) ( ARRAY(MAP, X, Y).type == PASSABLE ? true : false )


class node
{
public:
	//각각	시작점으로부터의 거리,	목적지로부터의 거리,	최종값을 의미 
	float	g = 0,				h = 0,				f = 0;
	//위치
	int x = 0, y = 0;
	//키패드의 숫자를 그대로 방향으로 사용할 것.
	//가령 direction[7]은 좌측 상단을 의미.
	//따라서 5와 0은 쓰지 않음.(각 노드마다 (node 포인터 크기)*2 가 낭비되지만, 요즘 컴퓨터에서는 미미한 낭비.)
	node *direction[10] = { 0 };

	nodetype type;

	//직접 (x,y) 2쌍을 이용해 두 점 사이의 거리를 구해 g, h에 대입.
	//void SetG(int start_x, int start_y) { g = GET_DISTANCE(x, y, start_x, start_y); }
	//void SetH(int dest_x, int dest_y) { h = GET_DISTANCE(x, y, dest_x, dest_y); }
	void SetG(void) { g = GET_DISTANCE(x, y, STARTPOINT_X, STARTPOINT_Y); }
	void SetH(void) { h = GET_DISTANCE(x, y, DESTINATION_X, DESTINATION_Y); }
	void RefreshF() { f = g + h; }
	node() {}
	virtual ~node() {}
};

//링크드 리스트.
struct linkednode
{
	node *data;
	//linkednode *prev;
	linkednode *next;
};


node **InitializeMap(int x, int y)
{
	node **temp = new node*[y];
	for (int i = 0; i < y; i++)
	{
		temp[i] = new node[x];
		for (int j = 0; j < x; j++)
		{
			//전부 PASSABLE로 초기화.
			temp[i][j].type = PASSABLE;
		}
	}
	return temp;
}

void DeleteMap(node **map, int x, int y)
{
	for (int i = 0; i < y; i++)
	{
		for (int j = 0; j < x; j++)
			delete (map[i] + j);
		delete map[i];
	}
	delete map;
}
void DeleteLinkedNode(linkednode *ln)
{
	linkednode *temp = ln;
	while (temp)
	{
		temp = ln->next;
		delete ln;
		ln = temp;
	}
}

//해당 list에 n이 있는지 확인.
//확인하는 방법은 리스트 내의 노드들과 n간의 x,y값을 비교한다.
bool IsOnList(linkednode list, node n)
{
	linkednode *temp = &list;
	while (temp)
	{
		if (temp->data->x == n.x && temp->data->y == n.y)
			return true;
		temp = temp->next;
	}
	return false;
}



int main(void)
{
	//맵 초기화
	node **map = InitializeMap(7, 5);

	//open 리스트의 헤드값. 가리키는 값은 고정됨.
	linkednode *openlisthead = new linkednode;//open 리스트의 머리. 첫 시작 부분이 먼저 open 리스트에 포함됨.
	linkednode *closelisthead = nullptr;//close 리스트의 머리. 현재는 비어있음.
	
	//맵 설정
	ARRAY(map, STARTPOINT_X, STARTPOINT_Y).type = STARTPOINT;
	ARRAY(map, DESTINATION_X, DESTINATION_Y).type = DESTINATION;
	ARRAY(map, 4, 2).type = WALL;
	ARRAY(map, 4, 3).type = WALL;
	ARRAY(map, 4, 4).type = WALL;

	//출발점 설정 및 openlist에 추가.
	openlisthead->data->x = 2;
	openlisthead->data->y = 3;
	openlisthead->data->SetG();
	openlisthead->data->SetH();
	openlisthead->data->RefreshF();
	openlisthead->next = nullptr;
	//openlisthead->prev = nullptr;



	linkednode *best = nullptr;

	//이 while 문은 최종 best경로를 찾았을 때 break 처리됨.
	//만일 실패했을 경우 failed를 출력하며 break.
	//openlist가 비어있을 경우 최적의 경로를 찾았다고 간주함.
	while (openlisthead)
	{
		//best가 open의 머리를 가리킴으로써
		//현재 open리스트를 최적루트로 간주함.
		//이후 openlist는 best의 다음값을 가리켜 그 다음값까지 오픈(조사된) 리스트에 포함시킴.
		//그리고 best의 다음값은 close 리스트를 다시 가리킴으로써
		//best->next 는 openlisthead->closelisthead가 되었다.
		//뭔말인지 모르겠다.

		//현재까지 
		best = openlisthead;
		openlisthead = openlisthead->next;
		best->next = closelisthead;

		closelisthead = best; //best(및 이후 노드)는 지금까지의 루프(현재 포함)에서 모두 탐색되므로 close리스트에 포함됨.
	}

	//while 이후 최종 best값이 산출됨.

	//정리
	DeleteLinkedNode(openlisthead);
	DeleteLinkedNode(closelisthead);
	DeleteMap(map, 7, 5);
	return 0;
}