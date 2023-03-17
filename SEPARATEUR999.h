#include<gtk-3.0/gtk/gtk.h>
#include"TAILLEPOS999.h"
#include"FCT_SUPP.h"

#ifndef SEPARATEUR999_H
#define SEPARATEUR999_H


typedef struct 
{
    GtkWidget *sep;
    char *couleur;
    Position p;
    Taille t;
    int type;//0 : horizontal ; 1: vertical
}Separateur;


Separateur *Init_Separateur(char *color,int type,int xpos,int ypos,int h,int L)
{
    Separateur *Sp;
    Sp=(Separateur*)malloc(sizeof(Separateur));
    if(!Sp)
    {
        printf("\nErreur d allocation[separateur]");
        exit(0);
    }
    Sp->t.Hauteur=h;
    Sp->t.Largeur=L;
    Sp->p.posX=xpos;
    Sp->p.posY=ypos;
    Sp->type=type;
    if(color)
    {
        Sp->couleur=(char*)malloc(sizeof(char));
        Sp->couleur=color;
    }
    else Sp->couleur=NULL;
    return((Separateur*)Sp);
}

void Creer_Separateur(Separateur *s)
{
    if(!s)
    {
        printf("\nSeparateur n existe pas!");
        exit(0);
    }
    switch(s->type)
    {
        case 0 : s->sep=gtk_separator_new(0);
                break;
        case 1 : s->sep=gtk_separator_new(1);
                break;
        default : printf("\nErreur type separateur!");
                exit(0);
    }
    gtk_widget_set_size_request(s->sep,s->t.Largeur,s->t.Hauteur);
    Modifier_Couleur_Widget(s->sep,(gchar*)s->couleur);
}

#endif