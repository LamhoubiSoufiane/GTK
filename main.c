#include "Macros.h"

int main(int argc, char* argv[])
{
    gtk_init(&argc, &argv);
    Mastructure *str = NULL;
    str = Lirefichier();
    Creer_Mastructure(str);

    Afficher_Fenetre(str->Information.Mafenetre);
    gtk_main();
}
/*
int main (int argc, char **argv)
{
    GtkWidget *p_window = NULL;


    gtk_init (&argc, &argv);


    p_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    Entry *E;
    E= Init_Entry(1,FALSE,15,TRUE,NULL,FALSE);
    Creer_Entry(E);



    gtk_container_add(p_window,E->entry);
    gtk_widget_show_all(p_window);

    gtk_main ();
    return EXIT_SUCCESS;
}
*/
