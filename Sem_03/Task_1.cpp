#include <iostream>
#include <queue>

void printBinary(size_t n)
{
	std::queue<size_t> q;

	q.push(1);

	for (size_t i = 0; i < n; i++)
	{
		size_t curr = q.front();
		q.pop();
		std::cout << curr << " ";
		q.push(curr * 10);
		q.push(curr * 10 + 1);
	}
}

int main()
{
	printBinary(10);
}
