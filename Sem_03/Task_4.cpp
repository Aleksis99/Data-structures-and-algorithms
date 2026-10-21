#include <iostream>
#include <queue>
#include <stdexcept>

class MovingAverage
{
private:
	std::queue<int> window;
	size_t k;
	long long sum = 0;

public:
	MovingAverage(size_t k) : k(k)
	{
		if (k == 0)
		{
			throw std::invalid_argument("Window size must be positive");
		}
	}

	double next(int value)
	{
		window.push(value);
		sum += value;

		if (window.size() > k)
		{
			sum -= window.front();
			window.pop();
		}

		return static_cast<double>(sum) / window.size();
	}
};

int main()
{
	MovingAverage avg(3);

	std::cout << avg.next(1) << std::endl;  // 1
	std::cout << avg.next(10) << std::endl; // 5.5
	std::cout << avg.next(3) << std::endl;  // 4.66667
	std::cout << avg.next(5) << std::endl;  // 6
}
