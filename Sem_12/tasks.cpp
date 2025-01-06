#include <iostream>
#include <unordered_map>
#include <iterator>
#include <queue>
#include <stack>
#include <algorithm>

void addEdge(std::vector<std::list<int>>& g, int v, int u, bool isDirected = false)
{
    g[v].push_back(u);

    if (!isDirected)
        g[u].push_back(v);
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

    //std::cout << curr << " ";

    visited[curr] = true;

    for (int neighbour: g[curr])
    {
        dfsVisit(g, neighbour, visited);
    }

    //std::cout << curr << " ";
}

void dfs(const std::vector<std::list<int>>& g, int start)
{
    std::vector<bool> visited(g.size(), false);
    dfsVisit(g, start, visited);
}

int countConectedComponents(const std::vector<std::list<int>>& g)
{
    int count = 0;
    std::vector<bool> visited(g.size(), false);

    for (size_t i = 0; i < g.size(); i++)
    {
        if (!visited[i])
        {
            dfsVisit(g, i, visited);
            count++;
        }
    }

    return count;
}

void CCAVG_dfs(const std::vector<std::list<int>>& g, int curr, int& count, int& sum, std::vector<bool>& visited)
{
    if (visited[curr])
        return;

    //std::cout << curr << " ";

    count++;
    sum += curr;

    visited[curr] = true;

    for (int neighbour : g[curr])
    {
        CCAVG_dfs(g, neighbour, count, sum, visited);
    }

    //std::cout << curr << " ";
}

double CCAVG(const std::vector<std::list<int>>& g)
{
    double result = 0;
    std::vector<bool> visited(g.size(), false);

    for (size_t i = 0; i < g.size(); i++)
    {
        if (!visited[i])
        {
            int sum = 0;
            int count = 0;
            CCAVG_dfs(g, i, count, sum, visited);
            result += ((double)sum) / count;
        }
    }

    return result;
}

void bfs(const std::vector<std::list<int>>& g, int start)
{
    std::queue<int> q;
    std::vector<bool> visited(g.size(), false);
    q.push(start);
    visited[start] = true;

    while (!q.empty())
    {
        int curr = q.front();
        q.pop();

        visited[curr] = true;

        for (int neighbour : g[curr])
        {
            if (!visited[neighbour])
            {
                q.push(neighbour);
                visited[neighbour] = true;
            }
        }
    }
}

std::vector<int> bfsShortestPath(const std::vector<std::list<int>>& g, int start, int end)
{
    std::queue<int> q;
    std::vector<bool> visited(g.size(), false);
    std::vector<int> parents(g.size(), -1);
    q.push(start);
    visited[start] = true;

    while (!q.empty())
    {
        int curr = q.front();
        q.pop();


        for (int neighbour : g[curr])
        {
            if (!visited[neighbour])
            {
                q.push(neighbour);
                parents[neighbour] = curr;
                visited[neighbour] = true;
            }

            if (neighbour == end)
                break;
        }
    }

    std::vector<int> result;
    int curr = end;
    while (parents[curr] != -1)
    {
        result.push_back(curr);
        curr = parents[curr];
    }

    result.push_back(start);
    std::reverse(result.begin(), result.end());

    return result;
}

void dfsTopoSort(const std::vector<std::list<int>>& g, 
    int curr, std::vector<bool>& visited, std::stack<int>& s)
{
    if (visited[curr])
        return;

    visited[curr] = true;

    for (int neighbour : g[curr])
    {
        dfsTopoSort(g, neighbour, visited, s);
    }

    s.push(curr);
}

std::vector<int> topoSort(const std::vector<std::list<int>>& g)
{
    std::vector<int> result;
    std::vector<bool> visited(g.size(), false);
    std::stack<int> s;

    for (size_t i = 0; i < g.size(); i++)
    {
        dfsTopoSort(g, i, visited, s);
    }

    while (!s.empty())
    {
        result.push_back(s.top());
        s.pop();
    }

    return result;
}

bool hasCylceHelp(const std::vector<std::list<int>>& g, int curr,
    std::vector<bool>& visited, std::vector<bool>& stack)
{
    visited[curr] = true;
    stack[curr] = true;

    for (int neighbour : g[curr])
    {
        if (visited[neighbour] && stack[neighbour])
            return true;

        if (!visited[neighbour] && hasCylceHelp(g, neighbour, visited, stack))
            return true;
    }

    stack[curr] = false;
}

bool hasCylce(const std::vector<std::list<int>>& g)
{
    std::vector<bool> visited(g.size(), false);
    std::vector<bool> stack(g.size(), false);

    for (size_t i = 0; i < g.size(); i++)
    {
        if (hasCylceHelp(g, i, visited, stack))
            return true;
    }

    return false;
}

int main()
{
    std::vector<std::list<int>> g(12);
    g = readGrapth(9, 8, false);
    //addEdge(g, 0, 2, true);
    //addEdge(g, 0, 4, true);
    //addEdge(g, 0, 5, true);
    //addEdge(g, 0, 8, true);

    //addEdge(g, 1, 7, true);
    //addEdge(g, 1, 3, true);

    //addEdge(g, 2, 4, true);
    //addEdge(g, 2, 5, true);
    //addEdge(g, 2, 6, true);
    //addEdge(g, 2, 7, true);

    //addEdge(g, 3, 9, true);

    //addEdge(g, 4, 6, true);

    //addEdge(g, 8, 11, true);
    //addEdge(g, 8, 10, true);

    std::cout<< CCAVG(g);

}