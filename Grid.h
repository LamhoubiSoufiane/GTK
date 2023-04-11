#pragma once


typedef struct
{
    GtkWidget *grid; //pointeur sur l'objet grid
    GtkWidget* container;//pointeur sur l'objet conteneur du grid
    int ID;//Identifiant du grid
    Taille T; //la taille du grid
    Position P;// la position du grid
}Mongrid; //Nom de SdD

/*
Nom         : Initier_grid
Entree      : coordonnees du grid , entier decrivons la langueur ,entier decrivons la hauteur
Sortie      : pointeur sur la structure de grid
Description : Fonction qui initier un grid
*/

Mongrid* Initier_grid(int id,int xpos, int ypos, int langueur, int hauteur)
{
    Mongrid* g;

    //allocation d'espace memoire pour  la structure
    g = (Mongrid*)malloc(sizeof(Mongrid));
    if (!g)
    {
        printf("\n erreur d'allocation[grid]");
        exit(0);
    }
    g->ID = id;//Initialisation de l identifiant du grid

    //mettre la taille du grid
    g->T.Hauteur = hauteur;
    g->T.Largeur = langueur;
    //mettre la position du grid
    g->P.posX= xpos;
    g->P.posY = ypos;

    return(Mongrid*)g;
}

void Creer_Grid(Mongrid* gr)
{
    if (!gr)
    {
        printf("\nErreur, grid n existe pas[Creer_grid]");
        exit(0);
    }
    //creation du grid
    gr->grid = gtk_grid_new();
}

/*
Nom         : Ajouter_elem_grid
Entree      : pointeur sur le grid , pointeur sur une widget
Description : Fonction qui insere  un element dans le grid
*/



void Ajouter_elem_grid(Mongrid* g, GtkWidget* elem)
{
    //ajouter l'elem child dans le grid selon les coordonnees et la taille du grid
    gtk_grid_attach(GTK_GRID(g->grid), elem, g->P.posX, g->P.posY, g->T.Hauteur, g->T.Largeur);
}

