#include <iostream>
#include <queue>
#include <vector>
#include <stack>
#include <list>
#include <set>
#include <map>

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
T iterateLevel(std::queue<const Node<T>*>& q)
{
	size_t levelSize = q.size();
	const Node<T>* curr = q.front();
	T result = q.front()->data;

	if (curr->left != nullptr)
	{
		q.push(curr->left);
	}

	if (curr->right != nullptr)
	{
		q.push(curr->right);
	}


	for (size_t i = 1; i < levelSize; i++)
	{
		curr = q.front();
		q.pop();

		result += curr->data;

		if (curr->left != nullptr)
		{
			q.push(curr->left);
		}

		if (curr->right != nullptr)
		{
			q.push(curr->right);
		}
	}

	return result;
}

template <class T>
bool equalLevelWise(const Node<int>* root)
{
	if (root == nullptr)
		return false;

	std::queue<const Node<T>*> q;
	std::set<T> set;

	while (!q.empty())
	{
		
		T levesSum = iterateLevel(q, set);
		
		if (set.count(levesSum) > 0)
			return true;

		set.insert(levesSum);
	}

	return false;
}

int main()
{
	
}
