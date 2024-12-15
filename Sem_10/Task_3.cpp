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

void hasEvenPaths(const Node<int>* root, int& counter)
{
	if (counter > 1)
		return;

	if (root == nullptr)
		return;

	if (root->data % 2 == 1)
		return;

	if (root->left == nullptr && root->right == nullptr)
	{
		counter++;
		return;
	}

	hasEvenPaths(root->left, counter);
	hasEvenPaths(root->right, counter);
}

bool hasEvenPaths(const Node<int>* root)
{
	int count = 0;
	hasEvenPaths(root, count);

	return count > 1;
}

int main()
{
	
}
