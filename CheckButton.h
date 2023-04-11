#pragma once

typedef struct L
{
    GtkWidget* btn;//Variable pour le bouton
    int idelm;
    int  mnemonic;//determiner si le bouton est avec mnemonic ou non
    char Nom[26];//tableau de 26 caractères pour le nom du bouton
    char NomIcone[26];//tableau de 26 caractères pour l'icone du bouton
    int activate;// entier pour activer le checkbutton
    struct L *svt; //suivant
}Liste_Check;//Nom de la structure

typedef struct
{
    int id;
    Liste_Check *Liste;
    Taille T;//taille du button
    Position P;//position du button
}L_CkButtons; //nom de la liste des checkbuttons

Liste_Check *Init_Cellule_checkbtn(int id,char *nom, char* icone,  int mnemonic,
                                   int activate)
{
    Liste_Check *Nv=(Liste_Check*)malloc(sizeof (Liste_Check));
    if(!Nv)
    {
        printf("\nErreur d allocation [init_cellule_checkbtn]");
        exit(0);
    }
    Nv->idelm=id;
    Nv->mnemonic = mnemonic;
    strcpy(Nv->Nom, nom);
    if(!strcmp(icone,"NULL")) icone=NULL;
    else strcpy(Nv->NomIcone, icone);		 //Initialiser le nom de l'icone
    Nv->activate = activate;

    //Initialiser le conteur du button
    Nv->svt=NULL;
    return ((Liste_Check*)Nv);
}

L_CkButtons *Init_Check_Button(int id,char *nom, char* icone,  int mnemonic,
                               int activate,int xpos, int ypos, int h, int l)
{
    L_CkButtons *Btn=(L_CkButtons*) malloc(sizeof (L_CkButtons));
    if(!Btn)
    {
        printf("\nErreur d allocation [Init_Check_Button]");
        exit(0);
    }
    Btn->id=id;
    Btn->Liste= Init_Cellule_checkbtn(id,nom,icone,mnemonic,activate);
    Btn->P.posX=xpos;
    Btn->P.posY=ypos;
    Btn->T.Hauteur=h;
    Btn->T.Largeur=l;
    return ((L_CkButtons*)Btn);
}

void Ajouter_Btn_Check(L_CkButtons *str,int id,char *nom, char* icone,  int mnemonic,
                       int activate)
{
    Liste_Check *nv,*ptr;
    if(!str)
    {
        printf("\nErreur str n existe pas![ajouter check btn]");
        exit(0);
    }
    nv= Init_Cellule_checkbtn(id,nom,icone,mnemonic,activate);

    if(!str->Liste)
    {
        str->Liste=nv;
    }
    else{
        ptr=str->Liste;
        while(ptr->svt) ptr=ptr->svt;
        ptr->svt=nv;
    }

}

void Creer_Btn_Check(Liste_Check *btn)
{
    if(!btn)
    {
        printf("\nErreur btn n existe pas[creer_btn_check]");
        exit(0);
    }
        if (btn->mnemonic)
            btn->btn= gtk_check_button_new_with_mnemonic(btn->Nom);
        else
            btn->btn = gtk_check_button_new_with_label(btn->Nom);
        if (btn->activate)
            gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(btn->btn), TRUE); // activer le checkbutton
        else
            gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(btn->btn), FALSE); // desactiver le checkbutton

}


