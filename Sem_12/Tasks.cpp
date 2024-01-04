#include<iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <queue>
#include <stack>

void addEdge(std::vector<std::list<int>>& g, int from, int to, bool isDirected = false)
{
    g[from].push_back(to);

    if (!isDirected)
        g[to].push_back(from);
}

std::vector<std::list<int>> readGrapth(int vectices, int edges, bool isDirected = true)
{
    std::vector<std::list<int>> result(vectices);

    for (size_t i = 0; i < edges; i++)
    {
        int from;
        int to;

        std::cin >> from >> to;

        addEdge(result, from, to, isDirected);
    }

    return result;
}


void dfsVisit(const std::vector<std::list<int>>& g, int curr, std::vector<bool>& visited)
{
	if (visited[curr])
		return;

	visited[curr] = true;
	//std::cout << curr << " ";

	for (int neighbour : g[curr])
	{
		dfsVisit(g, neighbour, visited);
	}
}

void dfs(const std::vector<std::list<int>>& g, int start)
{
	std::vector<bool> visited(g.size());
	dfsVisit(g, start, visited);
}

int conectedComponentsCount(const std::vector<std::list<int>>& g)
{
    std::vector<bool> visited(g.size());
    int result = 0;

    for (size_t i = 0; i < g.size(); i++)
    {
        if (!visited[i])
        {
            dfsVisit(g, i, visited);
            result++;
        }
    }

    return result;
}

void dfsVerticesSumAndCount(const std::vector<std::list<int>>& g, int curr, int& count, int& sum, std::vector<bool>& visited)
{
    if (visited[curr] == true)
        return;

    visited[curr] = true;
    sum += curr;
    count++;

    for (int neighbour : g[curr])
    {
        dfsVerticesSumAndCount(g, neighbour, count, sum, visited);
    }
}

double CCAVG(const std::vector<std::list<int>>& g)
{
    double result = 0;
    std::vector<bool> visited(g.size());

    for (size_t i = 0; i < g.size(); i++)
    {
        int sum = 0;
        int count = 0;

        dfsVerticesSumAndCount(g, i, count, sum, visited);

        if (count > 0)
        {
            result += (double)sum / count;
        }
    }

    return result;
}

void bfs(const std::vector<std::list<int>>& g, int start)
{
    std::queue<int> q;
    q.push(start);
    std::vector<bool> visited(g.size());

    while (!q.empty())
    {
        int curr = q.front();
        q.pop();

        if (visited[curr])
            continue;

        visited[curr] = true;
        std::cout << curr << " ";

        for (int neighbour : g[curr])
        {
            if (!visited[neighbour])
            {
                q.push(neighbour);
            }
        }
    }
}

std::vector<int> getPath(const std::vector<int>& parents, int start, int end)
{
    std::vector<int> result;

    if (parents[end] != -1)
    {
        int curr = end;

        while (curr != start)
        {
            result.push_back(curr);
            curr = parents[curr];
        }

        result.push_back(curr);
    }

    std::reverse(result.begin(), result.end());

    return result;
}

std::vector<int> bfsShortestPath(const std::vector<std::list<int>>& g, int start, int end)
{
    std::queue<int> q;
    q.push(start);
    std::vector<bool> visited(g.size());
    std::vector<int> parent(g.size(), -1);

    while (!q.empty())
    {
        int curr = q.front();
        q.pop();
        visited[curr] = true;

        if (curr == end)
            break;

        for (int neighbour : g[curr])
        {
            if (!visited[neighbour])
            {
                q.push(neighbour);
            }

            if (parent[neighbour] == -1)
            {
                parent[neighbour] = curr;
            }
        }
    }

    return getPath(parent, start, end);
}

void topoSorHelp(const std::vector<std::list<int>>& g, int curr, std::vector<bool>& visited, std::stack<int>& stack)
{
    if (visited[curr])
        return;

    visited[curr] = true;

    for (int neighbour : g[curr])
    {
        topoSorHelp(g, neighbour, visited, stack);
    }

    stack.push(curr);
}

std::vector<int> topoSort(const std::vector<std::list<int>>& g)
{
    std::stack<int> stack;
    std::vector<int> result;
    std::vector<bool> visited(g.size());

    for (size_t i = 0; i < g.size(); i++)
    {
        topoSorHelp(g, i, visited, stack);
    }

    while (!stack.empty())
    {
        result.push_back(stack.top());
        stack.pop();
    }

    return result;
}

bool hasCycleHelp(const std::vector<std::list<int>>& g, int curr, std::vector<bool>& visited, std::vector<bool>& stack)
{
    if (visited[curr])
        return false;

    visited[curr] = true;
    stack[curr] = true;

    for (int neighbour : g[curr])
    {
        if (stack[neighbour] == true || hasCycleHelp(g, neighbour, visited, stack))
        {
            return true;
        }
    }

    stack[curr] = false;

    return false;
}

bool hasCycle(const std::vector<std::list<int>>& g)
{
    std::vector<bool> visited(g.size());
    std::vector<bool> stack(g.size());

    for (size_t i = 0; i < g.size(); i++)
    {
        if (hasCycleHelp(g, i, visited, stack))
            return true;
    }

    return false;
}

int main()
{
    std::vector<std::list<int>> g(12);
    
    addEdge(g, 0, 2);
    addEdge(g, 0, 4);
    addEdge(g, 0, 5);
    addEdge(g, 0, 8);
    addEdge(g, 1, 7);
    addEdge(g, 1, 3);
    addEdge(g, 2, 4);
    addEdge(g, 2, 5);
    addEdge(g, 2, 6);
    addEdge(g, 2, 7);
    addEdge(g, 3, 9);
    addEdge(g, 4, 6);
    addEdge(g, 8, 11);
    addEdge(g, 8, 10);

    std::vector<int> path = topoSort(g);

    std::cout << hasCycle(g);
}

