#include <iostream>
#include <vector>
#include <string>
#include <list>

using namespace std;

template <typename T>
struct Node
{
	T data;
	std::vector<Node*> children;

	Node(const T& data) : data(data) {};
};

template <class T>
bool isTreeSameFromLeftAndRightView(const Node<T>* root)
{
	if (root == nullptr)
		return true;

	std::list<const Node<T>*> q;
	q.push_back(root);

	while (!q.empty())
	{
		if (q.front()->data != q.back()->data)
			return false;

		size_t currLevel = q.size();

		for (size_t i = 0; i < currLevel; i++)
		{
			const Node<T>* curr = q.front();
			q.pop_front();

			for (const Node<T>* child : curr->children)
			{
				q.push_back(child);
			}
		}
	}

	return true;
}

int main()
{
	
}