#ifndef GUI4CONNECT_HPP
#define GUI4CONNECT_HPP

#include <gtk/gtk.h>
#include <string>
#include <vector>
#include "Matrix6x7.hpp"
#include "bot.hpp"  // Se incluye para integrar el bot

using namespace std;

// Estructura para la información de cada celda (área de dibujo)
struct CellData {
    int row;
    int col;
};

// Declaración adelantada del callback de dibujo
gboolean draw_cell_callback(GtkWidget *widget, cairo_t *cr, gpointer data);

// Clase que maneja la interfaz gráfica del juego (4 en Línea)
class GameWindow {
public:
    GameWindow();
    ~GameWindow();

    // Método para acceder a la lógica del juego
    Matrix6x7& get_game();

    // Nuevo método para establecer el modo de juego:
    // 0: 1 vs 1, 1: 1 vs bot (jugada aleatoria), 2: 1 vs AI (jugada inteligente)
    void setGameMode(int mode);

private:
    GtkWidget *window;       // Ventana principal del juego
    GtkWidget *grid;         // Grid que contiene las celdas del tablero
    GtkWidget *hbox_buttons; // Contenedor horizontal para los botones (arriba)
    GtkWidget *column_buttons[7]; // Botón por cada columna
    GtkWidget *cells[6][7];  // Áreas de dibujo para cada celda

    // Arreglo de información de cada celda (para el callback de dibujo)
    CellData *cell_data[6][7];

    // Lógica del juego
    Matrix6x7 game;

    // Variables de control del turno y animación
    int current_player;
    int drop_column;         // Columna en la que se inserta la ficha
    int falling_row;         // Fila actual de la ficha en caída
    int drop_player;         // Jugador que lanzó la ficha
    guint drop_timer_id;     // ID del timer para la animación
    bool animating;          // Indica si se está animando la caída

    // Miembros nuevos para integrar el Bot
    Bot* bot;                // Objeto Bot para la jugada automática
    // Variable para indicar el modo de juego:
    // 0: 1 vs 1, 1: 1 vs bot (random), 2: 1 vs AI (inteligente)
    int game_mode;

    // Métodos internos
    static gboolean drop_timer_callback(gpointer data);
    void update_board();
    void drop_piece(int column, int player);
    void on_button_column_clicked(int col);

    // Método para ejecutar la jugada del bot (se invoca tras la jugada del jugador)
    void performBotMove();

    // Permitir que el callback de dibujo acceda a la instancia
    friend gboolean draw_cell_callback(GtkWidget *widget, cairo_t *cr, gpointer data);
};

// Clase para el menú principal de la aplicación
class MenuWindow {
public:
    MenuWindow();
    ~MenuWindow();
private:
    GtkWidget *window; // Ventana principal del menú
    GtkWidget *vbox;   // Contenedor vertical para los botones
    GtkWidget *btnCargar;
    GtkWidget *btn1vs1;
    GtkWidget *btn1vsBot;
    GtkWidget *btn1vsAI;

    static void on_menu_button_clicked(GtkWidget *widget, gpointer data);
};

#endif // GUI4CONNECT_HPP
