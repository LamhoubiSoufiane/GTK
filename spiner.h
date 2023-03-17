#include <gtk/gtk.h>
#include<stdio.h>
#include<stdlib.h>


typedef struct {
    GtkWidget *spinner;
    GtkWidget *button;
    Position pos;
    Taille tai;
} SpinnerData;


 SpinnerData *Init_spinner(GtkWidget *button,gint xpos,gint ypos,gint h,gint l)
    {
        SpinnerData *spiner;
        spiner=(SpinnerData*)malloc(sizeof(SpinnerData));
        if(!spiner)
        {
            printf("\nErreur d allocation[spiner]");
            exit(0);
        }
        spiner->spinner=gtk_spinner_new ();
         spiner->pos.posX=xpos;
         spiner->pos.posY=ypos;
         spiner->tai.Hauteur=h;
         spiner->tai.Largeur=l;
         return((SpinnerData*)spiner);
        
       
    }


    SpinnerData *creer_spinner()
    {   
        SpinnerData *nvsp;
        if(!nvsp)
        {
            printf("\nErreur spinner n'existe pas");
            exit(0);
        }
        nvsp=gtk_spinner_new ();
        gtk_widget_set_size_request(nvsp->spinner,nvsp->tai.Largeur,nvsp->tai.Hauteur);
        return((SpinnerData*)nvsp);
         
    }






