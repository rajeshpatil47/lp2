#include<iostream>
#include<queue>
#include <vector>
using namespace std;

class Graph{
    int V;
    vector<vector<int>> adj;

    public:
    Graph(int V){
        this -> V = V;
        adj.resize(V);
    }

    void addedge(int v, int w){
        adj[v].push_back(w);
        adj[w].push_back(v);
    }

    void DFSutil(int v, vector<bool> &visited){
        visited[v] = true;

        cout<< v << " ";

        for (int i : adj[v]){
            if(!visited[i]){
                DFSutil(i, visited);
            }
        }
    }

    void DFS (int start){
        vector<bool> visited (V, false);
        cout<<"DFS Traversal: ";

        DFSutil (start, visited);
        cout<<endl;
    }

    void BFS(int start){
        vector<bool> visited (V, false);

        queue<int> q;

        visited[start] = true;
        q.push(start);

        cout<<"BFS Traversal: ";

        while(!q.empty()){
            int v = q.front();
            cout<< v << " ";
            q.pop();

            for(int i : adj[v]){
                if(!visited[i]){
                    visited[i] = true;
                    q.push(i);
                }
            }
        }
    }

    void input(){
        int edges, v, w;
        cout<<"Enter Number of Edges: ";
        cin>>edges;

        cout<<"Enter " << edges <<" edges (ver1 vert2)"<<endl;
        for(int i = 0; i<edges; i++){
            cin>>v>>w;
            addedge(v,w);
        }
    }
};

int main(){
    int V, start;

    cout<<"Enter Number of Vertices: ";
    cin>>V;

    Graph g(V);
    g.input();

    cout<<"Enter starting Vertex: ";
    cin>>start;

    g.DFS(start);
    g.BFS(start);

    return 0;
}

