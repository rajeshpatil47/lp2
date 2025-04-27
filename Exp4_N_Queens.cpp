#include<iostream>
#include<cmath>
#include<vector>
using namespace std;


int getinput(){
    int n;
    cout<<"Enter number of Queens (N): ";
    cin>> n;
    return n;
}

void Print(vector<int> &board, int N){
    cout<<"\nSolution: "<<endl;
    for(int i = 0; i<N; i++){
        for(int j = 0; j<N; j++){
            if(board[i] == j){
                cout<<" Q ";
            } else{
                cout<<" . ";
            }
        }
        cout<<endl;
    }
}

bool isSafe(vector<int> &board, int row, int col){
    for(int i = 0; i<row; i++){
        if(board[i]==col || abs(board[i]-col) == abs(i-row)){
            return false;
        }
    }
    return true;
}

bool Solve1(vector<int> &board, int row, int N){
    if(row == N){
        Print(board, N);
        return true;
    }

    bool found = false;
    for(int col = 0; col<N; col++){
        if(isSafe(board, row, col)){
            board[row] = col;
            found = Solve1(board, row+1, N) || found;
            board[row] = -1;
        }
    }
    return found;
}

bool solve2(vector<int> &board, int row, int N, vector<bool> &colused, vector<bool> &diag1, vector<bool> &diag2){
    if(row == N){
        Print(board, N);
        return true;
    }

    bool found = false;
    for(int col=0; col<N; col++){
        if(!colused[col] && !diag1[row-col+N-1] && !diag2[row+col]){
            board[row] = col;
            colused[col] = diag1[row-col+N-1] = diag2[row+col] = true;
            found = solve2(board, row+1, N, colused, diag1, diag2) || found;
            colused[col] = diag1[row-col+N-1] = diag2[row+col] = false;
        }
    }

    return found;
}

int main(){
    int N = getinput();

    cout<<"Enter 1 for Backtracking"<<endl;
    cout<<"Enter 2 for Branch and Bound"<<endl;

    int ch;
    cout<<"Enter your choice: ";
    cin>>ch;

    switch (ch)
    {
    case 1:{
        cout<<"\nSolving uisng backtracking: "<<endl;
        vector<int> board(N, -1);

        if(!Solve1(board, 0, N)){
            cout<<"No solution found"<<endl;
        }
        break;
    }

    case 2:{
        cout<<"\nSolving using branch And Bound "<<endl;
        vector<int> board(N, -1);
        vector<bool> colused(N, false); 
        vector<bool>diag1(2*N-1, false);
        vector<bool>diag2(2*N-1, false);

        if(!solve2(board, 0, N, colused, diag1, diag2)){
            cout<<"No solution found"<<endl;
        }
        break;
    }
    
    default:
        cout<<"invalid Choice"<<endl;
        break;
    }

    return 0;
}
