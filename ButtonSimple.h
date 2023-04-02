
#ifndef BUTTONSIMPLE_H
#define BUTTONSIMPLE_H

typedef struct
{
    GtkWidget *btn;//Variable pour le bouton
    int Id;//Identifiant du button
    Position p;//Position du bouton
    Taille T;//Taille du bouton
    int mnemonic;//determiner si le bouton est avec mnemonic ou non
    char Nom[26];//tableau de 26 caractères pour le nom du bouton
    char NomIcone[26];//tableau de 26 caractères pour l'icone du bouton
}Button;//Nom de la structure



Button* Init_Button_Simple(int id,char nom[26], char *icone, int xpos, int ypos,
                            int h, int l, int mnemonic)
{
    Button* b;//pointeur de type button
    b = (Button*)malloc(sizeof(Button));//Allocation de la place memoire
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
    if (icone) strcpy(b->NomIcone, icone);
    else b->NomIcone[0] = '0';
    //Initialisation de la position
    b->p.posX = xpos;
    b->p.posY = ypos;
    //Initialisation de la taille
    b->T.Hauteur = h;
    b->T.Largeur = l;
    return((Button*)b);//Retourner l'adresse alouée
}


void Creer_Button_Simple(Fenetre* fn, Button* b)
{
    //Afficher un message d'erreur et quitter si le bouton n'existe pas
    if (!b)
    {
        printf("\nErreur, button n existe pas");
        exit(0);
    }
    //Afficher un message d'erreur et quitter si la fenetre n'existe pas
    if (!fn)
    {
        printf("\nErreur, fenetre n existe pas");
        exit(0);
    }
    //Creer le bouton 
    if (b->mnemonic) b->btn = gtk_button_new_with_mnemonic(b->Nom);
    else b->btn = gtk_button_new_with_label(b->Nom);
    //Modifier la taille du bouton
    gtk_widget_set_size_request(b->btn, b->T.Largeur, b->T.Hauteur);
    //Ajouter le bouton au fixed de la fenetre passée en argument
    Ajouter_Elem_Au_Fixed(fn, b->btn, b->p.posX, b->p.posY);
  
}
#endif
