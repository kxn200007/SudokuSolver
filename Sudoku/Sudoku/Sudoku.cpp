// Sudoku.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

const int N = 9; // Size of the Sudoku grid
const int NUM_EMPTY_CELLS = 40; // Number of empty cells in the generated puzzle

// Function to print the Sudoku grid
void printGrid(const vector<vector<int>>& grid) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            cout << grid[row][col] << " ";
            if ((col + 1) % 3 == 0 && col != N - 1) {
                cout << "| "; // Add vertical separator
            }
        }
        cout << endl;
        if ((row + 1) % 3 == 0 && row != N - 1) {
            cout << "------+-------+------" << endl; // Add horizontal separator
        }
    }
}

// Function to check if a number can be placed in a cell
bool isSafe(const vector<vector<int>>& grid, int row, int col, int num) {
    // Check if 'num' is not present in the current row and column
    for (int x = 0; x < N; x++) {
        if (grid[row][x] == num || grid[x][col] == num) {
            return false;
        }
    }

    // Check if 'num' is not present in the 3x3 subgrid
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[i + startRow][j + startCol] == num) {
                return false;
            }
        }
    }

    return true;
}

// Function to solve the Sudoku puzzle using backtracking
bool solveSudoku(vector<vector<int>>& grid) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            if (grid[row][col] == 0) {
                for (int num = 1; num <= N; num++) {
                    if (isSafe(grid, row, col, num)) {
                        grid[row][col] = num;
                        if (solveSudoku(grid)) {
                            return true;
                        }
                        grid[row][col] = 0; // If no solution is found, backtrack
                    }
                }
                return false;
            }
        }
    }
    return true; // The Sudoku is solved
}

// Function to generate a valid Sudoku puzzle
void generateSudoku(vector<vector<int>>& grid) {
    srand(static_cast<unsigned>(time(0)));

    // Start with an empty grid
    grid.assign(N, vector<int>(N, 0));

    // Randomly shuffle numbers to fill the diagonal subgrids
    vector<int> nums(N);
    for (int i = 1; i <= N; i++) {
        nums[i - 1] = i;
    }
    random_shuffle(nums.begin(), nums.end());

    for (int i = 0; i < N; i++) {
        grid[i][i] = nums[i];
    }

    // Solve the Sudoku to create a valid puzzle
    if (!solveSudoku(grid)) {
        cerr << "Error: No solution exists for this Sudoku puzzle." << endl;
        exit(1); // Exit with an error code
    }

    // Randomly remove cells to create the puzzle
    for (int i = 0; i < NUM_EMPTY_CELLS; i++) {
        int row = rand() % N;
        int col = rand() % N;
        while (grid[row][col] == 0) {
            row = rand() % N;
            col = rand() % N;
        }
        grid[row][col] = 0;
    }
}

// Function to solve the Sudoku puzzle
void solvePuzzle(vector<vector<int>>& grid) {
    vector<vector<int>> solvedGrid = grid; // Copy the grid to solve

    if (solveSudoku(solvedGrid)) {
        cout << "Solved Sudoku puzzle:" << endl;
        printGrid(solvedGrid);
    }
    else {
        cout << "Error: The puzzle cannot be solved." << endl;
    }
}

int main() {
    vector<vector<int>> grid;
    char userChoice;

    while (true) {
        generateSudoku(grid);

        cout << "Random Sudoku puzzle:" << endl;
        printGrid(grid);

        cout << "\nOptions:\n";
        cout << "(C)ontinue - Generate a new puzzle\n";
        cout << "(S)olve    - Solve the puzzle\n";
        cout << "(Q)uit     - Quit the program\n";
        cout << "Enter your choice: ";
        cin >> userChoice;

        if (userChoice == 'Q' || userChoice == 'q') {
            break; // Exit the loop if the user chooses to quit
        }
        else if (userChoice == 'S' || userChoice == 's') {
            solvePuzzle(grid);
            cout << "\nOptions:\n";
            cout << "(C)ontinue - Generate a new puzzle\n";
            cout << "(Q)uit     - Quit the program\n";
            cout << "Enter your choice: ";
            cin >> userChoice;
            if (userChoice == 'Q' || userChoice == 'q') {
                break; // Exit the loop if the user chooses to quit after solving
            }
        }
    }

    return 0;
}