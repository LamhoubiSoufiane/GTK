#pragma once

typedef struct A
{
    GtkWidget* dialog;
    // GtkWidget *content_area;
    int redimenB;
    int Modal;
    int ID;
    Taille TailleBD; /// Null :par defaut
    Position PosBD;  /// Null :par defaut, 0-0 :centre, 1-1 Position de la souris, 2-2 :	Centrez la fenï¿½tre sur son parent transitoire
    char Titre[20];
    char label[60];
    char Couleur[26];
} BDialogue;


BDialogue *Initier_Bdialogue(int ID,int H, int L, int resizable,
                             int posx, int posy, char *titre,
                             char *couleur, char *label,int Modal)
{
    BDialogue *BD;
    BD = (BDialogue *)malloc(sizeof(BDialogue));
    if (!BD)
    {
        printf("\nErreur d allocation[BDialog]");
        exit(0);
    }
    BD->dialog = (GtkWidget *)malloc(sizeof(GtkWidget));
    if (!BD->dialog)
    {
        printf("\nErreur d allocation[BDialog]");
        exit(0);
    }
    BD->redimenB = resizable;
    BD->TailleBD.Hauteur = H;
    BD->TailleBD.Largeur = L;
    BD->PosBD.posX = posx;
    BD->PosBD.posY = posy;
    BD->Modal = Modal;
    BD->ID=ID;
    if(titre) strcpy(BD->Titre, titre);
    else BD->Titre[0]='\0';
    if(label) strcpy(BD->label, label);
    else BD->label[0]='\0';
    if (couleur) strcpy(BD->Couleur,couleur);
    else BD->Couleur[0]='\0';
    return ((BDialogue *)BD);
}

void dialog_response(GtkDialog *dialog, gint response_id, gpointer user_data)
{
    // Afficher la rÃ©ponse de l'utilisateur

    if (response_id == GTK_RESPONSE_OK)
    {
        g_print("L'utilisateur a cliquÃ© sur OK.\n");
    }
    else if (response_id == GTK_RESPONSE_CANCEL)
    {
        g_print("L'utilisateur a cliquÃ© sur Annuler.\n");
    }

    // Fermer la boÃ®te de dialogue
    gtk_widget_destroy(GTK_WIDGET(dialog));

}

void Creer_Boite_Dialogue(BDialogue *BD,GtkWidget *fn)
{

    BD->dialog = gtk_message_dialog_new(NULL,GTK_DIALOG_MODAL,
                                        GTK_MESSAGE_INFO,GTK_BUTTONS_OK_CANCEL,
                                        BD->label);
    // set position
    gtk_window_move(GTK_WINDOW(BD->dialog), BD->PosBD.posX, BD->PosBD.posY); // the macro GTK_WINDOW will transforme  the widget dialog to a window
    // if size can change
    gtk_window_set_resizable(GTK_WINDOW(BD->dialog), BD->redimenB);
    // set size
    gtk_window_set_default_size(GTK_WINDOW(BD->dialog), BD->TailleBD.Largeur, BD->TailleBD.Hauteur);
    Modifier_Couleur_widget(BD->dialog,BD->Couleur);
    // g_signal_connect(S->Information.BD->dialog, "response", G_CALLBACK(creer_BDialogue), window);
    g_signal_connect(BD->dialog, "response", G_CALLBACK(dialog_response), NULL);
    //gtk_widget_show_all(BD->dialog);
}

/*Mastructure* Traitement_Boite_Dialogue(Mastructure* box, xmlNodePtr child)
{
    BDialogue* BD, * ptr = NULL;
    MonUnion Info;
    if (!box)
    {
        printf("\nErreur, box n existe pas[Traitement_ButtonSimple]!!");
        exit(0);
    }
    Info.BD = Initier_Bdialogue(atoi((char*)xmlGetProp(child, "id")),
                                atoi((char*)xmlGetProp(child, "Hauteur")),
                                atoi((char*)xmlGetProp(child, "Largeur")),
                                atoi((char*)xmlGetProp(child, "resizable")),
                                atoi((char*)xmlGetProp(child, "PositionX")),
                                atoi((char*)xmlGetProp(child, "PositionY")),
                                atoi((char*)xmlGetProp(child, "Hauteur")),
                                atoi((char*)xmlGetProp(child, "Largeur")),
                                (char*)xmlGetProp(child, "titre"),
                                (char*)xmlGetProp(child, "couleur"),
                                (char*)xmlGetProp(child, "label"),
                                (char*)xmlGetProp(child, "Modal")),
            BD = Creer_Init_Cellule_Mastructure(Info, 5);
    if (box->Fils)
    {
        ptr = box->Fils;
        while (ptr->Frere) ptr = ptr->Frere;
        ptr->Frere = button;
    }
    else box->Fils = button;
    return((Mastructure*)box);
}*/