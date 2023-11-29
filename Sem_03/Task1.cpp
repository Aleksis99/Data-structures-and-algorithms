#include <iostream>
#include <queue>
#include <string>

void printBinary(int n)
{
	std::queue<std::string> q;
	q.push("1");

	for (size_t i = 0; i < n; i++)
	{
		std::string curr = q.front();
		q.pop();
		std::cout << curr << std::endl;

		q.push(curr + "0");
		q.push(curr + "1");
	}
}

int main()
{
	printBinary(1000);
}

