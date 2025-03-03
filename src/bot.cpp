#include "bot.hpp"
#include <cstdlib>
#include <vector>
using namespace std;

// Constructor: inicializa la copia del tablero mediante get_table()
Bot::Bot(const Matrix6x7 &board) {
    updateMatrix(board);
}

// Actualiza la copia interna del tablero usando get_table()
void Bot::updateMatrix(const Matrix6x7 &board) {
    board_copy = board.get_table();  // Se asume que get_table() retorna un vector<vector<int>>
    maxR = board_copy.size() - 1;      // Con 6 filas, maxR será 5
    maxC = board_copy[0].size() - 1;     // Con 7 columnas, maxC será 6
}

// Retorna la fila en la que la ficha caería en la columna 'col'
int Bot::gravity(int col) {
    for (int r = maxR; r >= 0; r--) {
        if (board_copy[r][col] == 0)
            return r;
    }
    return -1;
}

// Recorre en la dirección (dR, dC) a partir de (R,C) para contar fichas consecutivas del jugador
bool Bot::scanTable(int R, int C, int dR, int dC, int player, int &count, bool checkPattern) {
    count = 1;
    int emptySpaces = 0;
    // Dirección hacia adelante
    for (int step = 1; step < 4; step++) {
        int r = R + step * dR;
        int c = C + step * dC;
        if (r >= 0 && r <= maxR && c >= 0 && c <= maxC) {
            if (board_copy[r][c] == player)
                count++;
            else if (board_copy[r][c] == 0)
                emptySpaces++;
            else
                break;
        }
    }
    // Dirección hacia atrás
    for (int step = 1; step < 4; step++) {
        int r = R - step * dR;
        int c = C - step * dC;
        if (r >= 0 && r <= maxR && c >= 0 && c <= maxC) {
            if (board_copy[r][c] == player)
                count++;
            else if (board_copy[r][c] == 0)
                emptySpaces++;
            else
                break;
        }
    }
    return checkPattern ? (count == 3 && emptySpaces > 0) : (count >= 4);
}

// Explora las 4 direcciones desde la posición (R, C) para verificar victoria o patrón estratégico
bool Bot::exploreBot(int R, int C, int player, bool checkPattern) {
    int directions[4][2] = { {0,1}, {1,0}, {1,1}, {1,-1} };
    int count;
    for (int i = 0; i < 4; i++) {
        if (scanTable(R, C, directions[i][0], directions[i][1], player, count, checkPattern))
            return true;
    }
    return false;
}

// Devuelve la mejor jugada para el bot (modo 1 vs AI)
int Bot::botMove() {
    vector<int> validMoves;
    // Se recopilan las columnas válidas (donde la celda superior es 0)
    for (int col = 0; col <= maxC; col++) {
        if (board_copy[0][col] == 0)
            validMoves.push_back(col);
    }
    
    // 1. Verifica si el bot puede ganar con alguna jugada
    for (int col : validMoves) {
        int row = gravity(col);
        if (row != -1) {
            int original = board_copy[row][col];
            board_copy[row][col] = -1; // Simula la jugada del bot
            if (exploreBot(row, col, -1)) {
                board_copy[row][col] = original; // Restaura
                return col;
            }
            board_copy[row][col] = original; // Restaura
        }
    }
    
    // 2. Verifica si el jugador podría ganar en el siguiente turno; si es así, bloquea
    for (int col : validMoves) {
        int row = gravity(col);
        if (row != -1) {
            int original = board_copy[row][col];
            board_copy[row][col] = 1; // Simula la jugada del jugador
            if (exploreBot(row, col, 1)) {
                board_copy[row][col] = original;
                return col;
            }
            board_copy[row][col] = original;
        }
    }
    
    // 3. Busca jugadas estratégicas para preparar una victoria futura
    for (int col : validMoves) {
        int row = gravity(col);
        if (row != -1) {
            int original = board_copy[row][col];
            board_copy[row][col] = -1; // Simula la jugada del bot
            if (exploreBot(row, col, -1, true)) {
                board_copy[row][col] = original;
                return col;
            }
            board_copy[row][col] = original;
        }
    }
    
    // 4. Prioriza columnas centrales (por ejemplo, 2, 3 y 4)
    vector<int> strategicMoves;
    for (int col : validMoves) {
        if (col == 3 || col == 2 || col == 4)
            strategicMoves.push_back(col);
    }
    if (!strategicMoves.empty())
        return strategicMoves[rand() % strategicMoves.size()];
    
    // 5. Si ninguna estrategia funciona, elige una columna aleatoria válida
    return validMoves[rand() % validMoves.size()];
}

// Devuelve una columna aleatoria válida (modo "1 vs Bot")
int Bot::randomColumn() {
    vector<int> available;
    for (int col = 0; col <= maxC; col++) {
        if (board_copy[0][col] == 0)
            available.push_back(col);
    }
    if (available.empty())
        return -1;
    return available[rand() % available.size()];
}

