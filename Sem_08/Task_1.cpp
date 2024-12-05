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
void treeToVec(const Node<T>* node, std::vector<T>& vec)
{
	if (node == nullptr)
		return;

	treeToVec(node->left, vec);
	vec.push_back(node->data);
	treeToVec(node->right, vec);

}

template <class T>
std::vector<T> treeToVec(const Node<T>* node)
{
	std::vector<T> result;
	treeToVec(node, result);
	return result;
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
	std::vector<int> vec = treeToVec(root);
	
	for (int el : vec)
	{
		std::cout << el << " ";
	}

	free(root);
}
