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

bool leaf(const Node<char>* root)
{
	return root != nullptr && root->left == nullptr && root->right == nullptr;
}

void getWords(const Node<char>* root,
	std::string& curr_word,
	std::vector<std::string>& words)
{
	if (root == nullptr)
		return;

	curr_word.push_back(root->data);

	if (leaf(root))
	{
		words.push_back(curr_word);
		curr_word.pop_back();
		return;
	}

	getWords(root->left, curr_word, words);
	getWords(root->right, curr_word, words);
	curr_word.pop_back();
}

std::vector<std::string> getWords(const Node<char>* root)
{
	std::vector<std::string> words;
	std::string curr_word = "";
	getWords(root, curr_word, words);

	return words;
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

	std::vector<std::string> words = getWords(root);

	for (const std::string word : words)
	{
		std::cout << word << std::endl;
	}
}
