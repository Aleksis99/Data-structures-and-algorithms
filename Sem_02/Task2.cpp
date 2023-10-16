#include <iostream>
#include <string>
#include <stack>

bool balancedPar(const std::string& s)
{
	std::stack<char> stack;

	for (size_t i = 0; i < s.size(); i++)
	{
		if (s[i] == '{' || s[i] == '(' || s[i] == '[') 
		{
			stack.push(s[i]);
		}
		else if (s[i] == '}' || s[i] == ')' || s[i] == ']')
		{
			if (stack.empty())
				return false;

			if (s[i] == '}' && stack.top() != '{'
				|| s[i] == ')' && stack.top() != '('
				|| s[i] == ']' && stack.top() != '[')
				return false;

			stack.pop();
		}
	}

	return stack.empty();
}

int main()
{
	std::cout << balancedPar("[(asd){asd}ad[{]]");
}
