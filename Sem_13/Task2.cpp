#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <list>

template <class T>
struct Node
{
	T data;
	Node* left;
	Node* right;

	Node(const T& data, Node* left = nullptr, Node* right = nullptr)
		: data(data), left(left), right(right) {};
};

void getWords(const Node<char>* root, std::string& currWord, std::vector<std::string>& words)
{
	if (root == nullptr)
		return;

	currWord.push_back(root->data);

	if (root->left == nullptr && root->right == nullptr)
	{
		words.push_back(currWord);
		currWord.pop_back();
		return;
	}

	getWords(root->left, currWord, words);
	getWords(root->right, currWord, words);
	currWord.pop_back();
}

struct Graph
{
	std::map<char, std::list<char>> adj;

	void addEdge(char from, char to)
	{
		adj[from].push_back(to);
		adj[to].push_back(from);
	}
};

bool hasWord(const Graph& g, const std::string& word)
{
	std::map<char, std::list<char>>::const_iterator it = g.adj.find(word[0]);

	if (it == g.adj.end())
		return false;

	for (size_t i = 1; i < word.size(); i++)
	{
		if (it == g.adj.end())
			return false;

		const std::list<char>& neighbours = (*it).second;
		bool found = false;

		for (char neigh : neighbours)
		{
			if (neigh == word[i])
			{
				found = true;
				break;
			}
		}

		if (!found)
			return false;

		it = g.adj.find(word[i]);
	}

	return true;
}

void pathExist(const Node<char>* root, const Graph& g)
{
	std::vector<std::string> words;
	std::string word = "";

	getWords(root, word, words);

	for (const std::string& word : words)
	{
		if (hasWord(g, word))
		{
			std::cout << word;
			return;
		}
	}
}

int main()
{
	Node<char>* root = new Node<char>('a');
	Node<char>* n1 = new Node<char>('e');
	Node<char>* n2 = new Node<char>('f');
	Node<char>* n3 = new Node<char>('d');
	Node<char>* n4 = new Node<char>('g');
	Node<char>* n5 = new Node<char>('c');
	Node<char>* n6 = new Node<char>('b');
	Node<char>* n7 = new Node<char>('h');
	root->left = n1;
	root->right = n2;
	n1->left = n3;
	n1->right = n4;
	n2->right = n5;
	n3->left = n6;
	n5->left = n7;

	Graph g;
	g.addEdge('a', 'f');
	g.addEdge('a', 'd');
	g.addEdge('b', 'h');
	g.addEdge('c', 'h');
	g.addEdge('d', 'e');
	g.addEdge('e', 'h');
	g.addEdge('f', 'h');
	g.addEdge('f', 'c');
	g.addEdge('g', 'b');
	g.addEdge('g', 'e');

	pathExist(root, g);
}
