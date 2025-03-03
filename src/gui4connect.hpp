#ifndef GUI4CONNECT_HPP
#define GUI4CONNECT_HPP

#include <gtk/gtk.h>
#include <string>
#include <vector>
#include "Matrix6x7.hpp"   // Se requiere para la definición de la matriz del juego
#include "bot.hpp"         // Para el Bot
#include "SaveLoad.hpp"    // Para SaveLoad

using namespace std;

// Estructura para almacenar los datos de cada celda (usada en el callback de dibujo)
struct CellData {
    int row;
    int col;
};

class GameWindow {
public:
    GameWindow();
    ~GameWindow();

    // Devuelve una referencia a la matriz del juego
    Matrix6x7& get_game();

    // Actualiza el tablero (redibuja todas las celdas)
    void update_board();

    // Maneja el clic en un botón de columna
    void on_button_column_clicked(int col);

    // Inserta la ficha en la columna indicada para el jugador (llama a drop_piece)
    void drop_piece(int column, int player);

    // Establece el modo de juego:
    // 0: 1 vs 1, 1: 1 vs Bot, 2: 1 vs AI
    void setGameMode(int mode);

    // Ejecuta la jugada del bot cuando es su turno
    void performBotMove();

    // Setter para current_player (para ajustar turno tras cargar partida)
    void setCurrentPlayer(int player);

    // Getter para acceder a la instancia de SaveLoad
    SaveLoad* getSaveLoad();

    // Callback para la animación de caída de ficha (método estático)
    static gboolean drop_timer_callback(gpointer data);

private:
    GtkWidget* window;
    GtkWidget* grid;
    GtkWidget* hbox_buttons;
    GtkWidget* column_buttons[7];
    GtkWidget* cells[6][7];
    CellData* cell_data[6][7];

    int current_player;   // 1 para azul, -1 para rojo
    int drop_timer_id;
    bool animating;
    int falling_row;
    int drop_player;
    int drop_column;
    int game_mode;        // 0: 1 vs 1, 1: 1 vs Bot, 2: 1 vs AI

    Matrix6x7 game;       // Instancia de la matriz del juego
    Bot* bot;             // Puntero al Bot (si se usa)
    SaveLoad* saveload;   // Puntero al SaveLoad para guardar/cargar la partida
};

class MenuWindow {
public:
    MenuWindow();
    ~MenuWindow();

    // Callback para los botones del menú
    static void on_menu_button_clicked(GtkWidget* widget, gpointer data);

private:
    GtkWidget* window;
    GtkWidget* vbox;
    GtkWidget* btnCargar;
    GtkWidget* btn1vs1;
    GtkWidget* btn1vsBot;
    GtkWidget* btn1vsAI;
};

#endif // GUI4CONNECT_HPP
