#pragma once

typedef struct
{
    GtkWidget *Linkbtn;
    Taille t;
    Position p;
    char *Link;
    char *Nom;
}LinkButton;

LinkButton *Init_LinkBtn(char *link,char *nom,int x,int y,int h,int l)
{
    LinkButton *lk;
    lk=(LinkButton*)malloc(sizeof(LinkButton));
    if(!lk)
    {
        printf("\nErreur d allocation linkButton");
        exit(0);
    }
    if(link)
    {
        lk->Link=(char*)malloc(sizeof(char));
        lk->Link=link;
    }
    else lk->Link=NULL;
    lk->p.posX=x;
    lk->p.posY=y;
    lk->t.Hauteur=h;
    lk->t.Largeur=l;
    if(nom)
    {
        lk->Nom=(char*)malloc(sizeof(char));
        lk->Nom=nom;
    }
    else lk->Nom=NULL;
    return((LinkButton*)lk);
}

void Creer_LinkBTN(LinkButton *lk)
{
    if(!lk)
    {
        printf("\nErreur linkbutton n existe pas");
        exit(0);
    }
    if(!lk->Link)
    {
        printf("\nLink dan Linkbutton n existe pas!!");
        exit(0);
    }
    if(lk->Nom) lk->Linkbtn=gtk_link_button_new_with_label(lk->Link,lk->Nom);
    else lk->Linkbtn=gtk_link_button_new(lk->Link);
    gtk_widget_set_size_request(lk->Linkbtn,lk->t.Largeur,lk->t.Hauteur);
}
