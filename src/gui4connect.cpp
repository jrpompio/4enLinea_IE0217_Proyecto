#include "gui4connect.hpp"
#include <gtk/gtk.h>
#include <string>
#include <iostream>

using namespace std;

// ========================
// Callback de dibujo para cada celda
// ========================
gboolean draw_cell_callback(GtkWidget *widget, cairo_t *cr, gpointer data) {
    CellData *cdata = static_cast<CellData*>(data);
    // Obtener la instancia de GameWindow a partir de la ventana toplevel
    GameWindow *gw = static_cast<GameWindow*>(g_object_get_data(G_OBJECT(gtk_widget_get_toplevel(widget)), "game_window"));
    if (!gw) return FALSE;

    const vector<vector<int>> &table = gw->get_game().get_table();
    int state = table[cdata->row][cdata->col];

    GtkAllocation allocation;
    gtk_widget_get_allocation(widget, &allocation);
    double width = allocation.width;
    double height = allocation.height;
    double radius = (width < height ? width : height) * 0.4;
    double cx = width / 2.0;
    double cy = height / 2.0;

    cairo_set_source_rgb(cr, 0.8, 0.8, 0.8);
    cairo_rectangle(cr, 0, 0, width, height);
    cairo_fill(cr);

    cairo_arc(cr, cx, cy, radius, 0, 2 * 3.1416);
    if(state == 1)
        cairo_set_source_rgb(cr, 0.0, 0.0, 1.0);
    else if(state == -1)
        cairo_set_source_rgb(cr, 1.0, 0.0, 0.0);
    else
        cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
    cairo_fill_preserve(cr);

    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_set_line_width(cr, 2.0);
    cairo_stroke(cr);

    return FALSE;
}

// ========================
// Implementación de GameWindow
// ========================
GameWindow::GameWindow() : current_player(1), drop_timer_id(0),
                           animating(false), falling_row(0), drop_player(0) {
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "4 en Línea - 1 vs 1");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 600);

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    hbox_buttons = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_box_pack_start(GTK_BOX(vbox), hbox_buttons, FALSE, FALSE, 0);

    for (int col = 0; col < 7; col++) {
        std::string btn_label = "Col " + std::to_string(col+1);
        column_buttons[col] = gtk_button_new_with_label(btn_label.c_str());
        gtk_box_pack_start(GTK_BOX(hbox_buttons), column_buttons[col], TRUE, TRUE, 0);
        int *p_col = new int(col);
        g_object_set_data_full(G_OBJECT(column_buttons[col]), "col", p_col, g_free);
        g_signal_connect(column_buttons[col], "clicked", G_CALLBACK(+[](GtkWidget *widget, gpointer data) {
            GameWindow *self = static_cast<GameWindow*>(data);
            if(self->animating)
                return;
            int *col_ptr = static_cast<int*>(g_object_get_data(G_OBJECT(widget), "col"));
            int col = *col_ptr;
            self->on_button_column_clicked(col);
        }), this);
    }

    grid = gtk_grid_new();
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);

    // Aplicar CSS para fondo gris en el grid
    gtk_widget_set_name(grid, "grid_bg");
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(provider, "#grid_bg { background-color: gray; }", -1, NULL);
    GtkStyleContext *context = gtk_widget_get_style_context(grid);
    gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    g_object_unref(provider);

    gtk_box_pack_start(GTK_BOX(vbox), grid, TRUE, TRUE, 0);

    for (int i = 0; i < 6; i++){
        for (int j = 0; j < 7; j++){
            cells[i][j] = gtk_drawing_area_new();
            gtk_widget_set_size_request(cells[i][j], 60, 60);
            cell_data[i][j] = new CellData;
            cell_data[i][j]->row = i;
            cell_data[i][j]->col = j;
            g_signal_connect(G_OBJECT(cells[i][j]), "draw", G_CALLBACK(draw_cell_callback), cell_data[i][j]);
            gtk_grid_attach(GTK_GRID(grid), cells[i][j], j, i, 1, 1);
        }
    }

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_object_set_data_full(G_OBJECT(window), "game_window", this, NULL);
    
    gtk_widget_show_all(window);
}

GameWindow::~GameWindow() {
    for (int i = 0; i < 6; i++){
        for (int j = 0; j < 7; j++){
            delete cell_data[i][j];
        }
    }
}

Matrix6x7& GameWindow::get_game() {
    return game;
}

void GameWindow::update_board() {
    for (int i = 0; i < 6; i++){
        for (int j = 0; j < 7; j++){
            gtk_widget_queue_draw(cells[i][j]);
        }
    }
    while (gtk_events_pending())
        gtk_main_iteration();
}

gboolean GameWindow::drop_timer_callback(gpointer data) {
    GameWindow *self = static_cast<GameWindow*>(data);
    int new_row = self->get_game().gravity(self->drop_column);

    if(new_row == self->falling_row) {
        self->animating = false;
        self->drop_timer_id = 0;
        if(self->get_game().exploreDirections(self->drop_column)) {
            const char *color = (self->drop_player == 1) ? "Azules" : "Rojas";
            GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(self->window),
                                                         GTK_DIALOG_DESTROY_WITH_PARENT,
                                                         GTK_MESSAGE_INFO,
                                                         GTK_BUTTONS_OK,
                                                         "¡Ganaron las fichas %s!", color);
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
            for (int col = 0; col < 7; col++){
                gtk_widget_set_sensitive(self->column_buttons[col], FALSE);
            }
        } else {
            const vector<vector<int>> &table = self->get_game().get_table();
            for (int col = 0; col < 7; col++){
                if(table[0][col] == 0)
                    gtk_widget_set_sensitive(self->column_buttons[col], TRUE);
                else
                    gtk_widget_set_sensitive(self->column_buttons[col], FALSE);
            }
        }
        return FALSE;
    } else {
        self->falling_row = new_row;
        self->update_board();
        return TRUE;
    }
}

void GameWindow::drop_piece(int column, int player) {
    cout << " se insertó en columna = " << column << endl;

    if(animating)
        return;
    for (int col = 0; col < 7; col++){
        gtk_widget_set_sensitive(column_buttons[col], FALSE);
    }
    animating = true;
    drop_column = column;
    falling_row = 0;
    drop_player = player;
    if(get_game().insert(column, player)) {
        update_board();
        drop_timer_id = g_timeout_add(200, drop_timer_callback, this);
    } else {
        animating = false;
        const vector<vector<int>> &table = get_game().get_table();
        for (int col = 0; col < 7; col++){
            if(table[0][col] == 0)
                gtk_widget_set_sensitive(column_buttons[col], TRUE);
        }
    }
}

void GameWindow::on_button_column_clicked(int col) {
    drop_piece(col, current_player);
    current_player = -current_player;
}

// ========================
// Implementación de MenuWindow
// ========================
MenuWindow::MenuWindow() {
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Menú Principal");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);

    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    btnCargar = gtk_button_new_with_label("Cargar partida");
    btn1vs1   = gtk_button_new_with_label("1 vs 1");
    btn1vsBot = gtk_button_new_with_label("1 vs Bot");
    btn1vsAI  = gtk_button_new_with_label("1 vs AI");

    gtk_box_pack_start(GTK_BOX(vbox), btnCargar, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), btn1vs1,   TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), btn1vsBot, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), btn1vsAI,  TRUE, TRUE, 0);

    g_signal_connect(btnCargar, "clicked", G_CALLBACK(MenuWindow::on_menu_button_clicked), this);
    g_signal_connect(btn1vs1,   "clicked", G_CALLBACK(MenuWindow::on_menu_button_clicked), this);
    g_signal_connect(btn1vsBot, "clicked", G_CALLBACK(MenuWindow::on_menu_button_clicked), this);
    g_signal_connect(btn1vsAI,  "clicked", G_CALLBACK(MenuWindow::on_menu_button_clicked), this);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_widget_show_all(window);
}

MenuWindow::~MenuWindow() {
    // Liberar recursos si es necesario
}

void MenuWindow::on_menu_button_clicked(GtkWidget *widget, gpointer data) {
    MenuWindow *menu = static_cast<MenuWindow*>(data);
    const gchar *label = gtk_button_get_label(GTK_BUTTON(widget));
    if(g_strcmp0(label, "1 vs 1") == 0) {
        gtk_widget_hide(menu->window);
        new GameWindow(); // Lanza el juego en modo 1 vs 1
    } else {
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(menu->window),
                                                     GTK_DIALOG_DESTROY_WITH_PARENT,
                                                     GTK_MESSAGE_INFO,
                                                     GTK_BUTTONS_OK,
                                                     "Funcionalidad '%s' no implementada.", label);
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }
}
