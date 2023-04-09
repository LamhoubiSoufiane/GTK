#pragma once
#include "StructFich.h"



Mastructure *Inserer_Fenetre(Mastructure *str, Mastructure *nv)
{
    Mastructure *ptr = NULL;
    if (!nv)
    {
        printf("\nLa nouvelle fenetre a inseree n existe pas !! [Inserer_Fenetre]");
        exit(0);
    }
    if (!str) return((Mastructure*)nv);
    ptr = str;
    while (ptr->Frere) ptr = ptr->Frere;
    ptr->Frere = nv;
    return((Mastructure*)str);
}



Mastructure* Traitement_Combobox(Mastructure* box, xmlNodePtr child)
{
    Mastructure* combo, * ptr = NULL;
    MonUnion Info;
    xmlNodePtr Elmcb;
    if (!box)
    {
        printf("\nErreur, box n existe pas[Traitement_Combobox]!!");
        exit(0);
    }
    Info.MonCombo = Init_Combobox(atoi((char*)xmlGetProp(child, "id")),
                                  atoi((char*)xmlGetProp(child, "PositionX")),
                                  atoi((char*)xmlGetProp(child, "PositionY")),
                                  atoi((char*)xmlGetProp(child, "Hauteur")),
                                  atoi((char*)xmlGetProp(child, "Largeur")),
                                  atoi((char*)xmlGetProp(child, "Entry")));
    combo = Creer_Init_Cellule_Mastructure(Info,13);
    for (Elmcb = child->children; Elmcb != NULL; Elmcb = Elmcb->next)
    {
        if (Elmcb->type == XML_ELEMENT_NODE)
        {
            if (!strcmp(Elmcb->name, "Elem")) Ajouter_Elem_Combobox(combo->Information.MonCombo,
                                                                    (char*)xmlGetProp(Elmcb, "Nom"),
                                                                    atoi((char*)xmlGetProp(Elmcb, "id")));
            else
            {
                printf("\nErreur, Format fichier invalide [elems du combobox]");
                exit(0);
            }
        }
    }
    if (box->Fils)
    {
        ptr = box->Fils;
        while (ptr->Frere) ptr = ptr->Frere;
        ptr->Frere = combo;
    }
    else box->Fils = combo;
    return((Mastructure*)box);
}

Mastructure* Traitement_Label(Mastructure* box, xmlNodePtr child)
{
    Mastructure* lb, * ptr = NULL;
    MonUnion Info;
    if (!box)
    {
        printf("\nErreur, box n existe pas[Traitement_ButtonSimple]!!");
        exit(0);
    }
    Info.Lab = Init_label(atoi((char*)xmlGetProp(child, "id")),
                          (char*)xmlGetProp(child, "Text"),
                          (char*)xmlGetProp(child, "Back_Color"),
                          (char*)xmlGetProp(child, "Text_Color"),
                          (char*)xmlGetProp(child, "Barrer_Text"),
                          (char*)xmlGetProp(child, "Barre_Color"),
                          (char*)xmlGetProp(child, "Font"),
                          (char*)xmlGetProp(child, "Size"),
                          (char*)xmlGetProp(child, "Underline"),
                          (char*)xmlGetProp(child, "Underline_Color"),
                          (char*)xmlGetProp(child, "Style_Text"),
                          (char*)xmlGetProp(child, "Weight"),
                          atoi((char*)xmlGetProp(child, "Select")),
                          atoi((char*)xmlGetProp(child, "Alignement")),
                          atoi((char*)xmlGetProp(child, "PositionX")),
                          atoi((char*)xmlGetProp(child, "PositionY")),
                          atoi((char*)xmlGetProp(child, "Hauteur")),
                          atoi((char*)xmlGetProp(child, "Largeur")));
    lb = Creer_Init_Cellule_Mastructure(Info,9);
    if (box->Fils)
    {
        ptr = box->Fils;
        while (ptr->Frere) ptr = ptr->Frere;
        ptr->Frere = lb;
    }
    else box->Fils = lb;
    return((Mastructure*)box);
}
Mastructure  *Traitement_Entry(Mastructure *box,xmlNodePtr child)
{
    Mastructure* En, * ptr = NULL;
    MonUnion Info;
    if (!box)
    {
        printf("\nErreur, box n existe pas[Traitement_ButtonSimple]!!");
        exit(0);
    }
    Info.Zonetxt= Init_Entry(atoi((char*)xmlGetProp(child, "id")),
                             atoi((char*)xmlGetProp(child, "Visibility")),
                             atoi((char*)xmlGetProp(child, "TailleCarac")),
                             atoi((char*)xmlGetProp(child, "Editable")),
                             (char*)xmlGetProp(child, "Text"),
                             atoi((char*)xmlGetProp(child, "Justnum")),
                             atoi((char*)xmlGetProp(child, "PositionX")),
                             atoi((char*)xmlGetProp(child, "PositionY")),
                             atoi((char*)xmlGetProp(child, "Hauteur")),
                             atoi((char*)xmlGetProp(child, "Largeur")));
    En= Creer_Init_Cellule_Mastructure(Info,10);
    if (box->Fils)
    {
        ptr = box->Fils;
        while (ptr->Frere) ptr = ptr->Frere;
        ptr->Frere = En;
    }
    else box->Fils = En;
    return((Mastructure*)box);
}
Mastructure* Traitement_ButtonSimple(Mastructure* box, xmlNodePtr child)
{
    Mastructure* button, * ptr = NULL;
    MonUnion Info;
    if (!box)
    {
        printf("\nErreur, box n existe pas[Traitement_ButtonSimple]!!");
        exit(0);
    }
    Info.Monbutton = Init_Button_Simple(atoi((char*)xmlGetProp(child, "id")),
                                        (char*)xmlGetProp(child, "Nom"),
                                        (char*)xmlGetProp(child, "Icone"),
                                        atoi((char*)xmlGetProp(child, "PositionX")),
                                        atoi((char*)xmlGetProp(child, "PositionY")),
                                        atoi((char*)xmlGetProp(child, "Hauteur")),
                                        atoi((char*)xmlGetProp(child, "Largeur")),
                                        atoi((char*)xmlGetProp(child, "Mnemonic")));
    button = Creer_Init_Cellule_Mastructure(Info,5);
    if (box->Fils)
    {
        ptr = box->Fils;
        while (ptr->Frere) ptr = ptr->Frere;
        ptr->Frere = button;
    }
    else box->Fils = button;
    return((Mastructure*)box);
}

Mastructure *Traitement_Grid(Mastructure* fen, xmlNodePtr fils)
{
    Mastructure* nvgr, * ptr = NULL;
    MonUnion Info;
    xmlNodePtr child;
    if (!fen)
    {
        printf("\nErreur, Fenetre n existe pas[Traitement_Box]!!");
        exit(0);
    }
    Info.Gr = Initier_grid(atoi((char*)xmlGetProp(fils, "id")),
                           atoi((char*)xmlGetProp(fils, "PositionX")),
                           atoi((char*)xmlGetProp(fils, "PositionY")),
                           atoi((char*)xmlGetProp(fils, "Largeur")),
                           atoi((char*)xmlGetProp(fils, "Hauteur")));
    nvgr = Creer_Init_Cellule_Mastructure(Info,2);
    for (child = fils->children; child != NULL; child = child->next)
    {
        if (child->type == XML_ELEMENT_NODE)
        {
            if (!strcmp(child->name, "Button")) nvgr = Traitement_ButtonSimple(nvgr, child);
            else if (!strcmp(child->name, "Combobox")) nvgr = Traitement_Combobox(nvgr, child);
            if (fen->Fils)
            {
                ptr = fen->Fils;
                while (ptr->Frere) ptr = ptr->Frere;
                ptr->Frere = nvgr;
            }
            else fen->Fils = nvgr;
        }

    }
    return((Mastructure*)fen);
}


Mastructure *Traitement_Menu(Mastructure *fen,xmlNodePtr fils)
{
    Mastructure *nvmenu,*ptr=NULL;
    MonUnion Info;
    xmlNodePtr child;
    Info.MonMenu= Init_Barre_Menu(atoi((char*)xmlGetProp(fils, "type")),
                                  atoi((char*)xmlGetProp(fils, "PositionX")),
                                       atoi((char*)xmlGetProp(fils, "PositionY")));
    for (child = fils->children; child != NULL; child = child->next)
    {
        if (child->type == XML_ELEMENT_NODE)
        {
            if(!strcmp(child->name,"Elem")) creer_menu(Info.MonMenu,
                                                       (char*) xmlGetProp(child,"Nom"),
                                                       (char*) xmlGetProp(child,"Icone"));
            else if(!strcmp(child->name,"Sous_Elem"))
                        creer_sous_menu(fen->Information.Mafenetre,
                                        Info.MonMenu,
                                        (char*) xmlGetProp(child,"Nom"),
                                        (char*) xmlGetProp(child,"MenuPere"),
                                        (char*) xmlGetProp(child,"Icone"),
                                        (char*) xmlGetProp(child,"Mnemonic"));
        }
    }
    nvmenu=Creer_Init_Cellule_Mastructure(Info,3);
    if(!fen->Fils) fen->Fils=nvmenu;
    else{
        ptr=fen->Fils;
        while(ptr->Frere) ptr=ptr->Frere;
        ptr->Frere=nvmenu;
    }
    return ((Mastructure*)fen);
}

Mastructure *Traitement_Box(Mastructure* fen, xmlNodePtr fils)
{
    Mastructure* nvbox, * ptr = NULL;
    MonUnion Info;
    xmlNodePtr child;
    if (!fen)
    {
        printf("\nErreur, Fenetre n existe pas[Traitement_Box]!!");
        exit(0);
    }
    Info.Monbox = Init_Box(atoi((char*)xmlGetProp(fils, "id")),
                           atoi((char*)xmlGetProp(fils, "Espace")),
                           atoi((char*)xmlGetProp(fils, "Type")),
                           (char*)xmlGetProp(fils, "Couleur"));
    nvbox = Creer_Init_Cellule_Mastructure(Info,1);
    for (child = fils->children; child != NULL; child = child->next)
    {
        if (child->type == XML_ELEMENT_NODE)
        {
            if (!strcmp(child->name, "Button")) nvbox = Traitement_ButtonSimple(nvbox, child);
            else if (!strcmp(child->name, "Combobox")) nvbox = Traitement_Combobox(nvbox, child);
            else if (!strcmp(child->name, "Label")) nvbox = Traitement_Label(nvbox, child);
            else if(!strcmp(child->name, "Entry")) nvbox = Traitement_Entry(nvbox, child);
            else if(!strcmp(child->name, "Combobox")) nvbox = Traitement_Combobox(nvbox, child);
            if (fen->Fils)
            {
                ptr = fen->Fils;
                while (ptr->Frere) ptr = ptr->Frere;
                ptr->Frere = nvbox;
            }
            else fen->Fils = nvbox;
        }

    }
    return((Mastructure*)fen);
}

Mastructure *Traitement_Frame(Mastructure* Fr, xmlNodePtr child)
{
    Mastructure* F, * ptr = NULL;
    MonUnion Info;
    xmlNodePtr fils;
    if (!Fr)
    {
        printf("\nErreur, Frame n existe pas[Traitement_Frame]!!");
        exit(0);
    }
    Info.fr= Init_Frame(atoi((char*)xmlGetProp(child, "id")),
                        (char*)xmlGetProp(child, "Text"),
                        atoi((char*)xmlGetProp(child, "Xalign")),
                        atoi((char*)xmlGetProp(child, "Yalign")),
                        atoi((char*)xmlGetProp(child, "Shadow")),
                        (char*)xmlGetProp(child, "Color"));
    F = Creer_Init_Cellule_Mastructure(Info,4);
    for (fils = child->children; fils != NULL; fils = fils->next)
    {
        if (fils->type == XML_ELEMENT_NODE)
        {
            if(!strcmp(fils->name,"Box")) F=Traitement_Box(F,fils->children);
            else if(!strcmp(fils->name,"Grid")) F=Traitement_Grid(F,fils->children);
            else
            {
                printf("\nErreur, format invalide fichier [taitement frame]");
                exit(0);
            }
            if (Fr->Fils)
            {
                ptr = Fr->Fils;
                while (ptr->Frere) ptr = ptr->Frere;
                ptr->Frere = F;
            }
            else Fr->Fils = F;
        }
    }

    return((Mastructure*)Fr);
}


Mastructure* Lirefichier()
{
    xmlDocPtr doc;
    xmlNodePtr root;
    xmlNodePtr noeud;
    xmlNodePtr fils;
    Mastructure* nv, * str = NULL, * ptr = NULL;
    MonUnion Info;
    doc = xmlParseFile("source.xml");
    if (!doc)
    {
        printf("\nErreur. Impossible d ouvrir le fichier .Xml!!");
        exit(0);
    }
    root = xmlDocGetRootElement(doc);
    if (!root)
    {
        printf("\nErreur. Fichier Xml est vide !! ");
        exit(0);
    }
    for (noeud = root->children; (noeud != NULL); noeud = noeud->next)
    {
        if (noeud->type == XML_ELEMENT_NODE)
        {
            if (!strcmp(noeud->name, "Fenetre"))
            {

                Info.Mafenetre = Init_Personnalise_Fenetre(atoi((char*)xmlGetProp(noeud, "id")),
                                                           atoi((char*)xmlGetProp(noeud, "Hauteur")),
                                                           atoi((char*)xmlGetProp(noeud, "Largeur")),
                                                           atoi((char*)xmlGetProp(noeud, "redimensionnable")),
                                                           atoi((char*)xmlGetProp(noeud, "PositionX")),
                                                           atoi((char*)xmlGetProp(noeud, "PositionY")),
                                                           atoi((char*)xmlGetProp(noeud, "BarreTitre")),
                                                           atoi((char*)xmlGetProp(noeud, "Ascenceurs")),
                                                           (char*)xmlGetProp(noeud, "Titre"),
                                                           (char*)xmlGetProp(noeud, "Sous_Titre"),
                                                           (char*)xmlGetProp(noeud, "Couleur"),
                                                           (char*)xmlGetProp(noeud, "Icone"));
                nv = Creer_Init_Cellule_Mastructure(Info,0);
                str = Inserer_Fenetre(str, nv);
                for (fils = noeud->children; fils != NULL; fils = fils->next)
                {
                    if (fils->type == XML_ELEMENT_NODE)
                    {
                        if (!strcmp(fils->name, "Box")) str = Traitement_Box(str, fils);
                        else if (!strcmp(fils->name, "Grid")) str = Traitement_Grid(str, fils);
                        else if(!strcmp(fils->name,"Menu")) str=Traitement_Menu(str,fils);
                        else if(!strcmp(fils->name,"Frame")) str=Traitement_Frame(str,fils);
                    }

                }

            }
            else
            {
                printf("\nErreur. Format du fichier xml invalide!!");
            }

        }
    }
    return((Mastructure*)str);
}


void Traitement_Creation_Structure(Mastructure *str)
{
    if (!str)
    {
        printf("\nErreur, structure n existe pas[Traitement_Creation_Structure]");
        exit(0);
    }
    switch (str->TypeInfo)
    {
        case 0: Creer_Fenetre(str->Information.Mafenetre);
            Add_Elems_Fixed(str);
            break;
        case 1: Creer_Box(str->Information.Monbox);
            Add_Elems_Box(str);
            break;
        case 2: Creer_Grid(str->Information.Gr);
            break;
        case 3 :
            break;
        case 4 :
            Ajouter_Au_Frame(str);
            break;
        case 5: Creer_Button_Simple(str->Information.Monbutton);
            break;
        case 9: creer_label(str->Information.Lab);
            break;
        case 10:
            Creer_Entry(str->Information.Zonetxt);
            break;
        case 13 :
            break;
        default:printf("\nErreur, typeUnion[Traitement_Creation_Structure]");
            exit(0);
    }
}

void Creer_Mastructure(Mastructure* Str)
{
    if (Str)
    {
        Creer_Mastructure(Str->Fils);
        Creer_Mastructure(Str->Frere);
        Traitement_Creation_Structure(Str);
    }
}


