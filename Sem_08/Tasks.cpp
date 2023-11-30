#include <iostream>
#include <queue>
#include <string>
#include <vector>



template <typename T>
struct Node
{
	T data;
	Node* left;
	Node* right;

	Node(const T& data) : data(data), left(nullptr), right(nullptr) {};
};

template <class T>
void treeToVec(Node<T>* root, std::vector<T>& outVec)
{
	if (root != nullptr)
	{
		treeToVec(root->left, outVec);
		outVec.push_back(root->data);
		treeToVec(root->right, outVec);
	}
}

template <class T>
std::vector<T> treeToVec(Node<T>* root)
{
	std::vector<T> result;
	treeToVec(root, result);

	return result;
}

template <class T>
bool isBST(Node<T>* root, T& last, bool& haslast)
{
	if (root == nullptr)
		return true;

	if (!haslast && root->left == nullptr)
	{
		haslast = true;
		last = root->data;

		return true;
	}

	if (!isBST(root->left) || root->data < last)
		return false;

	last = root->data;

	return isBST(root->right);
}

template <class T>
bool isBST(Node<T>* root)
{
	if (root == nullptr)
		return true;

	T last;
	bool hasLast = false;

	return isBST(root, last, hasLast);
}

template <class T>
bool areEqual(Node<T>* left, Node<T>* right)
{
	if (left == nullptr && right == nullptr)
		return true;

	if (left != nullptr && right != nullptr)
	{
		return
			left->data == right->data
			&& areEqual(left->left, right->left)
			&& areEqual(left->right, right->right);
	}

	return false;
}

std::string decodeHuff(const Node<char>* root, const std::string& code)
{
	std::string result;
	const Node<char>* curr = root;

	for (size_t i = 0; i < code.size(); i++)
	{
		if (code[i] == '0')
			curr = curr->left;

		if (code[i] == '1')
			curr = curr->right;

		if (curr->left == nullptr && curr->right == nullptr)
		{
			result.push_back(curr->data);
			curr = root;
		}
	}

	return result;
}

int countElementsInInterval(Node<int>* root, int min, int max)
{
	if (root == nullptr)
		return 0;

	if(root->data < min)
		return countElementsInInterval(root->right, min, max);

	if (root->data > max)
		return countElementsInInterval(root->left, min, max);

	return
		1
		+ countElementsInInterval(root->left, min, max)
		+ countElementsInInterval(root->right, min, max);
}

int sumOddNumberAncestors(Node<int>* root, int min, int max)
{
	int childrenSum = sumOddNumberAncestors(root->left, min, max)
		+ sumOddNumberAncestors(root->right, min, max);

	if ((countElementsInInterval(root->left, min, max)
		+ countElementsInInterval(root->right, min, max)) % 2 == 1)
	{
		return
			root->data + childrenSum;
	}

	return childrenSum;
}

template <class T>
int solveTask6(Node<T>* root, bool isOdd)
{
	if (root == nullptr)
		return 0;

	if (isOdd && root->right != nullptr && root->left == nullptr)
		return root->data + solveTask6(root->right, !isOdd);

	return solveTask6(root->right, !isOdd) + solveTask6(root->left, !isOdd);
}

template <class T>
int solveTask6(Node<T>* root)
{
	return solveTask6(root, false);
}

int main()
{
	Node<int>* root = new Node<int>(50);
	Node<int>* n1 = new Node<int>(25);
	Node<int>* n2 = new Node<int>(75);
	Node<int>* n3 = new Node<int>(12);
	Node<int>* n4 = new Node<int>(30);
	Node<int>* n5 = new Node<int>(60);
	Node<int>* n6 = new Node<int>(85);
	Node<int>* n7 = new Node<int>(52);
	Node<int>* n8 = new Node<int>(70);

	root->left = n1;
	root->right = n2;
	n1->left = n3;
	n1->right = n4;
	n2->left = n5;
	n2->right = n6;
	n5->left = n7;
	n5->right = n8;

	std::vector<int> v;
	treeToVec(root, v);

	for (size_t i = 0; i < v.size(); i++)
		std::cout << v[i] << ' ';
}

