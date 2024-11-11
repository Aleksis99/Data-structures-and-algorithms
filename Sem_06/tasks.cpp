#include <iostream>
#include <queue>
#include <vector>
#include <stack>
#include <list>
#include <string>

constexpr char True = 't';
constexpr char False = '0';

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

int getNum(const std::list<int>& l)
{
	int result = 0;

	for (std::list<int>::const_iterator it = l.cbegin(); it != l.cend(); ++it)
	{
		result *= 10;
		result += *it;
	}

	return result;
}

int getReversedNum(const std::list<int>& l)
{
	int result = 0;

	for (std::list<int>::const_reverse_iterator it = l.crbegin(); it != l.crend(); ++it)
	{
		result *= 10;
		result += *it;
	}

	return result;
}

int findListsSum(const std::list<std::list<int>>& lists)
{
	int result = 0;

	for (const std::list<int>& l : lists)
	{
		result += getNum(l);
		result += getReversedNum(l);
	}

	return result;
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

Node* shuffle(Node* head)
{
	Node* middle = findMiddle(head);

	Node* iter = middle->next;
	middle->next = nullptr;

	while (iter != nullptr)
	{
		Node* next = iter->next;
		iter->next = head;
		head = iter;
		iter = next;
	}

	return head;
}

Node* reverseStack(Node* head)
{
	if (head == nullptr)
		return head;

	std::stack<Node*> s;

	while (head != nullptr)
	{
		s.push(head);
		head = head->next;
	}

	head = s.top();
	s.pop();
	Node* iter = head;

	while (!s.empty())
	{
		Node* curr = s.top();
		iter->next = curr;
		iter = iter->next;
		s.pop();
	}

	return head;
}


Node* shuffle2(Node* head)
{
	Node* middle = findMiddle(head);

	Node* iter = middle->next;
	middle->next = nullptr;

	Node* reversed = reverseStack(iter);
	iter->next = head;

	return reversed;
}

bool letter(char c)
{
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool evalOp(char op, bool hasTrue, bool hasFalse)
{
	if (op == '!')
	{
		return !hasTrue;
	}

	if (op == '&')
	{
		return !hasFalse;
	}

	if (op == '|')
	{
		return hasTrue;
	}

	throw "Invalid expression";
}

bool evalExpr(const std::string expr)
{
	std::stack<char> s;

	for (char c : expr)
	{
		if (c == ',' || c =='\'')
			continue;

		if (c != ')')
		{
			s.push(c);
		}
		else
		{
			bool hasTrue = false;
			bool hasFlase = false;
			char top = s.top();

			while (top != '(')
			{
				if (letter(top))
					hasTrue = true;
				else
					hasFlase = true;

				s.pop();
				top = s.top();
			}

			s.pop();
			char op = s.top();
			s.pop();

			if (evalOp(op, hasTrue, hasFlase))
			{
				s.push(True);
			}
			else
			{
				s.push(False);
			}
		}
	}

	if (s.size() != 1)
		throw "Invalid expression";

	return letter(s.top());
}


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

DCLE* getToDelete(DCLE* head)
{
	if (head == nullptr)
		return nullptr;

	if (shouldDelete(head))
		return head;

	DCLE* iter = head->next;

	while (iter != head)
	{
		if (shouldDelete(iter))
			return iter;

		iter = iter->next;
	}

	return nullptr;
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
	DCLE* toDelete = getToDelete(head);

	while (toDelete != nullptr)
	{
		if (toDelete == head)
		{
			head = deleteNode(toDelete);
		}
		else
		{
			deleteNode(toDelete);
		}

		toDelete = getToDelete(head);
	}

	return head;
}

int main()
{
	//std::list<int> l;
	//l.push_back(1);
	//l.push_back(2);
	//l.push_back(3);
	//std::list<std::list<int>> ll;
	//ll.push_back(l);
	//ll.push_back(l);
	//std::cout << findListsSum(ll);
	Node* l1 = new Node(1, nullptr);
	Node* l2 = new Node(2, l1);
	Node* l3 = new Node(3, l2);
	Node* l4 = new Node(4, l3);
	Node* l5 = new Node(5, l4);

	Node* newHead = shuffle2(l5);
	print(newHead);

	//std::cout << evalExpr("!('*')") << std::endl;
	//std::cout << evalExpr("|('*', 'a')") << std::endl;
	//std::cout << evalExpr("&('B', '-')") << std::endl;
	//std::cout << evalExpr("|(&('c', '+', 'Z'), !('s'))") << std::endl;

}
