#include "astarnode.h"

bool list_astarnode::list_is_valid(void)
{
	if (prev) return false; //list에서 prev값은 항상 nullptr이어야 함.

	if (dataptr && lastelem) //데이터의 무결성 확인.
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
		linked_astarnode *oldhead = new linked_astarnode;
		oldhead->dataptr = dataptr; oldhead->next = next; oldhead->prev = this;
		if(oldhead->next) oldhead->next->prev = oldhead;
		dataptr = data; next = oldhead;
		if (lastelem == this) lastelem = lastelem->next;
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

	if (lastelem == this)
	{
		lastelem = nullptr;
		dataptr = nullptr; prev = nullptr; next = nullptr;
	}
	else
	{
		dataptr = next->dataptr;
		next = next->next;
		prev = nullptr;
	}

	return retval;
}

astarnode *list_astarnode::pop_back(void)
{
	if (!list_is_valid()) return nullptr;

	astarnode *retval = lastelem->dataptr;

	if (lastelem == this)
	{
		lastelem = nullptr;
		dataptr = nullptr; prev = nullptr; next = nullptr;
	}
	else
	{
		lastelem = lastelem->prev;
		delete lastelem->next; lastelem->next = nullptr;
	}

	return retval;
}

linked_astarnode *list_astarnode::search(astarnode *data)
{
	if (!data) return nullptr;

	linked_astarnode *iterator = this;
	while (iterator)
	{
		if (!iterator->dataptr)
		{
			iterator = nullptr; break;
		}

		if (iterator->dataptr->x == data->x && iterator->dataptr->y == data->y)
			break;
		else
			iterator = iterator->next;
	}

	return iterator;
}

//Bubble Sort 사용.
void list_astarnode::SortByFval(void)
{
	///현재 성공이 확인된 소트.

	bubble_sort_by_fval();//버블 정렬


	///실패 목록
	//quick_sort_by_fval(this, this, lastelem);//퀵 정렬. 대체로 잘 작동하는 듯 하지만 좀만 복잡해지면 꼬인다..


	

	
}

void list_astarnode::quick_sort_by_fval(linked_astarnode *head, linked_astarnode *oldleft, linked_astarnode *oldright)
{
	linked_astarnode *left = oldleft, *right = oldright;
	astarnode *pivotvalue = oldleft->dataptr;
	
	while (left != right)
	{
		while (left != right && right->dataptr->f >= pivotvalue->f) right = right->prev;
		if (left != right) left->dataptr = right->dataptr;

		while (left != right && left->dataptr->f <= pivotvalue->f) left = left->next;
		if (left != right) right->dataptr = left->dataptr;
	}

	left->dataptr = pivotvalue;

	if (left != oldleft)
		quick_sort_by_fval(head, oldleft, left->prev);
	if (left != oldright)
		quick_sort_by_fval(head, left->next, oldright);
}
void list_astarnode::bubble_sort_by_fval()
{
	linked_astarnode *iterator;
	linked_astarnode *bubblelast = lastelem;

	//손쉽게 O(n^2) 가 나오는 모습이다...
	while (bubblelast != this)
	{
		iterator = this;
		while (iterator->dataptr)
		{
			if (iterator->dataptr->f > iterator->next->dataptr->f)
			{
				astarnode *tempptr = iterator->dataptr;
				iterator->dataptr = iterator->next->dataptr;
				iterator->next->dataptr = tempptr;
			}

			if (iterator->next == bubblelast)
				break;

			iterator = iterator->next;
		}
		bubblelast = iterator;
	}
}