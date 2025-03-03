#ifndef SAVELOAD_HPP
#define SAVELOAD_HPP

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>

#include "Matrix6x7.hpp"  // Se incluye el header de Matrix6x7

using namespace std;

class SaveLoad {
private:
    vector<int> movimientos;  // Almacena los movimientos empaquetados.
    string filename;          // Nombre del archivo de guardado.
    string gameType;          // Tipo de partida ("1 vs 1", "1 vs bot", "1 vs AI").
    Matrix6x7* game;          // Puntero a la instancia de la matriz del juego.
    
public:
    // Constructor: recibe un puntero a la matriz y opcionalmente el nombre del archivo.
    SaveLoad(Matrix6x7* gameMatrix, const string &file = "movimientos.txt");
    
    // Establece el tipo de partida y lo escribe en la primera línea del archivo.
    // Se invoca al iniciar una nueva partida (al pulsar "1 vs 1", "1 vs bot", "1 vs AI").
    void setGameType(const string &tipo);
    
    // Guarda un movimiento en memoria y en el archivo.
    // Se invoca cada vez que se realice un insert en gui4connect.cpp.
    void save(int columna, int jugador);
    
    // Carga el tipo de partida y los movimientos guardados,
    // aplicando cada movimiento a la matriz del juego mediante los métodos insert, gravity y fill.
    void load();
    
    // Reinicia la partida borrando el contenido del archivo.
    // Se invoca al pulsar un botón para iniciar una nueva partida.
    void restart();
    
    // Getters opcionales para obtener el tipo de partida y el vector de movimientos.
    const string& getGameType() const;
    const vector<int>& getMovimientos() const;
};

#endif // SAVELOAD_HPP
