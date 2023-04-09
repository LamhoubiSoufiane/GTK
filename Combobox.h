#pragma once





//Structure de la liste des elements du combobox
typedef struct ent
{
    int id;//identifiant pour determiner les elements du combobox
    char Nom[26];//Titre de l'element
    struct ent *svt;//Pointeur sur le svt
}ListeCombo;//Nom de la structure

//Structure de la liste déroulante(Combobox)
typedef struct
{
    GtkWidget *combo;//Pointeur pour le combobox
    int ID;//Identifiant du combobox
    ListeCombo *Maliste;//Liste des éléments du combobox
    Taille T;//Taille du combobox
    Position pox;//Position du combobox
}Combobox;//Nom de la structure

/*
Nom         : Init_Elem_combo
Entree      : Un identificateur(entier) et un nom
Sortie      : une adresse d'une zone memoire
Description : Fonction permet de creer et d'initialiser un element
                de type ListeCombo
*/
ListeCombo *Init_Elem_combo(int id,char *titre)
{
    ListeCombo *nv;//Pointeur de type ListeCombo
    nv = (ListeCombo*)malloc(sizeof(ListeCombo));//Allocation de la place memoire
    //Afficher un message et quitter si l allocation est mal faite
    if (!nv)
    {
        printf("\nErreur d allocation [listecombo]");
        exit(0);
    }
    nv->id = id;//Initialiser l'identificateur
    strcpy(nv->Nom,titre);
    nv->svt =NULL;//Initialiser le pointeur svt
    return((ListeCombo*)nv);//Retourner l'adresse allouée
}

/*
Nom         : Init_Combobox
Entree      : 4 entiers pour hauteur, largeur,position x et y,
              et un boolean pour determiner si le combobox est
              avec une zone de texte ou non.
Sortie      : une adresse d'une zone memoire
Description : Fonction permet d'allouer de la place memoire
              d'initialiser et de creer un combobox

*/

Combobox* Init_Combobox(int IDC, int xpos, int ypos, int h, int l, int entry)
{
    Combobox *c;//pointeur de type Combobox
    c = (Combobox*)malloc(sizeof(Combobox));//Allocation de la place memoire
    //Afficher un message d erreur et quitter si l'allocation est mal faite
    if (!c)
    {
        printf("\nErreur d allocation [combobox]");
        exit(0);
    }
    c->ID = IDC;//Initialisation de l'identifiant du combobox
    //Initialisation de la position du combobox
    c->pox.posX = xpos;
    c->pox.posY = ypos;
    //Initialisation de la taille du combobox
    c->T.Hauteur = h;
    c->T.Largeur = l;
    c->Maliste = NULL;//Initialiser la liste des elements du combobox par NULL
    //Creation du combobox
    if (entry) c->combo = gtk_combo_box_text_new_with_entry();
    else c->combo = gtk_combo_box_text_new();
    gtk_widget_set_size_request(c->combo, l, h);
    return((Combobox*)c);//Retourner l'adresse allouée
}


/*
Nom         : Ajouter_Elem_Combobox
Entree      : Un combobox, nom et l'id de l'element
Sortie      : Element ajouté au combobox
Description : Fonction permet d'ajouter un element au combobox

*/
void Ajouter_Elem_Combobox(Combobox *c, char *titre, int id)
{
    ListeCombo *nvm, *ptr=NULL;//Declaration de deux pointeurs de type ListeCombo
    nvm = Init_Elem_combo(id, titre);//Initialiser le nvm
    //Si la liste des elements du combobox n'existe pas, nvm devient la liste
    if (!c->Maliste) c->Maliste = nvm;
    else//Sinon
    {
        ptr = c->Maliste;//Pointer sur la liste
        //Tant que le pointeur a un suivant,pointer sur le suivant
        while (ptr->svt) ptr = ptr->svt;
        ptr->svt = nvm;//Le pointeur a pour suivant nvm
    }
    //Ajouter l'element au combobox
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(c->combo), "id", titre);
}



