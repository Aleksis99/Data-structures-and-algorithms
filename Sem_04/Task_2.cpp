#include <iostream>

struct Node
{
	int data;
	Node* next;

	Node(int data, Node* next = nullptr) : data(data), next(next) {}
};

unsigned getDecimalValue(const Node* head)
{
	unsigned result = 0;

	while (head != nullptr)
	{
		result = (result << 1) + head->data;
		head = head->next;
	}

	return result;
}

int main()
{

}
