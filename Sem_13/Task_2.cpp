#include <iostream>
#include <list>
#include <unordered_map>
template <typename T>
struct Node
{
	T data;
	Node* left;
	Node* right;

	bool leaf() const
	{
		return left == nullptr && right == nullptr;
	}


	Node(const T& data, Node* left = nullptr, Node* right = nullptr) : data(data), left(left), right(right) {};
};

struct Graph
{
	using AdjList = std::unordered_map<char, std::list<char>> ;
	AdjList adj;


	void addEdge(char from, char to)
	{
		adj[from].push_back(to);
	}
};

bool findPathHelper(const Graph& g, const Node<char>* root, std::string& word)
{
	if (root == nullptr)
		return false;

	Graph::AdjList::const_iterator it = g.adj.find(root->data);

	if (it == g.adj.end() && !root->leaf())
		return false;

	word.push_back(root->data);

	if (root->left == nullptr && root->right == nullptr)
	{
		std::cout << word;

		return true;
	}

	const std::list<char>& neighbours = it->second;

	for (char neighbour : neighbours)
	{
		if (root->left != nullptr 
			&& neighbour == root->left->data
			&& findPathHelper(g, root->left, word))
		{
			return true;
		}

		if (root->right != nullptr
			&& neighbour == root->right->data
			&& findPathHelper(g, root->right, word))
		{
			return true;
		}
	}

	word.pop_back();

	return false;
}

void findPath(const Graph& g, const Node<char>* root)
{
	std::string word = "";
	findPathHelper(g, root, word);
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
	
	findPath(g, root);

}