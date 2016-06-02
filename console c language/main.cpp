#include <iostream>
#include "astarnode.h"
#include "userdefine.h"

using namespace std;

//���밪 ��ȯ.
#define ABS(val)	( (val)>=0 ? (val) : -(val) )



int main()
{
	////////////////////�Էµ� ���� ��ȿ�� Ȯ��
	if (CHECK_USERDEF_ALL())
	{
		cout << "�Է°��� �߸��Ǿ����ϴ�." << endl
			<< "userdefine.h ������ Ȯ�����ּ���." << endl
			<< "CHECK_USERDEF_MAPSIZE()			: " << CHECK_USERDEF_MAPSIZE() << endl
			<< "CHECK_USERDEF_STARTPOINT()		: " << CHECK_USERDEF_STARTPOINT() << endl
			<< "CHECK_USERDEF_DESTINATION()		: " << CHECK_USERDEF_DESTINATION() << endl
			<< "CHECK_USERDEF_OBSTACLE_LIST()	: " << CHECK_USERDEF_OBSTACLE_LIST() << endl;
		return 0;
	}
	////////////////////�Էµ� ���� ��ȿ�� Ȯ�� ��




	////////////////////////////////////////////////////////////���� ����////////////////////////////////////////////////////////////

	astarnode_map map;//��
	list_astarnode openlist;//�߰ߵ� ����Ʈ
	list_astarnode closelist;//Ž���� ����Ʈ
	astarnode *current;//������Ʈ�� ã�� �ּҰ�

	////userdefine.h ���� ������ ���� �̿��� �� ����
	map.CreateMap(MAPSIZE_X, MAPSIZE_Y);
	map.nodeptr(STARTPOINT_X, STARTPOINT_Y)->type = NODETYPE_STARTPOINT;
	map.nodeptr(DESTINATION_X, DESTINATION_Y)->type = NODETYPE_DESTINATION;
	for (int i = 0; i < OBSTACLES_AMOUNT; i++)
		map.nodeptr(OBSTACLES[i][0], OBSTACLES[i][1])->type = NODETYPE_IMPASSABLE;
	////userdefine.h ���� ������ ���� �̿��� �� ���� ��

	//openlist �ʱ⼳��
	openlist.push_front(map.nodeptr(STARTPOINT_X, STARTPOINT_Y));
	
	//while���� ���ǿ� ���ؼ� ������ ����� ��� ���з� �����Ѵ�.
	while (current = openlist.pop_front())
	{
		//���� ��尡 �������� ��� ������ �����Ѵ�.
		if (current->x == DESTINATION_X && current->y == DESTINATION_Y) break;

		closelist.push_front(current);

		astarnode *direction;
		//xSubVal : -1~1 ������ x��. �� ���� ����, �߾�, �������� �ǹ��Ѵ�.
		//ySubVal : 1~-1 ������ y��. �� ���� �Ʒ���, �߾�, ������ �ǹ��Ѵ�.
		for (int ySubVal = 1; ySubVal >= -1; ySubVal--)
		{
			for (int xSubVal = -1; xSubVal <= 1; xSubVal++)
			{
				
				direction = map.nodeptr(current->x + xSubVal, current->y + ySubVal);

				///direction ���˻�
				if (!direction) continue;//�� �� ���� ���
				if (direction->type != NODETYPE_PASSABLE) continue;//������ �� ���� ������ ���
				//if (direction == current) continue;//���߾��� ��� //current�� �̹� closelist�� �����Ƿ� ���� ����.
				if (closelist.search(direction)) continue;//�߰� �Ǿ����� Ž���� ���� �ִ� ���
				///direction ���˻� ��

				

				////�߰� �Ǿ����� Ž���� ���� ���� ���
				if (openlist.search(direction))
				{
					Point2D diff = { current->x - direction->x, current->y - direction->y };
					float distance_current_to_direction = ((diff.x && diff.y) ? DIAGONAL_BASE : STRAIGHT_BASE) * DISTANCE_UNIT;
					float current_g_plus_d_ctd = current->g + distance_current_to_direction;

					//�����Ʈ���� direction���� ���� g���� ���� g���� ���Ͽ� direction->g�� ����.
					if (direction->g > current_g_plus_d_ctd)
					{
						direction->parent = current; direction->g = current_g_plus_d_ctd;
						direction->f = direction->g + direction->h;
					}
				}
				////�߰� �Ǿ����� Ž���� ���� ���� ��� ��

				////�߰ߵ� �� ���� ����� ���
				else
				{
					direction->parent = current;
					openlist.push_back(direction);

					//direction ���� ������ ������ �Ÿ�
					Point2D diff; diff.x = ABS(direction->x - DESTINATION_X); diff.y = ABS(direction->y - DESTINATION_Y); //Point2D diff = { ABS(direction->x - DESTINATION_X), ABS(direction->y - DESTINATION_Y) };

					///g�� ����
					while (diff.x >= 1 && diff.y >= 1)
					{
						diff.x -= 1; diff.y -= 1;
						direction->g += DIAGONAL_BASE * DISTANCE_UNIT;
					}
					while (diff.x >= 1)
					{
						diff.x -= 1;
						direction->g += STRAIGHT_BASE * DISTANCE_UNIT;
					}
					while (diff.y >= 1)
					{
						diff.y -= 1;
						direction->g += STRAIGHT_BASE * DISTANCE_UNIT;
					}
					///g�� ���� ��

					///h�� ����
					diff = { direction->parent->x - direction->x, direction->parent->y - direction->y };
					direction->h += current->h + ((diff.x && diff.y) ? DIAGONAL_BASE : STRAIGHT_BASE) * DISTANCE_UNIT;
					///h�� ���� ��

					//f�� ������ ����
					direction->f = direction->g + direction->h;
				}
				////�߰ߵ� �� ���� ����� ��� ��

			}
		}

		openlist.SortByFval();
	}

	
	//////////////////////////////////////////////////////////// ���� �� ////////////////////////////////////////////////////////////


	////�׷��� ǥ�� ����

	astarnode *bestroute = current;

	if (!bestroute)
		cout << "FAILED!\n" << endl;
	else {
		cout << "SUCCESS!\n" << endl;
		if (bestroute->parent)
		{
			while (bestroute->parent)
			{
				bestroute->type = NODETYPE_FINALROUTE;
				bestroute = bestroute->parent;
			}
		}
	}


	for (int yi = 1; yi <= MAPSIZE_Y; yi++)
	{
		for (int xi = 1; xi <= MAPSIZE_X; xi++)
		{
			switch (map.nodeptr(xi, yi)->type)
			{
			case NODETYPE_STARTPOINT: cout << "S"; break;
			case NODETYPE_DESTINATION: cout << "D"; break;
			case NODETYPE_IMPASSABLE: cout << "X"; break;
			case NODETYPE_PASSABLE: cout << "O"; break;
			case NODETYPE_FINALROUTE: cout << "F"; break;
			case NODETYPE_CLOSED: cout << "C"; break;
			default: cout << "?"; break;
			}
		}
		cout << endl;
	}
	cout << endl;

	////�׷��� ǥ�� ��

	return 0;
}