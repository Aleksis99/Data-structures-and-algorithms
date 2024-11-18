// Task12.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <stack>
#include <queue>

struct Node
{
    char data;
    Node* left = nullptr;
    Node* middle = nullptr;
    Node* right = nullptr;

    Node(char data) : data(data) {};
};

Node* parse(char c)
{
    if (c == '*')
        return  nullptr;

    return new Node(c);
}

Node* parse(const std::string& str)
{
    if (str.size() == 0)
        return nullptr;

    if (str.size() == 1)
        return new Node(str[0]);

    std::stack<Node*> s;

    for (char c : str)
    {
        if (c == '(' || c == ' ')
            continue;

        if (c == ')')
        {
            Node* right = s.top();
            s.pop();
            Node* middle = s.top();
            s.pop();
            Node* left = s.top();
            s.pop();
            Node* root = s.top();
            s.pop();

            root->left = left;
            root->middle = middle;
            root->right = right;
            s.push(root);
        }
        else
        {
            s.push(parse(c));
        }
    }

    if (s.size() != 1)
        throw "invalid input";

    return s.top();
}

void addToQ(std::queue<const Node*>& q, const Node* node)
{
    if (node != nullptr)
    {
        q.push(node);
    }
}

void levelPrint(const Node* root)
{
    std::queue<const Node*> q;
    addToQ(q, root);

    while (!q.empty())
    {
        size_t curr_level_nodes = q.size();

        for (size_t i = 0; i < curr_level_nodes; i++)
        {
            const Node* curr = q.front();
            q.pop();
            std::cout << curr->data << " ";
            addToQ(q, curr->left);
            addToQ(q, curr->middle);
            addToQ(q, curr->right);
        }

        std::cout << std::endl;
    }
}

int main()
{
    std::string s = "(b (x (p * * *) (q * * *) (r (c * * *) * (a * * *))) (y * * (s * (t * * *) *)) *)";
    //std::cin >> s;
    Node* root = parse(s);
    levelPrint(root);
}
