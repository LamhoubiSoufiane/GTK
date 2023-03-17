#include<gtk-3.0/gtk/gtk.h>
#include "TAILLEPOS999.h"




#ifndef COMBOBOX999_H
#define COMBOBOX999_H

typedef struct ent
{
    int id;
    char *Nom;
    struct ent *svt;
}ListeCombo;

typedef struct 
{
    GtkWidget *combo;
    Taille T;
    Position pox;
    ListeCombo *Maliste;
}Combobox;


ListeCombo *Init_Elem_combo(char *nom,int id)
{
    ListeCombo *nv;
    nv=(ListeCombo*)malloc(sizeof(ListeCombo));
    if(!nv)
    {
        printf("\nErreur d allocation [listecombo]");
        exit(0);
    }
    nv->id=id;
    if(nom)
    {
        nv->Nom=(char*)malloc(sizeof(char));
        nv->Nom=nom;
    }
    else nv->Nom=NULL;
    nv->svt=NULL;
    return((ListeCombo*)nv);
}


Combobox *Init_Combobox(int xpos,int ypos,int h,int l,gboolean entry)
{
    Combobox *c;
    c=(Combobox*)malloc(sizeof(Combobox));
    if(!c)
    {
        printf("\nErreur d allocation [combobox]");
        exit(0);
    }
    c->pox.posX=xpos;
    c->pox.posY=ypos;
    c->T.Hauteur=h;
    c->T.Largeur=l;
    c->Maliste=NULL;
    if(entry) c->combo=gtk_combo_box_text_new_with_entry();
    else c->combo=gtk_combo_box_text_new();
    gtk_widget_set_size_request(c->combo,l,h);
    return((Combobox*)c);
}

void Ajouter_Elem_Combobox(Combobox *c,char *titre,int id)
{
    ListeCombo *nvm,*ptr;
    nvm=Init_Elem_combo(titre,id);
    if(!c->Maliste) c->Maliste=nvm;
    else 
    {
        ptr=c->Maliste;
        while(ptr->svt) ptr=ptr->svt;
        ptr->svt=nvm;
    }
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(c->combo),"id",titre);
}


#endif