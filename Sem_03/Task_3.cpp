#include <iostream>
#include <vector>
#include <cmath>
#include <queue>

bool equalSing(int a, int b)
{
	return a * b > 0;
}

bool areEqual(const std::vector<int>& arr)
{
	std::queue<int> q;

	for (size_t i = 0; i < arr.size(); i++)
	{
		if (arr[i] == 0)
			continue;

		if (q.empty() || equalSing(arr[i], q.front()))
		{
			q.push(arr[i]);
			continue;
		}
		
		if (abs(arr[i]) != abs(q.front()))
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
	std::vector<int> arr{ 1, 5, -1, 4, -5, 9, 8, -4, -9, 18, -8, -18, -7, 7, 7 };

	std::cout << areEqual(arr);
}