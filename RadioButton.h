#pragma once


typedef struct Rbtn
{
    GtkWidget *button;
    char *nom;
    struct Rbtn *Svt;
}Ent_Rbn;

typedef struct
{
    int Id;
    Ent_Rbn *ListeRbtn;
    Position pos;
    Taille t;
}RadioButton;

Ent_Rbn *Init_Creer_Ent_Rbn(char *nom)
{
    Ent_Rbn *btn;
    btn=(Ent_Rbn*)malloc(sizeof(Ent_Rbn));
    if(!btn)
    {
        printf("\nErreur d allocation memoire[Radiobutton]");
        exit(0);
    }
    if(nom)
    {
        btn->nom=(char*)malloc(sizeof(char));
        btn->nom=nom;
    }
    else btn->nom=NULL;
    btn->Svt=NULL;
    btn->button=NULL;
    return((Ent_Rbn*)btn);
}

RadioButton *Init_Radio_Button( int Id,char *nom,int xpos,int ypos,int hauteur,int largeur) // type : 0-> horizontal, 1-> vertical
{
    RadioButton *btn;
    btn=(RadioButton*)malloc(sizeof(RadioButton));
    if(!btn)
    {
        printf("\nErreur d allocation [Radiobutton]");
        exit(0);
    }
    btn->Id=Id;
    btn->ListeRbtn=Init_Creer_Ent_Rbn(nom);
    btn->pos.posX=xpos;
    btn->pos.posY=ypos;
    btn->t.Hauteur=hauteur;
    btn->t.Largeur=largeur;
    btn->ListeRbtn->button=gtk_radio_button_new_with_mnemonic(NULL,nom);
    return((RadioButton*)btn);
}

void Ajouter_Radio_Button(RadioButton *StrButton,char *Nom)
{
    Ent_Rbn *Nvbtn,*Ptcr;
    if(!StrButton)
    {
        printf("\nErreur StrButton n existe pas!");
        exit(0);
    }
    Nvbtn=Init_Creer_Ent_Rbn(Nom);
    Ptcr=StrButton->ListeRbtn;
    while(Ptcr->Svt) Ptcr=Ptcr->Svt;
    Ptcr->Svt=Nvbtn;
    Nvbtn->button=gtk_radio_button_new_with_mnemonic_from_widget(GTK_RADIO_BUTTON(StrButton->ListeRbtn->button),Nom);

}

//gtk_box_pack_start(btn->BOX,btn->ListeRbtn->button,TRUE,TRUE,0); fct init 1
//gtk_box_pack_start(StrButton->BOX,Nvbtn->button,TRUE,TRUE,0); ajouter
