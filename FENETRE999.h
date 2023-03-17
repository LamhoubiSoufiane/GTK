#include<gtk-3.0/gtk/gtk.h>
#include"TAILLEPOS999.h"

#ifndef FENETRE999_H
#define FENETRE999_H


typedef struct
{
    GtkWidget *fenetre;
    GtkWidget *TitleBar;
    GtkWidget *Ascenceurs;
    GtkWidget *Fixed;
    GtkAccelGroup *acc;
    int redimensionnable;
    Taille TailleFenetre;
    Position PosFenetre;// 0-0 :centre, 1-1 Position de la souris, 2-2 :Centrez la fen�tre sur son parent transitoire
    const char *Titre;
    const char *Sous_Titre;
    const char *Icone;
    GdkRGBA *C;
}Fenetre;



Fenetre *Init_Personnalise_Fenetre(int H, int L,int resizable,int posx, int posy,int titlebarre,const char *titre,const char *soustitre,
                                    const char *couleur,gboolean Scroll)
{
    Fenetre *fn;
    fn=(Fenetre*)malloc(sizeof(Fenetre));
    if(!fn)
    {
        printf("\nErreur d allocation[Fenetre]");
        exit(0);
    }
    fn->redimensionnable=resizable;
    fn->TailleFenetre.Hauteur=H;
    fn->TailleFenetre.Largeur=L;
    fn->PosFenetre.posX=posx;
    fn->PosFenetre.posY=posy;
    fn->Titre=(const char*)malloc(sizeof(const char));
    fn->Sous_Titre=(const char*)malloc(sizeof(const char));
    fn->Titre=titre;
    fn->Sous_Titre=soustitre;
    if(Scroll) fn->Ascenceurs=gtk_scrolled_window_new(NULL, NULL);
    else fn->Ascenceurs= NULL;
    if(titlebarre) fn->TitleBar=(GtkWidget*)malloc(sizeof(GtkWidget));
    else fn->TitleBar=NULL;
    fn->C=(GdkRGBA*)malloc(sizeof(GdkRGBA));
    gdk_rgba_parse(fn->C,couleur);
    fn->Fixed=gtk_fixed_new();
    fn->acc=gtk_accel_group_new();
    return((Fenetre*)fn);
}

void Creer_Fixed(Fenetre *fn,GtkWidget *elem,gint x,gint y)
{
    gtk_fixed_put(fn->Fixed,elem,x,y);
    // gtk_container_add(fn->fenetre,fn->Fixed);
}
void Creer_Fenetre(Fenetre *fn)
{
    if(!fn)
    {
        printf("\nErreur fenetre n existe pas!!");
        exit(0);
    }
    fn->fenetre=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    if(fn->redimensionnable) gtk_window_set_resizable(GTK_WINDOW(fn->fenetre),TRUE);
    else gtk_window_set_resizable(GTK_WINDOW(fn->fenetre),FALSE);
    gtk_window_activate_default (GTK_WINDOW(fn->fenetre));
    gtk_window_set_default_size (GTK_WINDOW(fn->fenetre),fn->TailleFenetre.Largeur,fn->TailleFenetre.Hauteur);

        switch(fn->PosFenetre.posX)
        {
            case 0 : gtk_window_set_position(GTK_WINDOW(fn->fenetre),GTK_WIN_POS_CENTER);
                    break;
            case 1 : gtk_window_set_position(GTK_WINDOW(fn->fenetre),GTK_WIN_POS_MOUSE);
                    break;
            case 2 : gtk_window_set_position(GTK_WINDOW(fn->fenetre),GTK_WIN_POS_CENTER_ON_PARENT);
                    break;
            default : gtk_window_move (GTK_WINDOW(fn->fenetre),fn->PosFenetre.posX,fn->PosFenetre.posY);
                    break;
        }

    if(fn->TitleBar)
    {
        fn->TitleBar=gtk_header_bar_new();
        gtk_header_bar_set_title (GTK_HEADER_BAR(fn->TitleBar), fn->Titre);
        if(fn->Sous_Titre) gtk_header_bar_set_subtitle (GTK_HEADER_BAR(fn->TitleBar),fn->Sous_Titre);
        gtk_window_set_titlebar(GTK_WINDOW(fn->fenetre),fn->TitleBar);
        gtk_header_bar_set_show_close_button(GTK_HEADER_BAR(fn->TitleBar),TRUE);
    }
    else gtk_window_set_title (GTK_WINDOW(fn->fenetre), fn->Titre);
    if(fn->C) gtk_widget_override_background_color(fn->fenetre,GTK_STATE_NORMAL,fn->C);
    if(fn->Ascenceurs)
    {
        gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(fn->Ascenceurs),GTK_POLICY_ALWAYS, GTK_POLICY_ALWAYS);
        gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW(fn->Ascenceurs),GTK_SHADOW_NONE);
        gtk_container_add(GTK_CONTAINER(fn->Ascenceurs),fn->Fixed);
        
    }
    gtk_window_add_accel_group(GTK_WINDOW(fn->fenetre),fn->acc);
}
#endif
