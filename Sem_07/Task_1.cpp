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
	Node(const T& data, Node* left=nullptr, Node* right=nullptr) 
		: data(data), left(left), right(right) {};
};

template <class T>
void free(Node<T>* root)
{
	if (root == nullptr)
		return;

	free(root->left);
	free(root->right);
	delete root;
}

template <class T>
struct NNode
{
	T data;
	std::vector<NNode*> children;

	NNode(const T& data) : data(data) {};
};

template <class T>
bool contains(const Node<T>* tree, const T& data)
{
	if (tree == nullptr)
		return false;

	if (tree->data == data)
		return true;

	return contains(tree->left, data) || contains(tree->right, data);
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

	std::cout << contains(root, 4);

	free(root);
}
