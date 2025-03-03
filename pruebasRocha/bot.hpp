#ifndef BOT_TREE
#define BOT_TREE

class BotTree {
    public:

    bool exploreBot(int R, int C, int player, bool checkPattern = false) {
        int directions[4][2] = {{0,1}, {1,0}, {1,1}, {1,-1}};
        int count;
        for (auto& dir : directions) {
            if (scanTable(R, C, dir[0], dir[1], player, count, checkPattern)) return true;
        }
        return false;
    }

    bool scanTable(int R, int C, int dR, int dC, int player, int &count, bool checkPattern = false) {
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
                if (exploreBot(row, col, -1)) {
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
                if (exploreBot(row, col, 1)) {
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
                if (exploreBot(row, col, -1, true)) {
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
}


#endif