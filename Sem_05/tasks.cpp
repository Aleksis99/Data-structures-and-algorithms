#include <iostream>
#include <queue>
#include <vector>
#include <stack>
#include <list>

struct Node
{
	int data;
	Node* next;

	Node(int data, Node* next = nullptr) : data(data), next(next) {};
};

void print(Node* head)
{
	while (head != nullptr)
	{
		std::cout << head->data << " ";
		head = head->next;
	}

	std::cout << std::endl;
}

Node* reverse(Node* head)
{
	if (head == nullptr)
		return head;

	Node* reversed = nullptr;
	Node* next = head->next;

	while (head->next != nullptr)
	{
		head->next = reversed;
		reversed = head;
		head = next;
		next = head->next;
	}
	head->next = reversed;
	return head;
}

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

	if (left->data < right->data)
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
		if (left->data < right->data)
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

void equalize(std::list<std::stack<int>>& list)
{
	std::stack<int> s;

	for (std::stack<int>& currStack : list)
	{
		while (!currStack.empty())
		{
			s.push(currStack.top());
			currStack.pop();
		}
	}

	std::list<std::stack<int>>::iterator it = list.begin();

	while (!s.empty())
	{
		if (it == list.end())
		{
			it = list.begin();
		}

		it->push(s.top());
		s.pop();
		++it;
	}
}

void equalize2(std::list<std::stack<int>>& list)
{
	int totalElements = 0;
	int numStacks = list.size();

	for (const std::stack<int>& currStack : list)
	{
		totalElements += currStack.size();
	}

	int minElementsPerStack = totalElements / numStacks;
	int overflow = totalElements % numStacks;

	std::stack<int> s;

	for (std::stack<int>& currStack : list)
	{

		while (currStack.size() > minElementsPerStack)
		{
			s.push(currStack.top());
			currStack.pop();
		}
	}

	for (std::stack<int>& currStack : list)
	{
		while (currStack.size() < minElementsPerStack)
		{
			currStack.push(s.top());
			s.pop();
		}

		if (overflow > 0)
		{
			currStack.push(s.top());
			s.pop();
			overflow--;
		}
	}
}

Node* doubleRecHelp(Node* head, bool& carry)
{
	if (head == nullptr)
		return head;

	carry = false;
	head->next = doubleRecHelp(head->next, carry);

	head->data *= 2;
	if (carry)
	{
		head->data += 1;
	}

	carry = false;

	if (head->data > 9)
	{
		head->data -= 10;
		carry = true;
	}

	return head;
}

Node* doubleItRec(Node* head)
{
	bool carry = false;
	Node* result = doubleRecHelp(head, carry);
	if (carry == true)
	{
		result = new Node(1, result);
	}

	return result;
}

Node* doubleIt(Node* head)
{
	std::stack<Node*> s;
	Node* it = head;

	while (it != nullptr)
	{
		s.push(it);
		it = it->next;
	}

	int carry = 0;

	while (!s.empty())
	{
		Node* curr = s.top();
		curr->data *= 2;
		curr->data += carry;
		carry = 0;
		s.pop();

		if (curr->data > 9)
		{
			carry = 1;
			curr->data -= 10;
		}
	}

	if (carry > 0)
	{
		head = new Node(1, head);
	}

	return head;
}



int main()
{

}
