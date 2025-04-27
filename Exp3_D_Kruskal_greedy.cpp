#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Structure to represent an edge with source, destination, and weight
struct Edge {
    int src, dest, weight;
};

// Structure to represent a subset for Union-Find
struct Subset {
    int parent, rank;
};

// Function to compare two edges based on weight (for sorting)
bool compareEdges(Edge a, Edge b) {
    return a.weight < b.weight;
}

// Function to find the parent of a node (with path compression)
int find(Subset subsets[], int i) {
    if (subsets[i].parent != i) {
        subsets[i].parent = find(subsets, subsets[i].parent);
    }
    return subsets[i].parent;
}

// Function to perform union of two sets (by rank)
void Union(Subset subsets[], int x, int y) {
    int rootX = find(subsets, x);
    int rootY = find(subsets, y);

    if (subsets[rootX].rank < subsets[rootY].rank)
        subsets[rootX].parent = rootY;
    else if (subsets[rootX].rank > subsets[rootY].rank)
        subsets[rootY].parent = rootX;
    else {
        subsets[rootY].parent = rootX;
        subsets[rootX].rank++;
    }
}

// Function to take user input for the graph
void inputGraph(vector<Edge> &edges, int &V, int &E) {
    cout << "Enter the number of vertices: ";
    cin >> V;
    cout << "Enter the number of edges: ";
    cin >> E;

    edges.resize(E);
    cout << "Enter edges (source destination weight):\n";
    for (int i = 0; i < E; i++) {
        cin >> edges[i].src >> edges[i].dest >> edges[i].weight;
    }
}

// Function to implement Kruskal's Algorithm
void kruskalMST(vector<Edge> &edges, int V, int E) {
    // Step 1: Sort edges in increasing order of weight
    sort(edges.begin(), edges.end(), compareEdges);

    // Allocate memory for subsets
    Subset *subsets = new Subset[V];

    // Initialize each vertex as a separate subset
    for (int v = 0; v < V; v++) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    vector<Edge> MST; // Store the edges of the MST
    int mstWeight = 0, edgeCount = 0;

    // Step 2: Pick the smallest edge and check for cycles using Union-Find
    for (int i = 0; i < E && edgeCount < V - 1; i++) {
        Edge nextEdge = edges[i];

        int rootSrc = find(subsets, nextEdge.src);
        int rootDest = find(subsets, nextEdge.dest);

        // If adding this edge does not create a cycle, add it to MST
        if (rootSrc != rootDest) {
            MST.push_back(nextEdge);
            mstWeight += nextEdge.weight;
            Union(subsets, rootSrc, rootDest);
            edgeCount++;
        }
    }

    // Display the Minimum Spanning Tree
    cout << "\nMinimum Spanning Tree (MST) Edges:\n";
    for (Edge edge : MST) {
        cout << edge.src << " -- " << edge.dest << " : " << edge.weight << "\n";
    }
    cout << "Total MST Weight: " << mstWeight << endl;

    delete[] subsets; // Free allocated memory
}

int main() {
    vector<Edge> edges;
    int V, E;

    inputGraph(edges, V, E);
    kruskalMST(edges, V, E);

    return 0;
}
