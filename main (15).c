///************************************************MAIN***********************************************************************
#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include "sdd.h"
#include "Macro.h"
#include "callbacks.h"
static void activate (GtkApplication* app,gpointer user_data)
{
/******************************** D E C L A R A T I O N * D E S * V A R I A B L E S ************************************/
    Fenetre *window,*w;
    scrollWindow*s;
    Icone *I;
    FIXED *zone;
    zone=init_fixed();
    Box *B1;
    B1=Creer_Box(12,300);
    Box *B2;
    B2=Creer_Box(12,300);
    Image* ilisi;
    Button* play;
//    ToolBar*T;
/********************************************** W I N D O W ************************************************************/
    window=init_window(0,0,700,1350,"Gtk intro-page","intro");
    window=create_window(app,window);
    w=init_window(0,0,700,1300,"Gtk interface","interface");
    w=create_window(app,w);
    s=initi_scrollwindow(NULL,0,0,0);
    s=create_scrollwindow(s);

/*************************************** bouton simple **********************************************************/
    play=initialise_simple_button("play","Play",FALSE,NULL);
    play=Creer_Button(play);
/************************************** IMAGE **********************************************************/
    ilisi=Image_init("logo.jpg",1,1);
    ilisi=Image_create(ilisi);
/************************************** TOOLBAR *********************************************************/
TOOLbar *Toolbar;
    GtkToolItem *it;
    Toolbar=initi_toolbar(GTK_TOOLBAR_ICONS,1,'v');
    create_toolbar(Toolbar);
    GtkToolItem *info,*quit;
    gtk_widget_set_size_request(Toolbar->toolbar ,40,100);
    info=creer_toolitem(Toolbar,1,"help-faq",NULL);
    quit=creer_toolitem(Toolbar,3,"window-close",NULL);
    creer_fixed(0,0,zone,Toolbar->toolbar,NULL);
    gtk_widget_set_name(Toolbar->toolbar,"tool");
    void shutdown()
    {
        g_application_quit(G_APPLICATION(app));
    }
    g_signal_connect(G_OBJECT(quit), "clicked",G_CALLBACK(shutdown), NULL);

/***************************************** FIXED ************************************************************/
    creer_fixed(955,525,zone,play->MonBoutton,NULL);
    creer_fixed(70,10,zone,ilisi->image,NULL);
/********************************** C S S   B E U T I F Y I N G ****************************************/
    style(window->Mafenetre,window->name);
    style(play->MonBoutton,play->name);
    style(Toolbar->toolbar,"tool");
/************************************adding elements to containers ******************************************/
  g_signal_connect(play->MonBoutton, "clicked",G_CALLBACK(cb_create), NULL);
    gtk_container_add(GTK_CONTAINER (s->scrollWindow),zone->fixed);
    gtk_container_add (GTK_CONTAINER (window->Mafenetre), s->scrollWindow);
    gtk_widget_show_all (window->Mafenetre);
}





int main (int    argc,char **argv)
{
    GtkApplication *app;
    int status;

    app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
    g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
    status = g_application_run (G_APPLICATION (app), argc, argv);
    g_object_unref (app);

    return status;

}
