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
bool equal(const Node<T>* lhs, const Node<T>* rhs)
{
	if (lhs == nullptr || rhs == nullptr)
		return lhs == rhs;

	if (lhs->data != rhs->data)
		return false;

	return equa(lhs->left, rhs->left) && equa(lhs->right, rhs->right)
}

template <class T>
bool isSbutree(const Node<T>* tree, const Node<T>* subTree)
{
	if (subTree == nullptr)
		return true;

	if (equal(tree, subTree))
		return true;

	if (tree == nullptr)
		return false;

	return isSbutree(tree->left, subTree) || isSbutree(tree->right, subTree);
}

int main()
{
	
}
