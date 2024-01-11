#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <algorithm>

struct Graph
{
	std::vector<std::list<int>> adj;

	Graph(int V) : adj(V) {};

	void addEdge(int from, int to)
	{
		adj[from].push_back(to);
		adj[to].push_back(from);
	}
};

struct ConComp
{
	std::vector<int> vertices;

	bool operator<(const ConComp& other) const
	{
		return vertices.size() < other.vertices.size();
	}
};

void dfs(const Graph& g, int currVertex, std::vector<bool>& visited, ConComp& conComp)
{
	if (visited[currVertex])
		return;

	visited[currVertex] = true;
	conComp.vertices.push_back(currVertex);

	for (int neigh : g.adj[currVertex])
	{
		dfs(g, neigh, visited, conComp);
	}
}

void getConCompInfo(const Graph& g)
{
	std::vector<ConComp> conComps;
	std::vector<bool> visited(g.adj.size());

	for (size_t i = 0; i < g.adj.size(); i++)
	{
		ConComp conComp;

		if (!visited[i])
		{
			dfs(g, i, visited, conComp);
			conComps.push_back(conComp);
		}
	}

	std::cout << conComps.size() << std::endl;
	std::sort(conComps.begin(), conComps.end());

	for (const ConComp& cc : conComps)
	{
		for (int vertex : cc.vertices)
		{
			std::cout << vertex << " ";
		}

		std::cout << std::endl;
	}
}

int main()
{
	Graph g(9);

	g.addEdge(0, 1);
	g.addEdge(0, 7);
	g.addEdge(1, 2);
	g.addEdge(1, 7);
	g.addEdge(2, 3);
	g.addEdge(2, 8);
	g.addEdge(2, 5);
	//g.addEdge(3, 4);
	g.addEdge(3, 5);
	//g.addEdge(4, 5);
	g.addEdge(5, 6);
	g.addEdge(6, 7);
	g.addEdge(6, 8);
	g.addEdge(7, 8);

	getConCompInfo(g);
}
