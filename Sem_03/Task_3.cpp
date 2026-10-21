#include <iostream>
#include <vector>
#include <cstdlib>
#include <queue>

bool equalSign(int a, int b)
{
	return (a > 0) == (b > 0);
}

bool areEqual(const std::vector<int>& arr)
{
	std::queue<int> q;

	for (size_t i = 0; i < arr.size(); i++)
	{
		if (arr[i] == 0)
			continue;

		if (q.empty() || equalSign(arr[i], q.front()))
		{
			q.push(arr[i]);
			continue;
		}

		if (std::abs(arr[i]) != std::abs(q.front()))
		{
			return false;
		}
		else
		{
			q.pop();
		}
	}

	return q.empty();
}

int main()
{
	std::vector<int> arr1{ 1, 5, -1, 4, -5, 9, 8, -4, -9, 18, -8, -18, -7, 7 };
	std::vector<int> arr2{ 1, -1, 2, -2, 3, 3 };

	std::cout << std::boolalpha;
	std::cout << areEqual(arr1) << std::endl; // true
	std::cout << areEqual(arr2) << std::endl; // false
}
