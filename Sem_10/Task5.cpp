
#include <iostream>
#include <map>
#include <vector>

template <typename T>
struct Node
{
    T data;
    std::vector<Node*> children;

    Node(const T& data) : data(data) {};
};


template <typename T>
void dfs(const Node<T>* root, int currDepth,
    std::map<const Node<T>*, int>& nodeDepths, 
    std::map<const Node<T>*, const Node<T>*>& prev)
{
    for (const Node<T>* child : root->children)
    {
        if (root->data % child->data == 0)  
        {
            prev[child] = root;
            nodeDepths[child] = currDepth + 1;
            dfs(child, currDepth + 1, nodeDepths, prev);
        }
    }
}

template <typename T>
std::vector<T> longestPrettyPath(const Node<T>* root)
{
    std::vector<T> result;

    if (root == nullptr)
        return result;

    std::map<const Node<T>*, int> nodeDepths;
    std::map<const Node<T>*, const Node<T>*> prev;
    nodeDepths[root] = 0;
    prev[root] = nullptr;
    dfs(root, 0, nodeDepths, prev);
    int maxDepth = -1;
    const Node<T>* maxDepthEl = nullptr;

    for (const std::pair<const Node<T>*, int> p : nodeDepths)
    {
        if (p.second > maxDepth)
        {
            maxDepth = p.second;
            maxDepthEl = p.first;
        }
    }

    while (maxDepthEl != nullptr)
    {
        result.push_back(maxDepthEl->data);
        maxDepthEl = prev[maxDepthEl];
    }

    std::reverse(result.begin(), result.end());

    return result;
}

int main()
{
    Node<int>* root = new Node<int>(5);
    root->children.push_back(new Node<int>(5));
    root->children.push_back(new Node<int>(9));
    root->children.push_back(new Node<int>(3));

    root->children[0]->children.push_back(new Node<int>(5));
    root->children[0]->children.push_back(new Node<int>(3));
    root->children[0]->children.push_back(new Node<int>(7));

    root->children[0]->children[2]->children.push_back(new Node<int>(9));

    root->children[2]->children.push_back(new Node<int>(5));
    root->children[2]->children.push_back(new Node<int>(4));

    root->children[2]->children[0]->children.push_back(new Node<int>(2));
    root->children[2]->children[1]->children.push_back(new Node<int>(9));

    std::vector<int> res = longestPrettyPath(root);

    for (int el : res)
    {
        std::cout << el << " ";
    }
}

