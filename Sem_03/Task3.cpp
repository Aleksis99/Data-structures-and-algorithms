#include <iostream>
#include <queue>
#include <vector>

bool areEqaulSubSeq(std::vector<int> arr)
{
	std::queue<int> q;

	for (size_t i = 0; i < arr.size(); i++)
	{
		if (arr[i] == 0)
			continue;

		if (q.empty() || q.front() * arr[i] > 0 /*same sing*/)
		{
			q.push(arr[i]);
			continue;
		}

		if (arr[i] * -1 == q.front())
		{
			q.pop();
		}
		else
		{
			return false;
		}
	}

	return q.empty();
}

int main()
{
	std::vector<int> arr = { 1, 5, -1, 4, -5, 9, 8, -4, -9, 18, -8, -18, -7, 7 };
	std::cout << areEqaulSubSeq(arr);
}