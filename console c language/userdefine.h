#define MAPSIZE_X		12
#define MAPSIZE_Y		12
#define STARTPOINT_X	2
#define STARTPOINT_Y	3
#define DESTINATION_X	10
#define DESTINATION_Y	3

#define OBSTACLE_LIST	{4,2},{4,3},{4,4},{4,5},{3,5},{3,2}, {5,2}, {8,1}, {8,2}, {8,3}, {8,4}, {8,5}, {8,6}, {8,7}, {8,8}, {7,8}, {6,8}, {6,9}


////이하는 수정하면 안 되는 부분
const unsigned int OBSTACLES[][2] = { OBSTACLE_LIST };
const unsigned int OBSTACLES_AMOUNT = sizeof(OBSTACLES) / (sizeof(int) * 2);

//정상값일시 모두 true를 리턴한다.

#define CHECK_USERDEF_MAPSIZE()		( MAPSIZE_X>0 && MAPSIZE_Y>0 )
#define CHECK_USERDEF_COORD(X,Y)	( (X<=0 && X>=MAPSIZE_X) && (Y<=0 && Y>=MAPSIZE_Y) )
#define CHECK_USERDEF_STARTPOINT()	CHECK_USERDEF_COORD(STARTPOINT_X, STARTPOINT_Y)
#define CHECK_USERDEF_DESTINATION()	CHECK_USERDEF_COORD(DESTINATION_X, DESTINATION_Y)
#define CHECK_USERDEF_OBSTACLE_LIST  [] \
			{ \
				for (int i = 0; i < OBSTACLES_AMOUNT; i++) \
					if (CHECK_USERDEF_COORD(OBSTACLES[i][0], OBSTACLES[i][1])) \
						return true; \
				return false; \
			}

#define CHECK_USERDEF_ALL()		( CHECK_USERDEF_MAPSIZE() && CHECK_USERDEF_STARTPOINT() && CHECK_USERDEF_DESTINATION() && CHECK_USERDEF_OBSTACLE_LIST() )
