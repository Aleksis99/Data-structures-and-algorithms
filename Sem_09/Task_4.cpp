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
	std::vector<Node*> children;

	Node(const T& data) : data(data) {};
};

template <class T>
bool isSameFromLeftAndRightView(const Node<T>* root)
{
	if (root == nullptr)
		return true;

	std::queue < const Node<T>*> q;
	q.push(root);

	while (!q.empty())
	{
		size_t levelSize = q.size();

		if (q.front()->data != q.back()->data)
			return false;

		for (size_t i = 0; i < levelSize; i++)
		{
			const Node<T>* currNode = q.front();
			q.pop();

			for (const Node<T>* child : currNode->children)
			{
				q.push(child);
			}
		}
	}

	return true;
}

int main()
{
	Node<int>* root = new Node<int>(5);
	root->children.push_back(new Node<int>(3));
	root->children.push_back(new Node<int>(9));
	root->children.push_back(new Node<int>(3));

	root->children[0]->children.push_back(new Node<int>(4));
	root->children[0]->children.push_back(new Node<int>(3));
	root->children[0]->children.push_back(new Node<int>(7));

	root->children[0]->children[2]->children.push_back(new Node<int>(8));

	root->children[2]->children.push_back(new Node<int>(5));
	root->children[2]->children.push_back(new Node<int>(4));

	root->children[2]->children[0]->children.push_back(new Node<int>(2));
	root->children[2]->children[1]->children.push_back(new Node<int>(8));

	std::cout << isSameFromLeftAndRightView(root);
}
