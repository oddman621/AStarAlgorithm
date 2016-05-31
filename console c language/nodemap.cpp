#include "nodemap.h"

void nodemap::CreateMap(int x, int y, int start_x, int start_y, int dest_x, int dest_y, const int obstacles[][2])
{
	if (mapdata) DeleteMap();

	this->x = x; this->y = y;
	mapdata = new node*[y];
	for (int i = 0; i < y; i++)
		mapdata[i] = new node[x];

	for (int xi = 1; xi <= x; x++){
		for (int yi = 1; yi <= y; y++)
			*NODEMAP(this, xi, yi) = node(xi, yi, start_x, start_y, dest_x, dest_y);}

	NODEMAP(this, start_x, start_y)->type = NODETYPE::STARTPOINT;
	NODEMAP(this, dest_x, dest_y)->type = NODETYPE::DESTINATION;

	int length = sizeof(obstacles) / (sizeof(int)* 2);

	if (obstacles != nullptr)
		for (int i = 0; i < length; i++)
			NODEMAP(this, obstacles[i][0], obstacles[i][1])->type = NODETYPE::IMPASSABLE;
}
void nodemap::DeleteMap()
{
	if (!mapdata) return;

	for (int i = 0; i < y; i++){
		for (int j = 0; j < x; j++)
			delete &mapdata[i][j];}
}