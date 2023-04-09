#pragma once

typedef struct
{
    int id;
    GtkWidget *Fr;
    char label[20];           // Texte de l'étiquette du cadre,Valeur par défaut : NULL
    int label_xalign;       // L'alignement horizontal de l'étiquette,Valeurs autorisées : [0,1]
    int label_yalign;       // L'alignement vertical de l'étiquette.Valeurs autorisées : [0,1] Valeur par défaut : 0,5
    GtkShadowType shadow_type; // Apparition de la bordure du cadre,Valeur par défaut : GTK_SHADOW_ETCHED_IN
    char Couleur[20];
}Frame;



/*    l'initialisation d'une Frame    */
Frame* Init_Frame(int id,char *label, int label_xalign,
                  int label_yalign, int shadow_type, char *Couleur)
{
    Frame *F;
    // Allocation de mémoire pour la structure Frame
    F = (Frame *) malloc(sizeof(Frame));
    if (!F) {
        printf("\nErreur d'allocation [Frame]");
        exit(0);
    }
    F->id = id;
    // Initialisation des attributs de la structure Frame avec les valeurs fournies
    strcpy(F->label, label);
    strcpy(F->Couleur, Couleur);
    F->label_xalign = label_xalign;
    F->label_yalign = label_yalign;
    switch (shadow_type) {
        case 0:
            F->shadow_type = GTK_SHADOW_NONE;
            break;
        case 1:
            F->shadow_type = GTK_SHADOW_IN;
            break;
        case 2:
            F->shadow_type = GTK_SHADOW_OUT;
            break;
        case 3:
            F->shadow_type = GTK_SHADOW_ETCHED_IN;
            break;
        case 4:
            F->shadow_type = GTK_SHADOW_ETCHED_OUT;
            break;
        default:
            printf("\nErreur shadow\n");
    }
}
    /*    La création d'une Frame    */
    void Creation_Frame(Frame* F, char *name)
    {
        if (!F)
        {
            printf("\nErreur de pointeur nul [Frame]");
            exit(0);
        }

        // Création d'un nouveau widget Gtk de type GtkFrame
        F->Fr = gtk_frame_new(name);

        // Configuration des attributs du cadre Gtk en utilisant les valeurs stockées dans la structure Frame
        gtk_frame_set_label(GTK_FRAME(F->Fr), F->label);
        gtk_frame_set_label_align(GTK_FRAME(F->Fr), (gfloat)F->label_xalign,(gfloat)F->label_yalign);
        gtk_frame_set_shadow_type(GTK_FRAME(F->Fr), F->shadow_type);


        /*GdkRGBA color;
        gdk_rgba_parse(&color, F->Couleur);

        // Définition de la couleur de fond du cadre Gtk
        gtk_widget_override_background_color(F->Fr, GTK_STATE_FLAG_NORMAL, &color);*/
    }
