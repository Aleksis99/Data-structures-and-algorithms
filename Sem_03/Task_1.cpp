#include <iostream>
#include <queue>
#include <string>

void printBinary(size_t n)
{
	std::queue<std::string> q;

	q.push("1");

	for (size_t i = 0; i < n; i++)
	{
		std::string curr = q.front();
		q.pop();
		std::cout << curr << " ";
		q.push(curr + "0");
		q.push(curr + "1");
	}

	std::cout << std::endl;
}

int main()
{
	printBinary(10);
}
