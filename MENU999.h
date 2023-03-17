#include<gtk-3.0/gtk/gtk.h>

#ifndef MENU999_H
#define MENU999_H

void test(GtkWidget *f,gpointer data)
{
    printf("\nBoutt");
}

typedef struct Mn
{
    GtkWidget *MenuItems;
    GtkWidget *menu;
    GtkWidget *icc;
    int TypeBarremenu; 
    char mnemonic;
    const char *Icone;
    const char *Nom;
    struct Mn *MenuFrere;
    struct Mn *MenuFils;
}Menu;

Menu *Init_Menu(int barre,int type) //type est ce que barre ou menuitem
{
    Menu *m;
    m=(Menu*)malloc(sizeof(Menu));
    if(!m)
    {
        printf("\nErreur d allocation[menu]");
        exit(0);
    }
    if(type)
    {   
        m->MenuItems=gtk_menu_bar_new();
        switch(barre)
        {
        case 0 : gtk_menu_bar_set_pack_direction(GTK_MENU_BAR(m->MenuItems),GTK_PACK_DIRECTION_LTR);
                break;
        case 1 : gtk_menu_bar_set_pack_direction(GTK_MENU_BAR(m->MenuItems),GTK_PACK_DIRECTION_RTL);
                break;
        case 2 : gtk_menu_bar_set_pack_direction(GTK_MENU_BAR(m->MenuItems),GTK_PACK_DIRECTION_TTB);
                break;
        case 3 : gtk_menu_bar_set_pack_direction(GTK_MENU_BAR(m->MenuItems),GTK_PACK_DIRECTION_BTT);
                break;
        default : printf("\nErreur barre menu");
                    exit(0);
        }
    }
    m->menu=NULL;
    m->Nom=NULL;
    m->MenuFrere = m->MenuFils = NULL;
    m->Icone=NULL;
    m->icc=NULL;
    m->TypeBarremenu=barre;
    return((Menu*)m);
}

Menu *creer_menu(Menu *m,const char *menu,const char *Ic)
{
    Menu *nvm;
    Menu *ptr=m;
    while(ptr->MenuFrere) ptr=ptr->MenuFrere;
    nvm=Init_Menu(0,0);
    nvm->MenuItems=NULL;
    nvm->menu=gtk_menu_new();
    nvm->Nom=(const char*)malloc(sizeof(const char));
    nvm->Icone=(const char*)malloc(sizeof(const char));
    nvm->Icone=Ic;
    nvm->Nom=menu;
    if(Ic)
    {
        nvm->MenuItems=gtk_image_menu_item_new_with_mnemonic(menu);
        nvm->icc=gtk_image_new_from_icon_name(Ic,GTK_ICON_SIZE_MENU);
        gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(nvm->MenuItems),nvm->icc);
        gtk_image_menu_item_set_always_show_image(GTK_IMAGE_MENU_ITEM(nvm->MenuItems),TRUE);
    }
    else nvm->MenuItems=gtk_menu_item_new_with_label(menu);
    gtk_menu_shell_append(GTK_MENU_SHELL(m->MenuItems),nvm->MenuItems);
    ptr->MenuFrere=nvm;
    return((Menu*)m);
}

void creer_sous_menu(Fenetre *fn,Menu *m,const char *sous_menu,const char *menupere,const char *Ic,
                                            char Caractere_mnemonic)
{
    Menu *nvm;
    Menu *ptr;
    if(m)
    {
        if((m->Nom) && (!strcmp(m->Nom,menupere)))
        {
            nvm=Init_Menu(0,0);
            nvm->MenuItems=NULL;
            nvm->menu=gtk_menu_new();
            nvm->MenuItems=gtk_menu_item_new_with_label(sous_menu);
            if(Ic)
            {
                nvm->Icone=(const char*)malloc(sizeof(const char));
                nvm->Icone=Ic;
                nvm->MenuItems=gtk_image_menu_item_new_with_mnemonic(sous_menu);
                nvm->icc=gtk_image_new_from_icon_name(Ic,GTK_ICON_SIZE_MENU);
                gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(nvm->MenuItems),nvm->icc);
                gtk_image_menu_item_set_always_show_image(GTK_IMAGE_MENU_ITEM(nvm->MenuItems),TRUE);
            }
            nvm->Nom=(const char*)malloc(sizeof(const char));
            nvm->Nom=sous_menu;
            if(!m->MenuFils) m->MenuFils=nvm;
            else
                {
                    ptr=m->MenuFils;
                    while(ptr->MenuFrere) ptr=ptr->MenuFrere;
                    ptr->MenuFrere=nvm;
                }
                nvm->mnemonic=Caractere_mnemonic;
                if(Caractere_mnemonic != '0') gtk_widget_add_accelerator(nvm->MenuItems,"activate",fn->acc,(int)Caractere_mnemonic,GDK_CONTROL_MASK,GTK_ACCEL_VISIBLE);
                g_signal_connect(nvm->MenuItems,"activate",G_CALLBACK(test),NULL); ///JUSTE POUR LE TEST !!!!
                gtk_menu_shell_append(GTK_MENU_SHELL(m->menu),nvm->MenuItems);
                gtk_menu_item_set_submenu(GTK_MENU_ITEM(m->MenuItems), m->menu);
                return;
            }
            creer_sous_menu(fn,m->MenuFils,sous_menu,menupere,Ic,Caractere_mnemonic);
            creer_sous_menu(fn,m->MenuFrere,sous_menu,menupere,Ic,Caractere_mnemonic);
        }
    }

#endif
