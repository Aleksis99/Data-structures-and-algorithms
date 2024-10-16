
#include <iostream>
#include <stack>

template <class T>
class Queue
{
private:
    std::stack<T> input;
    std::stack<T> output;

    void toOutput();
public:

    bool empty() const;
    size_t size() const;
    const T& top();
    void pop();
    void push(const T& data);
};



template<class T>
void Queue<T>::toOutput()
{
    while (!input.empty())
    {
        output.push(input.top());
        input.pop();
    }
}

template<class T>
bool Queue<T>::empty() const
{
    return this->input.empty() && this->output.empty();
}

template<class T>
size_t Queue<T>::size() const
{
    return this->input.size() + this->output.size();;
}

template<class T>
const T& Queue<T>::top()
{
    if (this->empty())
        throw "Empty queue";
    if (output.empty())
        toOutput();

    return output.top();
}

template<class T>
void Queue<T>::pop()
{
    if (this->empty())
        throw "Empty queue";
    if (output.empty())
        toOutput();

    output.pop();
}

template<class T>
void Queue<T>::push(const T& data)
{
    input.push(data);
}

int main()
{

    Queue<size_t> q;

    for (size_t i = 0; i < 20; i++)
    {
        q.push(i);
    }

    while (!q.empty())
    {
        std::cout << q.top() << " ";
        q.pop();
    }
}
