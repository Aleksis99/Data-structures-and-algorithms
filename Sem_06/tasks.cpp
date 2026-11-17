#include <iostream>
#include <stack>
#include <list>
#include <string>
#include <cctype>
#include <stdexcept>
#include <initializer_list>

constexpr char TRUE_MARK = 't';
constexpr char FALSE_MARK = '0';

struct Node
{
	int data;
	Node* next;

	Node(int data, Node* next = nullptr) : data(data), next(next) {}
};


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


long long getNum(const std::list<int>& l)
{
	long long result = 0;

	for (std::list<int>::const_iterator it = l.cbegin(); it != l.cend(); ++it)
	{
		result *= 10;
		result += *it;
	}

	return result;
}

long long getReversedNum(const std::list<int>& l)
{
	long long result = 0;

	for (std::list<int>::const_reverse_iterator it = l.crbegin(); it != l.crend(); ++it)
	{
		result *= 10;
		result += *it;
	}

	return result;
}

long long findListsSum(const std::list<std::list<int>>& lists)
{
	long long result = 0;

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
	if (head == nullptr)
		return head;

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
		iter->next = s.top();
		iter = iter->next;
		s.pop();
	}

	iter->next = nullptr;
	return head;
}

Node* shuffle2(Node* head)
{
	if (head == nullptr)
		return head;

	Node* middle = findMiddle(head);
	Node* secondHalf = middle->next;

	if (secondHalf == nullptr)
		return head;

	middle->next = nullptr;

	Node* reversed = reverseStack(secondHalf);
	secondHalf->next = head;

	return reversed;
}


bool isLetter(char c)
{
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool evalOp(char op, bool hasTrue, bool hasFalse)
{
	switch (op)
	{
	case '!':
		return !hasTrue;

	case '&':
		return !hasFalse;

	case '|':
		return hasTrue;

	default:
		throw std::invalid_argument("Unknown operator");
	}
}

bool evalExpr(const std::string expr)
{
	std::stack<char> s;

	for (char c : expr)
	{
		if (c == ',' || c == '\'')
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

			if (s.empty())
				throw std::invalid_argument("Missing '('");

			s.pop(); // '('

			if (s.empty())
				throw std::invalid_argument("Missing operator before '('");

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
		throw std::invalid_argument("Invalid expression");

	return letter(s.top());
}


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

DCLE* getToDelete(DCLE* head)
{
	if (head == nullptr)
		return nullptr;

	DCLE* iter = head;

	do
	{
		if (shouldDelete(iter))
			return iter;

		iter = iter->next;
	} while (iter != head);

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

// Simple version: find the first element with the property, delete it, start over.
// O(n^2) in the worst case. 
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

}
