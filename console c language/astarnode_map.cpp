#include "astarnode.h"
#include <iostream>
using namespace std;

//맵 데이터의 노드위치값을 C++ 배열에 맞게 변환
//#define MAP(map, x, y)	map[y-1][x-1]
#define MAP(map, x, y) ( *(map + ((y) - 1)) + ((x) - 1) )

astarnode *astarnode_map::nodeptr(unsigned int pos_x, unsigned int pos_y)
{
	if (pos_x > size_x || pos_y > size_y || pos_x <= 0 || pos_y <= 0 || !mapdata) return nullptr;
	return MAP(mapdata, pos_x, pos_y);
}

void astarnode_map::CreateMap(unsigned int size_x, unsigned int size_y)
{
	if (mapdata) DeleteMap();

	this->size_x = size_x; this->size_y = size_y;


	mapdata = new astarnode*[size_y];
	for (unsigned int i = 0; i < size_y; i++)
		mapdata[i] = new astarnode[size_x];

	for (unsigned int yi = 1; yi <= size_y; yi++)
	{
		for (unsigned int xi = 1; xi <= size_x; xi++)
		{
			MAP(mapdata, xi, yi)->x = xi;
			MAP(mapdata, xi, yi)->y = yi;
		}
	}
}

void astarnode_map::DeleteMap()
{
	if (!mapdata) return;

	for (unsigned int yi = 1; yi <= size_y; yi++)
	{
		delete [] mapdata[yi - 1];
	}
	delete [] mapdata;

	size_x = 0; size_y = 0;
}