#pragma once

typedef struct
{
    GtkWidget* entry;             // widget entry
    int id;
    int visibility;          // 1 si les caractères saisis sont visibles et 0 sinon
    int max_length;              // La longueur maximale des caractères autorisés
    int editable;            // 1 si l'entry est éditable et 0 sinon
    char text[50];                  // Le texte actuel de l'entry
    int Just_Num;            //1 si l'entry doit etre juste des nombres ET 0 sinon
    Position p;
    Taille t;
}Entry;



/*    l'initialisation d'un Entry    */

Entry* Init_Entry(int id,int visibility, int max_length,
                  int editable, char *text, int Just_Num,
                  int posx,int posy,int h,int l)
{
    // Allocation d'un espace mémoire pour une variable de type Entry
    Entry* E;
    E = (Entry*)malloc(sizeof(Entry));
    if (!E)
    {
        printf("\nErreur d'allocation [Entry]");
        exit(0);
    }
    // Initialisation des champs de la structure Entry avec les valeurs passées en paramètre
    E->id = id;
    E->visibility = visibility;
    E->max_length = max_length;
    E->editable = editable;
    if(strcmp(text,"NULL")) strcpy(E->text, text);
    else E->text[0]='\0';
    E->Just_Num = Just_Num;
    E->p.posX=posx;
    E->p.posY=posy;
    E->t.Hauteur=h;
    E->t.Largeur=l;
    // Retourne un pointeur vers la variable Entry nouvellement allouée
    return ((Entry*)E);
}

/*
* Cette fonction est un rappel pour le signal "changed" d'un GtkEntry.
* Elle filtre les entrées non-numériques et met à jour le texte de l'entry avec le texte filtré.
* Elle utilise les fonctions de la bibliothèque GLib pour manipuler les chaînes de caractères.
*/

static void on_entry_changed(GtkEditable* editable, gpointer user_data) {
    const gchar* text = gtk_entry_get_text(GTK_ENTRY(editable));
    gchar* filtered_text = g_strdup("");
    gint len = strlen(text);
    for (int i = 0; i < len; i++) {
        if (g_ascii_isdigit(text[i])) {
            filtered_text = g_strdup_printf("%s%c", filtered_text, text[i]);
        }
    }
    gtk_entry_set_text(GTK_ENTRY(editable), filtered_text);
    g_free(filtered_text);
}


/*    la Création d'un Entry    */

void Creer_Entry(Entry* E)
{
    // Vérifier si la structure Entry est valide
    if (!E)
    {
        printf("\nErreur d'allocation[Entry]");
        exit(0);
    }

    // Créer un nouveau widget Entry
    E->entry = gtk_entry_new();

    // Définir la visibilité des caractères saisis en fonction de E->visibility
    if (E->visibility) {
        gtk_entry_set_visibility(GTK_ENTRY(E->entry), TRUE);
    }
    else {
        gtk_entry_set_visibility(GTK_ENTRY(E->entry), FALSE);
    }

    // Limiter le nombre de caractères saisis si E->max_length > 0
    if (E->max_length > 0) {
        gtk_entry_set_max_length(GTK_ENTRY(E->entry), E->max_length);
    }

    // Définir si l'Entry est modifiable ou non en fonction de E->editable
    if(E->editable) gtk_editable_set_editable(GTK_EDITABLE(E->entry),TRUE);
    else gtk_editable_set_editable(GTK_EDITABLE(E->entry),FALSE);

    // Définir le texte initial de l'Entry en fonction de E->text
    if(E->text[0] != '\0') gtk_entry_set_text(GTK_ENTRY(E->entry), (gchar*)E->text);

    // Si E->Just_Num est TRUE, connecter le signal "changed" du widget Entry à la fonction de rappel on_entry_changed() Pour filter les entrées non_numériques
    if (E->Just_Num)
    {
        g_signal_connect(G_OBJECT(E->entry), "changed", G_CALLBACK(on_entry_changed), NULL);
    }
}



