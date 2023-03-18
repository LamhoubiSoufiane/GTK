#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdio.h>

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
    char select;              // 0:non ou 1:oui
    char alignement;          // 0:left,1:right,2:center, ou 3:fill

} Format;

typedef struct
{
    GtkWidget *Label; /// pointeur sur le label
    char texte[255];  /// le texte à afficher
    Format lab;       // formatage du texte

} MonLabel;

typedef struct
{
    GtkWidget *monbox;
    gint espace; // Espace entre les elems du box
    char type;   // GtkHBox;GtkVBox;GtkActionBar,GtkButtonBox...
    GdkRGBA *Color;

} Box;

typedef struct
{
    GtkWidget *monfixed;
    GtkWidget *container;

} Fixed;

/************************* F I X E D **********************/

Fixed *Init_Fixed(GtkWidget *container)
{
    Fixed *f = NULL;
    f = (Fixed *)malloc(sizeof(Fixed));
    if (!f)
    {
        printf("\nErreur d allocation[fixed]");
        exit(0);
    }
    f->monfixed = gtk_fixed_new();
    f->container = container;
    return ((Fixed *)f);
}

void Creer_Fixed(Fixed *f, GtkWidget *cnt, GtkWidget *item, gint x, gint y)
{
    // if(gtk_widget_get_parent(f->monfixed) != NULL) gtk_widget_unparent(f->monfixed);
    // f->monfixed = gtk_fixed_new();
    gtk_fixed_put(GTK_FIXED(f->monfixed), item, x, y);
    gtk_container_add(GTK_CONTAINER(f->container), f->monfixed);
}

/***************************L A B E L********************************************/

void init_label(MonLabel *l)
{

    strcpy(l->texte, "\n bonjour tout le monde \n how are you  ");
    strcpy(l->lab.background, "yellow");
    strcpy(l->lab.color, "black");
    strcpy(l->lab.barrer_txt, "false");
    strcpy(l->lab.color_bar, "black");
    strcpy(l->lab.font, "calibri"); // police
    strcpy(l->lab.size, "large");
    strcpy(l->lab.underline, "none");
    strcpy(l->lab.underline_color, "black");
    strcpy(l->lab.style, "italic");
    strcpy(l->lab.weight, "bold");
    l->lab.alignement = '3';
    l->lab.select = '1';
}

void creer_label(MonLabel *l)
{
    char *format, // ce pointeur est pour le formatage du texte
        *markup;  // pour regrouper les caractéristiques et le format

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

/**************************CLOSE_BUTTON*************************************/

void on_close_button_clicked(GtkButton *button, gpointer data)
{
    GtkWidget *label = GTK_WIDGET(data);
    gtk_widget_hide(label);
}

/***********************************MAIN*********************************************/

int main(int argc, char *argv[])
{

    gtk_init(&argc, &argv);

    MonLabel lb;

    init_label(&lb);
    creer_label(&lb);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    GtkWidget *F = gtk_fixed_new();

    gtk_container_add(GTK_CONTAINER(window), F);
    gtk_fixed_put(GTK_FIXED(F), lb.Label, 100, 100);

    // set fixed color DOESN'T WORK !!!
    /*
        GdkRGBA C;

        gdk_rgba_parse(&C, "black");

        gtk_widget_override_color(F, GTK_STATE_NORMAL, &C);

    */

    GtkWidget *close_button = gtk_button_new_from_icon_name("window-close", GTK_ICON_SIZE_BUTTON);
    g_signal_connect(close_button, "clicked", G_CALLBACK(on_close_button_clicked), window);
    gtk_fixed_put(GTK_FIXED(F), close_button, 200, 50);

    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}