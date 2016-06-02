#include "astarnode.h"

bool list_astarnode::list_is_valid(void)
{
	if (prev) return false; //list���� prev���� �׻� nullptr�̾�� ��.

	if (dataptr && lastelem) //�������� ���Ἲ Ȯ��.
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

	if (lastelem == this)
	{
		lastelem = nullptr;
		dataptr = nullptr; prev = nullptr; next = nullptr;
	}
	else
	{
		dataptr = next->dataptr;
		next = next->next;
		delete prev; prev = nullptr;
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

//Bubble Sort ���. �����ϱ� ����ϱ�.
//f���� ���� ������� ���ĵ�.
//���� ���� ��� �������� ����.

//�����Ʈ���� �����߻�.
//�ٸ��ŷ� �ٲ����.

//����Ʈ�� ����.
void list_astarnode::SortByFval(void)
{
	quick_sort_by_fval(this, this, lastelem);
}

void list_astarnode::quick_sort_by_fval(linked_astarnode *head, linked_astarnode *oldleft, linked_astarnode *oldright)
{
	if (!head || !oldleft || !oldright) return;
	if (oldleft == oldright) return;

	linked_astarnode *left = oldleft; linked_astarnode *right = oldright;
	astarnode *temp;
	float fval_pivot = left->dataptr->f;

	while (left != right && left != nullptr && right != nullptr)
	{
		while (left->dataptr->f <= fval_pivot && left != right) left = left->next;
		while (right->dataptr->f >= fval_pivot && left != right) right = right->prev;
		temp = left->dataptr;
		left->dataptr = right->dataptr;
		right->dataptr = temp;
	}
	temp = oldleft->dataptr;
	oldleft->dataptr = left->dataptr;
	left->dataptr = temp;

	quick_sort_by_fval(head, oldleft, left->prev);
	quick_sort_by_fval(head, left->next, oldright);
}