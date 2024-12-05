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

template <class T>
void treeMin(const Node<T>* node, T& currMin)
{
	if (node == nullptr)
		return;

	currMin = std::min(node->data, currMin);

	treeMin(node->left, currMin);
	treeMin(node->right, currMin);
}

template <class T>
T treeMin(const Node<T>* node)
{
	if (node == nullptr)
		throw "Empty tree";

	T currMin = node->data;

	treeMin(node, currMin);
	return currMin;
}

template <class T>
void treeMax(const Node<T>* node, T& currMax)
{
	if (node == nullptr)
		return;

	currMax = std::max(node->data, currMax);

	treeMax(node->left, currMax);
	treeMax(node->right, currMax);
}

template <class T>
T treeMax(const Node<T>* node)
{
	if (node == nullptr)
		throw "Empty tree";

	T currMax = node->data;

	treeMax(node, currMax);
	return currMax;
}


template <class T>
bool isBST(const Node<T>* root, const T& min, const T& max, bool& foundMin, bool& foundMax)
{
	if (root == nullptr)
		return true;

	if (root->data > max || root->data < min)
		return false;

	if (root->data == min)
	{
		if (foundMin)
			return false;

		foundMin = true;
	}

	if (root->data == max)
	{
		if (foundMax)
			return false;

		foundMax = true;
	}

	return isBST(root->left, min, root->data, foundMin, foundMax)
		&& isBST(root->right, root->data, max, foundMin, foundMax);
}

template <class T>
bool isBST(const Node<T>* root)
{
	if (root == nullptr)
		return true;

	T min = treeMin(root);
	T max = treeMax(root);

	bool foundMin = false;
	bool foundMax = false;


	return isBST(root, min, max, foundMin, foundMax);
}

int main()
{
	Node<int>* root = new Node<int>(50);
	Node<int>* n1 = new Node<int>(25);
	Node<int>* n2 = new Node<int>(75);
	Node<int>* n3 = new Node<int>(12);
	Node<int>* n4 = new Node<int>(30);
	Node<int>* n5 = new Node<int>(60);
	Node<int>* n6 = new Node<int>(85);
	Node<int>* n7 = new Node<int>(52);
	Node<int>* n8 = new Node<int>(70);

	root->left = n1;
	root->right = n2;
	n1->left = n3;
	n1->right = n4;
	n2->left = n5;
	n2->right = n6;
	n5->left = n7;
	n5->right = n8;

	std::cout << isBST(root);
}
