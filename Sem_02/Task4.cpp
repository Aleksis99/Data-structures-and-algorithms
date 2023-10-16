#include <iostream>
#include <vector>
#include <stack>

size_t findSquare(std::vector<size_t> input)
{
    size_t result = 0;
    std::stack<size_t> indexes;
    input.push_back(0);

    for (size_t i = 0; i < input.size(); i++)
    {
        while (!indexes.empty() && input[indexes.top()] >= input[i])
        {
            size_t currHeinght = input[indexes.top()];
            indexes.pop();
            size_t currWidth = indexes.empty() ? i : i - indexes.top() - 1;
            result = std::max(result, currHeinght * currWidth);
        }

        indexes.push(i);
    }

    return result;
}


int main()
{
}
