#include <gtk/gtk.h>
#include "gui4connect.hpp"

int main(int argc, char *argv[]){
    gtk_init(&argc, &argv);
    MenuWindow menu;
    gtk_main();
    return 0;
}
