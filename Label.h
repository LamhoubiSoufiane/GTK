#pragma once

typedef struct
{
    char style[10];           /// 0:italic,1:oblique,3:normal
    char font[26];            /// police d'ecriture
    char size[10];            /// size du texte small, meduim ,large
    char weight[15];          /// ultralight,light,normal,bold,ultrabold,heavy
    char color[26];           /// couleur du texte
    char background[26];      /// couleur du fond
    char underline[10];       /// single,double,low ou none
    char underline_color[26]; /// couleur du soulignement
    char barrer_txt[6];       /// true ou false
    char color_bar[26];       /// couleur du barriere
    int select;              // 0:non ou 1:oui
    int alignement;          // 0:left,1:right,2:center, ou 3:fill
}Format;

typedef struct
{
    GtkWidget* Label; /// pointeur sur le label
    int id;//Identifiant de label
    char texte[255];  /// le texte à afficher
    Format lab;       // formatage du texte
    Position pos;
    Taille T;
}MonLabel;

MonLabel *Init_label(int id, char* texte, char* back_color, char* txtcolr,
                     char* barrertxt, char* barcolor, char* font,
                     char* size, char* underline, char* underlinecolor, char* styletxt,
                     char* weight, int slct, int align,int xpos,int ypos,int h,int larg)
{
    MonLabel *l;
    l = (MonLabel*)malloc(sizeof(MonLabel));
    if (!l)
    {
        printf("\nErreur d allocation label");
        exit(0);
    }
    l->id = id;
    strcpy(l->texte, texte);
    strcpy(l->lab.background, back_color);
    strcpy(l->lab.color, txtcolr);
    strcpy(l->lab.barrer_txt, barrertxt);
    strcpy(l->lab.color_bar, barcolor);
    strcpy(l->lab.font, font); // police
    strcpy(l->lab.size, size);
    strcpy(l->lab.underline, underline);
    strcpy(l->lab.underline_color, underlinecolor);
    strcpy(l->lab.style, styletxt);
    strcpy(l->lab.weight, weight);
    l->lab.alignement = slct;
    l->lab.select = align;
    l->pos.posY = ypos;
    l->pos.posX = xpos;
    l->T.Hauteur = h;
    l->T.Largeur = larg;
    return((MonLabel*)l);
}

void creer_label(MonLabel* l)
{
    char* format, // ce pointeur est pour le formatage du texte
    * markup;  // pour regrouper les caractéristiques et le format

    // initialisation du label
    l->Label = gtk_label_new(NULL);

    /*   <span background-color=\"%s\"></ span> */

    // format du texte
    format = "<span style=\"%s\"><span font-size=\"%s\"><span font-family=\"%s\"><span font-weight=\"%s\"><span color=\"%s\"><span underline=\"%s\"><span underline_color=\"%s\"><span strikethrough=\"%s\"><span strikethrough_color=\"%s\">%s</span></span></span></span></span></span></span></span></span>";

    /*  l->lab.background,*/

    // association des caractéristique aux codes format
    markup = g_markup_printf_escaped(format, l->lab.style, l->lab.size, l->lab.font, l->lab.weight, l->lab.color, l->lab.underline, l->lab.underline_color, l->lab.barrer_txt, l->lab.color_bar, l->texte);

    // choix d'alignement
    switch (l->lab.alignement)
    {
        case 0:
            gtk_label_set_justify(GTK_LABEL(l->Label), GTK_JUSTIFY_LEFT);
            break;
        case 1:
            gtk_label_set_justify(GTK_LABEL(l->Label), GTK_JUSTIFY_RIGHT);
            break;
        case 2:
            gtk_label_set_justify(GTK_LABEL(l->Label), GTK_JUSTIFY_CENTER);
            break;
        case 3:
            gtk_label_set_justify(GTK_LABEL(l->Label), GTK_JUSTIFY_FILL);
    }

    // selection du texte
    if (l->lab.select == '0')
        gtk_label_set_selectable(GTK_LABEL(l->Label), FALSE);
    if (l->lab.select == '1')
        gtk_label_set_selectable(GTK_LABEL(l->Label), TRUE);

    // convertir le texte en utf8
    markup = g_locale_to_utf8(markup, -1, NULL, NULL, NULL);

    // association du texte avec le label
    gtk_label_set_markup(GTK_LABEL(l->Label), markup);

    // liber le pointeur markup
    g_free(markup);
}

