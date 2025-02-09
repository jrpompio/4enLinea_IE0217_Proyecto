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
                std::cout << board[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
};

int main() {
    ConnectFour game;  // Crear una instancia del juego
    game.displayBoard();  // Mostrar el tablero inicial
    return 0;
}
