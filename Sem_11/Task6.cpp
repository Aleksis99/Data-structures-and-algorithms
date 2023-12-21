#include <iostream>

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
int dfs(const Node<T>* root, int& currMax)
{
	if (root == nullptr)
		return 0;

	int leftHeight = dfs(root->left, currMax);
	int rightHeight = dfs(root->right, currMax);

	currMax = std::max(currMax, leftHeight + rightHeight);

	return std::max(leftHeight, rightHeight) + 1;
}

template <class T>
int diameter(const Node<T>* root)
{
	int d = 0;
	dfs(root, d);

	return d;
}

int main()
{
    std::cout << "Hello World!\n";
}
