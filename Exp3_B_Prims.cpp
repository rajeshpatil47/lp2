#include <iostream>
#include <vector>
#include <climits>

using namespace std;

// Function to take input for graph as an adjacency matrix
void inputGraph(vector<vector<int>>& graph, int V, int E) {
    // Initialize the adjacency matrix with a high value (indicating no direct edge)
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (i == j) 
                graph[i][j] = 0;  // No self-loops
            else 
                graph[i][j] = INT_MAX;
        }
    }

    cout << "Enter the list of edges (u, v, weight):" << endl;
    for (int i = 0; i < E; i++) {
        int u, v, weight;
        cout << "Enter an edge (u v weight): ";
        cin >> u >> v >> weight;

        graph[u][v] = weight;
        graph[v][u] = weight; // Since it's an undirected graph
    }
}

// Function to find the vertex with the minimum key value (not included in MST yet)
int minKey(vector<int>& key, vector<bool>& inMST, int V) {
    int min = INT_MAX, minIndex;

    for (int v = 0; v < V; v++) {
        if (!inMST[v] && key[v] < min) {
            min = key[v];
            minIndex = v;
        }
    }
    return minIndex;
}

// Function to implement Prim's algorithm
void primMST(vector<vector<int>>& graph, int V) {
    vector<int> parent(V, -1);   // Stores the MST
    vector<int> key(V, INT_MAX); // Minimum key values
    vector<bool> inMST(V, false);// To check if vertex is in MST

    key[0] = 0;  // Start from the first vertex (arbitrary choice)

    for (int count = 0; count < V - 1; count++) {
        int u = minKey(key, inMST, V); // Pick the minimum key vertex
        inMST[u] = true; // Include it in MST

        // Update key values and parent indices of adjacent vertices
        for (int v = 0; v < V; v++) {
            if (graph[u][v] != 0 && graph[u][v] != INT_MAX && !inMST[v] && graph[u][v] < key[v]) {
                key[v] = graph[u][v];
                parent[v] = u;
            }
        }
    }

    // Print the result
    cout << "\nList of edges in the Minimum Spanning Tree (MST):" << endl;
    int totalCost = 0;
    for (int i = 1; i < V; i++) {
        cout << "( " << parent[i] << " , " << i << " , " << graph[i][parent[i]] << " )" << endl;
        totalCost += graph[i][parent[i]];
    }
    cout << "Total cost of spanning tree: " << totalCost << endl;
}

// Main function
int main() {
    int V, E;
    
    cout << "Enter number of vertices: ";
    cin >> V;
    
    cout << "Enter number of edges: ";
    cin >> E;

    vector<vector<int>> graph(V, vector<int>(V, INT_MAX));

    inputGraph(graph, V, E);
    
    primMST(graph, V);

    return 0;
}
