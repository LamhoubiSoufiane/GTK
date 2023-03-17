#include<gtk-3.0/gtk/gtk.h>
#include"TAILLEPOS999.h"

#ifndef SWITCH999_H
#define SWITCH999_H

typedef struct
{
    GtkWidget *sw;
    gboolean State;
}SwitchButton;

SwitchButton *Init_Switch(gboolean State)
{
    SwitchButton *swt;
    swt=(SwitchButton*)malloc(sizeof(SwitchButton));
    if(!swt)
    {
        printf("\nErreur switch button");
        exit(0);
    }
    swt->State=State;
    return((SwitchButton*)swt);
}

void Creer_Switchbutton(SwitchButton *sw)
{
    if(!sw)
    {
        printf("\nErreur Switch button n existe pas");
        exit(0);
    }
    sw->sw=gtk_switch_new();
    gtk_switch_set_active(GTK_SWITCH(sw->sw),sw->State);
}
#endif