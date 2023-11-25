//
// Created by 志源 on 2023/11/16.
//

#include <iostream>
#include <string>

using namespace std;

const int MAX_ROWS = 10; // Maximum number of rows in the maze
const int MAX_COLS = 10; // Maximum number of columns in the maze
const int MAX_DIRS = 100; // Maximum number of directions

void strToInt(string s, int *move) {
    if (s == "N") {
        *move = -1;
        *(move + 1) = 0;
    } else if (s == "S") {
        *move = 1;
        *(move + 1) = 0;
    } else if (s == "W") {
        *move = 0;
        *(move + 1) = -1;
    } else if (s == "E") {
        *move = 0;
        *(move + 1) = 1;
    }
}

void findStart(int maze[MAX_ROWS][MAX_COLS], int *loc) {
    //find start point
    for (int i = 0; i < MAX_ROWS; ++i) {
        for (int j = 0; j < MAX_COLS; ++j) {
            if (maze[i][j] == 2) {
                loc[0] = i;
                loc[1] = j;
                return;
            }
        }
    }
}

string exitMaze(int maze[MAX_ROWS][MAX_COLS], string directions[], int numDirections) {
    //find start point
    int loc[] = {0, 0};
    findStart(maze, loc);

    for (int i = 0; i < numDirections; ++i) {
        string s = directions[i];
        int *move = new int[2];
        strToInt(s, move);
//        int x = move[0], y = move[1];
        int x1 = loc[0] + move[0];
        int y1 = loc[1] + move[1];

        if (x1 < 0 || x1 >= MAX_ROWS || y1 < 0 || y1 >= MAX_COLS || maze[x1][y1] == 1) {
            return "Dead";
        }
        if (maze[x1][y1] == 3) return "Finish";
        loc[0] = x1;
        loc[1] = y1;
    }
    return "Lost";
}


int main() {
    int maze[MAX_ROWS][MAX_COLS] = {
            {1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
            {1, 3, 1, 0, 1, 0, 0, 0, 0, 1},
            {1, 0, 1, 0, 0, 0, 1, 1, 0, 1},
            {1, 0, 1, 1, 1, 1, 1, 0, 0, 1},
            {1, 0, 1, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 1, 0, 1, 0, 1, 0, 0, 1},
            {1, 0, 1, 0, 1, 0, 0, 0, 0, 0},
            {1, 0, 1, 0, 1, 0, 1, 1, 0, 1},
            {1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
            {1, 1, 1, 0, 1, 1, 1, 1, 2, 1}
    };

    string directions[MAX_DIRS];
    int numDirections = 0;
    string input = "";

// Enter directions (N, E, S, W), one per line. Enter ' ' to finish input
    while (numDirections < MAX_DIRS) {
        getline(cin, input);
        if (input == "") {
            break;
        }
        if (input == "N" || input == "E" || input == "S" || input == "W") {
            directions[numDirections++] = input;
        } else {
            cout << "Invalid direction entered. Please enter N, E, S, or W." << endl;
        }
    }

    string result = exitMaze(maze, directions, numDirections);
    cout << "Result: " << result << endl;

    return 0;
}