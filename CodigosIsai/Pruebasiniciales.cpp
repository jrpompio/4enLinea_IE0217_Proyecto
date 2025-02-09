#include <iostream>
#include <vector>

class ConnectFour {
private:
    static const int ROWS = 6;  // Filas del tablero
    static const int COLS = 7;  // Columnas del tablero
    std::vector<std::vector<int>> board; // Matriz dinámica para el tablero

public:
    // Constructor: Inicializa el tablero con ceros
    ConnectFour() {
        board = std::vector<std::vector<int>>(ROWS, std::vector<int>(COLS, 0));
    }

    // Muestra el tablero en consola
    void displayBoard() {
        for (int i = 0; i < ROWS; ++i) {
            for (int j = 0; j < COLS; ++j) {
                if (board[i][j] == 1)
                    std::cout << " X "; // Jugador 1
                else if (board[i][j] == -1)
                    std::cout << " O "; // Jugador 2
                else
                    std::cout << " . "; // Espacio vacío
            }
            std::cout << std::endl;
        }
        std::cout << "-----------------------------" << std::endl;
        std::cout << " 1  2  3  4  5  6  7" << std::endl;
    }

    // Coloca una ficha en la columna especificada
    bool placePiece(int column, int player) {
        if (column < 0 || column >= COLS) {
            std::cout << "Columna fuera de rango.\n";
            return false;
        }

        for (int i = ROWS - 1; i >= 0; --i) { // Buscar la primera fila disponible desde abajo
            if (board[i][column] == 0) {
                board[i][column] = player;
                return true;
            }
        }

        std::cout << "Columna llena. Intente otra.\n";
        return false;
    }
};

int main() {
    ConnectFour game;  // Crear una instancia del juego
    int turn = 1;  // Jugador 1 comienza

    while (true) {
        game.displayBoard();  // Mostrar el tablero
        std::cout << "Turno del jugador " << (turn == 1 ? "1 (X)" : "2 (O)") << "\n";
        std::cout << "Ingrese columna (1-7) para jugar: ";
        
        int col;
        std::cin >> col;

        if (game.placePiece(col - 1, turn)) { // Restamos 1 para ajustarlo al índice
            turn = -turn; // Alternamos entre 1 y -1 (Jugador 1 y Jugador 2)
        }
    }

    return 0;
}
