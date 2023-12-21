#include <iostream>
#include <vector>
#include <string>
#include <list>

using namespace std;

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

	return equal(lhs->left, rhs->left) && equal(lhs->right, rhs->right);
}

//Да се напише функция, която приема двоично дърво T и двоично дърво R и проверява дали R е поддърво на T.
template <class T>
bool hasSubtree(const Node<T>* t, const Node<T>* r)
{
	if (equal(t, r))
		return true;

	return hasSubtree(t->left, r) || hasSubtree(t->right, r);
}

int main()
{
	
}