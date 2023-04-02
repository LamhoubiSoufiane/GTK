
#ifndef BOX_H
#define BOX_H


//Structure d'un box
typedef struct
{
    GtkWidget *monbox;//Variable pour le box
    int Id;//Identifiant du box
    int espace;//Espace entre les elems du box
    /*0 : horizontal
    * 1 : vertical
    */
    int type;
    char couleur[26];
}Box;//Nom de la structure

/*
Nom         : Init_Box
Entree      : Deux entiers et un nom de couleur
Sortie      : Une adresse memoire
Description : Fonction permet d'allouer de l'espace memoire pour une
              variable de type Box et l'initialiser
*/
Box* Init_Box(int id,int esp, int ty, char *Couleur)
{
    Box *nvbox;//Pointeur de type Box
    nvbox = (Box*)malloc(sizeof(Box));//Allocation de la place memoire
    //Afficher un message et quitter si l'allocation est mal faite
    if (!nvbox)
    {
        printf("\nErreur d allocation [BOX]");
        exit(0);
    }
    //Initialiser l'espace entre les elements du box
    nvbox->espace = esp;
    nvbox->type = ty;//Initialiser le type
    nvbox->Id = id;//Initialiser l'identifiant
    //Initialiser la couleur du box
    if (Couleur) strcpy(nvbox->couleur, Couleur);
    else strcpy(nvbox->couleur, "white");
    return((Box*)nvbox);//Retourner l 'adresse alouée
}

/*
Nom         : Creer_Box
Entree      : Un box
Sortie      : Un box crée
Description : Fonction permet de créer un box
*/

void Creer_Box(Box* b)
{
    //Afficher un message et quitter si le box n'existe pas
    if (!b)
    {
        printf("\nBox n existe pas");
        exit(0);
    }
    //Creation du box(horizontal ou vertical)
    switch (b->type)
    {
        case 0: b->monbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, b->espace);
                break;
        case 1: b->monbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, b->espace);
                break;
        default: printf("\nErreur type du box");
                exit(0);
    }
    //Modifier_Couleur_Widget(b->monbox, b->couleur);
}


/*
Nom         : Ajouter_Elem_Au_Box
Entree      : Un box et un element
Sortie      : Element ajouté au box
Description : Fonction permet d'ajouter un element dans un box
*/
void Ajouter_Elem_Au_Box(Box *b, GtkWidget *elem)
{
    //Afficher un message et quitter si le box n'existe pas
    if (!b)
    {
        printf("\nErreur, box n existe pas [ajouter elem au box]");
        exit(0);
    }
    //Ajouter l'element au box
    gtk_box_pack_start(GTK_BOX(b->monbox), elem, TRUE, TRUE, b->espace);
}
#endif
