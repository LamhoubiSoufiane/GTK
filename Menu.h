
#ifndef MENU_H
#define MENU_H

//Icone 

//Structure d'un menu
typedef struct Mn
{
    GtkWidget *ElemMenu;//Variable pour determiner l'element du menu
    GtkWidget *Id_SSMenu;//Variable pour determiner le sous-menu
    //GtkWidget *Icone;//Variable pour l'icone
    char mnemonic;//Le caractère mnemonic de l'element
    char Nom[26];//Tableau de 26 caractères pour le nom de l'element
    char Icone[50];//Tableau de 50 caractères pour l'icone
    struct Mn *MenuFrere;//Pointeur sur le Frère
    struct Mn *MenuFils;//Pointeur sur le Fils
}Menu;//Nom de la structure

/*
Nom         : Init_Barre_Menu
Entree      : Un entier 
Sortie      : Une adresse memoire
Description : Fonction permet d'allouer de l'espace memoire pour une 
              variable de type Menu et l'initialiser comme barre du menu 
*/

Menu *Init_Barre_Menu(int barre)
{
    Menu *m;//Pointeur de type Menu
    m = (Menu*)malloc(sizeof(Menu));//Allocation de la place memoire
    //Afficher un message et quitter si l'allocation est mal faite
    if (!m)
    {
        printf("\nErreur d allocation[menu]");
        exit(0);
    }
    //Initialiser ElemMenu par une barre de menu
    m->ElemMenu = gtk_menu_bar_new();
    /*Type de la barre de titre : 
    * 0 : les elements du menu sont stockés de la gauche vers la droite
    * 1 : les elements du menu sont stockés de la droite vers la gauche
    * 2 : les elements du menu sont stockés du haut vers le bas
    * 3 : les elements du menu sont stockés du bas vers le haut
    */
    switch (barre)
    {
        case 0: gtk_menu_bar_set_pack_direction(GTK_MENU_BAR(m->ElemMenu), GTK_PACK_DIRECTION_LTR);
                break;
        case 1: gtk_menu_bar_set_pack_direction(GTK_MENU_BAR(m->ElemMenu), GTK_PACK_DIRECTION_RTL);
                break;
        case 2: gtk_menu_bar_set_pack_direction(GTK_MENU_BAR(m->ElemMenu), GTK_PACK_DIRECTION_TTB);
                break;
        case 3: gtk_menu_bar_set_pack_direction(GTK_MENU_BAR(m->ElemMenu), GTK_PACK_DIRECTION_BTT);
                break;
        default: printf("\nErreur barre menu");
            exit(0);
    }
    m->Id_SSMenu = NULL;//Initialiser le groupe des sous menu par null
    m->MenuFrere = m->MenuFils = NULL;//Initialiser les pointeurs fils et frere par null
    return((Menu*)m);//Retourner une adresse
}

/*
Nom         : Init_Element_Menu
Entree      : Un nom et le nom de l'icone
Sortie      : Une adresse memoire
Description : Fonction permet d'allouer de l'espace memoire pour une
              variable de type Menu et l'initialiser comme element du menu
*/

Menu *Init_Element_Menu(char nom_menu[26], char *Ic)
{
    Menu *m;//Pointeur de type Menu
    m = (Menu*)malloc(sizeof(Menu));//Allocation de la place memoire
    //Afficher un message et quitter si l'allocation est mal faite
    if (!m)
    {
        printf("\nErreur d allocation[menu]");
        exit(0);
    }
    //Initialiser le groupe de sous-menu de l'element
    m->Id_SSMenu = gtk_menu_new();
    strcpy(m->Nom, nom_menu);//Initialiser le nom de l'element 
    //Initialiser l'icone de l'element 
    if (Ic) strcpy(m->Icone, Ic);
    else m->Icone[0] = '0';
    m->MenuFrere = m->MenuFils = NULL;//Initialiser les pointeurs fils et frere par null
    return((Menu*)m);//Retourner une adresse
}

/*
Nom         : creer_menu
Entree      : Un menu,un nom et le nom de l'icone
Sortie      : Element creer et ajouter dans le menu
Description : Fonction permet de creer un element de menu 
              et l'ajouter dans la barre menu
*/

void creer_menu(Menu *m,char nom_menu[26],char *Ic)
{
    Menu *nvm;//Pointeur de type Menu
    Menu* ptr;//Pointeur de type Menu 
    //GtkWidget* icc;
    ptr = m;//Pointer sur la barre menu
    //Tant que la barre menu a un frere, pointer sur le frere suivant
    while (ptr->MenuFrere) ptr = ptr->MenuFrere;
    nvm = Init_Element_Menu(nom_menu,Ic);//Initialiser nvm
    /*if (nvm->Icone[0] != '0')
    {
        nvm->ElemMenu = gtk_menu_item_new_with_mnemonic(nvm->Nom);
        icc = gtk_image_new_from_icon_name(nvm->Icone, GTK_ICON_SIZE_MENU);
        gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(nvm->ElemMenu),icc);
        gtk_image_menu_item_set_always_show_image(GTK_IMAGE_MENU_ITEM(nvm->ElemMenu), TRUE);
    }*/
    //else 
     nvm->ElemMenu = gtk_menu_item_new_with_label(nvm->Nom);//Creer le menu
     //Ajouter le menu a la barre menu
    gtk_menu_shell_append(GTK_MENU_SHELL(m->ElemMenu), nvm->ElemMenu);
    ptr->MenuFrere = nvm;//Ptr a comme frere svt nvm
}

/*
Nom         : creer_sous_menu
Entree      : Une fenetre,un menu,un nom du sous menu,
              le nom de menu pere,le nom de l'icone 
              et le caractère mnemonic
Sortie      : Element creer et ajouter comme sous-menu du menu pere
Description : Fonction permet de creer un sous-menu
*/

void creer_sous_menu(Fenetre* fn, Menu* m,char sous_menu[26], 
                    char menupere[26],char* Ic, char Caractere_mnemonic)                       
{
    Menu *nvm;//Pointeur de type Menu
    Menu *ptr;//Pointeur de type Menu
    //Si le menu existe
    if (m)
    {
        //Si le menu pere est trouvé
        if (!strcmp(m->Nom, menupere))
        {
            nvm = Init_Element_Menu(sous_menu, Ic);//Initialiser nvm
            nvm->ElemMenu = gtk_menu_item_new_with_label(sous_menu);//Creer 
            /*if (Ic)
            {
                nvm->MenuItems = gtk_image_menu_item_new_with_mnemonic(sous_menu);
                nvm->icc = gtk_image_new_from_icon_name(Ic, GTK_ICON_SIZE_MENU);
                gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(nvm->MenuItems), nvm->icc);
                gtk_image_menu_item_set_always_show_image(GTK_IMAGE_MENU_ITEM(nvm->MenuItems), TRUE);
            }*/
            //Si le menu pere n'a pas de fils, nvm devient son fils
            if (!m->MenuFils) m->MenuFils = nvm;
            else//sinon
            {
                ptr = m->MenuFils;//Pointer sur le fils
                //Tant que le fils a un frere,pointer sur le frere suivant
                while (ptr->MenuFrere) ptr = ptr->MenuFrere;
                ptr->MenuFrere = nvm;//ptr a comme frere nvm
            }
            nvm->mnemonic = Caractere_mnemonic;//Initialiser le caractère mnemonic
            if (Caractere_mnemonic != '0') //Si le caractère mnemonic existe 
                //Ajouter nvm au groupe d'accelerateur
                gtk_widget_add_accelerator(nvm->ElemMenu, "activate", fn->acc, (int)Caractere_mnemonic, 
                                            GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);//Ajouter au groupe d'accelerateur
            //g_signal_connect(nvm->MenuItems, "activate", G_CALLBACK(test), NULL); ///JUSTE POUR LE TEST !!!!
            //Ajouter nvm au groupe sous-menu du menu pere
            gtk_menu_shell_append(GTK_MENU_SHELL(m->Id_SSMenu), nvm->ElemMenu);
            //Ajouter le groupe sous-menu au menu pere
            gtk_menu_item_set_submenu(GTK_MENU_ITEM(m->ElemMenu), m->Id_SSMenu);
            return;
        }
        //Sinon appel reccursive sur le pointeur fils
        creer_sous_menu(fn, m->MenuFils, sous_menu, menupere, Ic, Caractere_mnemonic);
        //Appel reccursive sur le pointeur frere
        creer_sous_menu(fn, m->MenuFrere, sous_menu, menupere, Ic, Caractere_mnemonic);
    }
}
#endif
