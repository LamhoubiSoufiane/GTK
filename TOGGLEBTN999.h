#include<gtk-3.0/gtk/gtk.h>
#include"TAILLEPOS999.h"

#ifndef TOGGLEBTN999_H
#define TOGGLEBTN999_H

typedef struct
{
    GtkWidget *Toggle;
    char *Nom;
    // gboolean mnemonic;
    Position p;
    Taille t;
}Togglebutton;

Togglebutton *Init_Toggle_Button(char *titre,int posx,int posy,int h,int l)
{
    Togglebutton *Tgl;
    Tgl=(Togglebutton*)malloc(sizeof(Togglebutton));
    if(!Tgl)
    {
        printf("\nErreur d allocation togglebbutton");
        exit(0);
    }
    Tgl->p.posX=posx;
    Tgl->p.posY=posy;
    Tgl->t.Hauteur=h;
    Tgl->t.Largeur=l;
    if(titre)
    {
        Tgl->Nom=(char*)malloc(sizeof(char));
        Tgl->Nom=titre;
    }
    else Tgl->Nom=NULL;
    return((Togglebutton*)Tgl);
}

void Creer_toggle(Togglebutton *btn)
{
    if(!btn)
    {
        printf("\n button toggle n existe pas");
        exit(0);
    }
    btn->Toggle=gtk_toggle_button_new_with_mnemonic((gchar*)btn->Nom);
    gtk_widget_set_size_request(btn->Toggle,btn->t.Largeur,btn->t.Hauteur);
}

#endif

