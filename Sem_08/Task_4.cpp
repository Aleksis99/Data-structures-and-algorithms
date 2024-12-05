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

template <class T>
std::vector<T> decode(const Node<T>* root, const std::string& code)
{
	std::vector<T> result;
	const Node<T>* curr = root;
	for (char c : code)
	{
		if (c == '0')
		{
			curr = curr->left;
		}
		else
		{
			curr = curr->right;
		}

		if (curr->left == nullptr && curr->right == nullptr)
		{
			result.push_back(curr->data);
			curr = root;
		}
	}

	return result;
}

int main()
{

}
