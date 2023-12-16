#include <iostream>
#include <queue>
#include <string>
#include <vector>



template <typename T>
struct Node
{
	T data;
	std::vector<Node*> children;

	Node(const T& data) : data(data){};
};

struct Pair
{
	int include;
	int exlude;
};

Pair maxSubSumHelp(const Node<int>* root)
{
	if (root == nullptr)
		return { 0, 0 };

	Pair result({ root->data,0 });

	for (const Node<int>* child : root->children)
	{
		Pair childValues = maxSubSumHelp(child);
		result.include += childValues.exlude;
		result.exlude += std::max(childValues.include, childValues.exlude);
	}

	return result;
}

int maxSubSum(const Node<int>* root)
{
	Pair res = maxSubSumHelp(root);

	return std::max(res.include, res.exlude);
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

