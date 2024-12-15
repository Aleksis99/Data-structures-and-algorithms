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

struct Interval
{
	int start;
	int end;
};

bool hasIntersection(const Interval& lhs, const Interval& rhs)
{
	return !(lhs.end < rhs.start || rhs.end < lhs.start);
}

bool hasIntersection(const Node<Interval>* root, const Interval& interval)
{
	if (root == nullptr)
		return true;

	if (!hasIntersection(root->data, interval))
		return false;
	
	return hasIntersection(root->left, interval) && hasIntersection(root->right, interval);
}

Interval maxIntervalHelp(const Node<Interval>* root, const Node<Interval>* curr)
{
	if (curr == nullptr)
		return { 0, 0 };

	Interval result = maxIntervalHelp(root->right, curr);

	if (result.start != 0 || result.end != 0)
		return result;

	if (hasIntersection(root, curr->data))
		return curr->data;

	return maxIntervalHelp(root->left, curr);
}

Interval maxInterval(const Node<Interval>* root)
{
	return maxIntervalHelp(root, root);
}

int main()
{
	
}
