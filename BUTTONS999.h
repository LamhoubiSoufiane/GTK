#include<gtk-3.0/gtk/gtk.h>
#include "FENETRE999.h"
#include"TAILLEPOS999.h"

#ifndef BUTTONS999_H
#define BUTTONS999_H

void testbtn(GtkWidget *f,gpointer data)
{
    printf("\nBouttsimple");
}

typedef struct
{
    GtkWidget *btn;
    GtkWidget *contenaire; //ID fenetre;
    char *titre;
    gboolean mnemonic;
    char *NomIcone;
    Position p;
    Taille T;
}Button;

Button *Init_Button_Simple(char *nom,char *icone,gint xpos,gint ypos,
                            gint h,gint l,gboolean mnemonic)
{
    Button *b;
    b=(Button*)malloc(sizeof(Button));
    if(!b)
    {
        printf("\nErreur d allocation [button_simple]");
        exit(0);
    }
    if(nom)
    {
        b->titre=(char*)malloc(sizeof(char));
        b->titre=nom;
    }
    else b->titre=NULL;
    b->mnemonic=mnemonic;
    if(icone)
    {
        b->NomIcone=(char*)malloc(sizeof(char));
        b->NomIcone=icone;
    }
    b->p.posX=xpos;
    b->p.posY=ypos;
    b->T.Hauteur=h;
    b->T.Largeur=l;
    return((Button*)b);
}

void Creer_Button_Simple(Fenetre *fn,Button *b)
{
    if(!b)
    {
        printf("\nErreur, button n existe pas");
        exit(0);
    }
    if(!fn)
    {
        printf("\nErreur, fenetre n existe pas");
        exit(0);
    }
    b->contenaire=fn->fenetre;
    if(b->mnemonic)
    {
        if(b->titre) b->btn=gtk_button_new_with_mnemonic(b->titre);
        else b->btn=gtk_button_new_with_mnemonic("");
    }
    else b->btn=gtk_button_new_with_label(b->titre);
    gtk_widget_set_size_request(b->btn,b->T.Largeur,b->T.Hauteur);
    Creer_Fixed(fn,b->btn,300,100);
}


#endif