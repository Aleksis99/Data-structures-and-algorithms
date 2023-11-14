#include <iostream>
#include <list>
#include <stack>
struct Node
{
	int data;
	Node* next = nullptr;

	Node(int d, Node* n = nullptr) : data{ d }, next{ n } {}
};

void print(Node* ll)
{
	while (ll)
	{
		std::cout << ll->data << " ";
		ll = ll->next;
	}
	std::cout << std::endl;
}

void free(Node*& ll)
{
	while (ll)
	{
		Node* toDelete = ll;
		ll = ll->next;
		delete toDelete;
	}
}

// reverse a linked list
Node* reverse(Node* ll)
{
	Node* toReturn = nullptr;
	Node* next = nullptr;

	while (ll)
	{
		next = ll->next;

		// push front
		ll->next = toReturn;
		toReturn = ll;

		ll = next;
	}

	return toReturn;
}

// true if there is a cycle in the linked list. false otherwise.
bool hasCycle(Node* ll)
{
	Node* slow = ll;
	Node* fast = ll;

	while (fast && fast->next)
	{
		slow = slow->next;
		fast = fast->next->next;

		if (slow == fast) return true;
	}

	return false;
}

// add element to a tail and returns the new tail.
Node* push_back(Node* tail, Node* elem)
{
	tail->next = elem;
	return elem;
}

// helper for merge sort. append the next sorted element (arg) into tail (tail)
Node* appentNext(Node* tail, Node*& arg, Node*& toReturn)
{
	if (!toReturn)
	{
		toReturn = tail = arg;
		arg = arg->next;
	}
	else
	{
		tail = push_back(tail, arg);
		arg = arg->next;
	}

	return tail;
}

// Merge two sorted linked lists
Node* merge(Node* left, Node* right)
{
	Node* toReturn = nullptr;
	Node* it = nullptr;

	while (left && right)
	{
		Node*& toAppend = left->data < right->data ? left : right;
		it = appentNext(it, toAppend, toReturn);
	}

	Node* rest = left ? left : right;

	while (rest)
	{
		it = appentNext(it, rest, toReturn);
	}

	if (it)
		it->next = nullptr;

	return toReturn;
}

// returns one element before the middle of a linked list.
Node* findMiddle(Node* ll)
{
	Node* fast = ll;
	Node* slow = ll;
	Node* prev = ll;

	while (fast && fast->next)
	{
		prev = slow;
		fast = fast->next->next;
		slow = slow->next;
	}

	return prev;

}

// sorts linked list.
Node* mergeSort(Node* ll)
{
	if (!ll || !ll->next)
	{
		return ll;
	}

	Node* middle = findMiddle(ll);
	Node* rightList = middle->next;
	middle->next = nullptr;

	Node* left = mergeSort(ll);
	Node* right = mergeSort(rightList);

	return merge(left, right);
}

// Add new element with value data in the beginning of ll.
Node* pushFront(Node* ll, int data)
{
	return new Node(data, ll);
}

// after equalize is done each pair of stacks in ll
// has difference in their sizes which is at most 1.
void equalize(std::list<std::stack<int>>& ll)
{
	std::stack<int> helper;

	for (std::stack<int>& st : ll)
	{
		while (!st.empty())
		{
			helper.push(st.top());
			st.pop();
		}
	}
	using ListIterator = std::list<std::stack<int>>::iterator;

	ListIterator it = ll.begin();

	while (!helper.empty())
	{
		if (it == ll.end()) it = ll.begin();
		it->push(helper.top());
		helper.pop();
		++it;
	}
}

// ll is a number represented as linked list.
// this function returns 2 * number represented as linked list.
Node* doubleIt(Node* ll)
{
	std::stack<Node*> st;
	Node* toReturn = ll;

	while (ll)
	{
		st.push(ll);
		ll = ll->next;
	}

	bool carry = false;

	while (!st.empty())
	{
		st.top()->data = 2 * st.top()->data + carry;
		carry = false;

		if (st.top()->data >= 10)
		{
			st.top()->data -= 10;
			carry = true;
		}

		st.pop();
	}

	if (carry)
	{
		toReturn = new Node(1, toReturn);
	}

	return toReturn;
}

Node* doubleItReverse(Node* ll)
{
	ll = reverse(ll);

	Node* toReturn = ll;
	Node* prev = ll;
	bool carry = false;

	while (ll)
	{
		ll->data = 2 * ll->data + carry;
		carry = false;

		if (ll->data >= 10)
		{
			ll->data -= 10;
			carry = true;
		}

		prev = ll;
		ll = ll->next;
	}

	if (carry)
	{
		prev->next = new Node(1);
	}

	return reverse(toReturn);
}

int main()
{
	
}