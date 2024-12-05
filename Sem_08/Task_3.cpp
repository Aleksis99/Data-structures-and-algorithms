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
bool equal(const Node<T>* left, const Node<T>* right)
{
	if (left == nullptr && right == nullptr)
		return true;

	if (left == nullptr || right == nullptr)
		return false;

	if (left->data != right->data)
		return false;

	return equal(left->left, right->left) && equal(left->right, right->right)
}

int main()
{
	
}
