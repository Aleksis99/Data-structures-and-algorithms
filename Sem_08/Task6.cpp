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
	Node *left;
	Node *right;
	Node(const T &data, Node *left = nullptr, Node *right = nullptr)
		: data(data), left(left), right(right) {};
};

int solveTask(const Node<int> *root, bool isEven)
{
	if (root == nullptr)
		return 0;

	int sumChildren = solveTask(root->left, !isEven) + solveTask(root->right, !isEven);

	if (isEven && root->left == nullptr && root->right != nullptr)
	{
		return root->data + sumChildren;
	}

	return sumChildren;
}

int solveTask(const Node<int> *root)
{
	bool isEven = false;
	return solveTask(root, isEven);
}

int main()
{
}
