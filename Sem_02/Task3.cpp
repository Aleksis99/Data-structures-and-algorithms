#include <iostream>
#include <stack>

class Queue
{
private:
    std::stack<int> input;
    std::stack<int> output;

public:

    int front();
    void pop();
    void push(int data);
    bool empty() const;
    bool size() const;

};

int Queue::front() 
{
    if (empty())
        throw "Empty queue";

    if (output.empty())
    {
        while (!input.empty())
        {
            output.push(input.top());
            input.pop();
        }
    }

    return output.top();
}

void Queue::pop()
{
    if (empty())
        throw "Empty queue";

    if (output.empty())
    {
        while (!input.empty())
        {
            output.push(input.top());
            input.pop();
        }
    }

    output.pop();
}

void Queue::push(int data)
{
    input.push(data);
}

bool Queue::empty() const
{
    return size() == 0;
}

bool Queue::size() const
{
    return input.size() + output.size();
}

int main()
{
    Queue q;

    for (size_t i = 0; i < 20; i++)
    {
        q.push(i);
    }

    while (!q.empty())
    {
        std::cout << q.front() << " ";
        q.pop();
    }
}