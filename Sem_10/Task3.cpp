#include <iostream>
#include <string>
#include <queue>

template <class T>
struct Node
{
	T data;
	Node* left;
	Node* right;

	Node(const T& data, Node* left = nullptr, Node* right = nullptr)
		: data(data), left(left), right(right) {};
};


template <class T>
void printLevel(std::queue<const Node<T>*>& q, bool& hasNodes)
{
	hasNodes = false;
	size_t currLevel = q.size();

	for (size_t i = 0; i < currLevel; i++)
	{
		const Node<T>* curr = q.front();
		q.pop();

		if (curr != nullptr)
		{
			std::cout << curr->data;

			q.push(curr->left);
			q.push(curr->right);

			hasNodes = hasNodes
				|| curr->left != nullptr
				|| curr->right != nullptr;
		}
		else
		{
			std::cout << "_";
			q.push(nullptr);
			q.push(nullptr);
		}
	}
}

template <class T>
void print(const Node<T>* root)
{
	if (root == nullptr)
		return;

	std::queue<const Node<T>*> q;
	q.push(root);
	bool hasNodes = true;

	while (hasNodes)
	{
		printLevel(q, hasNodes);
		std::cout << std::endl;
	}
	
}

int main()
{
	Node<char>* root =	new Node<char>('a');
	Node<char>* n1 =	new Node<char>('b');
	Node<char>* n2 =	new Node<char>('c');
	Node<char>* n3 =	new Node<char>('d');
	Node<char>* n4 =	new Node<char>('e');
	Node<char>* n5 =	new Node<char>('f');
	Node<char>* n6 =	new Node<char>('g');
	Node<char>* n7 =	new Node<char>('h');
	Node<char>* n8 =	new Node<char>('I');

	root->left = n1;
	root->right = n2;
	n1->left = n3;
	n1->right = n4;
	n2->left = n5;
	n2->right = n6;
	n5->left = n7;
	n5->right = n8;

	print(root);
}
