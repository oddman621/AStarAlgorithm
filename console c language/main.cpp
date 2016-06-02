#include <iostream>
#include "astarnode.h"
#include "userdefine.h"

using namespace std;

//절대값 반환.
#define ABS(val)	( (val)>=0 ? (val) : -(val) )



int main()
{
	////////////////////입력된 값의 유효성 확인
	if (CHECK_USERDEF_ALL())
	{
		cout << "입력값이 잘못되었습니다." << endl
			<< "userdefine.h 파일을 확인해주세요." << endl
			<< "CHECK_USERDEF_MAPSIZE()			: " << CHECK_USERDEF_MAPSIZE() << endl
			<< "CHECK_USERDEF_STARTPOINT()		: " << CHECK_USERDEF_STARTPOINT() << endl
			<< "CHECK_USERDEF_DESTINATION()		: " << CHECK_USERDEF_DESTINATION() << endl
			<< "CHECK_USERDEF_OBSTACLE_LIST()	: " << CHECK_USERDEF_OBSTACLE_LIST() << endl;
		return 0;
	}
	////////////////////입력된 값의 유효성 확인 끝




	////////////////////////////////////////////////////////////구현 시작////////////////////////////////////////////////////////////

	astarnode_map map;//맵
	list_astarnode openlist;//발견된 리스트
	list_astarnode closelist;//탐색된 리스트
	astarnode *current;//최적루트를 찾을 주소값

	////userdefine.h 에서 설정된 값을 이용해 맵 제작
	map.CreateMap(MAPSIZE_X, MAPSIZE_Y);
	map.nodeptr(STARTPOINT_X, STARTPOINT_Y)->type = NODETYPE_STARTPOINT;
	map.nodeptr(DESTINATION_X, DESTINATION_Y)->type = NODETYPE_DESTINATION;
	for (int i = 0; i < OBSTACLES_AMOUNT; i++)
		map.nodeptr(OBSTACLES[i][0], OBSTACLES[i][1])->type = NODETYPE_IMPASSABLE;
	////userdefine.h 에서 설정된 값을 이용해 맵 제작 끝

	//openlist 초기설정
	openlist.push_front(map.nodeptr(STARTPOINT_X, STARTPOINT_Y));
	
	//while문의 조건에 의해서 루프가 종료될 경우 실패로 간주한다.
	while (current = openlist.pop_front())
	{
		//현재 노드가 도착점일 경우 루프를 종료한다.
		if (current->x == DESTINATION_X && current->y == DESTINATION_Y) break;

		closelist.push_front(current);

		astarnode *direction;
		//xSubVal : -1~1 사이의 x값. 각 값은 왼쪽, 중앙, 오른쪽을 의미한다.
		//ySubVal : 1~-1 사이의 y값. 각 값은 아랫쪽, 중앙, 윗쪽을 의미한다.
		for (int ySubVal = 1; ySubVal >= -1; ySubVal--)
		{
			for (int xSubVal = -1; xSubVal <= 1; xSubVal++)
			{
				
				direction = map.nodeptr(current->x + xSubVal, current->y + ySubVal);

				///direction 선검사
				if (!direction) continue;//갈 수 없을 경우
				if (direction->type != NODETYPE_PASSABLE) continue;//지나갈 수 없는 구역일 경우
				//if (direction == current) continue;//정중앙일 경우 //current는 이미 closelist에 있으므로 생략 가능.
				if (closelist.search(direction)) continue;//발견 되었으며 탐색한 적도 있는 경우
				///direction 선검사 끝

				

				////발견 되었으나 탐색한 적은 없는 경우
				if (openlist.search(direction))
				{
					Point2D diff = { current->x - direction->x, current->y - direction->y };
					float distance_current_to_direction = ((diff.x && diff.y) ? DIAGONAL_BASE : STRAIGHT_BASE) * DISTANCE_UNIT;
					float current_g_plus_d_ctd = current->g + distance_current_to_direction;

					//현재루트에서 direction으로 가는 g값과 기존 g값을 비교하여 direction->g값 설정.
					if (direction->g > current_g_plus_d_ctd)
					{
						direction->parent = current; direction->g = current_g_plus_d_ctd;
						direction->f = direction->g + direction->h;
					}
				}
				////발견 되었으나 탐색한 적은 없는 경우 끝

				////발견된 적 없는 노드일 경우
				else
				{
					direction->parent = current;
					openlist.push_back(direction);

					//direction 노드와 도착점 사이의 거리
					Point2D diff; diff.x = ABS(direction->x - DESTINATION_X); diff.y = ABS(direction->y - DESTINATION_Y); //Point2D diff = { ABS(direction->x - DESTINATION_X), ABS(direction->y - DESTINATION_Y) };

					///g값 산출
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
					///g값 산출 끝

					///h값 산출
					diff = { direction->parent->x - direction->x, direction->parent->y - direction->y };
					direction->h += current->h + ((diff.x && diff.y) ? DIAGONAL_BASE : STRAIGHT_BASE) * DISTANCE_UNIT;
					///h값 산출 끝

					//f에 최종값 대입
					direction->f = direction->g + direction->h;
				}
				////발견된 적 없는 노드일 경우 끝

			}
		}

		openlist.SortByFval();
	}

	
	//////////////////////////////////////////////////////////// 구현 끝 ////////////////////////////////////////////////////////////


	////그래픽 표현 시작

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

	////그래픽 표현 끝

	return 0;
}