#pragma once



typedef union
{
    Fenetre *Mafenetre;
    Menu *MonMenu;
    Box *Monbox;
    Button *Monbutton;
    Combobox *MonCombo;
    Mongrid *Gr;
    MonLabel *Lab;
    Entry *Zonetxt;
    Frame *fr;
    RadioButton *RadBtn;
    L_CkButtons *ChkBtn;
    Toggle_Button *Tgbutton;
    BDialogue *BD;
}MonUnion;



typedef struct cel
{
    MonUnion Information;
    int TypeInfo;
    struct cel* Frere;
    struct cel* Fils;
}Mastructure;

void Ajouter_Au_Frame(Mastructure *str);

Mastructure *Creer_Init_Cellule_Mastructure(MonUnion Inf,int TypeUnion)
{
    Mastructure* Nvstr;
    Nvstr = (Mastructure*)malloc(sizeof(Mastructure));
    if (!Nvstr)
    {
        printf("\nErreur d allocation [Mastructure]!!");
        exit(0);
    }
    Nvstr->Information = Inf;
    Nvstr->TypeInfo = TypeUnion;
    Nvstr->Fils =NULL;
    Nvstr->Frere = NULL;
    return((Mastructure*)Nvstr);
}


/*
Nom         : Ajouter_Elem_Au_Box
Entree      : Un box et un element
Sortie      : Element ajouté au box
Description : Fonction permet d'ajouter un element dans un box
*/

void Add_Elems_Box(Mastructure *str)
{
    Mastructure* ptr = NULL;
    Position p;
    Ent_Rbn *ptr2=NULL;
    Liste_Check *ptr3=NULL;
    //Afficher un message et quitter si le box n'existe pas
    if (!str)
    {
        printf("\nErreur, box n existe pas [ajouter elem au box]");
        exit(0);
    }
    ptr = str->Fils;
    while (ptr)
    {
        switch (ptr->TypeInfo)
        {
            case 4 :
                gtk_container_add(GTK_CONTAINER(str->Information.Monbox->monbox),ptr->Information.fr->Fr);
                p=ptr->Information.fr->p;
                break;
            case 5: gtk_box_pack_start(GTK_BOX(str->Information.Monbox->monbox),
                                       ptr->Information.Monbutton->btn, TRUE, TRUE,
                                       str->Information.Monbox->espace);
                p = ptr->Information.Monbutton->p;
                break;
            case 6:
                ptr2=ptr->Information.RadBtn->ListeRbtn;
                while(ptr2) {
                    gtk_box_pack_start(GTK_BOX(str->Information.Monbox->monbox),
                                       ptr2->button, TRUE, TRUE,
                                       str->Information.Monbox->espace);
                    ptr2 = ptr2->Svt;
                }
                p = ptr->Information.RadBtn->pos;
                break;
            case 7:ptr3=ptr->Information.ChkBtn->Liste;
                while(ptr3) {
                    Creer_Btn_Check(ptr3);
                    gtk_box_pack_start(GTK_BOX(str->Information.Monbox->monbox),
                                       ptr3->btn, TRUE, TRUE,
                                       str->Information.Monbox->espace);
                    ptr3 = ptr3->svt;
                }
                p = ptr->Information.ChkBtn->P;
                break;
            case 8:
                gtk_box_pack_start(GTK_BOX(str->Information.Monbox->monbox),
                                   ptr->Information.Tgbutton->toggle_button, TRUE, TRUE,
                                   str->Information.Monbox->espace);
                p = ptr->Information.Tgbutton->p;
                break;
            case 9: gtk_box_pack_start(GTK_BOX(str->Information.Monbox->monbox),
                                       ptr->Information.Lab->Label, TRUE, TRUE,
                                       str->Information.Monbox->espace);
                p = ptr->Information.Lab->pos;
                break;
            case 10:
                gtk_box_pack_start(GTK_BOX(str->Information.Monbox->monbox),
                                   ptr->Information.Zonetxt->entry, TRUE, TRUE,
                                   str->Information.Monbox->espace);
                p = ptr->Information.Zonetxt->p;
                break;
            case 13:gtk_box_pack_start(GTK_BOX(str->Information.Monbox->monbox),
                                       ptr->Information.MonCombo->combo, TRUE, TRUE,
                                       str->Information.Monbox->espace);
                p = ptr->Information.MonCombo->pox;
                break;

            default:printf("\nErreur, typeinfo [Ajouter_Elems_Au_box]");
                exit(0);
        }
        ptr = ptr->Frere;
    }
    str->Information.Monbox->p = p;
}

void Add_Elems_Fixed(Mastructure *str)
{
    Mastructure *ptr = NULL;
    if (!str)
    {
        printf("\nErreur, fenetre n existe pas[ajouter_Elems_Au_fixed]");
        exit(0);
    }
    ptr = str->Fils;
    while (ptr)
    {
        switch (ptr->TypeInfo)
        {
            case 1: //Ajouter elem au fixed de la fenetre fn à la position x et y
                gtk_fixed_put(GTK_FIXED(str->Information.Mafenetre->Fixed),
                              ptr->Information.Monbox->monbox,
                              ptr->Information.Monbox->p.posX,
                              ptr->Information.Monbox->p.posY);
                break;
            case 3:gtk_fixed_put(GTK_FIXED(str->Information.Mafenetre->Fixed),
                                 ptr->Information.MonMenu->ElemMenu,
                                 ptr->Information.MonMenu->p->posX,
                                 ptr->Information.MonMenu->p->posY);
                break;
            case 4:gtk_fixed_put(GTK_FIXED(str->Information.Mafenetre->Fixed),
                                 ptr->Information.fr->Fr,
                                 ptr->Fils->Information.Monbox->p.posX,
                                 ptr->Fils->Information.Monbox->p.posX);
                break;
            default:printf("\nErreur, typeinfo [Ajouter_Elems_Au_box]");
                exit(0);
        }
        ptr = ptr->Frere;
    }
}
void Ajouter_Au_Frame(Mastructure *str)
{
    Mastructure *ptr = NULL;
    if(!str)
    {
        printf("\nErreur,str n existe pas[ajouter_au_frame]");
        exit(0);
    }
    if(!str->Fils)
    {
        printf("\nErreur,fils n existe pas[ajouter_au_frame]");
        exit(0);
    }
    ptr=str->Fils;
    while (ptr)
    {
        switch (ptr->TypeInfo)
        {
            case 1:
                gtk_container_add(GTK_CONTAINER(str->Information.fr->Fr),ptr->Information.Monbox->monbox);
                break;
            case 2:gtk_container_add(GTK_CONTAINER(str->Information.fr->Fr),ptr->Information.Gr->grid);
                break;
            default:printf("\nErreur, typeinfo [Ajouter_Elems_Au_box]");
                exit(0);
        }
        ptr = ptr->Frere;
    }
}