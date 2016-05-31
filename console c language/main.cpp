#include "node.h"
#include "nodemap.h"
#include "UserDefine.h"



const int obstacles[][2] = { OBSTACLES };

int main(void)
{
	linkednodehead openlist, closelist;
	nodemap *myMap = new nodemap(MAPSIZE_X, MAPSIZE_Y, STARTPOINT_X, STARTPOINT_Y, DESTINATION_X, DESTINATION_Y, obstacles);
	openlist.Add(NODEMAP(myMap, STARTPOINT_X, STARTPOINT_Y));

	//open리스트가 비어있을 시 다 찾은 것으로 간주한다.
	//while문 종료시 closelist에는 최적의 경로에 대한 정보가 저장되어 있어야 한다.
	node *current = nullptr;
	while (!openlist.dataptr)
	{
		openlist.Pop(current);
		closelist.Add(current);

		if (!current) break;//찾기 실패
		if (current->x == DESTINATION_X && current->y == DESTINATION_Y) break;//찾기 성공

		//현재 탐색중인 노드를 중심으로 8방향 확장. 확장할 수 있는 방향이 존재하지 않을 경우 찾기는 실패한다.	

		if (NODEMAP_LEFT(myMap, current->x, current->y))
		{
		}
		if (NODEMAP_RIGHT(myMap, current->x, current->y))
		{
		}
		if (NODEMAP_UP(myMap, current->x, current->y))
		{
		}
		if (NODEMAP_DOWN(myMap, current->x, current->y))
		{
		}
		if (NODEMAP_DOWNLEFT(myMap, current->x, current->y))
		{
		}
		if (NODEMAP_DOWNRIGHT(myMap, current->x, current->y))
		{
		}
		if (NODEMAP_UPLEFT(myMap, current->x, current->y))
		{
		}
		if (NODEMAP_UPRIGHT(myMap, current->x, current->y))
		{
		}
	}

	return 0;
}