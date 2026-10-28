#include <iostream>

struct Node
{
	int data;
	Node* next;

	Node(int data, Node* next = nullptr) : data(data), next(next) {}
};

void removeDuplicates(Node* head)
{
	Node* iter = head;

	while (iter != nullptr && iter->next != nullptr)
	{
		if (iter->data == iter->next->data)
		{
			Node* toDelete = iter->next;
			iter->next = toDelete->next;
			delete toDelete;
		}
		else
		{
			iter = iter->next;
		}
	}
}

int main()
{

}
