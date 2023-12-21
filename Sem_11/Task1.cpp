#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>



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
void iterateLevel(std::queue<const Node<T>*>& Q, std::vector<T>& vec, size_t size)
{
	for (size_t i = 0; i < size; i++)
	{
		const Node<T>* currLhs = Q.front();
		Q.pop();
		vec.push_back(currLhs->data);

		if (currLhs->left != nullptr)
			Q.push(currLhs->left);
		if (currLhs->right != nullptr)
			Q.push(currLhs->right);
	}
}

template <class T>
bool areVecsTheSame(const std::vector<T>& lhsVec, const std::vector<T>& rhsVec)
{
	if (lhsVec.size() != rhsVec.size())
		return false;

	for (size_t i = 0; i < lhsVec.size(); i++)
	{
		if (lhsVec[i] != rhsVec[i])
			return false;
	}
}

template <class T>
bool sameLevels(const Node<T>* lhsRoot, const Node<T>* rhsRoot)
{
	if (lhsRoot == nullptr || rhsRoot == nullptr)
		return lhsRoot == rhsRoot;

	std::queue<const Node<T>*> lhsQ;
	std::queue<const Node<T>*> rhsQ;
	lhsQ.push(lhsRoot);
	rhsQ.push(rhsRoot);

	while (!lhsQ.empty() && !rhsQ.empty())
	{
		if (lhsQ.size() != rhsQ.size())
			return false;

		size_t size = lhsQ.size();
		std::vector<T> lhsVec;
		std::vector<T> rhsVec;

		iterateLevel(lhsQ, lhsVec, size);
		iterateLevel(rhsQ, rhsVec, size);
		
		std::sort(lhsVec.begin(), lhsVec.end());
		std::sort(rhsVec.begin(), rhsVec.end());

		if (!areVecsTheSame(lhsVec, rhsVec))
			return false;
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

	Node<int>* root2 = new Node<int>(1);
	Node<int>* n11 = new Node<int>(3);
	Node<int>* n22 = new Node<int>(2);
	Node<int>* n33 = new Node<int>(5);
	Node<int>* n44 = new Node<int>(4);
	root2->left = n11;
	root2->right = n22;
	n22->left = n33;
	n22->right = n44;

	std::cout << sameLevels(root1, root2);
}

