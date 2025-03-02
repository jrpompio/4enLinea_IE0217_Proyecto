#include "Matrix6x7.hpp"

Matrix6x7::Matrix6x7() {
    table = vector<vector<int>>(6, vector<int>(7, 0));
    fill();
}

void Matrix6x7::fill() {
    for (auto &row : table) {
        for (auto &celda : row) {
            celda = 0;
        }
    }
}

const vector<vector<int>>& Matrix6x7::get_table() const {
    return table;
}

bool Matrix6x7::insert(int col, int player) {
    if (table[0][col] == 0) {
        table[0][col] = player;
        return true;
    }
    return false;
}

int Matrix6x7::gravity(int col) {
    for (int row = 0; row < 6 - 1; row++) {
        if (table[row][col] != 0 && table[row+1][col] == 0) {
            int temp = table[row][col];
            table[row][col] = table[row+1][col];
            table[row+1][col] = temp;
            return row + 1;
        }
    }
    return 6 - 1;
}

bool Matrix6x7::explore(int R, int C, int dR, int dC) {
    path.clear();
    while (R >= 0 && R < 6 && C >= 0 && C < 7) {
        path.push_back(table[R][C]);
        R += dR;
        C += dC;
    }
    if (path.size() > 3 && path[0] == path[1] &&
        path[1] == path[2] && path[2] == path[3] &&
        path[0] != 0)
        return true;
    return false;
}

bool Matrix6x7::exploreDirections(int col, int row) {
    if (explore(row, col, 1, 0)   ||  // Vertical (hacia abajo)
        explore(row, col, 0, -1)  ||  // Horizontal (izquierda)
        explore(row, col, 0, 1)   ||  // Horizontal (derecha)
        explore(row, col, -1, -1) ||  // Diagonal (arriba-izquierda)
        explore(row, col, -1, 1)  ||  // Diagonal (arriba-derecha)
        explore(row, col, 1, -1)  ||  // Diagonal (abajo-izquierda)
        explore(row, col, 1, 1))       // Diagonal (abajo-derecha)
        return true;
    return false;
}
