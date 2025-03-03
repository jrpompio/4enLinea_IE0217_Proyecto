#include <iostream>
#include <vector>
#include <limits>
#include <iomanip>

using namespace std;

class matrix6x7 {
private:
    vector<vector<int>> table;
    const int maxR = 5; // 6 filas (0-5)
    const int maxC = 6; // 7 columnas (0-6)

public:
    matrix6x7() {
        table = vector<vector<int>>(6, vector<int>(7, 0)); // 6 filas x 7 columnas
    }

    void printM() {
        cout << endl;
        for (const auto &row : table) {
            for (const int val : row) {
                cout << setw(2) << val << " ";
            }
            cout << endl;
        }
    }

    bool insert(int column, int player) {
        int row = gravity(column);
        if (row != -1) {
            table[row][column] = player;
            return true;
        }
        return false;
    }

    int gravity(int col) {
        for (int row = maxR; row >= 0; row--) {
            if (table[row][col] == 0) return row;
        }
        return -1;
    }

    bool explore(int R, int C, int dR, int dC, int player, int &count, bool checkPattern = false) {
        count = 1;
        int emptySpaces = 0;
        for (int step = 1; step < 4; step++) {
            int r = R + step * dR;
            int c = C + step * dC;
            if (r >= 0 && r <= maxR && c >= 0 && c <= maxC) {
                if (table[r][c] == player) count++;
                else if (table[r][c] == 0) emptySpaces++;
                else break;
            }
        }
        for (int step = 1; step < 4; step++) {
            int r = R - step * dR;
            int c = C - step * dC;
            if (r >= 0 && r <= maxR && c >= 0 && c <= maxC) {
                if (table[r][c] == player) count++;
                else if (table[r][c] == 0) emptySpaces++;
                else break;
            }
        }
        return checkPattern ? (count == 3 && emptySpaces > 0) : (count >= 4);
    }

    bool exploreDirections(int R, int C, int player, bool checkPattern = false) {
        int directions[4][2] = {{0,1}, {1,0}, {1,1}, {1,-1}};
        int count;
        for (auto& dir : directions) {
            if (explore(R, C, dir[0], dir[1], player, count, checkPattern)) return true;
        }
        return false;
    }

    int evaluateBoard() {
        for (int row = 0; row <= maxR; row++) {
            for (int col = 0; col <= maxC; col++) {
                if (table[row][col] != 0) {
                    int player = table[row][col];
                    if (exploreDirections(row, col, player)) {
                        return (player == -1) ? 1000 : -1000;
                    }
                }
            }
        }
        return 0;
    }

    int botMove() {
    vector<int> validMoves;
    for (int col = 0; col <= maxC; col++) {
        if (table[0][col] == 0) validMoves.push_back(col);
    }

    // 1. Primero, buscar si el bot puede ganar en esta jugada
    for (int col : validMoves) {
        int row = gravity(col);
        if (row != -1) {
            table[row][col] = -1; // Simula el movimiento del bot
            if (exploreDirections(row, col, -1)) {
                table[row][col] = 0; // Restaura el tablero
                return col; // El bot gana aquí
            }
            table[row][col] = 0; // Restaura el tablero
        }
    }

    // 2. Luego, buscar si el jugador ganaría en la siguiente jugada y bloquearlo
    for (int col : validMoves) {
        int row = gravity(col);
        if (row != -1) {
            table[row][col] = 1; // Simula el movimiento del jugador
            if (exploreDirections(row, col, 1)) {
                table[row][col] = 0; // Restaura el tablero
                return col; // Bloquea al jugador
            }
            table[row][col] = 0; // Restaura el tablero
        }
    }

    // 3. Buscar movimientos estratégicos para formar una futura victoria
    for (int col : validMoves) {
        int row = gravity(col);
        if (row != -1) {
            table[row][col] = -1; // Simula el movimiento del bot
            if (exploreDirections(row, col, -1, true)) {
                table[row][col] = 0; // Restaura el tablero
                return col;
            }
            table[row][col] = 0; // Restaura el tablero
        }
    }

    // 4. Priorizar columnas estratégicas (centro)
    vector<int> strategicMoves;
    for (int col : validMoves) {
        if (col == 3 || col == 2 || col == 4) strategicMoves.push_back(col);
    }
    if (!strategicMoves.empty()) return strategicMoves[rand() % strategicMoves.size()];

    // 5. Si no hay jugadas estratégicas, elegir cualquier columna válida aleatoriamente
    return validMoves[rand() % validMoves.size()];
}

    int randomColumn() {
    vector<int> availableColumns;
    // Recorrer las columnas y agregar las que no estén llenas
    for (int col = 0; col <= maxC; col++) {
        if (table[0][col] == 0) {
            availableColumns.push_back(col);
        }
    }
    // Si no hay columnas disponibles, se retorna -1.
    if (availableColumns.empty())
        return -1;
    // Retornar una columna aleatoria de las disponibles
    return availableColumns[rand() % availableColumns.size()];
    }


    void playGame() {
        bool turn = true;
        while (true) {
            printM();
            if (turn) {
                int col;
                cout << "Elige una columna (0-6): ";
                cin >> col;
                while (col < 0 || col > maxC || table[0][col] != 0) {
                    cout << "Movimiento inválido. Intenta de nuevo: ";
                    cin >> col;
                }
                insert(col, 1);
                if (evaluateBoard() <= -1000) {
                    printM();
                    cout << "¡Felicidades! Has ganado.\n";
                    break;
                }
            } else {
                int move = randomColumn();
                insert(move, -1);
                if (evaluateBoard() >= 1000) {
                    printM();
                    cout << "La IA ha ganado.\n";
                    break;
                }
            }
            turn = !turn;
        }
    }
};

int main() {
    matrix6x7 game;
    cout << "Bienvenido a Conecta 4 con IA\n";
    game.playGame();
    return 0;
}