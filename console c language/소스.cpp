#include <stdio.h>
#include <math.h>

//-> 양의 x방향
//↓양의 y방향
//이 매트릭스의 첫번째 엘리먼트, 즉 원점은 (1,1)
//위의 정보를 바탕으로 조정할 것.
//맘대로 조정할 수 있는 상수들--------------------------------------
#define MAPSIZE_X		7										//맵사이즈 X값
#define MAPSIZE_Y		5										//맵사이즈 Y값
#define STARTPOINT_X	2										//시작점의 X값
#define STARTPOINT_Y	3										//시작점의 Y값
#define DESTINATION_X	6										//도착점의 X값
#define DESTINATION_Y	3										//도착점의 Y값
const int WALLLIST[][2] = { {4, 2}, {4, 3}, {4, 4} };			//지나갈 수 없는 WALL지역의 좌표. 각 x값, y값을 대표한다.
//맘대로 조정할 수 있는 상수들 끝-----------------------------------



//두 점 사이의 거리를 리턴.
#define GET_DISTANCE(X1, Y1, X2, Y2) ( sqrt( pow(X1-X2, 2) + pow(Y1-Y2, 2) ) )
//(x, y) 좌표값을 컴퓨터에 저장된 배열에 맞게 변환한다.
#define ARRAY(MAP, X, Y)			( MAP[Y-1][X-1] )
//해당 맵의 좌표가 PASSABLE인가?
#define IS_PASSABLE(MAP, X, Y) ( ARRAY(MAP, X, Y).type == PASSABLE ? true : false )
//해당 리스트에 존재하는가? 있다면 OUT으로 해당 링크드노드의 주소값이, 없을 경우 null값이 들어간다.
#define IS_ONLIST(LISTHEAD, NODEPTR, OUT)	OUT = LISTHEAD; while(OUT){if(OUT->data->x == NODEPTR->x && OUT->data->y == NODEPTR->y) break;OUT = OUT->next;}


//타입. 그래픽 환경에서 이 값을 이용해 그래픽 표현이 가능함.
enum nodetype { STARTPOINT, DESTINATION, WALL, PASSABLE };
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

	nodetype type = (nodetype)0;

	//직접 (x,y) 2쌍을 이용해 두 점 사이의 거리를 구해 g, h에 대입.
	//void SetG(int start_x, int start_y) { g = GET_DISTANCE(x, y, start_x, start_y); }
	//void SetH(int dest_x, int dest_y) { h = GET_DISTANCE(x, y, dest_x, dest_y); }
	void RefreshG(void) { g = GET_DISTANCE(x, y, STARTPOINT_X, STARTPOINT_Y); }
	void RefreshH(void) { h = GET_DISTANCE(x, y, DESTINATION_X, DESTINATION_Y); }
	void RefreshF(void) { f = g + h; }
	void RefreshGHF(void) { RefreshG(); RefreshH(); RefreshF(); }
	node() {}
	virtual ~node() {}
};
struct linkednode
{
	node *data = nullptr;
	linkednode *next = nullptr;
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
	int walllistsize = sizeof(WALLLIST) / (sizeof(int) * 2);
	for (int i = 0; i < walllistsize; i++)
		ARRAY(map, WALLLIST[i][0], WALLLIST[i][1]).type = WALL;

	//출발점 설정 및 openlist에 추가.
	openlisthead->data->x = STARTPOINT_X;
	openlisthead->data->y = STARTPOINT_Y;
	openlisthead->data->RefreshGHF();
	openlisthead->next = nullptr;



	linkednode *temp = nullptr;
	//이 while 문은 최종 best경로를 찾았을 때 break 처리됨.
	//만일 실패했을 경우 failed를 출력하며 break.
	//openlist가 비어있을 경우 최적의 경로를 찾았다고 간주함.
	//그렇게 찾은 최종 경로는 closelist에 저장되며,
	//이 리스트를 f값에 기반하여 역추적하면 최적 경로가 나온다.
	while (openlisthead)
	{

		temp = openlisthead;
		openlisthead = openlisthead->next;//다음 오픈 리스트를 참조한다.
		temp->next = closelisthead;
		closelisthead = temp;	//결국 closelisthead는 현재 탐색중인 노드를 가리키며, 이 뒤로 현재까지 조사된 노드들이 이어진다.
								//여기서 최종 목적지에 도달할 경우 이 리스트는 그대로 최적의 경로를 뽑을 자료가 된다.
								//그러나 만일 이 값이 null일 경우 최적의 경로를 찾는 데 실패하게 된다.
		if (!closelisthead)
		{
			printf("FAILED!\n");
			break;
		}
		if (closelisthead->data->x == DESTINATION_X - 1 && closelisthead->data->y == DESTINATION_Y - 1)
		{
			printf("SUCCESS!\n");
			break;
		}


	}

	//while 이후 최종 경로값이 산출되며, 이는 closelisthead에 저장되어 있다.
	//다만 도착점으로부터 시작점까지의 방향, 즉 역추적이기 때문에
	//이를 반대로 바꿔줄 필요가 있다. linkednode에 *prev를 추가하여 역방향으로도 갈 수 있도록 하거나
	//새로이 노드를 바꾸거나 만든다.

	//정리
	DeleteLinkedNode(openlisthead);
	DeleteLinkedNode(closelisthead);
	DeleteMap(map, 7, 5);
	return 0;
}