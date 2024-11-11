#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
#include <list>

struct DCLE {
	int data;
	DCLE* next;
	DCLE* prev;
};

bool shouldDelete(DCLE* head)
{
	if (head == nullptr || head->next == 0 || head->prev == 0)
		return false;

	return head->data % head->next->data == 0 && head->data % head->prev->data;
}

DCLE* deleteNode(DCLE* toDelete)
{
	if (toDelete == nullptr)
		return nullptr;

	if (toDelete == toDelete->next)
	{
		delete toDelete;

		return nullptr;
	}

	toDelete->next->prev = toDelete->prev;
	toDelete->prev->next = toDelete->next;

	DCLE* next = toDelete->next;
	delete toDelete;

	return next;
}

std::list<DCLE*> getToDelete(DCLE* head)
{
	std::list<DCLE*> result;

	if (head == nullptr)
		return result;

	if (shouldDelete(head))
	{
		result.push_back(head);
	}

	DCLE* iter = head->next;

	while (iter != head)
	{
		if (shouldDelete(iter))
		{
			result.push_back(iter);
		}

		iter = iter->next;
	}

	return result;
}

DCLE* task4(DCLE* head)
{
	std::list<DCLE*> toDelete = getToDelete(head);

	while (toDelete.size() > 0)
	{
		for (DCLE* el : toDelete)
		{
			if (el == head)
			{
				head = deleteNode(el);
			}
			else
			{
				deleteNode(el);
			}
		}

		toDelete = getToDelete(head);
	}

	return head;
}

int main()
{

}