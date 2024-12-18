#include <iostream>
#include <queue>
#include <vector>
#include <stack>
#include <list>
#include <string>

template <class T>
struct Node
{
	T data;
	Node* left;
	Node* right;
	Node(const T& data, Node* left = nullptr, Node* right = nullptr)
		: data(data), left(left), right(right) {};
};

void iterateLevel(std::queue<const Node<char>*>& q, bool& hasNodes)
{
	size_t levelSize = q.size();

	for (size_t i = 0; i < levelSize; i++)
	{
		const Node<char>* currNode = q.front();
		q.pop();

		if (currNode == nullptr)
		{
			std::cout << "_";

			q.push(nullptr);
			q.push(nullptr);
		}
		else
		{
			std::cout << currNode->data;

			q.push(currNode->left);
			q.push(currNode->right);

			hasNodes |=  currNode->left != nullptr
				|| currNode->right != nullptr;
		}
	}

	std::cout << std::endl;
}

void printLevel(const Node<char>* root)
{
	if (root == nullptr)
		return;

	std::queue<const Node<char>*> q;
	q.push(root);
	bool hasNodes = true;

	while (hasNodes)
	{
		hasNodes = false;
		iterateLevel(q, hasNodes);
	}
}

int main()
{
	Node<char>* n1 = new Node<char>('a');
	Node<char>* n2 = new Node<char>('b');
	Node<char>* n3 = new Node<char>('c');
	Node<char>* n4 = new Node<char>('d');
	n1->right = n2;
	n2->right = n3;
	n3->left = n4;
	printLevel(n1);
}
