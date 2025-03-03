#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>  
using namespace std;

class SaveLoad {
private:
    vector<int> movimientos;      // Se guardan los movimientos en memoria
    string filename;              // Nombre del archivo
public:
    // En el constructor se puede especificar el nombre del archivo, por defecto "movimientos.txt"
    SaveLoad(const string &file = "movimientos.txt") : filename(file) {}

    // Método para guardar un movimiento en memoria y en disco.
    // Se empaqueta el movimiento en 4 bits: bit3 = jugador, bits 0-2 = columna.
    void save(int columna, int jugador) {
        // Validaciones
        if (columna < 0 || columna > 6) {
            cout << "Error: la columna debe estar entre 0 y 6." << endl;
            return;
        }
        if (jugador != 0 && jugador != 1) {
            cout << "Error: el jugador debe ser 0 o 1." << endl;
            return;
        }
        // Empaquetar en 4 bits
        int move = (jugador << 3) | (columna & 0x07);                           // El jugador se mueve 3 a la izquierda y queda 1000. Mas, la posicion de la columna, con un 7(111) Quedando en decimal la posicion.
        // Guardar en memoria
        movimientos.push_back(move);

        // Guardar los 4 bits en el archivo de texto en formato hexadecimal
        ofstream ofs(filename, ios::app);                                       // ios::app significa Append. Por lo que no sobreescribe los datos, sino que los guarda al final. 
        if (!ofs.is_open()) {
            cerr << "Error al abrir el archivo para escritura." << endl;
            return;
        }
        ofs << hex << (int)move << " ";                                         // Convierte el dato de jugador y columna en Hexadecimal y lo guarda con un espacio
        ofs.close();                                                            // Cierra el archivo
    }

    // Método para cargar los movimientos guardados en el archivo
    void load() {
        movimientos.clear();                                                    // Limpia los datos del vector antes de hacer otra cosa
        ifstream ifs(filename);                                                 // Lee del archivo
        if (!ifs.is_open()) {                                                   // Validacion de acceso
            cerr << "Error al abrir el archivo para lectura." << endl; 
            return;
        }
        int moveVal;                                                            // Variable temporal para almacenar los datos extraidos
        // Leer cada valor en formato hexadecimal
        while (ifs >> hex >> moveVal) {                                         // Lee los datos en hexadecimal y los guarda en moveVal
            int move = static_cast<int>(moveVal);                               // Convierte los datos a enteros(por aquello)
            movimientos.push_back(move);
        }
        ifs.close();
    }

    // Método para reiniciar el juego
    void restart() {
        movimientos.clear();                                                    // Limpia la memoria del vector
        ofstream ofs(filename, ios::trunc);                                     // Abre el archivo con trunc(borra su contenido)
        if (!ofs.is_open()) {
            cerr << "Error al abrir el archivo para reiniciar." << endl;
            return;
        }
        ofs.close();
    }

    // Método para imprimir los movimientos en formato humano.
    // Se decodifica el nibble: el bit 3 representa al jugador y los bits 0-2 la columna.
    void print() const {
        for (size_t i = 0; i < movimientos.size(); i++) {
            int move = movimientos[i];
            int jugador = (move >> 3) & 0x01;                                   // Extraemos el bit de jugador
            int columna = move & 0x07;                                          // Extraemos la columna (3 bits)
            cout << "Movimiento " << i + 1 << ": Columna " << columna 
                 << ", Jugador " << (jugador == 0 ? "azul" : "rojo") << endl;
        }
    }
};

int main() {
    SaveLoad sl;
    
    // Ejemplos de guardado de movimientos
    sl.save(3, 1);  // Jugador 1 (rojo) tira en la columna 3
    sl.save(4, 0);  // Jugador 0 (azul) tira en la columna 4
    sl.save(2, 1);  // Jugador 1 (rojo) tira en la columna 2

    // Cargar movimientos del archivo
    sl.load();

    // Imprimir los movimientos 
    sl.print();

    sl.restart();
    cout << "Reiniciao pa" << endl;
    sl.save(5, 0);

    sl.print();

    return 0;
}

