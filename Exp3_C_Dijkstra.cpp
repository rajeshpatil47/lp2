#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max(); // Infinite value for unvisited nodes

// Graph representation using adjacency list
class Graph {
public:
    int V; // Number of vertices
    vector<vector<pair<int, int>>> adjList; // Adjacency list (node, weight)

    // Constructor to initialize the graph
    Graph(int vertices) {
        V = vertices;
        adjList.resize(V);
    }

    // Function to add an edge (u -> v) with weight w
    void addEdge(int u, int v, int w) {
        if (u < 0 || u >= V || v < 0 || v >= V) {
            cerr << "Invalid edge (" << u << ", " << v << ") - Skipped.\n";
            return;
        }
        adjList[u].push_back({v, w});
        adjList[v].push_back({u, w}); // Remove this line for a directed graph
    }
};

// Function to take input for the graph
void inputGraph(Graph &graph, int &E) {
    cout << "Enter the number of edges: ";
    cin >> E;

    cout << "Enter edges (source destination weight):\n";
    for (int i = 0; i < E; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph.addEdge(u, v, w);
    }
}

// Dijkstra’s Algorithm Implementation
vector<int> dijkstra(Graph &graph, int source) {
    int V = graph.V;
    vector<int> dist(V, INF); // Distance array, initialized to INF
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    dist[source] = 0; // Distance from source to itself is 0
    pq.push({0, source}); // Push (distance, node) into priority queue

    while (!pq.empty()) {
        int currDist = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        // Skip if this is a stale entry
        if (currDist > dist[u])
            continue;

        // Relaxation: Update distance for all adjacent vertices
        for (auto neighbor : graph.adjList[u]) {
            int v = neighbor.first;
            int weight = neighbor.second;

            if (dist[u] + weight < dist[v]) { // Relaxation condition
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    return dist; // Return shortest distances from source to all nodes
}

// Function to display the shortest path results
void displayResults(const vector<int> &dist, int source) {
    cout << "\nShortest distances from source node " << source << ":\n";
    for (int i = 0; i < dist.size(); i++) {
        cout << "Node " << i << " : ";
        if (dist[i] == INF)
            cout << "Unreachable\n";
        else
            cout << dist[i] << "\n";
    }
}

int main() {
    int V, E, source;

    cout << "Enter the number of vertices: ";
    cin >> V;

    if (V <= 0) {
        cerr << "Invalid number of vertices.\n";
        return 1;
    }

    cout << "(Note: Vertices are 0-indexed from 0 to " << V - 1 << ")\n";

    Graph graph(V); // Create a graph with V vertices
    inputGraph(graph, E);

    cout << "Enter the source node: ";
    cin >> source;

    if (source < 0 || source >= V) {
        cerr << "Invalid source node.\n";
        return 1;
    }

    vector<int> shortestDistances = dijkstra(graph, source);
    displayResults(shortestDistances, source);

    return 0;
}
