/*

자유롭게 값을 변경할 수 있는 곳.
값을 변경하여 다양한 맵과 다양한 장애물 및 상황을 만들어 시뮬레이션 해볼 수 있다.
행렬과 비슷한 좌표를 따른다. 즉, 원점은 (1, 1)이며, 양의 X축 방향은 오른쪽, 양의 Y축 방향은 아랫쪽이다.


MAPSIZE		: 맵사이즈
STARTPOINT	: 시작점
DESTINATION	: 도착점
OBSTACLES	: 장애물(들)의 좌표.

*/

#define MAPSIZE_X		7
#define MAPSIZE_Y		5
#define STARTPOINT_X	2
#define STARTPOINT_Y	3
#define DESTINATION_X	6
#define DESTINATION_Y	3
#define OBSTACLES		{4, 2}, {4, 3}, {4, 4}