#include <iostream>
#include <vector>

using namespace std;

class GraphColoring {
private:
    int V;  // Number of vertices
    vector<vector<int>> adjMatrix; // Adjacency matrix
    vector<int> colors; // Stores assigned colors

public:
    // Constructor
    GraphColoring(int vertices) {
        V = vertices;
        adjMatrix.resize(V, vector<int>(V, 0));
        colors.resize(V, 0); // Initialize all vertices with no color (0)
    }

    // Function to add an edge
    void addEdge(int u, int v) {
        adjMatrix[u][v] = 1;
        adjMatrix[v][u] = 1;
    }

    // Function to check if it's safe to color a node with a given color
    bool isSafe(int node, int color) {
        for (int i = 0; i < V; i++) {
            if (adjMatrix[node][i] && colors[i] == color) {
                return false; // If adjacent node has the same color, return false
            }
        }
        return true;
    }

    // Backtracking function to assign colors
    bool graphColoringUtil(int node, int m) {
        if (node == V) return true; // If all nodes are colored, return true

        // Try different colors
        for (int col = 1; col <= m; col++) {
            if (isSafe(node, col)) {
                colors[node] = col; // Assign color

                // Recursive call to color next node
                if (graphColoringUtil(node + 1, m)) return true;

                // If coloring fails, backtrack
                colors[node] = 0;
            }
        }
        return false;
    }

    // Function to solve Graph Coloring Problem
    bool solveGraphColoring(int m) {
        if (graphColoringUtil(0, m)) {
            printSolution();
            return true;
        } else {
            cout << "Solution not possible with " << m << " colors.\n";
            return false;
        }
    }

    // Function to print the assigned colors
    void printSolution() {
        cout << "Solution colors are: \n";
        for (int i = 0; i < V; i++)
            cout << "Vertex " << i << " ---> Color " << colors[i] << endl;
    }

    // Function to take user input for graph construction
    void inputGraph() {
        int edges;
        cout << "Enter the number of edges: ";
        cin >> edges;
        cout << "Enter the edges (vertex1 vertex2): \n";
        for (int i = 0; i < edges; i++) {
            int u, v;
            cin >> u >> v;
            addEdge(u, v);
        }
    }
};

int main() {
    int V, m;
    cout << "Enter number of vertices: ";
    cin >> V;

    GraphColoring graph(V);
    graph.inputGraph();

    cout << "Enter number of colors: ";
    cin >> m;

    // Solve graph coloring problem
    graph.solveGraphColoring(m);

    return 0;
}
