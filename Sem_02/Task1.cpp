#include <iostream>
#include <stack>

int fib(int n)
{
	if (n <= 1)
		return n;

	return fib(n - 1) + fib(n - 2);
}

int fibStack(int n)
{
	if (n <= 1)
		return n;

	int result = 0;
	std::stack<int> arguments;
	arguments.push(n);

	while (!arguments.empty())
	{
		int curr = arguments.top();
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

