#include<gtk-3.0/gtk/gtk.h>
#include"FENETRE999.h"

#ifndef FCT_SUPP_H
#define FCT_SUPP_H


void Modifier_Couleur_Widget(GtkWidget *Monwidget,const gchar *couleur)
{
    GdkRGBA c;
    gdk_rgba_parse(&c,couleur);
    gtk_widget_override_background_color(Monwidget,GTK_STATE_NORMAL,&c);
}

void Afficher_Fenetre(Fenetre *fn)
{
    if(!fn || !fn->fenetre)
    {
        printf("\nErreur fenetre n existe pas[ajouter fixed fenetre]");
        exit(0);
    }
    if(!fn->Fixed) 
    {
        printf("\nErreur fixed n existe pas [ajouter fixed fenetre]");
        exit(0);
    }
    if(fn->Ascenceurs) gtk_container_add(GTK_CONTAINER(fn->fenetre),fn->Ascenceurs);
    else gtk_container_add(GTK_CONTAINER(fn->fenetre),fn->Fixed);
    gtk_widget_show_all(fn->fenetre);
}

#endif