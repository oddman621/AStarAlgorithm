#include "node.h"
#include "nodemap.h"
#include "UserDefine.h"



const int obstacles[][2] = { OBSTACLES };

int main(void)
{
	linkednodehead openlist, closelist;
	nodemap *myMap = new nodemap(MAPSIZE_X, MAPSIZE_Y, STARTPOINT_X, STARTPOINT_Y, DESTINATION_X, DESTINATION_Y, obstacles);
	openlist.Add(NODEMAP(myMap, STARTPOINT_X, STARTPOINT_Y));

	//open����Ʈ�� ������� �� �� ã�� ������ �����Ѵ�.
	//while�� ����� closelist���� ������ ��ο� ���� ������ ����Ǿ� �־�� �Ѵ�.
	node *current = nullptr;
	while (!openlist.dataptr)
	{
		openlist.Pop(current);
		closelist.Add(current);

		if (!current) break;//ã�� ����
		if (current->x == DESTINATION_X && current->y == DESTINATION_Y) break;//ã�� ����

		//���� Ž������ ��带 �߽����� 8���� Ȯ��. Ȯ���� �� �ִ� ������ �������� ���� ��� ã��� �����Ѵ�.	

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