/*Design n-Queens matrix having first Queen placed. Use backtracking to place remaining
Queens to generate the final n-queen‘s matrix*/
// C++ program to solve N Queen Problem using backtracking
#include <iostream>
#include <vector>
using namespace std;
void printBoard(const vector<vector<int>> &board, int n)
{
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            cout << (board[i][j] ? "Q" : ".") << " ";
        }
        cout << endl;
    }
    cout << endl;
}
// Function to check if it's safe to place a queen at position (row, col)
bool isSafe(const vector<vector<int>> &board, int row, int col, int n)
{
    // Check in the same row
    for (int i = 0; i < n; ++i)
    {
        if (board[row][i])
        {
            return false;
        }
    }

    // Check in the same column
    // for (int i = 0; i < n; ++i)
    // {
    //     if (board[i][col])
    //     {
    //         return false;
    //     }
    // }

    // Check upper left diagonal
    for (int i = row, j = col; i >= 0 && j >= 0; --i, --j)
    {
        if (board[i][j])
        {
            return false;
        }
    }

    // Check upper right diagonal
    for (int i = row, j = col; i >= 0 && j < n; --i, ++j)
    {
        if (board[i][j])
        {
            return false;
        }
    }

    // Check lower left diagonal
    for (int i = row, j = col; i < n && j >= 0; ++i, --j)
    {
        if (board[i][j])
        {
            return false;
        }
    }
    // Check lower right diagonal
    for (int i = row, j = col; i < n && j < n; ++i, ++j)
    {
        if (board[i][j])
        {
            return false;
        }
    }
    return true;
}
// Function to solve N-Queens problem using backtracking
void solveNQueens(vector<vector<int>> &board, int col, int n)
{
    // If all queens are placed, print the solution
    if (col == n)
    {
        printBoard(board, n);
        return;
    }

    // Try placing queen in each row of the current column
    for (int i = 0; i < n; ++i)
    {
        if (isSafe(board, i, col, n))
        {
            // Place queen
            board[i][col] = 1;

            // Recur to place queens in the remaining columns
            solveNQueens(board, col + 1, n);

            // Backtrack: If placing queen in the current position doesn't lead to a solution, remove queen
            board[i][col] = 0;
        }
    }
}

int main()
{
    int n;

    // Get the size of the chessboard
    cout << "Enter the size of the chessboard (N): ";
    cin >> n;

    // Initialize the chessboard
    vector<vector<int>> board(n, vector<int>(n, 0));

    // Place the first queen (you can change the starting position if needed)
    cout << "R and C - ";
    int x, y;
    cin >> x >> y;
    board[x][y] = 1;

    // Start solving the N-Queens problem
    solveNQueens(board, 1, n);

    return 0;
}
