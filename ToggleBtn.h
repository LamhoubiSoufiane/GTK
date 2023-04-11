#pragma once

#include <gtk/gtk.h>

typedef struct
{
    GtkWidget* toggle_button;//Variable pour le bouton
    int Id;//Identifiant du button
    Position p;//Position du bouton
    Taille T;//Taille du bouton
    int mnemonic;//determiner si le bouton est avec mnemonic ou non
    char Nom[26];//tableau de 26 caractères pour le nom du bouton
    char NomIcone[26];//tableau de 26 caractères pour l'icone du bouton
}Toggle_Button;//Nom de la structure


Toggle_Button* Init_Toggle_Button(int id, char *nom, char* icone, int mnemonic,int xpos, int ypos,int h,int l)
{
    Toggle_Button* b;//pointeur de type button
    b = (Toggle_Button*)malloc(sizeof(Toggle_Button));//Allocation de la place memoire
    //Afficher un message et quitter si l'allocation est mal faite
    if (!b)
    {
        printf("\nErreur d allocation [button_simple]");
        exit(0);
    }
    b->Id = id;
    strcpy(b->Nom, nom);//Initialiser le nom
    b->mnemonic = mnemonic;//Initialiser le caractère mnemonic
    //Initialiser le nom de l'icone
    if(!strcmp(icone,"NULL")) b->NomIcone[0] = '0';
    else strcpy(b->NomIcone, icone);
    //Initialisation de la position
    b->p.posX = xpos;
    b->p.posY = ypos;
    //Initialisation de la taille
    b->T.Hauteur = h;
    b->T.Largeur = l;
    return((Toggle_Button*)b);//Retourner l'adresse alouée
}


void Creer_Toggle_Button(Toggle_Button * b)
{
    //Afficher un message d'erreur et quitter si le bouton n'existe pas
    if (!b)
    {
        printf("\nErreur, button n existe pas");
        exit(0);
    }
    //creer toggle button
    if(b->mnemonic)
        b->toggle_button = gtk_toggle_button_new_with_mnemonic(b->Nom);
    else b->toggle_button = gtk_toggle_button_new_with_label(b->Nom);

}



