#include <iostream>
#include <queue>
#include <vector>
#include <stack>
#include <list>

struct Node
{
	int data;
	Node* next;

	Node(int data, Node* next = nullptr) : data(data), next(next) {}
};


// Task 1
Node* reverse(Node* head)
{
	Node* reversed = nullptr;

	while (head != nullptr)
	{
		Node* next = head->next;
		head->next = reversed;
		reversed = head;
		head = next;
	}

	return reversed;
}

// Task 2
bool hasCycle(Node* head)
{
	if (head == nullptr)
		return false;


	Node* slow = head;
	Node* fast = head->next;

	while (fast != nullptr && fast->next != nullptr)
	{
		if (slow == fast)
			return true;

		slow = slow->next;
		fast = fast->next->next;
	}

	return false;
}

Node* findMiddle(Node* head)
{
	if (head == nullptr || head->next == nullptr)
		return head;

	Node* slow = head;
	Node* fast = head->next;

	while (fast != nullptr && fast->next != nullptr)
	{
		slow = slow->next;
		fast = fast->next->next;
	}

	return slow;
}

Node* merge(Node* left, Node* right)
{
	if (left == nullptr)
		return right;
	if (right == nullptr)
		return left;

	Node* curr = nullptr;

	if (left->data <= right->data)
	{
		curr = left;
		left = left->next;
	}
	else
	{
		curr = right;
		right = right->next;
	}

	Node* result = curr;

	while (left != nullptr && right != nullptr)
	{
		if (left->data <= right->data)
		{
			curr->next = left;
			left = left->next;
		}
		else
		{
			curr->next = right;
			right = right->next;
		}

		curr = curr->next;
	}

	if (left == nullptr)
	{
		curr->next = right;
	}
	else
	{
		curr->next = left;
	}

	return result;
}

// Task 3
Node* mergesort(Node* head)
{
	if (head == nullptr || head->next == nullptr)
	{
		return head;
	}

	Node* middle = findMiddle(head);
	Node* right = middle->next;
	middle->next = nullptr;

	return merge(mergesort(head), mergesort(right));
}

// Task 4
void equalize(std::list<std::stack<int>>& stacks)
{
	std::stack<int> s;

	for (std::stack<int>& currStack : stacks)
	{
		while (!currStack.empty())
		{
			s.push(currStack.top());
			currStack.pop();
		}
	}

	std::list<std::stack<int>>::iterator it = stacks.begin();

	while (!s.empty())
	{
		if (it == stacks.end())
		{
			it = stacks.begin();
		}

		it->push(s.top());
		s.pop();
		++it;
	}
}

// Task 4 var 2
void equalize2(std::list<std::stack<int>>& stacks)
{
	if (stacks.empty())
		return;

	size_t totalElements = 0;
	size_t numStacks = stacks.size();

	for (const std::stack<int>& currStack : stacks)
	{
		totalElements += currStack.size();
	}

	size_t minElementsPerStack = totalElements / numStacks;
	size_t overflow = totalElements % numStacks;

	std::queue<int> extras;

	for (std::stack<int>& currStack : stacks)
	{

		while (currStack.size() > minElementsPerStack)
		{
			extras.push(currStack.top());
			currStack.pop();
		}
	}

	for (std::stack<int>& currStack : stacks)
	{
		while (currStack.size() < minElementsPerStack)
		{
			currStack.push(extras.front());
			extras.pop();
		}

		if (overflow > 0)
		{
			currStack.push(extras.front());
			extras.pop();
			overflow--;
		}
	}
}

Node* doubleRecHelp(const Node* head, int& carry)
{
	if (head == nullptr)
		return nullptr;

	Node* doubledNext = doubleRecHelp(head->next, carry);

	int value = head->data * 2 + carry;
	carry = value / 10;

	return new Node(value % 10, doubledNext);
}

// Task 5, recursive
Node* doubleItRec(const Node* head)
{
	int carry = 0;
	Node* result = doubleRecHelp(head, carry);

	if (carry > 0)
	{
		result = new Node(carry, result);
	}

	return result;
}

// Task 5, with a stack
Node* doubleIt(const Node* head)
{
	std::stack<const Node*> s;

	while (head != nullptr)
	{
		s.push(head);
		head = head->next;
	}

	Node* result = nullptr;
	int carry = 0;

	while (!s.empty())
	{
		int value = s.top()->data * 2 + carry;
		s.pop();

		carry = value / 10;
		result = new Node(value % 10, result);
	}

	if (carry > 0)
	{
		result = new Node(carry, result);
	}

	return result;
}

// Task 6
Node* doubleReversed(const Node* head)
{
	Node dummy(0);
	Node* tail = &dummy;
	int carry = 0;

	while (head != nullptr)
	{
		int value = head->data * 2 + carry;
		carry = value / 10;

		tail->next = new Node(value % 10);
		tail = tail->next;
		head = head->next;
	}

	if (carry > 0)
	{
		tail->next = new Node(carry);
	}

	return dummy.next;
}

int main()
{

}
