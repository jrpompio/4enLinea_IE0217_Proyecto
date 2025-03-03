#include "SaveLoad.hpp"

SaveLoad::SaveLoad(Matrix6x7* gameMatrix, const string &file)
    : game(gameMatrix), filename(file), gameType("")
{
    // Inicializa el vector de movimientos vacío.
}

void SaveLoad::setGameType(const string &tipo) {
    gameType = tipo;
    // Abrir el archivo en modo 'trunc' para limpiar cualquier contenido previo y escribir el tipo de partida.
    ofstream ofs(filename, ios::trunc);
    if (!ofs.is_open()) {
        cerr << "Error al abrir el archivo para escribir el tipo de partida." << endl;
        return;
    }
    ofs << tipo << "\n";  // Guarda el tipo de partida en la primera línea.
    ofs.close();
}

void SaveLoad::save(int columna, int jugador) {
    // Validaciones básicas.
    if (columna < 0 || columna > 6) {
        cout << "Error: la columna debe estar entre 0 y 6." << endl;
        return;
    }
    if (jugador != 0 && jugador != 1) {
        cout << "Error: el jugador debe ser 0 o 1." << endl;
        return;
    }
    // Empaquetar el movimiento en 4 bits: bit 3 = jugador y bits 0-2 = columna.
    int move = (jugador << 3) | (columna & 0x07);
    movimientos.push_back(move);
    
    // Guardar el movimiento en el archivo en modo append, en formato hexadecimal.
    ofstream ofs(filename, ios::app);
    if (!ofs.is_open()) {
        cerr << "Error al abrir el archivo para escritura." << endl;
        return;
    }
    ofs << hex << move << " ";
    ofs.close();
}

void SaveLoad::load() {
    movimientos.clear();
    ifstream ifs(filename);
    if (!ifs.is_open()) {
        cerr << "Error al abrir el archivo para lectura." << endl;
        return;
    }
    // Leer la primera línea, que contiene el tipo de partida.
    if (!getline(ifs, gameType)) {
        cerr << "Error al leer el tipo de partida." << endl;
        return;
    }
    // Leer el resto del archivo para obtener los movimientos en formato hexadecimal.
    int moveVal;
    while (ifs >> hex >> moveVal) {
        movimientos.push_back(moveVal);
    }
    ifs.close();

    // Reproducir los movimientos en la matriz:
    // Para cada movimiento, se extrae el jugador y la columna,
    // y se aplican los métodos insert, gravity (ahora recibiendo la columna) y fill en la instancia de Matrix6x7.
    for (size_t i = 0; i < movimientos.size(); i++) {
        int move = movimientos[i];
        int jugador = (move >> 3);
        int columna = move & 0x07;
        if (jugador ==0 ){
            jugador = 1;} 
        else {
            jugador = -1;}
        game->insert(columna, jugador);
        game->gravity(columna);
        game->gravity(columna);
        game->gravity(columna);
        game->gravity(columna);
        game->gravity(columna);
        game->gravity(columna);
    }

}

void SaveLoad::restart() {
    movimientos.clear();
    // Se abre el archivo en modo 'trunc' para borrar su contenido.
    ofstream ofs(filename, ios::trunc);
    if (!ofs.is_open()) {
        cerr << "Error al abrir el archivo para reiniciar." << endl;
        return;
    }
    ofs.close();
}

const string& SaveLoad::getGameType() const {
    return gameType;
}

const vector<int>& SaveLoad::getMovimientos() const {
    return movimientos;
}
