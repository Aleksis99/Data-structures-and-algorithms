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

std::string getWordAtLevel(const Node<char>* root, int level)
{
	if (root == nullptr)
		return "";

	if (level == 0)
		return std::string(1, root->data);

	return getWordAtLevel(root->left, level - 1) + getWordAtLevel(root->right, level - 1);
}

void getWordAtLevel2(const Node<char>* root, int level, std::string& word)
{
	if (root == nullptr)
		return;

	if (level == 0)
	{
		word.push_back(root->data);
		return;
	}

	getWordAtLevel2(root->left, level - 1, word);
	getWordAtLevel2(root->right, level - 1, word);
}

std::string getWordAtLevel2(const Node<char>* root, int level)
{

	std::string word;
	getWordAtLevel2(root, level, word);

	return word;
}

int main()
{
	Node<char>* root = new Node<char>('a');
	Node<char>* n1 = new Node<char>('b');
	Node<char>* n2 = new Node<char>('c');
	Node<char>* n3 = new Node<char>('d');
	Node<char>* n4 = new Node<char>('e');
	Node<char>* n5 = new Node<char>('f');
	Node<char>* n6 = new Node<char>('g');
	Node<char>* n7 = new Node<char>('h');
	Node<char>* n8 = new Node<char>('i');
	root->left = n1;
	root->right = n2;
	n1->left = n3;
	n1->right = n4;
	n2->right = n5;
	n4->left = n6;
	n4->right = n7;
	n5->left = n8;

	std::cout << getWordAtLevel(root, 2) << std::endl;
	std::cout << getWordAtLevel2(root, 2);
}
