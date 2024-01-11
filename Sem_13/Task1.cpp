#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
#include <list>
#include <queue>

struct Edge
{
    int to;
    int weight;
};

struct Graph
{
    std::vector<std::list<Edge>> adj;

    Graph(int V) : adj(V) {};

    void addEdge(int from, int to, int w)
    {
        adj[from].push_back({ to, w });
        adj[to].push_back({ from, w });
    }
};

void dijksta(const Graph& g, int source)
{
    std::vector<int> dist(g.adj.size(), INT_MAX);
    std::vector<bool> visited(g.adj.size());
    std::vector<int> parents(g.adj.size(), -1);

    dist[source] = 0;

    for (size_t i = 0; i < g.adj.size(); i++)
    {
        int currVertex = -1;
        int currDist = INT_MAX;

        for (size_t vertex = 0; vertex < g.adj.size(); vertex++)
        {
            if (!visited[vertex] && dist[vertex] < currDist)
            {
                currVertex = vertex;
                currDist = dist[vertex];
            }
        }

        if (currDist == INT_MAX)
            break;

        visited[currVertex] = true;

        for (Edge edge : g.adj[currVertex])
        {
            if (!visited[edge.to] && dist[currVertex] + edge.weight < dist[edge.to])
            {
                dist[edge.to] = dist[currVertex] + edge.weight;
                parents[edge.to] = currVertex;
            }
        }
    }

    for (size_t i = 0; i < g.adj.size(); i++)
    {
        std::cout << i << " dist is " << dist[i] << std::endl;
    }

}

struct distPair
{
    int dist;
    int vertex;

    bool operator<(const distPair& other) const
    {
        return dist > other.dist;
    }
};


void dijksta2(const Graph& g, int source)
{
    std::vector<bool> visited(g.adj.size());
    std::vector<int> parents(g.adj.size(), -1);
    std::vector<int> dist(g.adj.size(), INT_MAX);
    std::priority_queue<distPair> q;

    q.push({ 0, source });

    while (!q.empty())
    {
        distPair currDist = q.top();
        q.pop();

        if (currDist.dist == INT_MAX)
            break;

        int currVertex = currDist.vertex;

        if (visited[currVertex])
            continue;

        visited[currDist.vertex] = true;
        dist[currDist.vertex] = currDist.dist;

        for (Edge edge : g.adj[currVertex])
        {
            if (!visited[edge.to] && dist[currVertex] + edge.weight < dist[edge.to])
            {
                dist[edge.to] = dist[currVertex] + edge.weight;
                parents[edge.to] = currVertex;
                q.push({ dist[edge.to], edge.to });
            }
        }
    }

    for (size_t i = 0; i < g.adj.size(); i++)
    {
        std::cout << i << " dist is " << dist[i] << std::endl;
    }
}


int main()
{
    Graph g(9);

    g.addEdge(0, 1, 4);
    g.addEdge(0, 7, 8);
    g.addEdge(1, 2, 8);
    g.addEdge(1, 7, 11);
    g.addEdge(2, 3, 7);
    g.addEdge(2, 8, 2);
    g.addEdge(2, 5, 4);
    g.addEdge(3, 4, 9);
    g.addEdge(3, 5, 14);
    g.addEdge(4, 5, 10);
    g.addEdge(5, 6, 2);
    g.addEdge(6, 7, 1);
    g.addEdge(6, 8, 6);
    g.addEdge(7, 8, 7);

    dijksta(g, 0);
    dijksta2(g, 0);
}

