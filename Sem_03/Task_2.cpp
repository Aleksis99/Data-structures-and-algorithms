#include <iostream>
#include <queue>
#include <cmath>
#include <string>

bool** init(size_t n)
{
	bool** matrix = new bool* [n];

	for (size_t i = 0; i < n; i++)
	{
		matrix[i] = new bool[n] {0};
	}

	return matrix;
}

void free(bool** matrix, size_t n)
{
	for (size_t i = 0; i < n; i++)
	{
		delete[] matrix[i];
	}

	delete[] matrix;
}

struct Node
{
	size_t x;
	size_t y;
	size_t dist;
};

bool validPosition(size_t n, size_t x, size_t y)
{
	return x < n && y < n;
}



void addNeighbours(std::queue<Node>& q, size_t n, size_t x, size_t y, size_t dist)
{
	for (int i = -2; i <= 2; i++)
	{
		for (int j = -2; j <= 2; j++)
		{
			if (abs(i) != abs(j) && i != 0 && j != 0
				&& validPosition(n, x+i, y+j))
			{
				q.push({ x + i, y + j, dist });
			}
		}
	}
}

int bfs(bool** matrix, size_t n, size_t x, size_t y, size_t endX, size_t endY)
{
	std::queue<Node> q;
	q.push({ x, y, 0 });

	while (!q.empty())
	{
		Node curr = q.front();
		q.pop();

		if (matrix[curr.x][curr.y] == true)
		{
			continue;
		}

		if (curr.x == endX && curr.y == endY)
		{
			free(matrix);
			return curr.dist;
		}
		matrix[curr.x][curr.y] = true;

		addNeighbours(q, n, curr.x, curr.y, curr.dist + 1);
	}

	free(matrix);
	return -1;
}

int main()
{
	size_t x=0, y=0, endX=7, endY=7, n = 50;
	//std::cin >> x >> y >> n;
	bool** matrix = init(n);
	std::cout<<bfs(matrix, n, x, y, endX, endY);

}