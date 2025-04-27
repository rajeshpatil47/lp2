#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <cmath>

using namespace std;

#define N 3  // Size of the puzzle (3x3)

// Structure to represent a state of the puzzle
struct Node {
    vector<vector<int>> state; // 3x3 puzzle board
    int g, h, f; // Cost values
    pair<int, int> zeroPos; // Position of the empty tile (0)
    vector<Node*> path; // Path to reach this node

    // Constructor
    Node(vector<vector<int>> s, int gCost, int hCost, pair<int, int> zero, vector<Node*> p) {
        state = s;
        g = gCost;
        h = hCost;
        f = g + h;
        zeroPos = zero;
        path = p;
    }

    // Operator overloading for priority queue (Min-Heap)
    bool operator>(const Node &other) const {
        return f > other.f;
    }
};

// Function to take input for the puzzle
vector<vector<int>> getInput(string prompt) {
    vector<vector<int>> board(N, vector<int>(N));
    cout << prompt << " (Enter 9 numbers row-wise, use 0 for empty tile):\n";
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            cin >> board[i][j];
    return board;
}

// Function to find the position of the zero tile
pair<int, int> findZero(const vector<vector<int>> &state) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (state[i][j] == 0)
                return {i, j};
    return {-1, -1};
}

// Function to check if two puzzle states are equal
bool isSameState(const vector<vector<int>> &a, const vector<vector<int>> &b) {
    return a == b;
}

// Heuristic function: Count misplaced tiles
int misplacedTiles(const vector<vector<int>> &state, const vector<vector<int>> &goal) {
    int misplaced = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (state[i][j] != 0 && state[i][j] != goal[i][j])
                misplaced++;
    return misplaced;
}

// Generate possible moves for the zero tile
vector<pair<int, int>> getMoves(pair<int, int> zeroPos) {
    int x = zeroPos.first, y = zeroPos.second;
    vector<pair<int, int>> moves;
    if (x > 0) moves.push_back({x - 1, y}); // Move up
    if (x < N - 1) moves.push_back({x + 1, y}); // Move down
    if (y > 0) moves.push_back({x, y - 1}); // Move left
    if (y < N - 1) moves.push_back({x, y + 1}); // Move right
    return moves;
}

// Apply a move to generate a new state
vector<vector<int>> applyMove(const vector<vector<int>> &state, pair<int, int> zeroPos, pair<int, int> newZeroPos) {
    vector<vector<int>> newState = state;
    swap(newState[zeroPos.first][zeroPos.second], newState[newZeroPos.first][newZeroPos.second]);
    return newState;
}

// Function to solve the 8-puzzle using A* search
void solvePuzzle(vector<vector<int>> startState, vector<vector<int>> goalState) {
    priority_queue<Node, vector<Node>, greater<Node>> openList; // Min-Heap
    set<vector<vector<int>>> closedList; // Visited states

    pair<int, int> startZero = findZero(startState);
    Node* startNode = new Node(startState, 0, misplacedTiles(startState, goalState), startZero, {});
    openList.push(*startNode);

    while (!openList.empty()) {
        Node current = openList.top();
        openList.pop();

        // If goal state is reached, print the solution
        if (isSameState(current.state, goalState)) {
            cout << "\nSolution Found!\n";
            for (Node* step : current.path) {
                for (const auto &row : step->state) {
                    for (int val : row)
                        cout << val << " ";
                    cout << endl;
                }
                cout << "------\n";
            }
            return;
        }

        // Add to closed list
        closedList.insert(current.state);

        // Generate possible moves
        for (auto move : getMoves(current.zeroPos)) {
            vector<vector<int>> newState = applyMove(current.state, current.zeroPos, move);
            if (closedList.find(newState) != closedList.end()) continue;

            vector<Node*> newPath = current.path;
            newPath.push_back(new Node(current.state, current.g, current.h, current.zeroPos, {}));

            int newG = current.g + 1;
            int newH = misplacedTiles(newState, goalState);
            Node* newNode = new Node(newState, newG, newH, move, newPath);
            openList.push(*newNode);
        }
    }

    cout << "No solution found!\n";
}

int main() {
    vector<vector<int>> startState = getInput("Enter the initial state");
    vector<vector<int>> goalState = getInput("Enter the goal state");

    cout << "Solving the 8-Puzzle using A* Algorithm...\n";
    solvePuzzle(startState, goalState);

    return 0;
}
