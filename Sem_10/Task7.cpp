#include <iostream>
#include <queue>
#include <vector>
#include <stack>
#include <list>
#include <string>
#include <set>

struct Node
{
	int val;
	char label;
	std::vector<Node*> children;

	Node(int val, char label) : val(val), label(label) {};
};

struct Branch
{
	std::string word;
	int value;

	bool operator<(const Branch& other) const
	{
		return value < other.value;
	}
};

void getBranches(const Node* root, std::set<Branch>& set, std::string& word, int& value)
{
	if (root == nullptr)
		return;

	word.push_back(root->label);
	value += root->val;

	if (root->children.empty())
	{
		set.insert({ word, value });
	}

	for (const Node* child : root->children)
	{
		getBranches(child, set, word, value);
	}

	word.pop_back();
	value -= root->val;
}

void commonBranches(const Node* tree, const Node* u, const Node* v, int k)
{
	std::set<Branch> setU;
	std::set<Branch> setV;
	std::string word = "";
	int value = 0;
	getBranches(u, setU, word, value);
	word.clear();
	value = 0;
	getBranches(v, setV, word, value);

	for (const Branch& branchU : setU)
	{
		if (setV.count({ branchU.word, k - branchU.value }) > 0)
		{
			std::cout << branchU.word << std::endl;
		}
	}
}


int main()
{
	/*
		A
	B       B
	C       C
*/

	Node n1({ 1, 'a' });
	Node n11({ 1, 'b' });
	Node n12({ 1, 'b' });
	Node n111({ 1, 'c' });
	Node n112({ 1, 'c' });
	Node n121({ 1, 'c' });
	Node n122({ 1, 'c' });
	n1.children.push_back(&n11);
	n1.children.push_back(&n12);
	n11.children.push_back(&n111);
	n12.children.push_back(&n121);
	commonBranches(&n11, &n12, &n11, 4);
}
