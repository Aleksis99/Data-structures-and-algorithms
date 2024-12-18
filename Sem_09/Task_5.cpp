#include <iostream>
#include <queue>
#include <vector>
#include <stack>
#include <list>
#include <map>

template <class T>
struct Node
{
	T data;
	std::vector<Node*> children;

	Node(const T& data) : data(data) {};
};

void dfs(
	const Node<int>* curr,
	std::map<const Node<int>*, const Node<int>*>& parent,
	std::map<const Node<int>*, int>& depth, int currDepth
	)
{
	if (curr == nullptr)
		return;

	depth[curr] = currDepth;

	for (const Node<int>* child : curr->children)
	{
		if (curr->data % child->data != 0)
			continue;

		parent[child] = curr;

		dfs(child, parent, depth, currDepth + 1);
	}
}

std::vector<int> longestPrittyPath(const Node<int>* root)
{
	std::map < const Node<int>*, const Node<int>* > parent;
	std::map < const Node<int>*, int> depth;
	int maxDepth = 0;
	dfs(root, parent, depth, maxDepth);

	maxDepth = -1;
	const Node<int>* maxDepthNode = nullptr;

	for (std::pair<const Node<int>*, int> node : depth)
	{
		if (node.second > maxDepth)
		{
			maxDepth = node.second;
			maxDepthNode = node.first;
		}
	}

	std::vector<int> path;
	const Node<int>* currNode = maxDepthNode;

	while (parent.count(currNode) > 0)
	{
		path.push_back(currNode->data);
		currNode = parent[currNode];
	}

	path.push_back(root->data);

	std::reverse(path.begin(), path.end());

	return path;
}

int main()
{
	Node<int>* root = new Node<int>(5);
	root->children.push_back(new Node<int>(3));
	root->children.push_back(new Node<int>(9));
	root->children.push_back(new Node<int>(1));

	root->children[0]->children.push_back(new Node<int>(4));
	root->children[0]->children.push_back(new Node<int>(3));
	root->children[0]->children.push_back(new Node<int>(7));

	root->children[0]->children[2]->children.push_back(new Node<int>(9));

	root->children[2]->children.push_back(new Node<int>(5));
	root->children[2]->children.push_back(new Node<int>(1));

	root->children[2]->children[0]->children.push_back(new Node<int>(2));
	root->children[2]->children[1]->children.push_back(new Node<int>(1));

	std::vector<int> path = longestPrittyPath(root);

	for (int val : path)
	{
		std::cout << val << " ";
	}
}
