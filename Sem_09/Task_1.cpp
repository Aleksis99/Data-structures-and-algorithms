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
struct Pair
{
	T incude;
	T exclude;
};

Pair<int> maxSubSumHelp(const Node<int>* root)
{
	if (root == nullptr)
		return { 0, 0 };

	Pair<int> currSubSums = { root->data, 0 };

	for (const Node<int>* child : root->children)
	{
		Pair<int> childSubSums = maxSubSumHelp(child);
		currSubSums.incude += childSubSums.exclude;
		currSubSums.exclude += std::max(childSubSums.incude, childSubSums.exclude);
	}

	return currSubSums;
}

int maxSubSum(const Node<int>* root)
{
	Pair<int> result = maxSubSumHelp(root);

	return std::max(result.incude, result.exclude);
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

	root->children[0]->children[2]->children.push_back(new Node<int>(9));

	root->children[2]->children.push_back(new Node<int>(5));
	root->children[2]->children.push_back(new Node<int>(4));

	root->children[2]->children[0]->children.push_back(new Node<int>(2));
	root->children[2]->children[1]->children.push_back(new Node<int>(9));

	std::cout << maxSubSum(root);


}
