#include <iostream>
#include <stack>
#include <string>

bool balanced(const std::string& str)
{
	std::stack<char> s;

	for (size_t i = 0; i < str.size(); i++)
	{
		if (str[i] == '(' || str[i] == '{' || str[i] == '[')
		{
			s.push(str[i]);
		}
		else if (str[i] == '}' || str[i] == ')' || str[i] == ']')
		{
			if (s.empty())
				return false;

			if (str[i] == '}' && s.top() != '{')
			{
				return false;
			}
			else if (str[i] == ')' && s.top() != '(')
			{
				return false;
			}
			else if (str[i] == ']' && s.top() != '[')
			{
				return false;
			}

			s.pop();
		}
	}

	return s.empty();
}

int main()
{
	std::cout << balanced("[asdasd{asda}asd(asd)]{");
}