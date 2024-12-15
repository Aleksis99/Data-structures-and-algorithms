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
int height(const Node<T>* root)
{
	if (root == nullptr)
		return 0;

	int leftHeigh = height(root->left);
	int rightHeigh = height(root->left);

	return std::max(leftHeigh, rightHeigh) + 1;
}

template <class T>
void diameterHelp(const Node<T>* root, int& height, int& diameter)
{
	if (root == nullptr)
		return;

	int leftHeight = 0;
	int leftDiameter = 0;
	diameterHelp(root->left, leftHeight, leftDiameter);
	int rightHeight = 0;
	int rightDiameter = 0;
	diameterHelp(root->right, rightHeight, rightDiameter);

	int currDiameter = leftHeight + rightHeight;
	diameter = std::max(currDiameter, std::max(leftDiameter, rightDiameter));
	height = 1 + std::max(leftHeight, rightHeight);
}

template <class T>
int diameter(const Node<T>* root)
{
	int height = 0;
	int diameter = 0;
	if (root == nullptr)
		return 0;

	diameterHelp(root, height, diameter);

	return diameter;
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

	std::cout << diameter(root);
}
