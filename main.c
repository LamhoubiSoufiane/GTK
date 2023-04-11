#include "Macros.h"


/*
int main(int argc, char* argv[])
{
    gtk_init(&argc, &argv);
    Mastructure *str = NULL;
    str = Lirefichier();
    Creer_Mastructure(str);
    Afficher_Fenetre(str->Information.Mafenetre);
    gtk_main();
}*/












//------------------------
int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);
    GtkWidget *box,*p_window,*image;
    box= gtk_box_new(1,0);
    p_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

    gtk_window_set_default_size(p_window, 800, 800);
    image= gtk_image_new_from_resource("/Images/76215.gif");


    gtk_box_pack_start(box,image,TRUE,TRUE,0);

    gtk_container_add(p_window,box);

    gtk_widget_show_all(p_window);
    gtk_main();
}
/*int main (int argc, char **argv)
{
    GtkWidget *p_window = NULL;
gtk_init (&argc, &argv);
/*GtkWidget *box;
box= gtk_box_new(1,0);


p_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
L_CkButtons *lc;
lc= Init_Check_Button(1,"btn1",NULL,0,1,3,1,1000,100,40,80);
Ajouter_Btn_Check(lc,2,"btn2",NULL,0,0,2,1);
Ajouter_Btn_Check(lc,3,"btn3",NULL,0,0,1,1);
Creer_Btn_Check(lc);

gtk_box_pack_start(box,lc->Liste->btn,TRUE,TRUE,0);
gtk_box_pack_start(box,lc->Liste->svt->btn,TRUE,TRUE,0);

gtk_container_add(p_window,box);
BDialogue *bd;
bd= Initier_Bdialogue()
gtk_widget_show_all(p_window);

gtk_main ();
return EXIT_SUCCESS;
}*/








