#pragma once
void Modifier_Couleur_widget(GtkWidget *widget,char *color)
{
    GdkRGBA C;
    gdk_rgba_parse(&C,color);
    gtk_widget_override_background_color(widget,GTK_STATE_NORMAL,&C);
}


