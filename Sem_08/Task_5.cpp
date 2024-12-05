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

int countInInterval(const Node<int> *root, int min, int max)
{
	if (root == nullptr)
		return 0;

	int countChildren = countInInterval(root->left, min, max) + countInInterval(root->right, min, max);

	if (root->data < min || root->data > max)
		return countChildren;

	return countChildren + 1;
}

int sumInInterval(const Node<int> *root, int min, int max)
{
	if (root == nullptr)
		return 0;

	int sumChildren = sumInInterval(root->left, min, max) + sumInInterval(root->right, min, max);

	if ((countInInterval(root->left, min, max) + countInInterval(root->right, min, max)) % 2 == 1)
		return root->data + sumChildren;

	return sumChildren;
}

int main()
{
}
