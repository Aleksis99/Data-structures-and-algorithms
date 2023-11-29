#include <iostream>
#include <string>
#include <queue>

bool** init(int n)
{
	bool** matrix = new bool* [n];

	for (size_t i = 0; i < n; i++)
	{
		matrix[i] = new bool[n] {0};
	}
	
	return matrix;
}

void free(bool** matrix, int n)
{
	for (size_t i = 0; i < n; i++)
	{
		delete[] matrix[i];
	}

	delete[] matrix;
}

struct Node
{
	int x;
	int y;
	int dist;
};

bool validPosition(int n, int x, int y)
{
	return x >= 0 && y >= 0 && x < n && y < n;
}

void addNeighbours(std::queue<Node>& q, const Node& curr, int n)
{
	for (int i = -2; i <= 2; i++)
	{
		for (int j = -2; j <= 2; j++)
		{
			if (abs(i) != abs(j) && i != 0 && j != 0
				&& validPosition(n, curr.x + i, curr.y + j))
			{
				q.push({ curr.x + i, curr.y + j, curr.dist + 1 });
			}
		}
	}
}

int minMoves(int n, int x, int y, int goalX, int goalY)
{
	bool** visited = init(n);
	std::queue<Node> q;
	q.push({ x, y, 0 });

	while (!q.empty())
	{
		Node curr = q.front();
		q.pop();

		if (visited[curr.x][curr.y])
			continue;
		
		if (curr.x == goalX && curr.y == goalY)
		{
			free(visited);

			return curr.dist;
		}

		visited[curr.x][curr.y] = true;
		addNeighbours(q, curr, n);
	}

	free(visited);

	return -1;
}


int main()
{
	std::cout << minMoves(50, 0, 0, 7, 7);
}
