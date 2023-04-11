#pragma once





//Couleur , icone

//Structure d'une fenetre
typedef struct
{
    GtkWidget *fenetre;//Pointeur de type Gtkwidget pour la fenetre
    GtkWidget *TitleBar;//Pointeur de type Gtkwidget pour la barre de titre
    GtkWidget *Ascenceurs;//Pointeur de type Gtkwidget pour les ascenceurs
    GtkWidget *Fixed;//Contenaire avec lequel on va positionner les widgets dans la fenetre
    GtkAccelGroup *acc;//Pointeur de type GtkAccelGroup pour les shortcuts.
    int Id;//Identifiant de la fenetre
    Taille TailleFenetre;//Variable de type Taille pour determiner la taille de la fenetre
    /*Variable de type Taille pour determiner la position de la fenetre
    0-0 : Centre de l'ecran;
    1-1 : Position de la souris*/
    Position PosFenetre;
    /*Variable pour determiner si la fenetre est redimensionnable
    0 : non redimensionnable*/
    int redimensionnable;
    char Titre[26];//Tableau de 26 caractères pour le titre de la fenetre
    char Sous_Titre[26];//Tableau de 26 caractères pour le sous-titre de la fenetre
    char Icone[26];//Tableau de 26 caractères pour l'icone de la fenetre
    char Couleur[26];//Tableau de 26 caractères pour la couleur de la fenetre
}Fenetre;//Nom de la Structure


/*
Nom         : Init_Personnalise_Fenetre
Entree      : Des entiers pour determiner l'hauteur(H),largeur(L),position x (posx),
              position y (posy),type de la barre de titre(titlebarre),et si
              la fenetre possede des ascenceurs ou non, ainsi que
              des tableaux pour le titre,sous-titre, la couleur et l'icone.
Sortie      : Adresse d'une zone mémoire
Description : Fonction permet l'allocation et l'initialisation
                d'une variable de type Fenetre
*/
Fenetre *Init_Personnalise_Fenetre(int ID,int H, int L, int resizable, int posx, int posy,
                                   int titlebarre, int Scroll, char titre[26],
                                   char soustitre[26],char couleur[26],char ic[26])
{
    Fenetre *fn; //Pointeur de type Fenetre
    fn = (Fenetre*)malloc(sizeof(Fenetre));//Allocation de la place mémoire
    //Afficher un message d'erreur et quitter si l'allocation est mal faite
    if (!fn)
    {
        printf("\nErreur d allocation[Fenetre]");
        exit(0);
    }
    fn->Id = ID;
    fn->redimensionnable = resizable;
    //Initialisation de la taille
    fn->TailleFenetre.Hauteur = H;
    fn->TailleFenetre.Largeur = L;
    //Initialisation de la position
    fn->PosFenetre.posX = posx;
    fn->PosFenetre.posY = posy;
    if (Scroll)//Si Scroll est different de 0
    {
        //Allocation de la place memoire
        fn->Ascenceurs = (GtkWidget*)malloc(sizeof(GtkWidget));
        //Afficher un message et quitter si l allocation est mal faite
        if (!fn->Ascenceurs)
        {
            printf("\nErreur d allocation fn->Ascenceurs!!");
            exit(0);
        }
        //Initialiser la variable des ascenceurs
        fn->Ascenceurs = gtk_scrolled_window_new(NULL, NULL);
    }
        //Initialiser la variable des ascenceurs par null si Scroll == 0
    else fn->Ascenceurs = NULL;
    if (titlebarre)//Si titlebarre est different de 0 (cad barre de titre personnalisée)
    {
        //Allocation de la place memoire
        fn->TitleBar = (GtkWidget*)malloc(sizeof(GtkWidget));
        //Afficher un message et quitter si l allocation est mal faite
        if (!fn->TitleBar)
        {
            printf("\nErreur d allocation fn->Titlebar!!");
            exit(0);
        }
    }
        //Initialiser Titlebar par null si titlebarre == 0
    else fn->TitleBar = NULL;
    //Allocation de la place memoire(fixed)
    fn->Fixed = (GtkWidget*)malloc(sizeof(GtkWidget));
    //Afficher un message et quitter si l allocation est mal faite
    if (!fn->Fixed)
    {
        printf("\nErreur d allocation fn->Fixed");
        exit(0);
    }
    fn->Fixed = gtk_fixed_new();//Initialisation du fixed
    //Allocation de la place memoire(accelgroup)
    fn->acc = (GtkAccelGroup*)malloc(sizeof(GtkAccelGroup));
    //Afficher un message et quitter si l allocation est mal faite
    if (!fn->acc)
    {
        printf("\nErreur d allocation fn->acc");
        exit(0);
    }
    fn->acc = gtk_accel_group_new();//Initialisation d'accel group
    strcpy(fn->Titre,titre);//Initialisation du titre
    strcpy(fn->Sous_Titre, soustitre);//Initialisation du sous-titre
    strcpy(fn->Couleur, couleur);//Initialisation de la couleur
    strcpy(fn->Icone, ic);//Initialisation de l'icone
    return((Fenetre*)fn);//Retourner une adresse memoire
}

/*
Nom         : Ajouter_Elem_Au_Fixed
Entree      : Fentre, un widget, position x et y
Sortie      : Element ajouté au fixed
Description : Fonction permet d'ajouter un element dans une fenetre
                et le positionner à l'aide du fixed
*/

/*void Ajouter_Elem_Au_Fixed(Fenetre *fn, GtkWidget *elem, gint x, gint y)
{
    //Ajouter elem au fixed de la fenetre fn à la position x et y
    gtk_fixed_put(GTK_FIXED(fn->Fixed), elem, x, y);
}*/



/*
Nom         : Creer_Fenetre
Entree      : Une fenetre
Sortie      : une fenetre crée
Description : Fonction permet de creer une fenetre
*/

void Creer_Fenetre(Fenetre *fn)
{
    //GdkPixbuf *icone=NULL;
    //GError *error = NULL;
    //Afficher un message d erreur et quitter si la fenetre n existe pas
    if (!fn)
    {
        printf("\nErreur fenetre n existe pas!!");
        exit(0);
    }
    fn->fenetre = gtk_window_new(GTK_WINDOW_TOPLEVEL);//Creation de la fenetre
    if (fn->redimensionnable) //Si la fenetre est redimensionnable
        gtk_window_set_resizable(GTK_WINDOW(fn->fenetre), TRUE);
    else gtk_window_set_resizable(GTK_WINDOW(fn->fenetre), FALSE);//sinon
    gtk_window_activate_default(GTK_WINDOW(fn->fenetre));
    //Modifier la taille de la fenetre
    gtk_window_set_default_size(GTK_WINDOW(fn->fenetre),
                                fn->TailleFenetre.Largeur,
                                fn->TailleFenetre.Hauteur);
    //Positionner la fenetre
    switch (fn->PosFenetre.posX)
    {
        case 0: gtk_window_set_position(GTK_WINDOW(fn->fenetre), GTK_WIN_POS_CENTER);
            break;
        case 1: gtk_window_set_position(GTK_WINDOW(fn->fenetre), GTK_WIN_POS_MOUSE);
            break;
        default: gtk_window_move(GTK_WINDOW(fn->fenetre), fn->PosFenetre.posX, fn->PosFenetre.posY);
            break;
    }
    if (fn->TitleBar)//si la barre de titre est personnalisée
    {
        fn->TitleBar = gtk_header_bar_new();//Creation de la barre de titre
        //Ajouter le titre
        gtk_header_bar_set_title(GTK_HEADER_BAR(fn->TitleBar), fn->Titre);
        //Ajouter le sous-titre
        if (strcmp(fn->Sous_Titre,"NULL")!=0) gtk_header_bar_set_subtitle(GTK_HEADER_BAR(fn->TitleBar), fn->Sous_Titre);
        //Ajouter la barre de titre à la fenetre
        gtk_window_set_titlebar(GTK_WINDOW(fn->fenetre), fn->TitleBar);
        //Afficher les buttons (fermer,agrandir,reduire) à la barre de titre
        gtk_header_bar_set_show_close_button(GTK_HEADER_BAR(fn->TitleBar), TRUE);
    }
        //Si la barre est par defaut, ajouter le titre
    else gtk_window_set_title(GTK_WINDOW(fn->fenetre), fn->Titre);
    if (fn->Ascenceurs)//Si la fenetre contient des ascenceurs
    {
        gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(fn->Ascenceurs), GTK_POLICY_ALWAYS, GTK_POLICY_ALWAYS);
        gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW(fn->Ascenceurs), 0);
        //Ajouter le fixed de la fenetre aux ascenceurs
        gtk_container_add(GTK_CONTAINER(fn->Ascenceurs), fn->Fixed);
    }
    //style(fn->fenetre, fn->Titre);
    gtk_window_add_accel_group(GTK_WINDOW(fn->fenetre), fn->acc);
    Modifier_Couleur_widget(fn->fenetre,fn->Couleur);
}

/*
Nom         : Afficher_Fenetre
Entree      : Une fenetre
Sortie      : affichage de la fenetre
Description : Fonction permet de afficher une fenetre
*/
void Afficher_Fenetre(Fenetre* fn)
{
    //Afficher un message et quitter si la fenetre n'existe pas
    if (!fn || !fn->fenetre)
    {
        printf("\nErreur fenetre n existe pas[ajouter fixed fenetre]");
        exit(0);
    }
    //Afficher un message et quitter si le fixed de la fenetre n existe pas
    if (!fn->Fixed)
    {
        printf("\nErreur fixed n existe pas [ajouter fixed fenetre]");
        exit(0);
    }
    // Si la fenetre contient des ascenceurs
    if (fn->Ascenceurs)
        gtk_container_add(GTK_CONTAINER(fn->fenetre), fn->Ascenceurs); //Ajouter les ascenceurs
        //Sinon ajouter directement le fixed à la fenetre
    else gtk_container_add(GTK_CONTAINER(fn->fenetre), fn->Fixed);
    gtk_widget_show_all(fn->fenetre);//Afficher la fenetre
}


