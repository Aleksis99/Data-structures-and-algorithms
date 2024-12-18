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
void print(const Node<T>* root)
{
	if (root == nullptr)
		return;

	std::queue<const Node<T>*> q;
	q.push(root);

	while (!q.empty())
	{
		size_t levelSize = q.size();

		for (size_t i = 0; i < levelSize; i++)
		{
			const Node<T>* curr = q.front();
			q.pop();

			std::cout << curr->data << " ";

			if (curr->left != nullptr)
				q.push(curr->left);

			if (curr->right != nullptr)
				q.push(curr->right);
		}

		std::cout << std::endl;
	}
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

	print(root);
}
