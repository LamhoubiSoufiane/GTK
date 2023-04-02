#include<gtk/gtk.h>
#include<libxml/parser.h>
#include<libxml/tree.h>
#include <stdio.h>
#include<stdlib.h>
#include"Fenetre.h"
#include"Menu.h"
#include"Box.h"
#include"ButtonSimple.h"
#include"Combobox.h"
#include"LectureFichierXml.h"

//#include"MacroSupp.h"

/*
Fenetre *Parcourir_Arbre_Xml(xmlNodePtr root)
{
    Fenetre* fn;
    xmlNodePtr noeud;
    xmlNodePtr fils;
    int haut=0;
    int larg=0;
    int px=0;
    int py=0;
    int titlbr=0;
    char *tit=NULL;
    char *sstit=NULL;
    char *ic=NULL;
    int red=0;
    int id=0;
    gchar* id_str=NULL;
    gchar* name = (gchar*)malloc(sizeof(gchar));
    gchar* name_prop = (gchar*)malloc(sizeof(gchar));
    gchar* content = (gchar*)malloc(sizeof(gchar));
    for (noeud = root->children; (noeud != NULL); noeud = noeud->next)
    {
        if ((noeud->type == XML_ELEMENT_NODE) && (!strcmp((gchar*)noeud->name, "object")))
        {
            name = (gchar*)xmlGetProp(noeud, (xmlChar*)"classe");
            printf("\n%s", name);
            if (!strcmp(name, "Fenetre"))
            {
                id_str = (gchar*)xmlGetProp(noeud, (xmlChar*)"id");
                id = atoi(id_str);
                // Str->Info.Mafenetre=Init_Default_Fenetre();
                for (fils = noeud->children; (fils != NULL); fils = fils->next)
                {
                    if ((fils->type == XML_ELEMENT_NODE) && (!strcmp((gchar*)fils->name, "property")))
                    {
                        name_prop = (gchar*)xmlGetProp(fils, (xmlChar*)"name");
                        content = (gchar*)xmlNodeGetContent(fils);
                        if (!strcmp(name_prop, "Hauteur")) haut = atoi(content);
                        else if (!strcmp(name_prop, "Largeur"))  larg = atoi(content);
                        else if (!strcmp(name_prop, "PositionX"))  px = atoi(content);
                        else if (!strcmp(name_prop, "PositionY"))  py = atoi(content);
                        else if (!strcmp(name_prop, "Redimensionnable"))
                        {
                            red = atoi(content);
                        }
                        else if (!strcmp(name_prop, "TitleBarre"))
                        {
                            titlbr = atoi(content);

                        }
                        else if (!strcmp(name_prop, "Titre")) tit = content;
                        else if (strcmp(name_prop, "SousTitre")) sstit = content;
                        else if (strcmp(name_prop, "Icone")) ic = content;
                    }
                    fn = Init_Personnalise_Fenetre(haut, larg, red, px, py,1, 1, tit, sstit, "yellow", ic);
                    return((Fenetre*)fn);

                }
            }
        }
    }
}*/


int main(int argc, char* argv[])
{
    /*<Box id="11" Espace="0" Type="1" Couleur="yellow">	
		</Box>*/
    gtk_init(&argc, &argv);
    Mastructure *str = NULL;
    str = Lirefichier();
    printf("\n%s", str->Fils->Fils->Information.Monbutton->Nom);
    //test(str);
    //printf("\n%s", str->Information.Mafenetre->Titre);
    Creer_Fenetre(str->Information.Mafenetre);
    /******F E N E T R E ************/
    /*Fenetre* fn;
    fn = Init_Personnalise_Fenetre(700, 700, 1, 1, 1, 1, 1, "Window", "", "yellow", "");
    Creer_Fenetre(fn);*/
    /******M E N U *********/
    /*Menu* m;
    m = Init_Barre_Menu(2);
    creer_menu(m, "file", "folder-new");
    creer_menu(m, "Edit", "document-edit");
    creer_menu(m, "About", "help-about");
    creer_sous_menu(fn, m, "share", "file", "document-save", 's');
    creer_sous_menu(fn, m, "aaa", "Edit", "document-save-as", 'a');
    creer_sous_menu(fn, m, "bbb", "Edit", "document-send", '0');
    creer_sous_menu(fn, m, "ccc", "Edit", "edit-copy", 'c');
    creer_sous_menu(fn, m, "ddd", "About", "edit-cut", 'd');
    creer_sous_menu(fn, m, "eee", "About", "edit-delete", 'e');
    creer_sous_menu(fn, m, "xxx", "bbb", "mail-send", '0');
    creer_sous_menu(fn, m, "yyy", "bbb", "media-eject", 'y');
    creer_sous_menu(fn, m, "zzz", "bbb", "window-new", 'z');
    creer_sous_menu(fn, m, "www", "xxx", "window-close", 'w');
    Ajouter_Elem_Au_Fixed(fn, m->ElemMenu, 200, 400);*/
    /******B U T T O N  *********/
    /*Button *btn;
    btn = Init_Button_Simple("_OOk", NULL, 300, 800, 40, 80, 1);
    Creer_Button_Simple(fn, btn);*/
    /*******C O M B O B O X *******/
    /*Combobox* cmb;
    cmb = Init_Combobox(100, 200, 30, 60, FALSE);
    Ajouter_Elem_Combobox(cmb, "elem1", 1);
    Ajouter_Elem_Combobox(cmb, "elem2", 2);
    Ajouter_Elem_Combobox(cmb, "elem3", 3);
    Ajouter_Elem_Combobox(cmb, "elem4", 4);

    Ajouter_Elem_Au_Fixed(fn, cmb->combo, cmb->pox.posX, cmb->pox.posY);*/


    Afficher_Fenetre(str->Information.Mafenetre);
    gtk_main();

}


