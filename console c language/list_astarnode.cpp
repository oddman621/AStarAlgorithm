#include "astarnode.h"

bool list_astarnode::list_is_valid(void)
{
	if (dataptr && lastelem)
		return true;

	return false;
}

void list_astarnode::push_front(astarnode *data)
{
	if (!data) return;

	if (!list_is_valid())
	{
		dataptr = data;
		lastelem = this;
	}
	else
	{
		linked_astarnode *temp = new linked_astarnode;
		temp->dataptr = dataptr; temp->next = next; temp->prev = this;
		dataptr = data;
		next = temp;
	}
}

void list_astarnode::push_back(astarnode *data)
{
	if (!data) return;

	if (!list_is_valid())
	{
		dataptr = data;
		lastelem = this;
	}
	else
	{
		lastelem->next = new linked_astarnode;
		lastelem->next->prev = lastelem;
		lastelem = lastelem->next;
		lastelem->dataptr = data;
	}
}

astarnode *list_astarnode::pop_front(void)
{
	if (!list_is_valid()) return nullptr;

	astarnode *retval = dataptr;

	dataptr = next->dataptr;
	next = next->next;
	delete prev; prev = nullptr;

	return retval;
}

astarnode *list_astarnode::pop_back(void)
{
	if (!list_is_valid()) return nullptr;

	astarnode *retval = lastelem->dataptr;

	lastelem = lastelem->prev;
	delete lastelem->next; lastelem->next = nullptr;

	return retval;
}

linked_astarnode *list_astarnode::search(astarnode *data)
{
	if (!data) return nullptr;

	linked_astarnode *iterator = this;
	while (iterator)
	{
		if (iterator->dataptr->x == data->x && iterator->dataptr->y == data->y)
			break;
		else
			iterator = iterator->next;
	}

	return iterator;
}

//Bubble Sort
void list_astarnode::SortByFval(void)
{
	if (!list_is_valid() && !next) return;

	linked_astarnode *iterator = this;
	linked_astarnode * bubblelast = lastelem;

	while (bubblelast != this)
	{
		iterator = this;
		while (true)
		{
			if (iterator->dataptr->f > iterator->next->dataptr->f)
			{
				astarnode *tempptr = iterator->dataptr;
				iterator->dataptr = iterator->next->dataptr;
				iterator->next->dataptr = tempptr;
			}

			if (iterator->next == bubblelast)
				break;
			else
				iterator = iterator->next;
		}
		bubblelast = bubblelast->prev;
	}
}