#include <iostream>
#include <queue>

bool** initMatrix(size_t n)
{
	bool** matrix = new bool* [n];

	for (size_t i = 0; i < n; i++)
	{
		matrix[i] = new bool[n] {false};
	}

	return matrix;
}

void freeMatrix(bool** matrix, size_t n)
{
	for (size_t i = 0; i < n; i++)
	{
		delete[] matrix[i];
	}

	delete[] matrix;
}

struct Cell
{
	int x;
	int y;
	int dist;
};

const int MOVES_COUNT = 8;
const int dx[MOVES_COUNT] = { -2, -2, -1, -1, 1, 1, 2, 2 };
const int dy[MOVES_COUNT] = { -1, 1, -2, 2, -2, 2, -1, 1 };

bool validPosition(int n, int x, int y)
{
	return x >= 0 && y >= 0 && x < n && y < n;
}

void addNeighbours(std::queue<Cell>& q, bool** visited, int n, const Cell& curr)
{
	for (int i = 0; i < MOVES_COUNT; i++)
	{
		int newX = curr.x + dx[i];
		int newY = curr.y + dy[i];

		if (validPosition(n, newX, newY) && !visited[newX][newY])
		{
			visited[newX][newY] = true;
			q.push({ newX, newY, curr.dist + 1 });
		}
	}
}

int bfs(int n, int x, int y, int endX, int endY)
{
	if (!validPosition(n, x, y) || !validPosition(n, endX, endY))
	{
		return -1;
	}

	bool** visited = initMatrix(n);
	std::queue<Cell> q;

	visited[x][y] = true;
	q.push({ x, y, 0 });

	int result = -1;

	while (!q.empty())
	{
		Cell curr = q.front();
		q.pop();

		if (curr.x == endX && curr.y == endY)
		{
			result = curr.dist;
			break;
		}

		addNeighbours(q, visited, n, curr);
	}

	freeMatrix(visited, n);
	return result;
}

int main()
{
	std::cout << bfs(8, 0, 0, 2, 1) << std::endl; // 1
	std::cout << bfs(8, 0, 0, 7, 7) << std::endl; // 6
}
