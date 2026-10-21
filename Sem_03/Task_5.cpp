#include <iostream>
#include <vector>
#include <deque>

std::vector<int> slidingWindowMax(const std::vector<int>& arr, size_t k)
{
	std::vector<int> result;

	if (k == 0 || k > arr.size())
	{
		return result;
	}

	std::deque<size_t> dq;

	for (size_t i = 0; i < arr.size(); i++)
	{
		if (!dq.empty() && dq.front() + k <= i)
		{
			dq.pop_front();
		}

		while (!dq.empty() && arr[dq.back()] <= arr[i])
		{
			dq.pop_back();
		}

		dq.push_back(i);

		if (i + 1 >= k)
		{
			result.push_back(arr[dq.front()]);
		}
	}

	return result;
}

void print(const std::vector<int>& arr)
{
	for (size_t i = 0; i < arr.size(); i++)
	{
		std::cout << arr[i] << " ";
	}

	std::cout << std::endl;
}

int main()
{
	print(slidingWindowMax({ 1, 3, -1, -3, 5, 3, 6, 7 }, 3)); // 3 3 5 5 6 7
	print(slidingWindowMax({ 4, 2, 12, 3 }, 1));              // 4 2 12 3
}
