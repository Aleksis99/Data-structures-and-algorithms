#include <iostream>
#include <vector>
#include <queue>
#include <list>

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

void Dijksta(const Graph& g, int start)
{
    std::vector<int> parent(g.adj.size(), -1);
    std::vector<int> dist(g.adj.size(), INT_MAX);
    std::vector<bool> visited(g.adj.size(), false);

    dist[start] = 0;

    for (size_t i = 0; i < g.adj.size(); i++)
    {
        int currDist = INT_MAX;
        int currVertex = -1;

        for (size_t vertex = 0; vertex < g.adj.size(); vertex++)
        {
            if (!visited[vertex] && dist[vertex] < currDist)
            {
                currDist = dist[vertex];
                currVertex = vertex;
            }
        }

        if (currDist == INT_MAX)
            break;

        visited[currVertex] = true;

        for (const Edge& edge : g.adj[currVertex])
        {
            int to = edge.to;
            int weight = edge.weight;

            if (!visited[to] && dist[to] > dist[currVertex] + weight)
            {
                dist[to] = dist[currVertex] + weight;
                parent[to] = currVertex;
            }

        }
    }


    for (size_t i = 0; i < dist.size(); i++)
    {
        std::cout << i << " " << dist[i] << std::endl;
    }
}

struct DistPair
{
    int vertex;
    int dist;

    bool operator<(const DistPair& other) const
    {
        return dist > other.dist;
    }
};

void DijkstaPriorityQ(const Graph& g, int start)
{
    std::vector<int> parent(g.adj.size(), -1);
    std::vector<int> dist(g.adj.size(), INT_MAX);
    std::vector<bool> visited(g.adj.size(), false);
    std::priority_queue<DistPair> pq = std::priority_queue<DistPair>();
    pq.push({ start, 0 });

    while (!pq.empty())
    {
        DistPair currPair = pq.top();
        pq.pop();
        int vertex = currPair.vertex;
        int distToVertex = currPair.dist;

        if (distToVertex == INT_MAX)
            break;

        if (visited[vertex])
            continue;

        visited[vertex] = true;
        dist[vertex] = distToVertex;

        for (const Edge& neighbour : g.adj[vertex])
        {
            int weight = neighbour.weight;
            int to = neighbour.to;
            if (weight + distToVertex < dist[to] && !visited[to])
            {
                pq.push({ to, weight + distToVertex });
            }
        }
    }

    for (size_t i = 0; i < dist.size(); i++)
    {
        std::cout << i << " " << dist[i] << std::endl;
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

    Dijksta(g, 0);
    DijkstaPriorityQ(g, 0);
}
