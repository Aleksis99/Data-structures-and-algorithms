#include <iostream>
#include <string>
#include <queue>

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
	double start;
	double end;
};

bool intersection(const Interval& lhs, const Interval& rhs)
{
	return !(lhs.end < rhs.start || rhs.end < lhs.start);
}

bool intersectsWithAll(const Node<Interval>* root, const Interval& interval)
{
	if (root == nullptr)
		return true;

	if (!intersection(root->data, interval))
		return false;

	return intersectsWithAll(root->left, interval) && intersectsWithAll(root->right, interval);
}

const Node<Interval>* getMaxIntervalHelper(const Node<Interval>* root, const Node<Interval>* currNode)
{
	if (root == nullptr || currNode == nullptr)
		return nullptr;

	const Node<Interval>* rightSubTreeInterval = getMaxIntervalHelper(root, currNode->right);

	if (rightSubTreeInterval != nullptr)
		return rightSubTreeInterval;

	if (intersectsWithAll(root, currNode->data))
	{
		return currNode;
	}

	return getMaxIntervalHelper(root, currNode->left);
}

Interval getMaxInterval(const Node<Interval>* root)
{
	const Node<Interval>* result = getMaxIntervalHelper(root, root);

	if (result == nullptr)
		return { 0, 0 };

	return result->data;
}

int main()
{
	Node<Interval>* root = new  Node<Interval>({ 8,12 });
	Node<Interval>* n1 = new    Node<Interval>({ 6,8 }); // Replace with {6,8} and getMaxInterval(root) will return {8,12}
	Node<Interval>* n2 = new    Node<Interval>({ 10,20 });
	Node<Interval>* n3 = new    Node<Interval>({ 7,12 });
	Node<Interval>* n4 = new    Node<Interval>({ 11,18 });
	Node<Interval>* n5 = new    Node<Interval>({ 10,30 });
	root->left = n1;
	root->right = n2;
	n1->right = n3;
	n2->left = n4;
	n2->right = n5;
	Interval it = getMaxInterval(root);

	std::cout << it.start << " " << it.end;

}
