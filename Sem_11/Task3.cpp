#include <iostream>
#include <string>
#include <queue>
#include <vector>

template <class T>
struct Node
{
	T data;
	Node* left;
	Node* right;

	Node(const T& data, Node* left = nullptr, Node* right = nullptr)
		: data(data), left(left), right(right) {};
};


void hasPathsHelp(const Node<int>* root, int& countPaths)
{
	if (root == nullptr || root->data % 2 == 1)
		return;

	if (countPaths > 1)
		return;

	if (root->left == nullptr && root->right == nullptr)
	{
		countPaths += 1;
	}
	else
	{
		hasPathsHelp(root->left, countPaths);
		hasPathsHelp(root->right, countPaths);
	}
}

bool hasPaths(const Node<int>* root)
{
	int countPaths;
	hasPathsHelp(root, countPaths);

	return countPaths > 1;
}

int main()
{
	
}
