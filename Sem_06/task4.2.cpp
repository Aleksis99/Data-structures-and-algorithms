#include <iostream>
#include <cstddef>
#include <initializer_list>



struct DCLE
{
	int inf;
	DCLE* next;
	DCLE* prev;
};

bool shouldDelete(const DCLE* node)
{
	if (node == nullptr || node->next == node)
		return false;

	if (node->next->inf == 0 || node->prev->inf == 0)
		return false;

	return node->inf % node->next->inf == 0 && node->inf % node->prev->inf == 0;
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

DCLE* task4(DCLE* head)
{
	if (head == nullptr)
		return nullptr;

	std::size_t size = 1;
	for (DCLE* iter = head->next; iter != head; iter = iter->next)
		++size;

	DCLE* curr = head;
	std::size_t checkedInRow = 0;

	while (checkedInRow < size)
	{
		if (shouldDelete(curr))
		{
			DCLE* prev = curr->prev;
			bool wasHead = curr == head;

			DCLE* next = deleteNode(curr);
			--size;

			if (next == nullptr)
				return nullptr;

			if (wasHead)
				head = next;

			curr = prev;
			checkedInRow = 0;
		}
		else
		{
			curr = curr->next;
			++checkedInRow;
		}
	}

	return head;
}


int main()
{
}
