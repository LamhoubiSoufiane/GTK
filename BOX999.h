#include<gtk-3.0/gtk/gtk.h>
#include "FCT_SUPP.h"

#ifndef BOX999_H
#define BOX999_H

typedef struct 
{
    GtkWidget *monbox;
    int espace;//Espace entre les elems du box
    int type;//0 : horiz --- 1: vert
    char *couleur;
    //Les bordures, les extremites des bordures, couleur des bordures ...
}Box;

Box *Init_Box(int esp,int ty,char *Couleur)
{
    Box *nvbox;
    nvbox=(Box*)malloc(sizeof(Box));
    if(!nvbox)
    {
        printf("\nErreur d allocation [BOX]");
        exit(0);
    }
    nvbox->espace=esp;
    nvbox->type=ty;
    if(Couleur)
    {
        nvbox->couleur=(char*)malloc(sizeof(char));
        nvbox->couleur=Couleur;
    }
    else nvbox->couleur=NULL;
    return((Box*)nvbox);
}

void Creer_Box(Box *b)
{
    if(!b)
    {
        printf("\nBox n existe pas");
        exit(0);
    }
    switch(b->type)
    {
        case 0 : b->monbox=gtk_box_new(GTK_ORIENTATION_HORIZONTAL,b->espace);
                    break;
        case 1 : b->monbox=gtk_box_new(GTK_ORIENTATION_VERTICAL,b->espace);
                    break;
        default : printf("\nErreur type du box");
                    exit(0);
    }
    if(b->couleur) Modifier_Couleur_Widget(b->monbox,b->couleur);
}

void Ajouter_Elem_Au_Box(Box *b,GtkWidget *elem)
{
    if(!b)
    {
        printf("\nErreur, box n existe pas [ajouter elem au box]");
        exit(0);
    }
    gtk_box_pack_start (GTK_BOX (b->monbox), elem, TRUE, TRUE, b->espace);
}

#endif