#include <iostream>
#include <stack>

// 0 1 1 2 3 5 8
size_t fib(size_t n)
{
	if (n <= 1)
		return n;

	return fib(n - 1) + fib(n - 2);
}

size_t fibStack(size_t n)
{
	if (n <= 1)
		return n;

	std::stack<size_t> arguments;
	arguments.push(n);
	size_t result = 0;

	while (!arguments.empty())
	{
		size_t curr = arguments.top();
		arguments.pop();

		if (curr <= 1)
			result += curr;
		else
		{
			arguments.push(curr - 1);
			arguments.push(curr - 2);
		}
	}

	return result;
}


int main()
{
	std::cout << fib(6) << " " << fibStack(6);
}
