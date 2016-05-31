#include "node.h"

void linkednodehead::Add(node *data)
{
	if (!data) return;

	if (!dataptr)
	{
		dataptr = data;
		last = this;
	}
	else
	{
		last->next = new linkednodehead;
		last->next->dataptr = data;
		last = last->next;
	}
}
void linkednodehead::Pop(node *data)
{
	data = dataptr;
	dataptr = next->dataptr;
	next = next->next;
}
void linkednodehead::SortByFval()
{
	linkednode *iterator;
	linkednode *bubblelast = last;

	while (bubblelast != this)
	{
		iterator = this;

		while (true)
		{
			//dataptr값을 스왑하는 것으로 끝.
			if (iterator->dataptr->f > iterator->next->dataptr->f)
			{
				node *tempptr = iterator->dataptr;
				iterator->dataptr = iterator->next->dataptr;
				iterator->next->dataptr = tempptr;
			}

			if (iterator->next == bubblelast) 
				break;
			else
				iterator = iterator->next;
		}

		bubblelast = iterator;
	}
}
linkednode *linkednodehead::Search(node *data)
{
	linkednode *iterator = this;

	while (iterator)
	{
		if (iterator->dataptr->x == data->x && iterator->dataptr->y == data->y)
			break;
		iterator = iterator->next;
	}

	return iterator;
}