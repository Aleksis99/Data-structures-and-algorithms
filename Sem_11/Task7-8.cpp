
#include <iostream>
#include <vector>
#include <string>

struct Node
{
    size_t data;
    char label;
    std::vector<Node*> children;

    Node(const size_t& data, char label) : data(data), label(label) {};
};

struct Branch
{
    std::string word;
    size_t sum;
};

void getBranches(const Node* root, std::vector<Branch>& branches, std::string& currWord, size_t& currSum)
{
    if (root == nullptr)
        return;

    currWord.push_back(root->label);
    currSum += root->data;

    if (root->children.empty())
    {
        branches.push_back({ currWord, currSum });
    }
    else
    {
        for (const Node* child : root->children)
        {
            getBranches(child, branches, currWord, currSum);
        }
    }

    currWord.pop_back();
    currSum -= root->data;
}

void commonBranches(const Node* root, const Node* u, const Node* v, size_t k)
{
    std::string word = "";
    size_t sum = 0;
    std::vector<Branch> branchesU;
    std::vector<Branch> branchesV;
    getBranches(u, branchesU, word, sum);
    word.clear();
    sum = 0;
    getBranches(v, branchesV, word, sum);

    for (const Branch& branchV : branchesV)
    {
        for (const Branch& branchU : branchesU)
        {
            if (branchV.sum + branchU.sum == k && branchV.word == branchU.word)
            {
                std::cout << branchU.word << std::endl;
            }
        }
    }
}

int sumVal(const Node* root, const Node* v, const Node* u)
{
    if (v == nullptr || u == nullptr)
        return 0;

    std::vector<Branch> branchesV;
    std::vector<Branch> branchesU;
    std::string word = "";
    size_t sum = 0;
    getBranches(v, branchesV, word, sum);
    word.clear();
    sum = 0;
    getBranches(u, branchesU, word, sum);
    size_t result = 0;

    for (const Branch& branchV : branchesV)
    {
        for (const Branch& branchU : branchesU)
        {
            if (branchV.word == branchU.word)
            {
                result += branchV.sum + branchU.sum;
            }
        }
    }

    return result;
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
    commonBranches(&n1, &n1, &n1, 6);

    std::cout<<sumVal(&n1, &n1, &n1);
}

