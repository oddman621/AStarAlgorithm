#pragma once
#include <math.h>

#define DISTANCE_UNIT	1
#define DISTANCE_CROSS	sqrt(2)

struct astarnode
{
public:
	double f = 0, g = 0, h = 0;
	int x = 0, y = 0;
	astarnode *parent = nullptr;
	astarnode() {}
	astarnode(float x, float y, float start_x, float start_y, float dest_x, float dest_y)
	{
		this->x = x; this->y = y;
		g = pow(x - start_x, 2) + pow(y - start_y, 2);
		h = pow(x - dest_x, 2) + pow(y - dest_y, 2);
		f = g + h;
	}
	virtual ~astarnode() {}
};

struct linked_astarnode
{
	astarnode *dataptr;
	linked_astarnode *prev;
	linked_astarnode *next;
};

class list_astarnode : public linked_astarnode
{
private:
	linked_astarnode *lastelem = nullptr;
	bool list_is_valid(void);
public:
	void push_front(astarnode *data);
	void push_back(astarnode *data);
	astarnode *pop_front(void);
	astarnode *pop_back(void);
	linked_astarnode *search(astarnode *data);
	void SortByFval(void);
};