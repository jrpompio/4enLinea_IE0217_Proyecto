#ifndef BOT_HPP
#define BOT_HPP

#include "Matrix6x7.hpp"
#include <vector>

class Bot {
public:
    // Constructor: recibe el tablero y extrae su estado mediante get_table()
    Bot(const Matrix6x7 &board);

    // Actualiza la copia interna del estado del tablero usando get_table()
    void updateMatrix(const Matrix6x7 &board);

    // Devuelve la mejor jugada para el bot (modo 1 vs AI)
    int botMove();

    // Devuelve una columna aleatoria válida (modo 1 vs Bot)
    int randomColumn();

private:
    std::vector<std::vector<int>> board_copy; // Copia del estado del tablero obtenido con get_table()
    int maxR; // Último índice de fila (con 6 filas, maxR será 5)
    int maxC; // Último índice de columna (con 7 columnas, maxC será 6)

    // Retorna la fila en la que la ficha caería en la columna 'col'
    int gravity(int col);

    // Recorre en la dirección (dR, dC) desde (R, C) para contar fichas consecutivas del jugador
    bool scanTable(int R, int C, int dR, int dC, int player, int &count, bool checkPattern = false);

    // Explora las 4 direcciones desde (R, C) para determinar si se cumple la condición ganadora o estratégica
    bool exploreBot(int R, int C, int player, bool checkPattern = false);
};

#endif // BOT_HPP
