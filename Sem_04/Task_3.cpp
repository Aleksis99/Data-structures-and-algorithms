#include <iostream>
#include <stack>

struct Node
{
	int data;
	Node *next;

	Node(int data, Node *next = nullptr) : data(data), next(next) {}
};

bool isPalindrome(const Node *head)
{
	std::stack<int> st;

	for (const Node *iter = head; iter != nullptr; iter = iter->next)
	{
		st.push(iter->data);
	}

	while (head != nullptr)
	{
		if (head->data != st.top())
			return false;

		st.pop();
		head = head->next;
	}

	return true;
}

int main()
{
}
