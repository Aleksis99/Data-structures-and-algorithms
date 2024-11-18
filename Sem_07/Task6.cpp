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
int count(const Node<T>* root)
{
	if (root == nullptr)
		return 0;

	return 1 + count(root->left) + count(root->right);
}

bool elemsFrom1toN(const Node<int>* root, std::vector<bool>& seen)
{
	if (root == nullptr)
		return true;

	if (root->data <= 0 || root->data > seen.size() || seen[root->data - 1])
		return false;

	seen[root->data - 1] = true;

	return elemsFrom1toN(root->left, seen) && elemsFrom1toN(root->right, seen);
}

bool elemsFrom1toN(const Node<int>* root)
{
	int countElems = count(root);
	std::vector<bool> seen = std::vector<bool>(countElems, false);
	return elemsFrom1toN(root, seen);
}

int main()
{
	Node<int>* root = new Node<int>(2);
	Node<int>* n1 = new Node<int>(7);
	Node<int>* n2 = new Node<int>(5);
	Node<int>* n3 = new Node<int>(2);
	Node<int>* n4 = new Node<int>(6);
	Node<int>* n5 = new Node<int>(9);
	Node<int>* n6 = new Node<int>(5);
	Node<int>* n7 = new Node<int>(11);
	Node<int>* n8 = new Node<int>(4);

	root->left = n1;
	root->right = n2;
	n1->left = n3;
	n1->right = n4;
	n2->right = n5;
	n4->left = n6;
	n4->right = n7;
	n5->left = n8;

	std::cout << count(root);
}
