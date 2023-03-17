#include<gtk-3.0/gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include "FENETRE999.h"
#include "MENU999.h"
#include "BUTTONS999.H"
#include"FCT_SUPP.h"
#include "RADBUTT999.h"
#include"SEPARATEUR999.h"
#include"COMBOBOX999.h"
#include"BOX999.h"
#include "TOGGLEBTN999.h"
#include "LINKBUTTON.h"



//COULEUR DES BUTTONS !!! [nom modifiable]


int main (int argc, char *argv[])
{
    gtk_init(&argc, &argv);

    Fenetre *fn;
    fn=Init_Personnalise_Fenetre(400,500,1,1,1,1,"Test","Test_sous_titre","white",TRUE); // Scroll window !! 
    Creer_Fenetre(fn);
    /**********************************************/
    /**********************************************/
    Menu *m;
    m=Init_Menu(0,1);
    m=creer_menu(m,"file","folder-new");
    m=creer_menu(m,"Edit","document-edit");
    m=creer_menu(m,"About","help-about");
    creer_sous_menu(fn,m,"share","file","document-save",'s');
    creer_sous_menu(fn,m,"aaa","Edit","document-save-as",'a');
    creer_sous_menu(fn,m,"bbb","Edit","document-send",'0');
    creer_sous_menu(fn,m,"ccc","Edit","edit-copy",'c');
    creer_sous_menu(fn,m,"ddd","About","edit-cut",'d');
    creer_sous_menu(fn,m,"eee","About","edit-delete",'e');
    creer_sous_menu(fn,m,"xxx","bbb","mail-send",'0');
    creer_sous_menu(fn,m,"yyy","bbb","media-eject",'y');
    creer_sous_menu(fn,m,"zzz","bbb","window-new",'z');
    creer_sous_menu(fn,m,"www","xxx","window-close",'w');
    /**********************************************/
    Box *bx;
    bx=Init_Box(0,1,"red");
    Creer_Box(bx);
    Ajouter_Elem_Au_Box(bx,m->MenuItems);

    Box *bx2;
    bx2=Init_Box(0,1,"rose");
    Creer_Box(bx2);
    
    /**********************************************/

    Button *btn;
    btn=Init_Button_Simple("_OOK",NULL,100,700,50,30,TRUE);
    Creer_Button_Simple(fn,btn);
    GtkWidget *btn2;
    btn2=gtk_button_new_from_icon_name("document-save",4); //4 : GTK_ICON_SIZE_BUTTON

    /**********************************************/
    /**********************************************/

    RadioButton *Radd;
    Radd=Init_Radio_Button("_bouton1",500,100,100,100,1);
    Ajouter_Radio_Button(Radd,"bou_ton 2");
    Ajouter_Radio_Button(Radd,"bouto_n 3");
    
    /**********************************************/
    /**********************************************/

    Separateur *sep;
    sep=Init_Separateur("blue",1,0,0,20,300);
    Creer_Separateur(sep);

    /**********************************************/
    /**********************************************/
    Combobox *cmbx,*cmbx2;
    cmbx=Init_Combobox(800,300,20,60,TRUE);
    cmbx2=Init_Combobox(800,400,20,60,FALSE);
    Ajouter_Elem_Combobox(cmbx,"elem1",1);
    Ajouter_Elem_Combobox(cmbx,"elem2",2);
    Ajouter_Elem_Combobox(cmbx,"elem3",3);
    Ajouter_Elem_Combobox(cmbx,"elem4",4);
    Ajouter_Elem_Combobox(cmbx2,"elem88",88);
    Ajouter_Elem_Combobox(cmbx2,"elem77",77);
    
    /**********************************************/
    /**********************************************/
    Togglebutton *tgl;
    tgl=Init_Toggle_Button("TO_GGLEBTN",800,0,40,40);
    Creer_toggle(tgl);
    // Ajouter_Elem_Au_Box(bx2,tgl->Toggle);
    /**********************************************/
    /**********************************************/

    GtkWidget *sw,*sw2;
    sw=gtk_switch_new();
    sw2=gtk_switch_new();
    gtk_switch_set_active(GTK_SWITCH(sw),TRUE);
    gtk_switch_set_active(GTK_SWITCH(sw2),FALSE);
    Ajouter_Elem_Au_Box(bx2,sw);
    Ajouter_Elem_Au_Box(bx2,sw2);
    /**********************************************/
    /**********************************************/
    LinkButton *lk;
    lk=Init_LinkBtn("google.com","linkbtn",500,50,30,60);
    Creer_LinkBTN(lk);
    Modifier_Couleur_Widget(lk->Linkbtn,"aqua");
    /**********************************************/
    /**********************************************/
    Creer_Fixed(fn,bx->monbox,100,200);
    Creer_Fixed(fn,btn2,10,20);
    Creer_Fixed(fn,Radd->BOX,Radd->pos.posX,Radd->pos.posY);
    Creer_Fixed(fn,sep->sep,sep->p.posX,sep->p.posY);
    Creer_Fixed(fn,cmbx->combo,cmbx->pox.posX,cmbx->pox.posY);
    Creer_Fixed(fn,cmbx2->combo,cmbx2->pox.posX,cmbx2->pox.posY);
    Creer_Fixed(fn,tgl->Toggle,tgl->p.posX,tgl->p.posY);
    Creer_Fixed(fn,bx2->monbox,800,100);
    Creer_Fixed(fn,lk->Linkbtn,lk->p.posX,lk->p.posY);
    /**********************************************/
    /**********************************************/
    Afficher_Fenetre(fn);
    gtk_main ();

}