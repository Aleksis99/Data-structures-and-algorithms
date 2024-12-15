#include <iostream>
#include <queue>
#include <vector>
#include <stack>
#include <list>
#include <string>
#include <set>


template <class T>
struct Node
{
	T data;
	Node* left;
	Node* right;
	Node(const T& data, Node* left = nullptr, Node* right = nullptr)
		: data(data), left(left), right(right) {};
};

void iterateLevel(std::queue<const Node<int>*>& q, std::multiset<int>& set)
{
	size_t levelSize = q.size();

	for (size_t i = 0; i < levelSize; i++)
	{
		const Node<int>* curr = q.front();
		q.pop();
		set.insert(curr->data);

		if (curr->left != nullptr)
		{
			q.push(curr->left);
		}

		if (curr->right != nullptr)
		{
			q.push(curr->right);
		}
	}
}

bool equalLevelWise(const Node<int>* lhs, const Node<int>* rhs)
{
	if (lhs == nullptr || rhs == nullptr)
		return lhs == rhs;

	std::queue<const Node<int>*> lhsQ;
	std::queue<const Node<int>*> rhsQ;
	std::multiset<int> lhsSet;
	std::multiset<int> rhsSet;
	lhsQ.push(lhs);
	rhsQ.push(rhs);

	while (!lhsQ.empty() && !rhsQ.empty())
	{
		if (lhsQ.size() != rhsQ.size())
			return false;

		iterateLevel(lhsQ, lhsSet);
		iterateLevel(rhsQ, rhsSet);

		for (int val : lhsSet)
		{
			if (lhsSet.count(val) != rhsSet.count(val))
				return false;
		}

		lhsSet.clear();
		rhsSet.clear();

	}
	return lhsQ.empty() && rhsQ.empty();
}

int main()
{
	Node<int>* root1 = new Node<int>(1);
	Node<int>* n1 = new Node<int>(2);
	Node<int>* n2 = new Node<int>(3);
	Node<int>* n3 = new Node<int>(4);
	Node<int>* n4 = new Node<int>(5);
	root1->left = n1;
	root1->right = n2;
	n2->left = n3;
	n2->right = n4;
	n1->right = n4;

	Node<int>* root2 = new Node<int>(1);
	Node<int>* n11 = new Node<int>(3);
	Node<int>* n22 = new Node<int>(2);
	Node<int>* n33 = new Node<int>(5);
	Node<int>* n44 = new Node<int>(4);
	root2->left = n11;
	root2->right = n22;
	n22->left = n33;
	n22->right = n44;
	n11->left = n33;

	std::cout << equalLevelWise(root1, root2);

}
