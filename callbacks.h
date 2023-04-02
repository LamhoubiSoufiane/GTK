#include <gtk/gtk.h>
//#include "ajouter_individu.h"

gint X_Reservees[2]={500,160};
gint Y_Reservees[2]={160,400};
int waitvar = 5;

/*** BASE INFOS ***/
CelluleIndiv *BaseInfos[2];

FIXED *Farea;

Label *InfosCovidLb,*TypeCovidLb;
ComboBox *CbTypeCovid;

/** -------------- CHAMPS DES DONNEES DE CREATION DES INDIVIDUS ---------------------**/
Entry *NomE1,*PosX1,*PosY1;
ComboBox *CbAge1,*CbMv1,*CbSexe1,*CbGenetiquement,*CbDiabete,*CbCardiaque,*CbPoumons,*CbCancers,*CbTar,*CbDjCovid,*CbMaladeCovid,*CbAvatars;
gint DernierIdInsere = 0;
/** --------------- FIN DE CHAMPS DES DONNEES DE CREATION DES INDIVIDUS ---------------**/

/** -------------- CHAMPS DES DONNEES DE MODIFICATION DES INDIVIDUS ------------------------**/
Entry *ModifNomEntry,*ModifPosXEntry,*ModifPosYEntry;
ComboBox *ModifAgeCb,*ModifSexecb;
/** -------------- CHAMPS DES DONNEES DE MODIFICATION DES INDIVIDUS ------------------------**/
/** ---------------- FENETRE LISTE INDIVS --------------------------------------------------**/
Fenetre *FNListeIndiv;
/** ---------------- FIN DE FENETRE LISTE INDIVS --------------------------------------------------**/
/** ---------------- FENETRE DE MODIFICATION D'UN INDIVIDU -------------------------------------**/
Fenetre *FNModif;
/** ---------------- FIN DE FENETRE DE MODIFICATION D'UN INDIVIDU -------------------------------------**/

/**************************************************** NOM_FICHIER********************************************/
const gchar *str1[50];
const gchar str2[]=".txt";
/*****************************************************FIN NOM FICHIER*************************************/
const gchar*nomf;

Entry*E111;

/** -------------------------------- PLAY AREA TOOLBAR BUTTONS ---------------------------------------------**/
   GtkToolItem *PareaPlay,*PareaPause,*PareaAfficher,*PareaSupprimer,*PareaSave;
/** -------------------------------- FIN DE PLAY AREA TOOLBAR BUTTONS ---------------------------------------------**/

/** ------------------------ PLAY AREA FENETRE --------------------------------------**/
Fenetre *playarea;
/** ------------------------ FIN DE PLAY AREA FENETRE --------------------------------------**/

/** --------------------------- IMAGE CLICK SIGNALS ACTIVATION VARIABLE ---------------------**/
gint ActivateSignal = 0;
/** --------------------------- FIN DE IMAGE CLICK SIGNALS ACTIVATION VARIABLE ---------------------**/

/** ---------------------------- SUPPRESSION SIGNALS ------------------------------------------------**/
gint SupprimerSignal = 0;

/** ---------------------------- FIN DE SUPPRESSION SIGNALS ------------------------------------------------**/


/** -------------------- INITIALISATION DE LA BASE D'INFOS ----------------------------------**/
void InitialiserBaseInfos(CelluleIndiv *BaseDonnees[2])
{
    BaseDonnees[0] = BaseDonnees[1] = NULL;
}

/** --------------------- FIN DE INITIALISATION DE LA BASE D'INFOS -----------------------------**/


void MaladeCovidChamps(GtkWidget *widget,gpointer *data)
{
    switch(gtk_combo_box_get_active(widget))
    {
        case 0: gtk_widget_show_now(InfosCovidLb->Label);
                gtk_widget_show_now(TypeCovidLb->Label);
                gtk_widget_show_now(CbTypeCovid->comboBox);
                break;
        case 1: gtk_widget_hide(InfosCovidLb->Label);
                gtk_widget_hide(TypeCovidLb->Label);
                gtk_widget_hide(CbTypeCovid->comboBox);
                break;
    }
}







/** ------------------------------ FONCTIONS DU MOUVEMENT -------------------------------------------------**/

/**------------------------------- FONCTION DU MOUVEMENT ALEATOIRE ----------------------------------------**/
gboolean MouvementAleatoire(gpointer *data)
{
    CelluleIndiv *Indiv;
    Indiv = (CelluleIndiv*)data;
    int NumAleatoire = (int)(rand() % 4 + 1);
    switch(NumAleatoire)
    {
        case 1: Moving_Fixed(Farea,Indiv->Pos_x+20,Indiv->Pos_y,Indiv,BaseInfos);
                break;
        case 2: Moving_Fixed(Farea,Indiv->Pos_x,Indiv->Pos_y+20,Indiv,BaseInfos);
                break;
        case 3: Moving_Fixed(Farea,Indiv->Pos_x-20,Indiv->Pos_y,Indiv, BaseInfos);
                break;
        case 4: Moving_Fixed(Farea,Indiv->Pos_x,Indiv->Pos_y-20,Indiv, BaseInfos);
                break;
    }
    return TRUE;
}
/**----------------------------- FIN DU FONCTION DU MOUVEMENT ALEATOIRE -------------------------------------------**/



/** ---------------------------- FONCTION DU MOUVEMENT HORIZONTAL -------------------------------------------------**/
/*gboolean MouvementHorizontal(gpointer *Data)
{
    CelluleIndiv *Indiv;
    Indiv = (CelluleIndiv*)Data;
    switch(Indiv->MvH)
    {
        case 0: if(Indiv->Pos_x >= 1000)
                {
                    Indiv->MvH = 1;
                    break;
                }
                Moving_Fixed(Farea,Indiv->Pos_x+20,Indiv->Pos_y,Indiv,BaseInfos);
                break;
        case 1: if(Indiv->Pos_x <= 100)
                {
                    Indiv->MvH = 0;
                    break;
                }
                Moving_Fixed(Farea,Indiv->Pos_x-20,Indiv->Pos_y,Indiv,BaseInfos);
                break;
    }
    return TRUE;
}*/

gboolean MouvementHorizontal(gpointer *Data)
{
    CelluleIndiv *Indiv;
    Indiv = (CelluleIndiv*)Data;
    int NumAleatoire = (int)(rand() % 2 + 1);
    switch(NumAleatoire)
    {
        case 1: Moving_Fixed(Farea,Indiv->Pos_x+20,Indiv->Pos_y,Indiv,BaseInfos);
                break;
        case 2: Moving_Fixed(Farea,Indiv->Pos_x-20,Indiv->Pos_y,Indiv, BaseInfos);
                break;
    }
    return TRUE;
}
/** ------------------------------- FIN DU FONCTION DU MOUVEMENT HORIZONTAL ----------------------------------------------------------**/




/** ------------------------------- FONCTION DU MOUVEMENT VERTICAL ------------------------------------------------------**/
/*gboolean MouvementVertical(gpointer *Data)
{
    CelluleIndiv *Indiv;
    Indiv = (CelluleIndiv*)Data;
    switch(Indiv->MvV)
    {
        case 0: if(Indiv->Pos_y >= 800)
                {
                    Indiv->MvV = 1;
                    break;
                }
                Moving_Fixed(Farea,Indiv->Pos_x,Indiv->Pos_y+20,Indiv,BaseInfos);
                break;
        case 1: if(Indiv->Pos_y <= 100)
                {
                    Indiv->MvV = 0;
                    break;
                }
                Moving_Fixed(Farea,Indiv->Pos_x,Indiv->Pos_y-20,Indiv,BaseInfos);
                break;
    }
    return TRUE;
}*/
gboolean MouvementVertical(gpointer *Data)
{
    CelluleIndiv *Indiv;
    Indiv = (CelluleIndiv*)Data;
    int NumAleatoire = (int)(rand() % 2 + 1);
    switch(NumAleatoire)
    {
        case 1: Moving_Fixed(Farea,Indiv->Pos_x,Indiv->Pos_y+20,Indiv,BaseInfos);
                break;
        case 2: Moving_Fixed(Farea,Indiv->Pos_x,Indiv->Pos_y-20,Indiv, BaseInfos);
                break;
    }
    return TRUE;
}
/** -------------------------------- FIN DU FONCTION DU MOUVEMENT VERTICAL -------------------------------------------------**/

/** ------------- FONCTION DU COMMENCEMENT DU MOUVEMENT DE TOUS LES INDIVIDUS ------------------------------**/


/** --------------- FIN DU FONCTION DU MOUVEMENT DE TOUS LES INDIVIDUS --------------------------------------------**/


/** ------------------ FONCTION DE STOPPER LE MOUVEMENT DE TOUS LES INDIVS ----------------------------------------------**/

void StoperMouvementIndivs(GtkWidget *widget,gpointer *data)
{
    gtk_widget_set_sensitive(PareaPlay,TRUE);
    gtk_widget_set_sensitive(PareaAfficher,TRUE);
    gtk_widget_set_sensitive(PareaSave,TRUE);
    gtk_widget_set_sensitive(PareaSupprimer,TRUE);
    gtk_widget_set_sensitive(PareaPause,FALSE);
     CelluleIndiv *Ptcrt;
     Ptcrt = BaseInfos[0];
     while(Ptcrt)
     {
         g_source_remove(Ptcrt->MvStop);
         Ptcrt = Ptcrt->Suivant;
     }

     Ptcrt = BaseInfos[1];
     while(Ptcrt)
     {
         g_source_remove(Ptcrt->MvStop);
         Ptcrt = Ptcrt->Suivant;
     }
}
/** ------------------ FIN DE FONCTION DE STOPPER LE MOUVEMENT DE TOUS LES INDIVS ----------------------------------------------**/



/** -------------------------- FIN DE FONCTIONS DU MOUVEMENT ------------------------------------------------**/








/** --------------------------------------- CREER INDIVIDU FONCTION -------------------------------------------------------------------------------------------------------------**/
void CreationIndividu(GtkWidget *widget,gpointer *data)
{
    CelluleIndiv *nvindiv;
    nvindiv = Creer_Individu(++DernierIdInsere,gtk_entry_get_text(NomE1->entry),atoi(gtk_entry_get_text(PosX1->entry)),atoi(gtk_entry_get_text(PosY1->entry)),
                             gtk_combo_box_get_active(CbMv1->comboBox),gtk_combo_box_get_active(CbAge1->comboBox),gtk_combo_box_get_active(CbGenetiquement->comboBox),
                             gtk_combo_box_get_active(CbDiabete->comboBox),gtk_combo_box_get_active(CbCardiaque->comboBox),gtk_combo_box_get_active(CbPoumons->comboBox),
                             gtk_combo_box_get_active(CbCancers->comboBox),gtk_combo_box_get_active(CbTar->comboBox),gtk_combo_box_get_active(CbDjCovid->comboBox),
                             gtk_combo_box_get_active(CbMaladeCovid->comboBox),gtk_combo_box_get_active(CbTypeCovid->comboBox),gtk_combo_box_get_active(CbSexe1->comboBox),
                             gtk_combo_box_get_active(CbAvatars->comboBox)
                             );
    AjouterIndivBaseInfo(nvindiv,BaseInfos);
    g_print("Individu Cree!");
}

/** --------------------------------------- FIN DE CREER INDIVIDU FONCTION -------------------------------------------------------------------------------------------------------------**/







/** -------------------------------------- MODIFIER INDIVIDU FONCTION --------------------------------------------------------------------------------------------------------------------**/
void ModifierIndividu(GtkWidget *widget,gpointer *data)
{
    gint IndivId = (gint)data;
    ModifierIndivInfos(IndivId,BaseInfos,gtk_entry_get_text(ModifNomEntry->entry),atoi(gtk_entry_get_text(ModifPosXEntry->entry)),
                       atoi(gtk_entry_get_text(ModifPosYEntry->entry)),gtk_combo_box_get_active(ModifSexecb->comboBox),
                       gtk_combo_box_get_active(ModifAgeCb->comboBox)
                       );
    GtkWidget *window = gtk_widget_get_toplevel(widget);
    gtk_window_close(window);
    gtk_window_close(FNListeIndiv->Mafenetre);
    FenetreListeIndividus(NULL,NULL);
}



/** -------------------------------------- FIN DE MODIFIER INDIVIDU FONCTION --------------------------------------------------------------------------------------------------------------------**/

/** ------------------------------------ CONFIRMER SUPPRESSION INDIVIDU BOITE DIALOG ------------------------------------------------------------------------------------------------**/
void ConfirmerSuppressionDialog(GtkWidget *widget,gpointer *data)
{
    GtkWidget *BoiteDialog,*Contenu;
    Label *BDialogLabel;
    gint IndivId = (gint) data;

    BoiteDialog = gtk_dialog_new();
    gtk_dialog_add_button(BoiteDialog,"Supprimer",GTK_RESPONSE_YES);
    gtk_dialog_add_button(BoiteDialog,"Annuler",GTK_RESPONSE_NO);
    Contenu = gtk_dialog_get_content_area(BoiteDialog);

    BDialogLabel = Creation_Initialisation_Structure_Label("Vous etes sure de supprimer cette individu ?","",0,0,0,0);
    BDialogLabel = Creer_Label(BDialogLabel);

    gtk_container_add(Contenu,BDialogLabel->Label);
    gtk_widget_show_all(BoiteDialog);
    style(BDialogLabel->Label,"AttentionLb");
    gint reponse = gtk_dialog_run(BoiteDialog);
    if(reponse == GTK_RESPONSE_YES)
    {
        SupprimerIndivParId(IndivId,BaseInfos);
        g_print("Individu avec ID = %d est supprime",IndivId);
        gtk_widget_destroy(BoiteDialog);
        gtk_window_close(FNModif->Mafenetre);
        gtk_window_close(FNListeIndiv->Mafenetre);
        FenetreListeIndividus(NULL,NULL);
        return;

    }
    else if (reponse == GTK_RESPONSE_NO) g_print("Action annulee");
    gtk_widget_destroy(BoiteDialog);
}


/** ------------------------------------ FIN DE CONFIRMER SUPPRESSION INDIVIDU BOITE DIALOG ------------------------------------------------------------------------------------------------**/














/** --------------------------------------- AFFICHER INFO INDIVIDU DANS PLAY AREA FUNCTION -------------------------------------------------------------------------------------**/


void AfficherInfosIndivPlayArea(GtkWidget *widget, gpointer *data)
{
    gint IndivId = atoi(gtk_widget_get_name(widget));
    gchar InfoMessage[150];
    InfoMessagePlayarea(BaseInfos,IndivId,InfoMessage);
    GtkWidget *DialogInfos;
    DialogInfos = gtk_message_dialog_new(playarea->Mafenetre,GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,InfoMessage);
    gint reponse = gtk_dialog_run(DialogInfos);
    gtk_widget_destroy(DialogInfos);
}

/** --------------------------------------- FIN DE AFFICHER INFO INDIVIDU DANS PLAY AREA FUNCTION -------------------------------------------------------------------------------------**/






/** ------------------------------------- FONCTION D'ACTIVATION DES SIGNAUX SUR LES IMAGES POUR AFFICHER LES INFOS D'UN INDIV EN CLICK ---------------------------------------------------**/



void ActivationSignalsInfosIndivs(GtkWidget *widget, gpointer data)
{
    CelluleIndiv *Ptcrt;
    switch(ActivateSignal)
    {
         case 0: gtk_widget_set_sensitive(PareaPlay,FALSE);
                 gtk_widget_set_sensitive(PareaAfficher,TRUE);
                 gtk_widget_set_sensitive(PareaSave,FALSE);
                 gtk_widget_set_sensitive(PareaSupprimer,FALSE);
                 gtk_widget_set_sensitive(PareaPause,FALSE);
                 Ptcrt = BaseInfos[0];
                 while(Ptcrt)
                 {
                       Ptcrt->ActiveSignalId = g_signal_connect (G_OBJECT (Ptcrt->IndivImage->ImageEbox),"button_press_event",G_CALLBACK (AfficherInfosIndivPlayArea),NULL);
                       Ptcrt = Ptcrt->Suivant;
                 }
                 Ptcrt = BaseInfos[1];
                 while(Ptcrt)
                 {
                       Ptcrt->ActiveSignalId = g_signal_connect (G_OBJECT (Ptcrt->IndivImage->ImageEbox),"button_press_event",G_CALLBACK (AfficherInfosIndivPlayArea),NULL);
                       Ptcrt = Ptcrt->Suivant;
                 }
                 ActivateSignal = 1;
                 break;
         case 1: gtk_widget_set_sensitive(PareaPlay,TRUE);
                 gtk_widget_set_sensitive(PareaAfficher,TRUE);
                 gtk_widget_set_sensitive(PareaSave,TRUE);
                 gtk_widget_set_sensitive(PareaSupprimer,TRUE);
                 gtk_widget_set_sensitive(PareaPause,FALSE);
                 Ptcrt = BaseInfos[0];
                 while(Ptcrt)
                 {
                       if(Ptcrt->ActiveSignalId != -1) g_signal_handler_disconnect(Ptcrt->IndivImage->ImageEbox,Ptcrt->ActiveSignalId);
                       Ptcrt = Ptcrt->Suivant;
                 }
                 Ptcrt = BaseInfos[1];
                 while(Ptcrt)
                 {
                       if(Ptcrt->ActiveSignalId != -1) g_signal_handler_disconnect(Ptcrt->IndivImage->ImageEbox,Ptcrt->ActiveSignalId);
                       Ptcrt = Ptcrt->Suivant;
                 }
                 ActivateSignal = 0;
                 break;
     }

}
/** ------------------------------------- FIN DE FONCTION D'ACTIVATION DES SIGNAUX SUR LES IMAGES POUR AFFICHER LES INFOS D'UN INDIV EN CLICK ---------------------------------------------------**/



/** --------------------------------------- FONCTION D'INCREMENTATION ---------------------------------------------------------**/
gboolean IncrementerVar(GtkWidget *widget, gint *var)
{
    if(*var == 5)
    {
        gtk_widget_destroy(widget);
        return TRUE;
    }
    *var++;
    return FALSE;
}

/** --------------------------------------- FONCTION D'INCREMENTATION ---------------------------------------------------------**/



/** --------------------------------------- FONCTION DE SUPPRESSION INDIV PLAY AREA --------------------------------------------------------------------------------------------**/

void SupprimerIndivPlayArea(GtkWidget *widget, gpointer *data)
{
    gint IndivId = atoi(gtk_widget_get_name(widget));
    CelluleIndiv *Indiv;
    Indiv = ChercherIndivParId(IndivId,BaseInfos);
    gtk_widget_destroy(Indiv->IndivImage->ImageEbox);
    switch(Indiv->Avatar)
    {
        case 0 : Indiv->IndivImage = Image_init("avatars/blue_deadbody.png",0,0);
                 Indiv->Avatar = 6;
                 Indiv->EstMort = 1;
                 break;
        case 1 : Indiv->IndivImage = Image_init("avatars/green_deadbody.png",0,0);
                 Indiv->Avatar = 7;
                 Indiv->EstMort = 1;
                 break;
        case 2 : Indiv->IndivImage = Image_init("avatars/orange_deadbody.png",0,0);
                 Indiv->Avatar = 8;
                 Indiv->EstMort = 1;
                 break;
        case 3 : Indiv->IndivImage = Image_init("avatars/pink_deadbody.png",0,0);
                 Indiv->Avatar = 9;
                 Indiv->EstMort = 1;
                 break;
        case 4 : Indiv->IndivImage = Image_init("avatars/purple_deadbody.png",0,0);
                 Indiv->Avatar = 10;
                 Indiv->EstMort = 1;
                 break;
        case 5 : Indiv->IndivImage = Image_init("avatars/yellow_deadbody.png",0,0);
                 Indiv->Avatar = 11;
                 Indiv->EstMort = 1;
                 break;
    }
    Indiv->IndivImage = Image_create(Indiv->IndivImage);
    creer_fixed(Indiv->Pos_x,Indiv->Pos_y,Farea,Indiv->IndivImage->ImageEbox,NULL);
    gtk_widget_show_all(Indiv->IndivImage->ImageEbox);
}

/** --------------------------------------- FIN DE FONCTION DE SUPPRESSION INDIV PLAY AREA --------------------------------------------------------------------------------------------**/

int MourrirIndiv(CelluleIndiv*indiv)
{
    //CelluleIndiv*Ptcrt;
    int NumAleatoire = (int)(rand() % 10 + 1);
    //Ptcrt=BaseInfos[0];
    //while(Ptcrt)
    //{
        //g_print("\nnum aleatoire : %d",NumAleatoire);
        g_print("\nID : %d \t Score : %d",indiv->Id,indiv->Score);
        if(indiv->Score<=5)
        {
            if(NumAleatoire==1) return((int)0);
            else return((int)1);
        }
        else if((indiv->Score>5)&&(indiv->Score<12))
        {
            if((NumAleatoire==1)||(NumAleatoire==2)||(NumAleatoire==3)||(NumAleatoire==4)) return((int) 0);
            else return((int)1);
        }
        else if((indiv->Score>=12)&&(indiv->Score<18))
        {
            if((NumAleatoire==7)||(NumAleatoire==8)||(NumAleatoire==9)||(NumAleatoire==10)) return((int)1);
            else return((int)0);
        }
        else
        {
            if((NumAleatoire==1)||(NumAleatoire==2)) return ((int)1);
            else return((int)0);
        }
        //Ptcrt=Ptcrt->Suivant;
    //}
}


/** ------------------------------------------ FONCTION MOURIR DANS PLAYAREA AVEC LE TEMPS -----------------------------------------------------------------------**/

void MourrirMaladeTemps(gint IndivId)
{
    CelluleIndiv *Indiv;
    Indiv = ChercherIndivParId(IndivId,BaseInfos);
    Indiv->ValDeMort=MourrirIndiv(Indiv);
    g_print("\n%d",Indiv->ValDeMort);
    if(Indiv->ValDeMort==0)
    {
        gtk_widget_destroy(Indiv->IndivImage->ImageEbox);
        switch(Indiv->Avatar)
        {
            case 0 :
                    g_source_remove(Indiv->MvStop);
                    Indiv->IndivImage = Image_init("avatars/blue_deadbody.png",0,0);
                    Indiv->Avatar = 6;
                    Indiv->EstMort = 1;
                    break;
            case 1 :
                    g_source_remove(Indiv->MvStop);
                    Indiv->IndivImage = Image_init("avatars/green_deadbody.png",0,0);
                    Indiv->Avatar = 7;
                    Indiv->EstMort = 1;
                    break;
            case 2 :
                    g_source_remove(Indiv->MvStop);
                    Indiv->IndivImage = Image_init("avatars/orange_deadbody.png",0,0);
                    Indiv->Avatar = 8;
                    Indiv->EstMort = 1;
                    break;
            case 3 :
                    g_source_remove(Indiv->MvStop);
                    Indiv->IndivImage = Image_init("avatars/pink_deadbody.png",0,0);
                    Indiv->Avatar = 9;
                    Indiv->EstMort = 1;
                    break;
            case 4 :
                    g_source_remove(Indiv->MvStop);
                    Indiv->IndivImage = Image_init("avatars/purple_deadbody.png",0,0);
                    Indiv->Avatar = 10;
                    Indiv->EstMort = 1;
                    break;
            case 5 :
                    g_source_remove(Indiv->MvStop);
                    Indiv->IndivImage = Image_init("avatars/yellow_deadbody.png",0,0);
                    Indiv->Avatar = 11;
                    Indiv->EstMort = 1;
                    break;
        }
    }
    Indiv->IndivImage = Image_create(Indiv->IndivImage);
    creer_fixed(Indiv->Pos_x,Indiv->Pos_y,Farea,Indiv->IndivImage->ImageEbox,NULL);
    gtk_widget_show_all(Indiv->IndivImage->ImageEbox);

}
void Supprimer_indiv_mort(CelluleIndiv*indiv)
{
    gtk_widget_destroy(indiv->IndivImage->image);
    gtk_widget_destroy(indiv->VirusImage->image);
}

void Indiv_guerie(CelluleIndiv*indiv)
{
    gtk_widget_destroy(indiv->VirusImage->image);
}
gboolean CalculerTempsMaladie(gpointer *data)
{
    CelluleIndiv *Ptcrt;
    if(!BaseInfos)
    {
        g_print("Base infos n'existe pas !");
        exit(0);
    }
    Ptcrt = BaseInfos[0];
    while(Ptcrt)
    {
        //g_print("\n%d",Ptcrt->Id);
        switch(Ptcrt->TypeCovid)
        {
        case 0 :
            if(Ptcrt->TempsCpt==10) MourrirMaladeTemps(Ptcrt->Id);
            Ptcrt->TempsCpt++;
            if((Ptcrt->TempsCpt==15)&&(Ptcrt->ValDeMort==0)) Supprimer_indiv_mort(Ptcrt);
            if((Ptcrt->TempsCpt==20)&&(Ptcrt->ValDeMort!=0)) Indiv_guerie(Ptcrt);
            break;
        case 1 :
            if(Ptcrt->TempsCpt==20) MourrirMaladeTemps(Ptcrt->Id);
            Ptcrt->TempsCpt++;
            if((Ptcrt->TempsCpt==25) &&(Ptcrt->ValDeMort==0)) Supprimer_indiv_mort(Ptcrt);
            if((Ptcrt->TempsCpt==30)&&(Ptcrt->ValDeMort!=0)) Indiv_guerie(Ptcrt);
            break;
        case 2 :
            if(Ptcrt->TempsCpt==30) MourrirMaladeTemps(Ptcrt->Id);
            Ptcrt->TempsCpt++;
            if((Ptcrt->TempsCpt==35) &&(Ptcrt->ValDeMort==0)) Supprimer_indiv_mort(Ptcrt);
            if((Ptcrt->TempsCpt==40)&&(Ptcrt->ValDeMort!=0)) Indiv_guerie(Ptcrt);
            break;
        }
        Ptcrt = Ptcrt->Suivant;
    }
    return TRUE;
}


void CommencerMouvement(GtkWidget *widget,gpointer *data)
{
    g_timeout_add_seconds(1,CalculerTempsMaladie,NULL);
    gtk_widget_set_sensitive(PareaPlay,FALSE);
    gtk_widget_set_sensitive(PareaAfficher,FALSE);
    gtk_widget_set_sensitive(PareaSave,FALSE);
    gtk_widget_set_sensitive(PareaSupprimer,FALSE);
    gtk_widget_set_sensitive(PareaPause,TRUE);
    CelluleIndiv *Ptcrt;
    Ptcrt = BaseInfos[0];
    while(Ptcrt)
    {
        if(Ptcrt->EstMort == 0)
        {
            switch(Ptcrt->TypeMv)
             {
            case 0: Ptcrt->MvStop = g_timeout_add(200,MouvementAleatoire,Ptcrt);
                    break;
            case 1: Ptcrt->MvStop = g_timeout_add(200,MouvementHorizontal,Ptcrt);
                    break;
            case 2: Ptcrt->MvStop = g_timeout_add(200,MouvementVertical,Ptcrt);
                    break;
            default: Ptcrt->MvStop = g_timeout_add(200,MouvementAleatoire,Ptcrt);
                     break;
             }
        }
        Ptcrt = Ptcrt->Suivant;
    }
    Ptcrt = BaseInfos[1];
    while(Ptcrt)
    {
         if(Ptcrt->EstMort == 0)
        {
            switch(Ptcrt->TypeMv)
             {
            case 0: Ptcrt->MvStop = g_timeout_add(200,MouvementAleatoire,Ptcrt);
                    break;
            case 1: Ptcrt->MvStop = g_timeout_add(200,MouvementHorizontal,Ptcrt);
                    break;
            case 2: Ptcrt->MvStop = g_timeout_add(200,MouvementVertical,Ptcrt);
                    break;
            default: Ptcrt->MvStop = g_timeout_add(200,MouvementAleatoire,Ptcrt);
                     break;
             }
        }
        Ptcrt = Ptcrt->Suivant;
    }
}

/** -------------------------------------------- FONCTION D'ACTIVATION SIGNALS SUPPRESSION INDIVIDU PLAY AREA --------------------------------------------------------------------**/


void ActivateSignalSuppression(GtkWidget *widget, gpointer *data)
{
    CelluleIndiv *Ptcrt;
    switch(SupprimerSignal)
    {
        case 0:  gtk_widget_set_sensitive(PareaPlay,FALSE);
                 gtk_widget_set_sensitive(PareaAfficher,FALSE);
                 gtk_widget_set_sensitive(PareaSave,FALSE);
                 gtk_widget_set_sensitive(PareaSupprimer,TRUE);
                 gtk_widget_set_sensitive(PareaPause,FALSE);
                 Ptcrt = BaseInfos[0];
                 while(Ptcrt)
                 {
                       Ptcrt->SuppressionSignalId = g_signal_connect (G_OBJECT (Ptcrt->IndivImage->ImageEbox),"button_press_event",G_CALLBACK (SupprimerIndivPlayArea),NULL);
                       Ptcrt = Ptcrt->Suivant;
                 }
                 Ptcrt = BaseInfos[1];
                 while(Ptcrt)
                 {
                       Ptcrt->SuppressionSignalId = g_signal_connect (G_OBJECT (Ptcrt->IndivImage->ImageEbox),"button_press_event",G_CALLBACK (SupprimerIndivPlayArea),NULL);
                       Ptcrt = Ptcrt->Suivant;
                 }
                 SupprimerSignal = 1;
                 break;
        case 1:  gtk_widget_set_sensitive(PareaPlay,TRUE);
                 gtk_widget_set_sensitive(PareaAfficher,TRUE);
                 gtk_widget_set_sensitive(PareaSave,TRUE);
                 gtk_widget_set_sensitive(PareaSupprimer,TRUE);
                 gtk_widget_set_sensitive(PareaPause,FALSE);
                 Ptcrt = BaseInfos[0];
                 while(Ptcrt)
                 {
                       if(Ptcrt->SuppressionSignalId != -1) g_signal_handler_disconnect(Ptcrt->IndivImage->ImageEbox,Ptcrt->SuppressionSignalId);
                       Ptcrt = Ptcrt->Suivant;
                 }
                 Ptcrt = BaseInfos[1];
                 while(Ptcrt)
                 {
                       if(Ptcrt->SuppressionSignalId != -1) g_signal_handler_disconnect(Ptcrt->IndivImage->ImageEbox,Ptcrt->SuppressionSignalId);
                       Ptcrt = Ptcrt->Suivant;
                 }
                 SupprimerSignal = 0;
                 break;
    }
}
/** -------------------------------------------- FIN DE FONCTION D'ACTIVATION SIGNALS SUPPRESSION INDIVIDU PLAY AREA --------------------------------------------------------------------**/






/** ------------------------------------- MODIFIER INDIVIDU FENETRE FONCTION --------------------------------------------------------------------------------------------------------------------**/

void FenetreModifierIndiv(GtkWidget *widget,gpointer *data)
{
    Label *IdLb,*NomLb,*PositionLb,*SexeLb,*AgeLb,*IndivIdLb;
    FIXED *fxd;
    Button *ValiderBtn,*SupprimerBtn;
    GtkWidget *IdLabel;
    IdLabel = (GtkWidget*)data;
    gint IdIndiv = atoi(gtk_label_get_text(IdLabel));
    CelluleIndiv *IndivInfos;
    IndivInfos = ChercherIndivParId(IdIndiv,BaseInfos);
    gchar PosX[10];
    gchar PosY[10];
    if(!IndivInfos)
    {
        g_print("Individu n'existe pas !");
        exit(0);
    }

    /** CONVERTIR LES POSITIONS DE GINT A GCHAR **/
    itoa(IndivInfos->Pos_x,PosX,10);
    itoa(IndivInfos->Pos_y,PosY,10);
    /** FIN DE CONVERTIR LES POSITIONS DE GINT A GCHAR **/

    /** FENETRE **/
    FNModif = init_window(0,0,800,1000,"Modifier un individu","");
    FNModif = create_window2(FNModif);
    gtk_window_set_icon_from_file   (FNModif->Mafenetre, "icone_corona.jpg", NULL);
    gtk_window_set_position(GTK_WINDOW(FNModif->Mafenetre), GTK_WIN_POS_CENTER_ALWAYS);
    /** FIN DE FENETRE **/

    /** FIXED **/
    fxd = init_fixed();
    /** FIN DE FIXED **/


    /** LABELS **/
    IdLb = Creation_Initialisation_Structure_Label("Identifiant:","",0,0,0,0);
    IdLb = Creer_Label(IdLb);

    IndivIdLb = Creation_Initialisation_Structure_Label(gtk_label_get_text(IdLabel),"",0,0,0,0);
    IndivIdLb = Creer_Label(IndivIdLb);

    NomLb = Creation_Initialisation_Structure_Label("Nom:","",0,0,0,0);
    NomLb = Creer_Label(NomLb);

    PositionLb = Creation_Initialisation_Structure_Label("Position(X,Y):","",0,0,0,0);
    PositionLb = Creer_Label(PositionLb);

    SexeLb = Creation_Initialisation_Structure_Label("Sexe:","",0,0,0,0);
    SexeLb = Creer_Label(SexeLb);

    AgeLb = Creation_Initialisation_Structure_Label("Age:","",0,0,0,0);
    AgeLb = Creer_Label(AgeLb);
    /** FIN DE LABELS **/

    /** ENTRIES **/
    ModifNomEntry = Entry_init(TRUE,NULL);
    ModifNomEntry = Entry_create(ModifNomEntry);

    ModifPosXEntry = Entry_init(TRUE,NULL);
    ModifPosXEntry = Entry_create(ModifPosXEntry);

    ModifPosYEntry = Entry_init(TRUE,NULL);
    ModifPosYEntry = Entry_create(ModifPosYEntry);
    /** FIN DE ENTRIES **/

    /** COMBO BOX **/
    ModifAgeCb = Init_ComboBox();
    ModifAgeCb = Create_ComboBox(0,0,0);
    Ajouter_Element_Combobox(ModifAgeCb,"Age < 12ans","1");
    Ajouter_Element_Combobox(ModifAgeCb,"12 < Age =< 25","2");
    Ajouter_Element_Combobox(ModifAgeCb,"25 < Age =< 40","3");
    Ajouter_Element_Combobox(ModifAgeCb,"40 < Age =< 65","4");
    Ajouter_Element_Combobox(ModifAgeCb,"65 < Age","5");

    ModifSexecb = Init_ComboBox();
    ModifSexecb = Create_ComboBox(0,0,0);
    Ajouter_Element_Combobox(ModifSexecb,"Homme","1");
    Ajouter_Element_Combobox(ModifSexecb,"Femme","2");
    /** FIN DE COMBO BOX **/

    /** BOUTTONS **/
    ValiderBtn = initialise_simple_button("","Valider",TRUE,NULL);
    ValiderBtn = Creer_Button(ValiderBtn);

    SupprimerBtn = initialise_simple_button("","Supprimer",TRUE,NULL);
    SupprimerBtn = Creer_Button(SupprimerBtn);
    /** FIN DE BOUTTONS **/

    /** SIGNALS **/
    g_signal_connect (G_OBJECT (ValiderBtn->MonBoutton), "clicked",G_CALLBACK (ModifierIndividu),IdIndiv);
    g_signal_connect (G_OBJECT (SupprimerBtn->MonBoutton), "clicked",G_CALLBACK (ConfirmerSuppressionDialog),IdIndiv);


    /** FIN DE SIGNALS **/

    /** CREATION DES FIXED **/
    creer_fixed(250,100,fxd,IdLb->Label,NULL);
    creer_fixed(450,100,fxd,IndivIdLb->Label,NULL);

    creer_fixed(250,200,fxd,NomLb->Label,NULL);
    creer_fixed(350,200,fxd,ModifNomEntry->entry,NULL);

    creer_fixed(250,300,fxd,PositionLb->Label,NULL);
    creer_fixed(400,300,fxd,ModifPosXEntry->entry,NULL);
    creer_fixed(600,300,fxd,ModifPosYEntry->entry,NULL);

    creer_fixed(250,400,fxd,SexeLb->Label,NULL);
    creer_fixed(350,400,fxd,ModifSexecb->comboBox,NULL);

    creer_fixed(250,500,fxd,AgeLb->Label,NULL);
    creer_fixed(350,500,fxd,ModifAgeCb->comboBox,NULL);

    creer_fixed(400,700,fxd,ValiderBtn->MonBoutton,NULL);
    creer_fixed(600,700,fxd,SupprimerBtn->MonBoutton,NULL);
    /** FIN DE CREATION DES FIXED **/

    /** SET ENTRIES DEFAULT VALUES **/
    gtk_entry_set_text(ModifNomEntry->entry,IndivInfos->Nomcomplet);
    gtk_entry_set_text(ModifPosXEntry->entry,PosX);
    gtk_entry_set_text(ModifPosYEntry->entry,PosY);
    /** FIN DE SET ENTRIES DEFAULT VALUES **/

    /** SET COMBOBOX DEFAULT VALUES **/
    gtk_combo_box_set_active(ModifAgeCb->comboBox,IndivInfos->Age);
    gtk_combo_box_set_active(ModifSexecb->comboBox,IndivInfos->Sexe);
    /** FIN DE SET COMBOBOX DEFAULT VALUES **/

    /** STYLE **/
    style(IdLb->Label,"ModifLabels");
    style(IndivIdLb->Label,"ModifLabels");
    style(NomLb->Label,"ModifLabels");
    style(PositionLb->Label,"ModifLabels");
    style(SexeLb->Label,"ModifLabels");
    style(AgeLb->Label,"ModifLabels");
    /** FIN DE STYLE **/

    gtk_container_add(FNModif->Mafenetre,fxd->fixed);
    gtk_widget_show_all(FNModif->Mafenetre);
}

/** ------------------------------------- FIN DE MODIFIER INDIVIDU FENETRE FONCTION --------------------------------------------------------------------------------------------------------------------**/






/** ----------------------------------- FONCTION DE TERMINATION DE LA CREATION DES INDIVIDUS --------------------------------------------------------**/

void TerminerCreationIndividus(GtkWidget *widget,gpointer *data)
{
     GtkWidget *window = gtk_widget_get_toplevel(widget);
     gtk_window_close(window);
}
/** ------------------------------------ FIN DE FONCTION DE TERMINATION DE LA CREATION DES INDIVIDUS --------------------------------------------------**/




/** ----------------------------------- FONCTION DE LA FENETRE DU GESTION DES INDIVIDUS MALADES ---------------------------------------------------------**/

void FenetreGestionIndivMalades(GtkWidget *widget,gpointer *data)
{
    EntriesListe *Individu1;
    /** DECLARATION DES VARIABLE **/
     Fenetre *FN;
     scrollWindow *Sw;
     Label *Titre,*Indiv1Titre,*Indiv1Nom,*Indiv1Position,*Indiv1Age,*Indiv1MvType,*Indiv1Sexe,*BilanSanteLb,
           *GenetiquementLb,*DiabeteLb,*CardiaqueLb,*PoumonsLb,*CancersLb,*TarLb,*DejaMaladeCovidLb,
           *MaladeCovidLb,*AvatarsLb;
     FIXED *fxdpcp;
     Button *ValiderBtn,*AnnulerBtn,*TerminerBtn;
    /** FIN DE DECLARATION DES VARIABLES **/

     /** FENETRE **/
     FN = init_window(0,0,1000,1000,"Gestion des individus malades","");
     FN = create_window2(FN);

     gtk_window_set_icon_from_file   (FN->Mafenetre, "icone_corona.jpg", NULL);
     /** FIN DE FENETRE **/

     /** SCROLL FENETRE **/
     Sw = initi_scrollwindow(NULL,0,0,0);
     Sw = create_scrollwindow(Sw);
     /** FIN DE SCROLL FENETRE **/

     /** FIXED **/
     fxdpcp = init_fixed();
     /** FIN DE FIXED **/

     /** LABELS **/

     /** TITRE PRINCIPAL **/
     Titre = Creation_Initialisation_Structure_Label("Interface de gestion des individus malades","",0,0,0,0);
     Titre = Creer_Label(Titre);
     /** FIN DE TITRE PRINCIPAL **/

     /** INDIVIDU 1 **/
     Indiv1Titre = Creation_Initialisation_Structure_Label("Donnees Personnelles: ","",0,0,0,0);
     Indiv1Titre = Creer_Label(Indiv1Titre);

     Indiv1Nom = Creation_Initialisation_Structure_Label("Nom complet:","",0,0,0,0);
     Indiv1Nom = Creer_Label(Indiv1Nom);

     Indiv1Position = Creation_Initialisation_Structure_Label("Position Initiale:(X,Y)","",0,0,0,0);
     Indiv1Position = Creer_Label(Indiv1Position);

     Indiv1Age = Creation_Initialisation_Structure_Label("Age:","",0,0,0,0);
     Indiv1Age = Creer_Label(Indiv1Age);

     Indiv1MvType = Creation_Initialisation_Structure_Label("Type du mouvement:","",0,0,0,0);
     Indiv1MvType = Creer_Label(Indiv1MvType);

     Indiv1Sexe = Creation_Initialisation_Structure_Label("Sexe:","",0,0,0,0);
     Indiv1Sexe = Creer_Label(Indiv1Sexe);

     BilanSanteLb = Creation_Initialisation_Structure_Label("Bilan Sante:","",0,0,0,0);
     BilanSanteLb = Creer_Label(BilanSanteLb);

     GenetiquementLb = Creation_Initialisation_Structure_Label("Genetiquement:","",0,0,0,0);
     GenetiquementLb = Creer_Label(GenetiquementLb);

     DiabeteLb = Creation_Initialisation_Structure_Label("Diabete:","",0,0,0,0);
     DiabeteLb = Creer_Label(DiabeteLb);

     CardiaqueLb = Creation_Initialisation_Structure_Label("Cardiaque:","",0,0,0,0);
     CardiaqueLb = Creer_Label(CardiaqueLb);

     PoumonsLb = Creation_Initialisation_Structure_Label("Poumons:","",0,0,0,0);
     PoumonsLb = Creer_Label(PoumonsLb);

     CancersLb = Creation_Initialisation_Structure_Label("Cancers:","",0,0,0,0);
     CancersLb = Creer_Label(CancersLb);

     TarLb = Creation_Initialisation_Structure_Label("Tension arterielle:","",0,0,0,0);
     TarLb = Creer_Label(TarLb);

     DejaMaladeCovidLb = Creation_Initialisation_Structure_Label("Deja malade(Covid):","",0,0,0,0);
     DejaMaladeCovidLb = Creer_Label(DejaMaladeCovidLb);

     InfosCovidLb = Creation_Initialisation_Structure_Label("Informations sur Covid:","",0,0,0,0);
     InfosCovidLb = Creer_Label(InfosCovidLb);

     TypeCovidLb = Creation_Initialisation_Structure_Label("Type Covid:","",0,0,0,0);
     TypeCovidLb = Creer_Label(TypeCovidLb);

     MaladeCovidLb = Creation_Initialisation_Structure_Label("Malade(Covid):","",0,0,0,0);
     MaladeCovidLb = Creer_Label(MaladeCovidLb);

     AvatarsLb = Creation_Initialisation_Structure_Label("Avatar:","",0,0,0,0);
     AvatarsLb = Creer_Label(AvatarsLb);
     /** FIN DE INDIVIDU 1 **/

     /** FIN LABELS **/

     /** ENTRIES **/
     /** INDIVIDU 1 **/
     NomE1 = Entry_init(TRUE,NULL);
     NomE1 = Entry_create(NomE1);

     PosX1 = Entry_init(TRUE,NULL);
     PosX1 = Entry_create(PosX1);

     PosY1 = Entry_init(TRUE,NULL);
     PosY1 = Entry_create(PosY1);
     /** FIN DE INDIVIDU 1 **/

     /** FIN ENTRIES **/

     /** COMBO BOX **/
     /** INDIVIDU 1 **/
     CbAge1 = Init_ComboBox();
     CbAge1 = Create_ComboBox(0,0,0);
     Ajouter_Element_Combobox(CbAge1,"Age < 12ans","1");
     Ajouter_Element_Combobox(CbAge1,"12 < Age =< 25","2");
     Ajouter_Element_Combobox(CbAge1,"25 < Age =< 40","3");
     Ajouter_Element_Combobox(CbAge1,"40 < Age =< 65","4");
     Ajouter_Element_Combobox(CbAge1,"65 < Age","5");


     CbMv1 = Init_ComboBox();
     CbMv1 = Create_ComboBox(0,0,0);
     Ajouter_Element_Combobox(CbMv1,"Aleatoirement","1");
     Ajouter_Element_Combobox(CbMv1,"Horizontalement","2");
     Ajouter_Element_Combobox(CbMv1,"Verticalement","3");

     CbSexe1 = Init_ComboBox();
     CbSexe1 = Create_ComboBox(0,0,0);
     Ajouter_Element_Combobox(CbSexe1,"Homme","1");
     Ajouter_Element_Combobox(CbSexe1,"Femme","2");

     CbGenetiquement = Init_ComboBox();
     CbGenetiquement = Create_ComboBox(0,0,0);
     Ajouter_Element_Combobox(CbGenetiquement,"Fort","1");
     Ajouter_Element_Combobox(CbGenetiquement,"Moyen","2");
     Ajouter_Element_Combobox(CbGenetiquement,"Fragile","3");
     Ajouter_Element_Combobox(CbGenetiquement,"Faible","4");

     CbDiabete = Init_ComboBox();
     CbDiabete = Create_ComboBox(0,0,0);
     Ajouter_Element_Combobox(CbDiabete,"Normal","1");
     Ajouter_Element_Combobox(CbDiabete,"Modere","2");
     Ajouter_Element_Combobox(CbDiabete,"Avance","3");

     CbCardiaque = Init_ComboBox();
     CbCardiaque = Create_ComboBox(0,0,0);
     Ajouter_Element_Combobox(CbCardiaque,"Normal","1");
     Ajouter_Element_Combobox(CbCardiaque,"Malade","2");
     Ajouter_Element_Combobox(CbCardiaque,"Severe","3");

     CbPoumons = Init_ComboBox();
     CbPoumons = Create_ComboBox(0,0,0);
     Ajouter_Element_Combobox(CbPoumons,"Sein","1");
     Ajouter_Element_Combobox(CbPoumons,"Malade","2");
     Ajouter_Element_Combobox(CbPoumons,"Gravement touche","3");

     CbCancers = Init_ComboBox();
     CbCancers = Create_ComboBox(0,0,0);
     Ajouter_Element_Combobox(CbCancers,"Sein","1");
     Ajouter_Element_Combobox(CbCancers,"Moyen","2");
     Ajouter_Element_Combobox(CbCancers,"Fort","3");

     CbTar = Init_ComboBox();
     CbTar = Create_ComboBox(0,0,0);
     Ajouter_Element_Combobox(CbTar,"Faible","1");
     Ajouter_Element_Combobox(CbTar,"Moyen","2");
     Ajouter_Element_Combobox(CbTar,"Fort","3");

     CbDjCovid = Init_ComboBox();
     CbDjCovid = Create_ComboBox(0,0,0);
     Ajouter_Element_Combobox(CbDjCovid,"Oui","1");
     Ajouter_Element_Combobox(CbDjCovid,"Non","2");

     CbMaladeCovid = Init_ComboBox();
     CbMaladeCovid = Create_ComboBox(0,0,0);
     Ajouter_Element_Combobox(CbMaladeCovid,"Oui","1");
     Ajouter_Element_Combobox(CbMaladeCovid,"Non","2");

     CbTypeCovid = Init_ComboBox();
     CbTypeCovid = Create_ComboBox(0,0,0);
     Ajouter_Element_Combobox(CbTypeCovid,"Type 1","1");
     Ajouter_Element_Combobox(CbTypeCovid,"Type 2","2");
     Ajouter_Element_Combobox(CbTypeCovid,"Type 3","3");

     CbAvatars = Init_ComboBox();
     CbAvatars = Create_ComboBox(0,0,0);
     Ajouter_Element_Combobox(CbAvatars,"Bleu","1");
     Ajouter_Element_Combobox(CbAvatars,"Vert","2");
     Ajouter_Element_Combobox(CbAvatars,"Orange","3");
     Ajouter_Element_Combobox(CbAvatars,"Rose","4");
     Ajouter_Element_Combobox(CbAvatars,"Mauve","5");
     Ajouter_Element_Combobox(CbAvatars,"Jaune","6");
     /** FIN DE INDIVIDU 1 **/


     /** FIN DE COMBO BOX **/

     /** BUTTONS **/
     ValiderBtn = initialise_simple_button("","Valider",FALSE,NULL);
     ValiderBtn = Creer_Button(ValiderBtn);

     AnnulerBtn = initialise_simple_button("","Annuler",FALSE,NULL);
     AnnulerBtn = Creer_Button(AnnulerBtn);

     TerminerBtn = initialise_simple_button("","Terminer",FALSE,NULL);
     TerminerBtn = Creer_Button(TerminerBtn);
     /** FIN BUTTONS **/

     /** CREATION FIXED **/
     creer_fixed(400,100,fxdpcp,Titre->Label,NULL);


     /** INDIVIDU 1 **/
              /** TITRE **/
      creer_fixed(50,200,fxdpcp,Indiv1Titre->Label,NULL);
              /** NOM **/
     creer_fixed(100,230,fxdpcp,Indiv1Nom->Label,NULL);
     creer_fixed(100,250,fxdpcp,NomE1->entry,NULL);

             /** POSITION **/
     creer_fixed(300,230,fxdpcp,Indiv1Position->Label,NULL);
     creer_fixed(300,250,fxdpcp,PosX1->entry,NULL);
     creer_fixed(500,250,fxdpcp,PosY1->entry,NULL);

             /** AGE **/
     creer_fixed(700,230,fxdpcp,Indiv1Age->Label,NULL);
     creer_fixed(700,250,fxdpcp,CbAge1->comboBox,NULL);

             /** TYPE MOUVEMENT **/
     creer_fixed(900,230,fxdpcp,Indiv1MvType->Label,NULL);
     creer_fixed(900,250,fxdpcp,CbMv1->comboBox,NULL);

             /** SEXE **/
     creer_fixed(1100,230,fxdpcp,Indiv1Sexe->Label,NULL);
     creer_fixed(1100,250,fxdpcp,CbSexe1->comboBox,NULL);

            /** BILAN SANTE TITRE **/
     creer_fixed(50,400,fxdpcp,BilanSanteLb->Label,NULL);

            /** GENETIQUEMENT **/
     creer_fixed(100,430,fxdpcp,GenetiquementLb->Label,NULL);
     creer_fixed(100,450,fxdpcp,CbGenetiquement->comboBox,NULL);

           /** DIABETE **/
     creer_fixed(300,430,fxdpcp,DiabeteLb->Label,NULL);
     creer_fixed(300,450,fxdpcp,CbDiabete->comboBox,NULL);

           /** CARDIAQUE **/
     creer_fixed(500,430,fxdpcp,CardiaqueLb->Label,NULL);
     creer_fixed(500,450,fxdpcp,CbCardiaque->comboBox,NULL);

           /** POUMONS **/
     creer_fixed(700,430,fxdpcp,PoumonsLb->Label,NULL);
     creer_fixed(700,450,fxdpcp,CbPoumons->comboBox,NULL);

           /** CANCERS **/
     creer_fixed(900,430,fxdpcp,CancersLb->Label,NULL);
     creer_fixed(900,450,fxdpcp,CbCancers->comboBox,NULL);

           /** TENSION ARTERIELLE**/
     creer_fixed(1100,430,fxdpcp,TarLb->Label,NULL);
     creer_fixed(1100,450,fxdpcp,CbTar->comboBox,NULL);

          /** DEJA MALADE COVID **/
     creer_fixed(1300,430,fxdpcp,DejaMaladeCovidLb->Label,NULL);
     creer_fixed(1300,450,fxdpcp,CbDjCovid->comboBox,NULL);

            /** MALADE COVID **/
     creer_fixed(1500,430,fxdpcp,MaladeCovidLb->Label,NULL);
     creer_fixed(1500,450,fxdpcp,CbMaladeCovid->comboBox,NULL);

           /** INFOS COVID TITRE **/
    creer_fixed(50,600,fxdpcp,InfosCovidLb->Label,NULL);

            /** TYPE COVID **/
     creer_fixed(100,630,fxdpcp,TypeCovidLb->Label,NULL);
     creer_fixed(100,650,fxdpcp,CbTypeCovid->comboBox,NULL);

            /** AVATARS **/
     creer_fixed(1300,230,fxdpcp,AvatarsLb->Label,NULL);
     creer_fixed(1300,250,fxdpcp,CbAvatars->comboBox,NULL);


     /** FIN DE INDIVIDU 1 **/

     /** BUTTONS **/
     creer_fixed(400,800,fxdpcp,ValiderBtn->MonBoutton,NULL);
     creer_fixed(600,800,fxdpcp,AnnulerBtn->MonBoutton,NULL);
     creer_fixed(800,800,fxdpcp,TerminerBtn->MonBoutton,NULL);

     /** FIN DE CREATION FIXED **/

     /** PLACEHOLDER **/

     /** INDIVIDU 1 **/
     gtk_entry_set_placeholder_text(NomE1->entry,"Nom complet..");
     gtk_entry_set_placeholder_text(PosX1->entry,"Position X..");
     gtk_entry_set_placeholder_text(PosY1->entry,"Position Y..");
     /** FIN DE INDIVIDU 1 **/



     /** FIN PLACEHOLDER **/

     /** STYLE **/
     style(Titre->Label,"TitreITRMalade");

     /** STYLE INDIV 1 **/
     style(Indiv1Titre->Label,"Indiv1Titre");
     style(BilanSanteLb->Label,"Indiv1Titre");
     style(InfosCovidLb->Label,"Indiv1Titre");
     style(Indiv1Nom->Label,"TitreLabel");
     style(Indiv1Position->Label,"TitreLabel");
     style(Indiv1Age->Label,"TitreLabel");
     style(Indiv1MvType->Label,"TitreLabel");
     style(Indiv1Sexe->Label,"TitreLabel");
     style(GenetiquementLb->Label,"TitreLabel");
     style(DiabeteLb->Label,"TitreLabel");
     style(CardiaqueLb->Label,"TitreLabel");
     style(PoumonsLb->Label,"TitreLabel");
     style(CancersLb->Label,"TitreLabel");
     style(TarLb->Label,"TitreLabel");
     style(DejaMaladeCovidLb->Label,"TitreLabel");
     style(TypeCovidLb->Label,"TitreLabel");
     style(MaladeCovidLb->Label,"TitreLabel");
     style(AvatarsLb->Label,"TitreLabel");
     /** FIN DE STYLE INDIV 1**/


     style(ValiderBtn->MonBoutton,"ValiderBtn");
     style(AnnulerBtn->MonBoutton,"AnnulerBtn");
     /** FIN DE STYLE **/

     /** SIZE **/
     gtk_widget_set_size_request(CbGenetiquement->comboBox,150,20);
     gtk_widget_set_size_request(CbDiabete->comboBox,150,20);
     gtk_widget_set_size_request(CbCardiaque->comboBox,150,20);
     gtk_widget_set_size_request(CbPoumons->comboBox,150,20);
     gtk_widget_set_size_request(CbCancers->comboBox,150,20);
     gtk_widget_set_size_request(CbTar->comboBox,150,20);
     gtk_widget_set_size_request(CbDjCovid->comboBox,150,20);
     gtk_widget_set_size_request(CbTypeCovid->comboBox,150,20);
     gtk_widget_set_size_request(CbMaladeCovid->comboBox,150,20);
     gtk_widget_set_size_request(CbAvatars->comboBox,150,20);
     /** SIZE **/


     /** SIGNALS **/
     g_signal_connect (G_OBJECT (ValiderBtn->MonBoutton), "clicked",G_CALLBACK (CreationIndividu),NULL);
     g_signal_connect (G_OBJECT (TerminerBtn->MonBoutton), "clicked",G_CALLBACK (TerminerCreationIndividus),NULL);
     g_signal_connect (G_OBJECT (CbMaladeCovid->comboBox), "changed",G_CALLBACK (MaladeCovidChamps),NULL);
     /** FIN SIGNALS **/

     gtk_container_add(Sw->scrollWindow,fxdpcp->fixed);
     gtk_container_add(FN->Mafenetre,Sw->scrollWindow);
     gtk_widget_show_all(FN->Mafenetre);

     /** HIDE WIDGETS **/
     gtk_widget_hide(InfosCovidLb->Label);
     gtk_widget_hide(TypeCovidLb->Label);
     gtk_widget_hide(CbTypeCovid->comboBox);
     /** FIN DE HIDE WIDGETS **/

}

/** ----------------------------------- FIN DU FONCTION DE LA FENETRE DU GESTION DES INDIVIDUS MALADES ---------------------------------------------------------**/











/** -------------------------------- FONCTION DE LA FENETRE DE LISTE DES INDIVIDUS -----------------------------------------------------------------------------**/

void FenetreListeIndividus(GtkWidget *widget,gpointer *data)
{
    scrollWindow *sw;
    Label *TitrePcp,*Nomlb,*MaladeCvdLb,*SexeLb,*BaseVideLb,*AgeLb,*PositionLb,*TypeMvLb,*IndivIdLb;
    FIXED *fxd;
    gint indMalade = 0;
    gint NbIndiv =0 ;
    gint DernierY = 200;
    ListeInfos *nvelem,*ListeInf,*PtcrtListe;
    ListeInf = NULL;
    CelluleIndiv *Ptcrt;
    gchar Age[26],TypeMouvement[26];

    /** -------------------- FENETRE --------------------**/
    FNListeIndiv = init_window(0,0,1000,2000,"Liste des individus","");
    FNListeIndiv = create_window2(FNListeIndiv);

    sw = initi_scrollwindow(NULL,0,0,0);
    sw = create_scrollwindow(sw);

    gtk_window_set_icon_from_file   (FNListeIndiv->Mafenetre, "icone_corona.jpg", NULL);
    /** --------------------- FIN DE FENETRE -------------**/

    /** -------------------- LABELS ------------------------**/
    TitrePcp = Creation_Initialisation_Structure_Label("Interface de gestion des individus","",0,0,0,0);
    TitrePcp = Creer_Label(TitrePcp);

    Nomlb = Creation_Initialisation_Structure_Label("Nom Complet","",0,0,0,0);
    Nomlb = Creer_Label(Nomlb);

    MaladeCvdLb = Creation_Initialisation_Structure_Label("Malade Covid","",0,0,0,0);
    MaladeCvdLb = Creer_Label(MaladeCvdLb);

    SexeLb = Creation_Initialisation_Structure_Label("Sexe","",0,0,0,0);
    SexeLb = Creer_Label(SexeLb);

    BaseVideLb = Creation_Initialisation_Structure_Label("Votre base d'informations est vide actuellement.","",0,0,0,0);
    BaseVideLb = Creer_Label(BaseVideLb);

    AgeLb = Creation_Initialisation_Structure_Label("Age","",0,0,0,0);
    AgeLb = Creer_Label(AgeLb);

    PositionLb = Creation_Initialisation_Structure_Label("Position initiale {X,Y}","",0,0,0,0);
    PositionLb = Creer_Label(PositionLb);

    TypeMvLb = Creation_Initialisation_Structure_Label("Type mouvement","",0,0,0,0);
    TypeMvLb = Creer_Label(TypeMvLb);

    IndivIdLb = Creation_Initialisation_Structure_Label("Id","",0,0,0,0);
    IndivIdLb = Creer_Label(IndivIdLb);


    /** -------------------- FIN DE LABELS ------------------**/

    /** --------------------- FIXED --------------------------**/
    fxd = init_fixed();
    /** --------------------- FIN DE FIXED -------------------**/

    /** -------------------- CREATION FIXED -------------------**/
    creer_fixed(700,100,fxd,TitrePcp->Label,NULL);
    creer_fixed(20,200,fxd,IndivIdLb->Label,NULL);
    creer_fixed(100,200,fxd,Nomlb->Label,NULL);
    creer_fixed(400,200,fxd,MaladeCvdLb->Label,NULL);
    creer_fixed(700,200,fxd,SexeLb->Label,NULL);
    creer_fixed(1000,200,fxd,AgeLb->Label,NULL);
    creer_fixed(1300,200,fxd,PositionLb->Label,NULL);
    creer_fixed(1600,200,fxd,TypeMvLb->Label,NULL);
    /** -------------------- FIN DE CREATION FIXED --------------**/

    /** --------------------- CALCUL DU NOMBRE DES INDIVIDUS ------------------**/
    Ptcrt = BaseInfos[0];
    while(Ptcrt)
    {
        NbIndiv++;
        Ptcrt = Ptcrt->Suivant;
    }
    Ptcrt = BaseInfos[1];
    while(Ptcrt)
    {
        NbIndiv++;
        Ptcrt = Ptcrt->Suivant;
    }
    g_print("Nombre individus = %d",NbIndiv);
    /** --------------------- FIN DE CALCUL DU NOMBRE DES INDIVIDUS -------------**/

    /** -------------------- AFFICHAGE DES INFOS --------------------------------**/
    if(NbIndiv == 0) creer_fixed(600,400,fxd,BaseVideLb->Label,NULL);
    else
    {
        Ptcrt = BaseInfos[0];
        while(Ptcrt)
        {
            switch(Ptcrt->Age)
            {
                case 0: strcpy(Age,"Age<12");
                        break;
                case 1: strcpy(Age,"12<=Age<25");
                        break;
                case 2: strcpy(Age,"25<=Age<40");
                        break;
                case 3: strcpy(Age,"40<=Age<65");
                        break;
                case 4: strcpy(Age,"65<=Age");
                        break;
                default: strcpy(Age,"Undefined");
                         break;
            }

            switch(Ptcrt->TypeMv)
            {
                case 0: strcpy(TypeMouvement,"Aleatoirement");
                        break;
                case 1: strcpy(TypeMouvement,"Horizontalement");
                        break;
                case 2: strcpy(TypeMouvement,"Verticalement");
                        break;
                default: strcpy(TypeMouvement,"Undefined");
                         break;

            }

            if(Ptcrt->Sexe == 0) nvelem = CreerListeInfos(Ptcrt->Id,Ptcrt->Nomcomplet,"OUI","Homme",Age,Ptcrt->Pos_x,Ptcrt->Pos_y,TypeMouvement);
            else if (Ptcrt->Sexe == 1) nvelem = CreerListeInfos(Ptcrt->Id,Ptcrt->Nomcomplet,"OUI","FEMME",Age,Ptcrt->Pos_x,Ptcrt->Pos_y,TypeMouvement);
            else nvelem = CreerListeInfos(Ptcrt->Id,Ptcrt->Nomcomplet,"OUI","Non saisie!",Age,Ptcrt->Pos_x,Ptcrt->Pos_y,TypeMouvement);
            ListeInf = AjouterElemListeInfos(nvelem,ListeInf);
            style(nvelem->IndivMaladeCovidLb->Label,"IndivMaladeLb");
            Ptcrt = Ptcrt->Suivant;
        }
        Ptcrt = BaseInfos[1];
        while(Ptcrt)
        {
             switch(Ptcrt->Age)
            {
                case 0: strcpy(Age,"Age<12");
                        break;
                case 1: strcpy(Age,"12<=Age<25");
                        break;
                case 2: strcpy(Age,"25<=Age<40");
                        break;
                case 3: strcpy(Age,"40<=Age<65");
                        break;
                case 4: strcpy(Age,"65<=Age");
                        break;
                default: strcpy(Age,"Undefined");
                         break;
            }

            switch(Ptcrt->TypeMv)
            {
                case 0: strcpy(TypeMouvement,"Aleatoirement");
                        break;
                case 1: strcpy(TypeMouvement,"Horizontalement");
                        break;
                case 2: strcpy(TypeMouvement,"Verticalement");
                        break;
                default: strcpy(TypeMouvement,"Undefined");
                         break;

            }


            if(Ptcrt->Sexe == 0) nvelem = CreerListeInfos(Ptcrt->Id,Ptcrt->Nomcomplet,"NON","Homme",Age,Ptcrt->Pos_x,Ptcrt->Pos_y,TypeMouvement);
            else if (Ptcrt->Sexe == 1) nvelem = CreerListeInfos(Ptcrt->Id,Ptcrt->Nomcomplet,"NON","FEMME",Age,Ptcrt->Pos_x,Ptcrt->Pos_y,TypeMouvement);
            else nvelem = CreerListeInfos(Ptcrt->Id,Ptcrt->Nomcomplet,"NON","Non saisie!",Age,Ptcrt->Pos_x,Ptcrt->Pos_y,TypeMouvement);
            ListeInf = AjouterElemListeInfos(nvelem,ListeInf);
            style(nvelem->IndivMaladeCovidLb->Label,"IndivNonMaladeLb");
            Ptcrt = Ptcrt->Suivant;
        }
        PtcrtListe = ListeInf;
        while(PtcrtListe)
        {
            /** CREATION DES FIXED **/
            creer_fixed(20,DernierY+100,fxd,PtcrtListe->IndivIdLb->Label,NULL);
            creer_fixed(100,DernierY+100,fxd,PtcrtListe->IndivNomLb->Label,NULL);
            creer_fixed(400,DernierY+100,fxd,PtcrtListe->IndivMaladeCovidLb->Label,NULL);
            creer_fixed(700,DernierY+100,fxd,PtcrtListe->IndivSexeLb->Label,NULL);
            creer_fixed(1000,DernierY+100,fxd,PtcrtListe->AgeLb->Label,NULL);
            creer_fixed(1300,DernierY+100,fxd,PtcrtListe->PositionLb->Label,NULL);
            creer_fixed(1600,DernierY+100,fxd,PtcrtListe->TypeMvLb->Label,NULL);
            creer_fixed(1800,DernierY+100,fxd,PtcrtListe->ModifierIndivBtn->MonBoutton,NULL);
            /** FIN DE CREATION DES FIXED **/

            /** BOUTTONS SIGNALS (MODIFIER BOUTTON)**/
            g_signal_connect (G_OBJECT (PtcrtListe->ModifierIndivBtn->MonBoutton), "clicked",G_CALLBACK (FenetreModifierIndiv),PtcrtListe->IndivIdLb->Label);
            /** FIN DE BOUTTON SIGNALS (MODIFIER BOUTTON)**/

            /** STYLE **/
            style(PtcrtListe->IndivIdLb->Label,"IndivInfosLb");
            style(PtcrtListe->IndivNomLb->Label,"IndivInfosLb");
            style(PtcrtListe->IndivSexeLb->Label,"IndivInfosLb");
            style(PtcrtListe->AgeLb->Label,"IndivInfosLb");
            style(PtcrtListe->PositionLb->Label,"IndivInfosLb");
            style(PtcrtListe->TypeMvLb->Label,"IndivInfosLb");
            /** FIN DE STYLE **/

            DernierY = DernierY +100;
            PtcrtListe = PtcrtListe->Suivant;
        }
    }

    /** -------------------- FIN DE AFFICHAGE DES INFOS --------------------------**/


    /** --------------------- STYLE ------------------------------**/
    style(FNListeIndiv->Mafenetre,"ListeIndivFN");
    style(TitrePcp->Label,"ListeIndivTitre");
    style(Nomlb->Label,"ListeIndivLabels");
    style(IndivIdLb->Label,"IdLabel");
    style(MaladeCvdLb->Label,"ListeIndivLabels");
    style(SexeLb->Label,"ListeIndivLabels");
    style(AgeLb->Label,"ListeIndivLabels");
    style(PositionLb->Label,"ListeIndivLabels");
    style(TypeMvLb->Label,"ListeIndivLabels");
    style(BaseVideLb->Label,"BaseInfoVideLb");
    /** -------------------- FIN DE STYLE --------------------------**/



    gtk_container_add(sw->scrollWindow,fxd->fixed);
    gtk_container_add(FNListeIndiv->Mafenetre,sw->scrollWindow);
    gtk_widget_show_all(FNListeIndiv->Mafenetre);

}

/** -------------------------------- FIN DE FONCTION DE LA FENETRE DE LISTE DES INDIVIDUS -----------------------------------------------------------------------------**/








void sauvegarder_jeu(GtkWidget *widget,gpointer *data)
{
    CelluleIndiv*Ptcr;
    FILE*fp;
    fp=fopen(nomf,"w");
    Ptcr=BaseInfos[0];
    while(Ptcr)
    {
        fprintf(fp,"%d",Ptcr->Id);
        fputs(",",fp);
        fprintf(fp,"%d",Ptcr->MaladeCovid);
        fputs(",",fp);
        fprintf(fp,"%s",Ptcr->Nomcomplet);
        fputs(",",fp);
        fprintf(fp,"%d",Ptcr->Age);
        fputs(",",fp);
        fprintf(fp,"%d",Ptcr->Sexe);
        fputs(",",fp);
        fprintf(fp,"%d",Ptcr->Genetiquement);
        fputs(",",fp);
        fprintf(fp,"%d",Ptcr->Diabete);
        fputs(",",fp);
        fprintf(fp,"%d",Ptcr->Cardiaque);
        fputs(",",fp);
        fprintf(fp,"%d",Ptcr->Poumons);
        fputs(",",fp);
        fprintf(fp,"%d",Ptcr->Cancers);
        fputs(",",fp);
        fprintf(fp,"%d",Ptcr->Tar);
        fputs(",",fp);
        fprintf(fp,"%d",Ptcr->DjCovid);
        fputs(",",fp);
        fprintf(fp,"%d",Ptcr->TypeCovid);
        fputs(",",fp);
        fprintf(fp,"%d",Ptcr->TypeMv);
        fputs(",",fp);
        fprintf(fp,"%d",Ptcr->Pos_x);
        fputs(",",fp);
        fprintf(fp,"%d",Ptcr->Pos_y);
        fputs(",",fp);
        fprintf(fp,"%d",Ptcr->MvH);
        fputs(",",fp);
        fprintf(fp,"%d",Ptcr->MvV);
        fputs(",",fp);
        fprintf(fp,"%d",Ptcr->Score);
        fputs(",",fp);
        fprintf(fp,"%d",Ptcr->Avatar);
        fputs(",",fp);
        fprintf(fp,"%d",Ptcr->EstMort);
        fputs("\n",fp);
        Ptcr=Ptcr->Suivant;
    }
    Ptcr=BaseInfos[1];
    while(Ptcr)
    {
        fprintf(fp,"%d",Ptcr->Id);
        fputs(",",fp);
        fprintf(fp,"%d",Ptcr->MaladeCovid);
        fputs(",",fp);
        fprintf(fp,"%s",Ptcr->Nomcomplet);
        fputs(",",fp);
        fprintf(fp,"%d",Ptcr->Age);
        fputs(",",fp);
        fprintf(fp,"%d",Ptcr->Sexe);
        fputs(",",fp);
        fprintf(fp,"%d",Ptcr->Genetiquement);
        fputs(",",fp);
        fprintf(fp,"%d",Ptcr->Diabete);
        fputs(",",fp);
        fprintf(fp,"%d",Ptcr->Cardiaque);
        fputs(",",fp);
        fprintf(fp,"%d",Ptcr->Poumons);
        fputs(",",fp);
        fprintf(fp,"%d",Ptcr->Cancers);
        fputs(",",fp);
        fprintf(fp,"%d",Ptcr->Tar);
        fputs(",",fp);
        fprintf(fp,"%d",Ptcr->DjCovid);
        fputs(",",fp);
        fprintf(fp,"%d",Ptcr->TypeCovid);
        fputs(",",fp);
        fprintf(fp,"%d",Ptcr->TypeMv);
        fputs(",",fp);
        fprintf(fp,"%d",Ptcr->Pos_x);
        fputs(",",fp);
        fprintf(fp,"%d",Ptcr->Pos_y);
        fputs(",",fp);
        fprintf(fp,"%d",Ptcr->MvH);
        fputs(",",fp);
        fprintf(fp,"%d",Ptcr->MvV);
        fputs(",",fp);
        fprintf(fp,"%d",Ptcr->Score);
        fputs(",",fp);
        fprintf(fp,"%d",Ptcr->Avatar);
        fputs("\n",fp);
        Ptcr=Ptcr->Suivant;
    }
    fclose(fp);
}





gboolean Open_PlayArea(GtkWidget *widget,gpointer *data)
{
   CelluleIndiv *Ptcrt;
   TOOLbar *Tbar;
   gchar IndivTooltip[100];
   gchar IndivId[5];



   /** ------------ FENETRE --------------------------------**/
   playarea = init_window(0,0,1000,1600,"Play area","playarea");
   playarea = create_window2(playarea);

   gtk_window_set_icon_from_file   (playarea->Mafenetre, "icone_corona.jpg", NULL);
   /** ------------- FIN DE FENETRE -------------------------**/

   /** -------------- TOOLBAR ---------------------------------**/
    Tbar=initi_toolbar(GTK_TOOLBAR_ICONS,1,'h');
    create_toolbar(Tbar);
    PareaPlay=creer_toolitem(Tbar,1,"media-playback-start",NULL);
    PareaPause=creer_toolitem(Tbar,2,"media-playback-pause",NULL);
    PareaAfficher = creer_toolitem(Tbar,3,"edit-find",NULL);
    PareaSupprimer = creer_toolitem(Tbar,4,"edit-delete",NULL);
    PareaSave=creer_toolitem(Tbar,5,"document-save",NULL);
    gtk_widget_set_size_request(Tbar->toolbar ,200,50);


   /** --------------- FIN DE TOOLBAR --------------------------**/

   /** --------------- FIXED ------------------------------------**/
   Farea = init_fixed();
   creer_fixed(700,0,Farea,Tbar->toolbar,NULL);
   /** --------------- FIN DE FIXED ------------------------------**/
    calcul_score(BaseInfos);
   /** ------------- INDIVIDUS --------------------------------**/
   Ptcrt = BaseInfos[0];
   while(Ptcrt)
   {
       switch(Ptcrt->Avatar)
       {

           case 0: Ptcrt->IndivImage = Image_init("avatars/Blue_amongUS.png",0,0);
                     Ptcrt->VirusImage = Image_init("greenvirus.png",0,0);
                   break;
           case 1: Ptcrt->IndivImage = Image_init("avatars/green_amongUS.png",0,0);
                   Ptcrt->VirusImage = Image_init("greenvirus.png",0,0);
                   break;
           case 2: Ptcrt->IndivImage = Image_init("avatars/orange_amongUS.png",0,0);
                   Ptcrt->VirusImage = Image_init("greenvirus.png",0,0);
                   break;
           case 3: Ptcrt->IndivImage = Image_init("avatars/pink_amongUS.png",0,0);
                   Ptcrt->VirusImage = Image_init("greenvirus.png",0,0);
                   break;
           case 4: Ptcrt->IndivImage = Image_init("avatars/purple_amongUS.png",0,0);
                   Ptcrt->VirusImage = Image_init("greenvirus.png",0,0);
                   break;
           case 5: Ptcrt->IndivImage = Image_init("avatars/yellow_amongUS.png",0,0);
                   Ptcrt->VirusImage = Image_init("greenvirus.png",0,0);
                   break;
           case 6: Ptcrt->IndivImage = Image_init("avatars/blue_deadbody.png",0,0);
                   Ptcrt->VirusImage = Image_init("greenvirus.png",0,0);
                   break;
           case 7: Ptcrt->IndivImage = Image_init("avatars/green_deadbody.png",0,0);
                   Ptcrt->VirusImage = Image_init("greenvirus.png",0,0);
                   break;
           case 8: Ptcrt->IndivImage = Image_init("avatars/orange_deadbody.png",0,0);
                   Ptcrt->VirusImage = Image_init("greenvirus.png",0,0);
                   break;
           case 9: Ptcrt->IndivImage = Image_init("avatars/pink_deadbody.png",0,0);
                   Ptcrt->VirusImage = Image_init("greenvirus.png",0,0);
                   break;
           case 10: Ptcrt->IndivImage = Image_init("avatars/purple_deadbody.png",0,0);
                    Ptcrt->VirusImage = Image_init("greenvirus.png",0,0);
                   break;
           case 11: Ptcrt->IndivImage = Image_init("avatars/yellow_deadbody.png",0,0);
                    Ptcrt->VirusImage = Image_init("greenvirus.png",0,0);
                   break;
       }
       Ptcrt->IndivImage = Image_create(Ptcrt->IndivImage);
       Ptcrt->VirusImage = Image_create(Ptcrt->VirusImage);
       AfficherInfosIndiv(Ptcrt->Id,BaseInfos,IndivTooltip);
       gtk_widget_set_tooltip_text(Ptcrt->IndivImage->image,IndivTooltip);
       creer_fixed(Ptcrt->Pos_x,Ptcrt->Pos_y,Farea,Ptcrt->IndivImage->ImageEbox,NULL);
       creer_fixed(Ptcrt->Pos_x+10,Ptcrt->Pos_y-20,Farea,Ptcrt->VirusImage->ImageEbox,NULL);
       itoa(Ptcrt->Id,IndivId,5);
       gtk_widget_set_name(Ptcrt->IndivImage->ImageEbox,IndivId);
       Ptcrt = Ptcrt->Suivant;
   }
   Ptcrt = BaseInfos[1];
   while(Ptcrt)
   {
        switch(Ptcrt->Avatar)
       {
             case 0: Ptcrt->IndivImage = Image_init("avatars/Blue_amongUS.png",0,0);
                   break;
           case 1: Ptcrt->IndivImage = Image_init("avatars/green_amongUS.png",0,0);
                   break;
           case 2: Ptcrt->IndivImage = Image_init("avatars/orange_amongUS.png",0,0);
                   break;
           case 3: Ptcrt->IndivImage = Image_init("avatars/pink_amongUS.png",0,0);
                   break;
           case 4: Ptcrt->IndivImage = Image_init("avatars/purple_amongUS.png",0,0);
                   break;
           case 5: Ptcrt->IndivImage = Image_init("avatars/yellow_amongUS.png",0,0);
                   break;
           case 6: Ptcrt->IndivImage = Image_init("avatars/blue_deadbody.png",0,0);
                   break;
           case 7: Ptcrt->IndivImage = Image_init("avatars/green_deadbody.png",0,0);
                   break;
           case 8: Ptcrt->IndivImage = Image_init("avatars/orange_deadbody.png",0,0);
                   break;
           case 9: Ptcrt->IndivImage = Image_init("avatars/pink_deadbody.png",0,0);
                   break;
           case 10: Ptcrt->IndivImage = Image_init("avatars/purple_deadbody.png",0,0);
                   break;
           case 11: Ptcrt->IndivImage = Image_init("avatars/yellow_deadbody.png",0,0);
                   break;
       }
       Ptcrt->IndivImage = Image_create(Ptcrt->IndivImage);
       AfficherInfosIndiv(Ptcrt->Id,BaseInfos,IndivTooltip);
       gtk_widget_set_tooltip_text(Ptcrt->IndivImage->image,IndivTooltip);
       creer_fixed(Ptcrt->Pos_x,Ptcrt->Pos_y,Farea,Ptcrt->IndivImage->ImageEbox,NULL);
       itoa(Ptcrt->Id,IndivId,5);
       gtk_widget_set_name(Ptcrt->IndivImage->ImageEbox,IndivId);
       Ptcrt = Ptcrt->Suivant;
   }
   /** -------------- FIN DE INDIVIDUS --------------------------**/

   /** ---------------- STYLE ------------------------------------**/
   style(Tbar->toolbar,"PlayTbar");
   /** ------------------ FIN DE STYLE ---------------------------**/

   g_signal_connect(PareaPlay,"clicked",G_CALLBACK(CommencerMouvement),NULL);
   g_signal_connect(PareaPause,"clicked",G_CALLBACK(StoperMouvementIndivs),NULL);
   g_signal_connect(PareaSave,"clicked",G_CALLBACK(sauvegarder_jeu),NULL);
   g_signal_connect(PareaAfficher,"clicked",G_CALLBACK(ActivationSignalsInfosIndivs),NULL);
   g_signal_connect(PareaSupprimer,"clicked",G_CALLBACK(ActivateSignalSuppression),NULL);
   gtk_widget_set_sensitive(PareaPause,FALSE);
   gtk_container_add(playarea->Mafenetre,Farea->fixed);
   gtk_widget_show_all(playarea->Mafenetre);
   //g_timeout_add_seconds(1,CalculerTempsMaladie,NULL);
   /********CSS******/
    style(playarea->Mafenetre,playarea->name);
}

/************************************************************* FONCTION SAUVEGARDE ******************************************/

/************************************************************* FIN DE LA FONCTION DE SAUVEGARDE ************************/
int Convertir_Caractere_En_Entier(char* car)
{
    return((int)*car - '0');
}
/************************************************************** FONCTION REMPLIR BASE INFO*********************************/
void Remplir_base_information()
{
    char ligne[200];
    const char separateur[2]=",";
    char*token;
    int i=0;
    CelluleIndiv*NvIndiv;
    int val;
    FILE*fp;
    fp=fopen(nomf,"r");
    if(fp==NULL)
    {
        printf("\naucune partie  n'est enregistrer!!\n");
    }
    while(fgets(ligne,sizeof(ligne),fp))
    {
        token=strtok(ligne,separateur);
        NvIndiv=Creer_Individu(0,"soufiane",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
        if(!NvIndiv)
        {
            printf("\nerreur d'allocation (nouveau indiv [remplissage base info]) \n");
            exit(0);
        }
        while(token)
        {

            switch(i)
            {
                case 0 :
                    val=Convertir_Caractere_En_Entier(token);
                    NvIndiv->Id=val;
                    printf("\n%d",NvIndiv->Id);
                    break;
                case 1 :
                    val=Convertir_Caractere_En_Entier(token);
                    NvIndiv->MaladeCovid=val;
                    printf(" , %d",NvIndiv->MaladeCovid);
                    break;
                case 2 :
                    strcpy(NvIndiv->Nomcomplet,token);
                    printf(" , %s ", NvIndiv->Nomcomplet);
                    break;
                case 3 :
                    val=Convertir_Caractere_En_Entier(token);
                    NvIndiv->Age=val;
                    printf(" , %d ", NvIndiv->Age);
                    break;
                case 4 :
                    val=Convertir_Caractere_En_Entier(token);
                    NvIndiv->Sexe=val;
                    printf(" , %d",NvIndiv->Sexe);
                    break;
                case 5 :
                    val=Convertir_Caractere_En_Entier(token);
                    NvIndiv->Genetiquement=val;
                    printf(" , %d", NvIndiv->Genetiquement);
                    break;
                case 6 :
                    val=Convertir_Caractere_En_Entier(token);
                    NvIndiv->Diabete=val;
                    printf(" , %d ",NvIndiv->Diabete);
                    break;
                case 7 :
                    val = Convertir_Caractere_En_Entier(token);
                    NvIndiv->Cardiaque=val;
                    printf(" , %d ", NvIndiv->Cardiaque);
                    break;
                case 8 :
                    val= Convertir_Caractere_En_Entier(token);
                    NvIndiv->Poumons=val;
                    printf(" , %d ", NvIndiv->Poumons);
                    break;
                case 9  :
                    val = Convertir_Caractere_En_Entier(token);
                    NvIndiv->Cancers=val;
                    printf(" , %d", NvIndiv->Cancers);
                    break;
                case 10 :
                    val=Convertir_Caractere_En_Entier(token);
                    NvIndiv->Tar=val;
                    printf(" , %d", NvIndiv->Tar);
                    break;
                case 11 :
                    val=Convertir_Caractere_En_Entier(token);
                    NvIndiv->DjCovid=val;
                    printf(" , %d ", NvIndiv->DjCovid);
                    break;
                case 12 :
                    val=Convertir_Caractere_En_Entier(token);
                    NvIndiv->TypeCovid=val;
                    printf(" , %d", NvIndiv->TypeCovid);
                    break;
                case 13 :
                    val=Convertir_Caractere_En_Entier(token);
                    NvIndiv->TypeMv=val;
                    printf(" , %d ",NvIndiv->TypeMv);
                    break;
                case 14 :
                    //val=Convertir_Caractere_En_Entier(token);
                    NvIndiv->Pos_x=atoi(token);
                    printf(" , %d", NvIndiv->Pos_x);
                    break;
                case 15 :
                    //val=Convertir_Caractere_En_Entier(token);
                    NvIndiv->Pos_y=atoi(token);
                    printf(" , %d ", NvIndiv->Pos_y);
                    break;
                case 16 :
                   // val=Convertir_Caractere_En_Entier(token);
                    NvIndiv->MvH=atoi(token);
                    printf(" , %d ", NvIndiv->MvH);
                    break;
                case 17 :
                    //val=Convertir_Caractere_En_Entier(token);
                    NvIndiv->MvV=atoi(token);
                    printf(" , %d ",NvIndiv->MvV);
                    break;
                case 18:
                    NvIndiv->Score = atoi(token);
                    printf(" , %d ", NvIndiv->Score);
                    break;
                case 19:
                    NvIndiv->Avatar = atoi(token);
                    printf(" , %d ", NvIndiv->Avatar);
                    break;
                 case 20:
                    NvIndiv->EstMort = atoi(token);
                    printf(" , %d ", NvIndiv->EstMort);
                    break;
            }
            token=strtok(NULL,",");
            i++;
        }
        AjouterIndivBaseInfo(NvIndiv,BaseInfos);
        i=0;
    }
    fclose(fp);
}

/*************************************************************** FIN DE LA FONCTION DE REMPLISSAGE **********************/


void cb_create1(GtkWidget *widget,gpointer *data)
{
    InitialiserBaseInfos(BaseInfos);
    nomf=gtk_entry_get_text (GTK_ENTRY (E111->entry));
    strcat(nomf,".txt");
    gtk_button_released(widget);

/**-------------------------------------------------------WINDOW----------------------------------------------------------**/
    Fenetre *s;
    s=init_window(0,0,700,1400,"interface de simulation","intrfc");
    s=create_window2(s);

    gtk_window_set_icon_from_file   (s->Mafenetre, "icone_corona.jpg", NULL);
/**-------------------------------------------------------FIXED---------------------------------------------------------**/
    FIXED *zone;
    zone=init_fixed();

/**------------------------------------------------------TOOLBAR---------------------------------------------------------**/
    TOOLbar *Toolbar,*t;
    /*Toolbar=initi_toolbar(GTK_TOOLBAR_ICONS,1,'h');
    create_toolbar(Toolbar);
    GtkToolItem *info,*quit,*save,*smile,*neww,*play,*pause;
    gtk_widget_set_size_request(Toolbar->toolbar ,1300,40);
    info=creer_toolitem(Toolbar,1,"help-about",NULL);
    quit=creer_toolitem(Toolbar,3,"application-exit",NULL);
    save=creer_toolitem(Toolbar,4,"document-save",NULL);
    smile=creer_toolitem(Toolbar,5,"face-smile",NULL);
    neww=creer_toolitem(Toolbar,5,"document-new",NULL);
    creer_fixed(5,5,zone,Toolbar->toolbar,NULL);
    gtk_widget_set_name(Toolbar->toolbar,"tool");*/
    GtkToolItem*play,*pause;
    t=initi_toolbar(GTK_TOOLBAR_ICONS,1,'h');
    create_toolbar(t);
    play=creer_toolitem(t,5,"media-playback-start",NULL);
    pause=creer_toolitem(t,5,"media-playback-pause",NULL);
    gtk_widget_set_size_request(t->toolbar ,100,30);
    creer_fixed(1000,600,zone,t->toolbar,NULL);
      /*gtk_widget_set_tooltip_text (info, "Iformations");
      gtk_widget_set_tooltip_text (quit, "Quitter");
      gtk_widget_set_tooltip_text (save, "Sauvegarder");
      gtk_widget_set_tooltip_text (smile, "hhhhhhhh");
      gtk_widget_set_tooltip_text (neww, "Nouveau fichier");*/
      gtk_widget_set_tooltip_text (play, "Play");
      gtk_widget_set_tooltip_text (pause, "Pause");
      g_signal_connect(play, "clicked",G_CALLBACK(Open_PlayArea), NULL);



/**------------------------------------------------------buttons---------------------------------------------------------**/
    Button*ajouter,*IndivListeBtn;
    ajouter=initialise_simple_button("ajouter","ajouter",FALSE,NULL);
    ajouter=Creer_Button(ajouter);
    creer_fixed(1140,600,zone,ajouter->MonBoutton,NULL);
    g_signal_connect(ajouter->MonBoutton, "clicked",G_CALLBACK(FenetreGestionIndivMalades), NULL);
    gtk_widget_set_tooltip_text (ajouter->MonBoutton, "ajouter un individu dans la base de donnees et/ou dans l'interface du jeu");

    IndivListeBtn=initialise_simple_button("","Liste des individus",FALSE,NULL);
    IndivListeBtn=Creer_Button(IndivListeBtn);
    creer_fixed(100,600,zone,IndivListeBtn->MonBoutton,NULL);
    g_signal_connect(IndivListeBtn->MonBoutton, "clicked",G_CALLBACK(FenetreListeIndividus), NULL);


/**----------------------------------------------------------CSS------------------------------------------------------------**/
    style(s->Mafenetre,s->name);
//    style(Toolbar->toolbar,"tool1");
    style(t->toolbar,"tool2");



    style(ajouter->MonBoutton,ajouter->name);
    style(IndivListeBtn->MonBoutton,ajouter->name);

    gtk_container_add(GTK_CONTAINER (s->Mafenetre),zone->fixed);

    gtk_widget_show_all(s->Mafenetre);

}

void cb_create2(GtkWidget *widget,gpointer *data)
{
    nomf=gtk_entry_get_text (GTK_ENTRY (E111->entry));
    strcat(nomf,".txt");
    Remplir_base_information();
    gtk_button_released(widget);
    DernierIdInsere = ChercherMaxIdBaseInfos(BaseInfos);

/**-------------------------------------------------------WINDOW----------------------------------------------------------**/
    Fenetre *s;
    s=init_window(0,0,700,1400,"interface de simulation","intrfc");
    s=create_window2(s);

    gtk_window_set_icon_from_file   (s->Mafenetre, "icone_corona.jpg", NULL);
/**-------------------------------------------------------FIXED---------------------------------------------------------**/
    FIXED *zone;
    zone=init_fixed();

/**------------------------------------------------------TOOLBAR---------------------------------------------------------**/
    TOOLbar *Toolbar,*t;
    /*Toolbar=initi_toolbar(GTK_TOOLBAR_ICONS,1,'h');
    create_toolbar(Toolbar);
    GtkToolItem *info,*quit,*save,*smile,*neww,*play,*pause;
    gtk_widget_set_size_request(Toolbar->toolbar ,1300,40);
    info=creer_toolitem(Toolbar,1,"help-about",NULL);
    quit=creer_toolitem(Toolbar,3,"application-exit",NULL);
    save=creer_toolitem(Toolbar,4,"document-save",NULL);
    smile=creer_toolitem(Toolbar,5,"face-smile",NULL);
    neww=creer_toolitem(Toolbar,5,"document-new",NULL);
    creer_fixed(5,5,zone,Toolbar->toolbar,NULL);
    gtk_widget_set_name(Toolbar->toolbar,"tool");*/
    GtkToolItem*play,*pause;
    t=initi_toolbar(GTK_TOOLBAR_ICONS,1,'h');
    create_toolbar(t);
    play=creer_toolitem(t,5,"media-playback-start",NULL);
    pause=creer_toolitem(t,5,"media-playback-pause",NULL);
    gtk_widget_set_size_request(t->toolbar ,100,30);
    creer_fixed(1000,600,zone,t->toolbar,NULL);
      /*gtk_widget_set_tooltip_text (info, "Iformations");
      gtk_widget_set_tooltip_text (quit, "Quitter");
      gtk_widget_set_tooltip_text (save, "Sauvegarder");
      gtk_widget_set_tooltip_text (smile, "hhhhhhhh");
      gtk_widget_set_tooltip_text (neww, "Nouveau fichier");*/
      gtk_widget_set_tooltip_text (play, "Play");
      gtk_widget_set_tooltip_text (pause, "Pause");
      g_signal_connect(play, "clicked",G_CALLBACK(Open_PlayArea), NULL);






/**------------------------------------------------------buttons---------------------------------------------------------**/
    Button*ajouter,*IndivListeBtn;
    ajouter=initialise_simple_button("ajouter","ajouter",FALSE,NULL);
    ajouter=Creer_Button(ajouter);
    creer_fixed(1140,600,zone,ajouter->MonBoutton,NULL);
    g_signal_connect(ajouter->MonBoutton, "clicked",G_CALLBACK(FenetreGestionIndivMalades), NULL);
    gtk_widget_set_tooltip_text (ajouter->MonBoutton, "ajouter un individu dans la base de donnees et/ou dans l'interface du jeu");

    IndivListeBtn=initialise_simple_button("","Liste des individus",FALSE,NULL);
    IndivListeBtn=Creer_Button(IndivListeBtn);
    creer_fixed(100,600,zone,IndivListeBtn->MonBoutton,NULL);
    g_signal_connect(IndivListeBtn->MonBoutton, "clicked",G_CALLBACK(FenetreListeIndividus), NULL);


/**----------------------------------------------------------CSS------------------------------------------------------------**/
    style(s->Mafenetre,s->name);
//    style(Toolbar->toolbar,"tool1");
    style(t->toolbar,"tool2");



    style(ajouter->MonBoutton,ajouter->name);
    style(IndivListeBtn->MonBoutton,ajouter->name);

    gtk_container_add(GTK_CONTAINER (s->Mafenetre),zone->fixed);

    gtk_widget_show_all(s->Mafenetre);

}
/**********************************************************Nouveau fichier********************************/
void New_file(GtkWidget *widget,gpointer *data)
{
    Fenetre*fnw;
    scrollWindow*s12;
    FIXED*zone;
    Label*Lnw;

    Button*b1;


    zone=init_fixed();


    fnw=init_window(0,0,800,1000,"creer fichier","creerfichier");
    fnw=create_window2(fnw);
    s12=initi_scrollwindow(NULL,0,0,0);
    s12=create_scrollwindow(s12);

    gtk_window_set_icon_from_file   (fnw->Mafenetre, "icone_corona.jpg", NULL);

    Lnw = Creation_Initialisation_Structure_Label("Donnez un nom a votre fichier","",0,0,0,0);
    Lnw = Creer_Label(Lnw);

    E111 = Entry_init(TRUE,NULL);
    E111 = Entry_create(E111);



    b1=initialise_simple_button("OK","OK",FALSE,NULL);
    b1=Creer_Button(b1);

    creer_fixed(400,400,zone,Lnw->Label,NULL);
    creer_fixed(400,455,zone,E111->entry,NULL);
    creer_fixed(510,510,zone,b1->MonBoutton,NULL);

    g_signal_connect(b1->MonBoutton, "clicked",G_CALLBACK(cb_create1), NULL);

    gtk_container_add(GTK_CONTAINER(s12->scrollWindow),zone->fixed);
    gtk_container_add(GTK_CONTAINER(fnw->Mafenetre),s12->scrollWindow);
    gtk_widget_show_all(fnw->Mafenetre);
    /*------------------CSS-------------------*/
    style(fnw->Mafenetre,fnw->name);
    style(b1->MonBoutton,b1->name);
    style(Lnw->Label,"ModifLabels2");

    gtk_window_set_position(GTK_WINDOW(fnw->Mafenetre), GTK_WIN_POS_CENTER_ALWAYS);

}
/***********************************************Continuer*************************************************/


void continuer(GtkWidget *widget,gpointer *data)
{
    Fenetre*fnw;
    scrollWindow*s12;
    FIXED*zone;
    Label*Lnw;

    Button*b1;


    zone=init_fixed();


    fnw=init_window(0,0,800,1000,"ouvrir fichier","creerfichier");
    fnw=create_window2(fnw);
    s12=initi_scrollwindow(NULL,0,0,0);
    s12=create_scrollwindow(s12);

    Lnw = Creation_Initialisation_Structure_Label("Entrer le nom de votre fichier sauvegarde","",0,0,0,0);
    Lnw = Creer_Label(Lnw);

    gtk_window_set_icon_from_file   (fnw->Mafenetre, "icone_corona.jpg", NULL);

    E111 = Entry_init(TRUE,NULL);
    E111 = Entry_create(E111);



    b1=initialise_simple_button("OK","OK",FALSE,NULL);
    b1=Creer_Button(b1);

    creer_fixed(355,400,zone,Lnw->Label,NULL);
    creer_fixed(400,455,zone,E111->entry,NULL);
    creer_fixed(510,510,zone,b1->MonBoutton,NULL);

    g_signal_connect(b1->MonBoutton, "clicked",G_CALLBACK(cb_create2), NULL);

    gtk_container_add(GTK_CONTAINER(s12->scrollWindow),zone->fixed);
    gtk_container_add(GTK_CONTAINER(fnw->Mafenetre),s12->scrollWindow);
    gtk_widget_show_all(fnw->Mafenetre);

    /*-----------------CSS---------------*/
    style(fnw->Mafenetre,fnw->name);
    style(b1->MonBoutton,b1->name);
    style(Lnw->Label,"ModifLabels2");
    gtk_window_set_position(GTK_WINDOW(fnw->Mafenetre), GTK_WIN_POS_CENTER_ALWAYS);

}


