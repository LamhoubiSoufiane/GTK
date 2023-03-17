#include<gtk-3.0/gtk/gtk.h>
#include"TAILLEPOS999.h"
#include"FENETRE999.h"


#ifndef RADBUTT999_H
#define RADBUTT999_H

typedef struct Rbtn
{
    GtkWidget *button;
    char *nom;
    struct Rbtn *Svt;
}Ent_Rbn;

typedef struct 
{
    Ent_Rbn *ListeRbtn;
    GtkWidget *BOX;//Il faut le remplacer avec la structure du box !! 
    Position pos;
    Taille t;
}RadioButton;

Ent_Rbn *Init_Creer_Ent_Rbn(char *nom)
{
    Ent_Rbn *btn;
    btn=(Ent_Rbn*)malloc(sizeof(Ent_Rbn));
    if(!btn)
    {
        printf("\nErreur d allocation memoire[Radiobutton]");
        exit(0);
    }
    if(nom)
    {
        btn->nom=(char*)malloc(sizeof(char));
        btn->nom=nom;
    }
    else btn->nom=NULL;
    btn->Svt=NULL;
    btn->button=NULL;
    return((Ent_Rbn*)btn);
}

RadioButton *Init_Radio_Button(char *nom,int xpos,int ypos,int hauteur,int largeur,int type) // type : 0-> horizontal, 1-> vertical
{
    RadioButton *btn;
    btn=(RadioButton*)malloc(sizeof(RadioButton));
    if(!btn)
    {
        printf("\nErreur d allocation [Radiobutton]");
        exit(0);
    }
    switch(type)
    {
        case 0 : btn->BOX=gtk_box_new(0,0);
                break;
        case 1 : btn->BOX=gtk_box_new(1,0);
                break;
    }
    btn->ListeRbtn=Init_Creer_Ent_Rbn(nom);
    btn->pos.posX=xpos;
    btn->pos.posY=ypos;
    btn->t.Hauteur=hauteur;
    btn->t.Largeur=largeur;
    btn->ListeRbtn->button=gtk_radio_button_new_with_mnemonic(NULL,nom);
    gtk_box_pack_start(btn->BOX,btn->ListeRbtn->button,TRUE,TRUE,0);
    return((RadioButton*)btn);
}

void Ajouter_Radio_Button(RadioButton *StrButton,char *Nom)
{
    Ent_Rbn *Nvbtn,*Ptcr;
    if(!StrButton)
    {
        printf("\nErreur StrButton n existe pas!");
        exit(0);
    }
    Nvbtn=Init_Creer_Ent_Rbn(Nom);
    Ptcr=StrButton->ListeRbtn;
    while(Ptcr->Svt) Ptcr=Ptcr->Svt;
    Ptcr->Svt=Nvbtn;
    Nvbtn->button=gtk_radio_button_new_with_mnemonic_from_widget(GTK_RADIO_BUTTON(StrButton->ListeRbtn->button),Nom);
    gtk_box_pack_start(StrButton->BOX,Nvbtn->button,TRUE,TRUE,0);
}

#endif
