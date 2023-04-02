void add_to_container(GtkWidget *container,GtkWidget* containing)
{
        gtk_container_add(GTK_CONTAINER (container),containing);
}
/** Inutile pour l'instant **/
gchar* Creation_Variable_gchar(const gchar* param)
{
    gchar* nvelem;
    nvelem = (gchar*)malloc(sizeof(gchar));
    if(!nvelem)
    {
        g_print("\nErreur d'allocation(gchar)\n");
        exit(0);
    }
    strcpy(nvelem,param);
    return(gchar*)nvelem;
}

/*********************************F E N E T R E*******************************************/

/** Fonction d'allocation de structure Fenetre*****/
Fenetre* Creation_Initialisation_Structure_Fenetre()
{
    Fenetre *Nvfenetre;
    Nvfenetre = (Fenetre*)malloc(sizeof(Fenetre));
    if(!Nvfenetre)
    {
        g_print("\n Erreur d'allocation (Fenetere)!\n");
        exit(0);
    }
    Nvfenetre->Fenetre_Mere = NULL;
    Nvfenetre->Resizable = TRUE;
    Nvfenetre->Titre = (gchar*)malloc(sizeof(gchar));
    Nvfenetre->Longueur = Nvfenetre->Hauteur = 1000;
    return(Fenetre*) Nvfenetre;
}

Fenetre* init_window(int x, int y,int h, int l,const gchar*titre,gchar*name)
{
Fenetre* Window = NULL;
//Allocation memoire
Window = (Fenetre*)malloc(sizeof(Fenetre));
// Test d'allocation
if(!Window)
{
g_print("\nErreur d'allocation !!!\n");
exit(1);
}
//Allocation du pointeur titre
Window->Titre = (gchar*)malloc(30*sizeof(gchar));
Window->name = (gchar*)malloc(30*sizeof(gchar));

Window->Fichier_icon=(gchar*)malloc(30*sizeof(gchar));
// affectation d'un titre a la fenetre
if(titre)
strcpy(Window->Titre,titre);
else
Window->Titre = NULL;
if(name)
strcpy(Window->name,name);
else
Window->name = NULL;
Window->Hauteur = h; // initialisation de la hauteur
Window->Longueur = l; // initialisation de la largeur // initialisation de la position
Window->Position_x = x;
Window->Position_y= y;
return (Fenetre*)Window; //Retourner la structure
}


/*************************************************************
La fonction : create_window
Entree :Un pointeur vers la structure WindowObject
initialis�e
Sortie : Un pointeur vers la variable WindowObject
Description : Cette fonction permet de cr�er une fen�tre en
Fct des param�tres r�cup�r�s de la structure
WindowObject
*************************************************************/
Fenetre* create_window(GtkApplication *app,Fenetre *WO)
{
//Creation de la fenetre
WO->Mafenetre= gtk_application_window_new(app);
gtk_widget_set_name(WO->Mafenetre,WO->name);
// Attribution d'un titre
if(WO->Titre)
gtk_window_set_title(GTK_WINDOW(WO->Mafenetre),WO->Titre);
// Si le user introduit une hauteur et une largeur
if((WO->Hauteur) && (WO->Longueur))
{
gtk_window_set_default_size(GTK_WINDOW(WO->Mafenetre),
(WO->Longueur),(WO->Hauteur));
}
if(WO->Resizable)
gtk_window_set_resizable(GTK_WINDOW(WO->Mafenetre),TRUE);
else //Si res = false, redimensionnement = FAUX
gtk_window_set_resizable(GTK_WINDOW(WO->Mafenetre),FALSE);
return (Fenetre*)WO;
}
/**********************************************************
La fonction : add_to_window
-Entrees :Un pointeur vers la variable WindowObject
elem :le GtkWidget � ajouter
-Sortie : ajout d'un GtkWidget � la fen�tre
-description: Cette fonction permet d'ajouter un widget � une
fenetre
**********************************************************/
/*void add_to_window(WindowObject* WO, GtkWidget* elem)
{
//Ajout de elem � WO
gtk_container_add(GTK_CONTAINER(WO->window),elem);
}
*/


/********************************** G  R  I  D****************************************************/
/** Fonction d'allocation de structure Grid**/
Grid* Creation_Initialisation_Structure_Grid()
{
    Grid* nvGrid;
    nvGrid = (Grid*)malloc(sizeof(Grid));
    if(!nvGrid)
    {
        g_print("\n Erreur d'allocation (Grid)\n");
        exit(0);
    }
    nvGrid->Mongrid = gtk_grid_new();
    nvGrid->Dernier_Fils = NULL;
    nvGrid->Contenaire = NULL;
    nvGrid->baseline_row = 0;
    nvGrid->colonne_homoge = FALSE;
    nvGrid->espace_colonne = 50;
    nvGrid->espace_ligne = 50;
    nvGrid->ligne_homoge = FALSE;
    nvGrid->fils_gauche_attach = 0;
    nvGrid->fils_hauteur = 1;
    nvGrid->fils_longueur = 1;
    nvGrid->fils_haut_attach = 0;

    return(Grid*)nvGrid;
}
Grid *Creer_Grid(gboolean ColonneHomog, gint EspaceColonne, gboolean LigneHomog, gint EspaceLigne)
{
    Grid *Nvgrid;
    Nvgrid = Creation_Initialisation_Structure_Grid();
    gtk_grid_set_row_homogeneous(Nvgrid->Mongrid,LigneHomog);
    gtk_grid_set_row_spacing(Nvgrid->Mongrid,EspaceLigne);
    gtk_grid_set_column_homogeneous(Nvgrid->Mongrid,ColonneHomog);
    gtk_grid_set_column_spacing(Nvgrid->Mongrid,EspaceColonne);
    return(Grid*)Nvgrid;
}

void Ajouter_UnElement_Au_Grid(Grid * UnGrid,GtkWidget* Fils)
{
    if(!UnGrid)
    {
        g_print("\n Erreur le Grid n'existe pas!\n");
        exit(0);
    }
    if(!Fils)
    {
        g_print("\n Erreur, l'element a ajouter au Grid n'existe pas !\n");
        exit(0);
    }
    if(!UnGrid->Dernier_Fils)
        gtk_grid_attach(UnGrid->Mongrid,Fils,0,0,2,2);
    else
        gtk_grid_attach_next_to(UnGrid->Mongrid,Fils,UnGrid->Dernier_Fils,GTK_POS_RIGHT,2,2);
    UnGrid->Dernier_Fils = Fils;
}

/**
fonction:
entree:
sortie:
role:
**/
void Modifier_Couleur_Widget(GtkWidget *Monwidget, const gchar* couleur)
{
    GdkRGBA Nvcouleur;
    gdk_color_parse(couleur, &Nvcouleur);
    gtk_widget_modify_bg(Monwidget, GTK_STATE_NORMAL, &Nvcouleur);
}


/*************************************** B U T T O N ******************************************/
/*********
fonction:initialise_simple_button( gchar *titre,gboolean mnemonic,GtkWidget *conteneur)
entree:un titre de button,un gboolean true ou false pour choisir mnemonic,et le contenaire du boutton
sortie:button initialisee
role:cette fonction permet d'allouer escpace mem et de remplir les champs d'un button simple
*********/
Button *initialise_simple_button( gchar*name,gchar *titre,gboolean mnemonic,GtkWidget *conteneur)
{
Button *butt =NULL;
// allocation dynamique des diff�rentes champs
butt=(Button*) malloc(sizeof(Button));
    if(!butt)
    {
        printf("\n Erreur d'allocation Button !!\n");
        exit(0);
    }
butt->Contenaire=conteneur;
butt->Titre=(gchar*)malloc(256 *sizeof(gchar));
    if(!butt->Titre)
    {
        g_print("Erreur d'allocation (Structure Button (Titre))");
        exit(0);
    }
if(titre) strcpy(butt->Titre,titre);
else butt->Titre = NULL;
butt->name=name;
//stock_icon
butt->Mnemonic=mnemonic;
return((Button*)butt);
}//fin de la fonction
/**
fonction:Creer_Button(Button* b)
entree:unbutton
sortie:creation d'un button
role:cette fonction perme de creer un button a l'aide des fcts GTK
**/
Button * Creer_Button(Button* b)
{
    if(!b) b=(Button*)malloc(sizeof(Button));
    if(b->Titre)
        b->MonBoutton=gtk_button_new_with_label(b->Titre);
    else
        b->MonBoutton=gtk_button_new_with_label("");
    if(b->Mnemonic && b->Titre)
        b->MonBoutton=gtk_button_new_with_mnemonic(b->Titre);
    gtk_button_set_label(b->MonBoutton,b->Titre);
    gtk_widget_set_name(b->MonBoutton,b->name);

    gtk_button_set_use_underline(b->MonBoutton,b->Mnemonic);
    return(Button*)b;
}

/******************************************* B O X **********************************************/
/**
fonction:
entree:
sortie:
role:
**/
Box *Creation_Initialisation_Structure_Box()
{
    Box *Nvbox;
    Nvbox = (Box*)malloc(sizeof(Box));
    if(!Nvbox)
    {
        g_print("\n Erreur d'allocation du Box\n");
        exit(0);
    }
    Nvbox->Box_Type = 0;
    Nvbox->Espace_Fils = 10;
    Nvbox->Monbox = NULL;
    return(Box*)Nvbox;
}
/**
fonction:
entree:
sortie:
role:
**/
Box *Creer_Box(gint Box_Type,gint Espace_fils)
{
    Box* Nvbox;
    Nvbox = Creation_Initialisation_Structure_Box();
    Nvbox->Espace_Fils = Espace_fils;
    if(Box_Type == 1)
        Nvbox->Monbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,Nvbox->Espace_Fils);
    else
        Nvbox->Monbox = gtk_box_new(GTK_ORIENTATION_VERTICAL,Nvbox->Espace_Fils);
    return(Box*)Nvbox;
}

void Ajouter_Element_Au_Box(Box* Monbox,GtkWidget *Fils,gboolean etendre, gboolean occuper, guint extra_espace)
{
    if(!Monbox)
    {
        g_print("\n Erreur le box n'existe pas! Fonction (Ajouter_Element_Au_Box)\n");
        exit(0);
    }
    gtk_box_pack_start(Monbox->Monbox,Fils,etendre,occuper,extra_espace);
}

/*********************************C H E C K   B U T T O N****************************************/
checkbuttonobj* init_checkbutton(gchar* nom, gchar* etiq)
{
    ///Allocation memoire
     checkbuttonobj* b = NULL;
     b = (checkbuttonobj*)malloc(sizeof(checkbuttonobj));
     ///Test d'allocation
     if(!b)
     {
        printf("\nERROR\n");
        exit(0);
     }
     b->label = NULL;
     b->name = NULL;
     ///Allocation du label et nom
     b->label = (gchar*)malloc(30*sizeof(gchar));
     b->name = (gchar*)malloc(30*sizeof(gchar));
     ///affectation de l'etiquette et du nom
     if(etiq)
     {
        if(b->label)strcpy(b->label,etiq);
        else        printf("\nErreur d'allocation");
     }

     if(nom)
     {
        if(b->name)strcpy(b->name,nom);
        else        printf("\nErreur d'allocation");
     }

     return(checkbuttonobj*)b;
}
/****************************/
void create_checkbutton(checkbuttonobj* b)
{
     if(b->label)
        b->checkbutton=gtk_check_button_new_with_mnemonic(b->label);///cr�ation du checkbouton avec label

     else
        b->checkbutton=gtk_check_button_new();///cr�ation du checkbouton sans label

     if(b->name) gtk_widget_set_name(b->checkbutton,b->name);
}
/***********************************F R A M E*************************************************/
/**
fonction:
entree:
sortie:
role:
**/
frame * initialisation_frame(GtkWidget *widget,GtkWidget *container,gchar* label,float H,float L, int shadow, gint align_x,gint align_y)
{
    frame*f;
    f=( frame*)malloc(sizeof(frame));
    if(!f)
    {
        g_print("erreur d'allocation frame ");
        exit(0);
    }
     f->label = (gchar*)malloc(sizeof(gchar));
    if(!f->label)
    {
        g_print("Erreur d'allocation Structure frame (Label)");
        exit(0);
    }
    if (label)
        strcpy (f->label, label);
    f->frame=widget;
    f->contenaire=container;
    f->Hauteur=H;
    f->Largeur=L;
    f->shadow=shadow;
    f->align_x=align_x;
    f->align_y=align_y;
    return((frame*)f);
}
/**
fonction:
entree:
sortie:
role:
**/
frame* creer_frame(frame*f)
{
   GtkShadowType type;
   //if(!f->frame)
   f->frame=gtk_frame_new(f->label);
   //else
    //gtk_frame_set_label_widget(GTK_FRAME(f->frame),f->frame);
       switch(f->shadow)
   {
     case 0: {  type=GTK_SHADOW_NONE;break;}
     case 1: {  type=GTK_SHADOW_IN;break;}
     case 2: {  type=GTK_SHADOW_OUT ;break;}
     case 3: {  type=GTK_SHADOW_ETCHED_IN;break;}
     case 4: {  type=GTK_SHADOW_ETCHED_OUT;break;}
   }
   gtk_frame_set_label_align(GTK_FRAME(f->frame),f->align_x,f->align_y);
   gtk_frame_set_shadow_type(GTK_FRAME(f->frame),type);
   gtk_widget_set_size_request(f->frame,f->Largeur, f->Hauteur);
   //f->contenaire=gtk_fixed_new();
   return((frame*)f);
}
/************************************************************ I C O N E **********************************************************/

/**
fonction:Icone_init(GtkWidget *container,const gchar *adricone)
entree:le contenaire de l'icone et le chemin vers l'icone
sortie:l'icone initialsee
role:intialiser une structure d'icone et remplir ses champs
**/

Icone* Icone_init(GtkWidget *container,const gchar *adricone)
{  //allocation de la memoire
   Icone *icone=(Icone*)malloc(sizeof(Icone));
   icone->adricone=(gchar*)malloc(sizeof(gchar));
   //remplissage des champs
   icone->Contenaire=container;
    if(adricone)
        strcpy(icone->adricone,adricone);
    return((Icone*)icone);
}
/**
fonction:Icone_create(Icone *icone)
entree: l'objet icone
sortie:creation de l'icone
role:cette fct permet de creer une icone
**/
GtkWidget* Icone_create(Icone *icone)
{   // fct pour inserer icone a partir la biblio gtk
    gtk_window_set_icon_from_file(GTK_WINDOW(icone->Contenaire), icone->adricone, NULL);
    return((GtkWidget*)icone->Contenaire);
}

///***************************** m s s a g e  b u t t o n *****************************************/
//�a me pose un PROB !-!
/***
void Button_Click_Message(Button* monbtn, gpointer data)
{
    g_print("%s",data);
}


void Ajouter_Message_Button_Click(Button *monbtn, const gchar *MsgAfficher)
{
    if(!monbtn)
    {
        g_print("\n Erreur Button n'existe pas (Fonction:Ajouter_Message_Button_Click)\n");
        exit(0);
    }
    strcpy(monbtn->OnClickMsg,MsgAfficher);
    g_signal_connect(G_OBJECT(monbtn->MonBoutton), "clicked",G_CALLBACK(Button_Click_Message),monbtn->OnClickMsg);
}
**/

///****************************************** f i x e d *************************************************************/
/**
fonction:
entree:
sortie:
role:
**/
FIXED *init_fixed()
{
    FIXED *F=NULL;
    F=(FIXED*)malloc(sizeof(FIXED));
    F->fixed=gtk_fixed_new ();
    F->P.pos_x=0;
    F->P.pos_y=0;
    return F;
}
/**
fonction:
entree:
sortie:
role:
**/
void creer_fixed(gint x,gint y,FIXED *F,GtkWidget *W,GtkWidget *C)
{
    gtk_fixed_put(GTK_FIXED (F->fixed), W, x, y);
    gtk_container_add(GTK_CONTAINER (C), F->fixed);
    F->P.pos_x = x;
    F->P.pos_y = y;
}

void creer_fixed_container_is_grid(gint x,gint y,FIXED *F,GtkWidget *W,Grid *C)
{
    gtk_fixed_put(GTK_FIXED (F->fixed), W, x, y);
    Ajouter_UnElement_Au_Grid(C, F->fixed);
}

///************************************ L A B E L***************************************************************************/
/**
fonction:
entree:
sortie:
role:
**/
Label * Creation_Initialisation_Structure_Label(const gchar *Label_Text,gchar* Label_Pattern,gfloat Alignment_x,gfloat Alignment_y,gint hauteur,gint largeur  )
{
    Label *Nvlabel;
    Nvlabel = (Label*)malloc(sizeof(Label));
    if(!Nvlabel)
    {
        g_print("Erreur d'allocation (Structure Label)");
        exit(0);
    }
    Nvlabel->Label_Text = (gchar*)malloc(50*sizeof(gchar));
    if(!Nvlabel->Label_Text)
    {
        g_print("Erreur d'allocation (Structure Label (Text)))");
        exit(0);
    }
    Nvlabel->Label_Pattern = (gchar*)malloc(sizeof(gchar));
    if(!Nvlabel->Label_Pattern)
    {
        g_print("Erreur d'allocation (Structure Label (Pattern))");
        exit(0);
    }
     //Nvlabel->Contenaire=container;
    if(Label_Text)
        strcpy(Nvlabel->Label_Text,Label_Text);

    else
        strcpy(Nvlabel->Label_Text,"Titre par default");
    if(Label_Pattern)
        strcpy(Nvlabel->Label_Pattern,Label_Pattern);
    else
        strcpy(Nvlabel->Label_Pattern,"label pattern par default");

    //Nvlabel->Type_Position=Label_Justification;
    Nvlabel->Alignement_x=Alignment_x;
    Nvlabel->Alignement_y=Alignment_y;
    Nvlabel->Hauteur=hauteur;
    Nvlabel->Largeur=largeur;
    return(Label*)Nvlabel;
}
/**
fonction:
entree:
sortie:
role:
**/
Label *Creer_Label(Label* Nvlabel)
{

    //GtkJustification type;
   /* switch(Nvlabel->Type_Position)
   {
     case 0: {  type=GTK_JUSTIFY_LEFT;break;}
     case 1: {  type=GTK_JUSTIFY_RIGHT;break;}
     case 2: {  type=GTK_JUSTIFY_CENTER ;break;}
     case 3: {  type=GTK_JUSTIFY_FILL;break;}
   }*/
    //gtk_label_set_justify(GTK_LABEL(Nvlabel->Label),Nvlabel->Type_Position);
    Nvlabel->Label=gtk_label_new(Nvlabel->Label_Text);
    gtk_label_set_xalign(GTK_LABEL(Nvlabel->Label), Nvlabel->Alignement_x);
    gtk_label_set_yalign(GTK_LABEL(Nvlabel->Label), Nvlabel->Alignement_y);
    gtk_widget_set_size_request(Nvlabel->Label,Nvlabel->Largeur, Nvlabel->Hauteur);
    gtk_label_set_label(Nvlabel->Label,Nvlabel->Label_Text);
    return(Label*)Nvlabel;
}

///************************************************E N T R Y *********************************************************

/***
fonction:Entry_init
Entrée: l'objet qui va contenir notre zone de saisie et visibility pour établir ou non la visibilité.
Sortie: un objet de type Entry
role: Cette fonction permet d'initialiser une zone des entrées de saisie ***/
Entry *Entry_init(gboolean visibility,GtkWidget *racine )

{
//Allocation de l�espace m�moire pour notre widget
   Entry *objet = NULL;
    objet = (Entry*)malloc(sizeof(Entry));
    if(!objet)
    {
        printf("Erreur d'allocation"); exit(-1);
    }
    //initialisation de la mani�re de saisie
      objet->visibility = visibility;
    //initilisation du conteneur
     objet->contenaire= racine;
    return ((Entry*) objet);
}
/**
fonction: Entry_create
Entrée: un objet de type Entry.
Sortie: un objet de type Entry’.
role: Cette fonction permet de créer une zone de saisie
**/
Entry *Entry_create (Entry *objet)
{
    //Creation de l'objet Entry
    objet->entry = gtk_entry_new ();
     //si on veut que le texte apparaisse normalement
    if (objet->visibility)
      gtk_entry_set_visibility (GTK_ENTRY(objet->entry),TRUE);
    else //si on veut un texte securise(mpt de passe)
    {
    gtk_entry_set_visibility (GTK_ENTRY(objet->entry),FALSE);
    }
    return ((Entry*) objet);
}//fin de la fonction Entry_create

/****************************************************S C A L E*****************************************************************/
/***
fonction : init_scale
Entree : Le conteneur du scale
        Type du scale (0 pour horizontal /1 pour verticale)
        la valeur minimale/maximale
        Le pas du scale
-Sortie : un pointeur vers une structure Scale initialisé
-role:Cette fonction permet d'initialiser les champs d'un scale et de le retourner
***/
Scale * init_scale(GtkWidget* cont, int type, gint Min, gint Max, gint step)
{
Scale* S = NULL;
//Allocation memoire
S = (Scale*)malloc(sizeof(Scale));
//remplir les champs du scale S
S->contenaire = cont;//contenaire
S->orient = type;//orientation :verticale ou horizontale
S->Min= Min;//valeur min
S->Max = Max;//valeur max
S->pas = step;//pas de deplacement
return (Scale*)S;
}
/*******************************************************
fonction:create_scale(Scale* S)
Entree :scale initialise
Sortie :scale cree
role:Cette fonction permet la creation d'un scale apres son initialisation
*******************************************************/
Scale* create_scale(Scale* S)
{
//Creer le scale selon l'orientation
//si orient=0 donc horizontal
if(S->orient == 0)
S->scale = gtk_hscale_new_with_range(S->Min,S->Max,S->pas);
else //si orient est verticale
    if(S->orient == 1)
S->scale = gtk_vscale_new_with_range(S->Min,S->Max,S->pas);
//positionner le scale
gtk_scale_set_value_pos(GTK_SCALE(S->scale),GTK_POS_TOP);
return (Scale*)S;
}

///********************************************I M A G E***********************************************************
/**
fonction:Image_init(char *chemin,int x,int y)
entree:le chemin vers l'image et sa lareur et longueur
sortie:imigae initialsee
role:cette fonction permet de remplir les champs d'un objet de type image
**/
Image* Image_init(char *chemin,int x,int y)
{
    Image *image=(Image*)malloc(sizeof(Image));
    //initialisation du chemin
    image->adrimage=(char*)malloc(256*sizeof(char));
    if(chemin)
    strcpy(image->adrimage,chemin);
    //initialisation de la position
    image->posx = x;
    image->posy = y;
    image->ImageEbox = gtk_event_box_new();
    return ((Image*)image);
}//fin de la fonction initialiser_image

/**
fonction:Image_create(Image* image)
entree:image initialsee
sortie:creation de l'image
role:cette fonction permet de creer une image et de l'inserer
**/
Image* Image_create(Image* image)
{
 //inserer l'image a partir de fonction gtk
  image->image = gtk_image_new_from_file (image->adrimage);
  gtk_container_add(image->ImageEbox,image->image);
  return (Image*)image;
}

/******************************************** T O G G L E  B U T T O N **************************************************************/

/**
fonction:init_toggle(gchar *label, gboolean mnemonic, GtkWidget *pere)
entree:un label ,un gboolean true ou false pour choisir mnemonic,et le contenaire du boutton
sortie:toggle button initialisee
role:cette fonction permet d'allouer escpace mem et de remplir les champs d'un toggle button
**/
ToggleButton *init_toggle(gchar *label, gboolean mnemonic, GtkWidget *pere)
{
   ToggleButton *bout = NULL;
    /*allocation_dynamique_du_bouton*/
    bout = (ToggleButton*)malloc (sizeof (ToggleButton));
    bout->Contenaire = pere;
    /*allocation_de_l'espace_memoire_pour_label*/
    bout->label = (gchar*)malloc (30*sizeof (gchar));
    if (label)
        strcpy (bout->label, label);
    else bout->label = NULL;

    bout->mnemonic = mnemonic;
    /*retourner_le_bouton_cree*/
    return ((ToggleButton*) bout);
}

/*********************************************************************/
/**
fonction:create_toggle (ToggleButton *btn)
entree:un toggle button
sortie:creation du toggle button
role:cette fonction perme de creer un toggle button a l'aide des fcts GTK
**/
ToggleButton *create_toggle (ToggleButton *btn)
{
    /*si_le_bouton_a_un_label_et_unmnemonic*/
    if ((btn->mnemonic) && (btn->label))
        /*creation_du_bouton_avec_mnemonic*/
        btn->Toggle =gtk_toggle_button_new_with_mnemonic(btn->label);
    else if ((btn->label))
    /*creation_du_bouton_avec_label*/
      btn->Toggle =gtk_toggle_button_new_with_label(btn->label);
    else
    /*si_n'existe_pas_le_label_creer_un_label_par_deffaut*/
      btn->Toggle =gtk_toggle_button_new_with_label( "togglebutton::::label par default");
    return ((ToggleButton*) btn);
}
/******************************************** RADIO BUTTON**************************************************************/
/**
fonction:init_radio22(gchar *label, gboolean mnemonic, GtkWidget *pere)
entree:un label ,un gboolean true ou false pour choisir mnemonic,et le contenaire du boutton
sortie:radio button initialise
role:cette fonction permet d'allouer escpace mem et de remplir les champs d'un radio button
**/
RadioButton *init_radio22(gchar *label, gboolean mnemonic, GtkWidget *pere)
{
   RadioButton *bout = NULL;
    /*allocation_dynamique_du_bouton*/
    bout = (RadioButton*)malloc (sizeof (RadioButton));
    bout->contenaire = pere;
    /*allocation_de_l'espace_memoire_pour_label*/
    bout->label = (gchar*)malloc (30*sizeof (gchar));
    if (label)
        strcpy (bout->label, label);
    else bout->label = NULL;

    bout->mnemonic = mnemonic;
    /*retourner_le_bouton_cree*/
    return ((RadioButton*) bout);
}

/*********************************************************************/
/**
fonction:create_radio22 (RadioButton *btn,RadioButton *btn1)
entree:un radio button,un radio button de meme groupe
sortie:creation du radio button
role:cette fonction perme de creer un radio button a l'aide des fcts GTK
**/
RadioButton *create_radio22 (RadioButton *btn,RadioButton *btn1)
{   //initialiser groupe par null
    GtkWidget *group = NULL;
    if (btn1)
        //grouper le boutton et les lier
        group = btn1->radio;
        //si mnemonic true et label
    if ((btn->mnemonic) && (btn->label))
        btn->radio =gtk_radio_button_new_with_mnemonic_from_widget (GTK_RADIO_BUTTON (group),(btn->label));
        //if label
    else if ((btn->label))
      btn->radio =gtk_radio_button_new_with_label_from_widget ( GTK_RADIO_BUTTON (group), btn->label);
    else //creation d'un button avec label par defaut
      btn->radio =gtk_radio_button_new_with_label_from_widget (GTK_RADIO_BUTTON (group),"label par default");
    return ((RadioButton*) btn);
}


/*** C O M B O    B O X ****************************************************************/

/**
   FONCTION : Init_ComboBox();
   Entree : Aucun parametre a saisir en entre;
   Sortie : Zone memoire allouee pour la nouvelle variable de type ComboBox;
   Fonctionnement: Cette fonction permet l'allocation zone memoire d'une nouvelle variable de type ComboBox
**/
ComboBox *Init_ComboBox()
{
    ComboBox*Cbox; // Declaration de la nouvelle variable
    Cbox = (ComboBox*)malloc(sizeof(ComboBox)); // Allocation memoire
    if(!Cbox) // Si probleme d'allocation, message d'erreur et sortir de la fonction
    {
        g_print("Erreur d'allocation combo box");
        exit(0);
    }
    // Initialisation du widget et le contenaire
    Cbox->comboBox = Cbox->contenaire = NULL;
    // Initialisation des positions x et y
    Cbox->posx = Cbox->posy = 0;
    // Initialisation de entry, 0 c'est false
    Cbox->entry = 0;
    // retour par adresse
    return(ComboBox*)Cbox;
}




/**
   FONCTION : Create_ComboBox();
   Entree: Param1 entier pour la position x , param2 entier pour la position y , param 3 entier 1 ou 0 pour entry ou pas
   Sortie : Creation du nouveau Combo box
**/
ComboBox *Create_ComboBox(gint posx,gint posy,gint entry)
{
    // Declaration de la variable
     ComboBox* Cbox;
     // Allocation memoire et initialisation
     Cbox = Init_ComboBox();
     // Si entry = 1, creation du widget combo box avec entry
     if(entry == 1) Cbox->comboBox = gtk_combo_box_text_new_with_entry();
     // Sinon , creation du widget sans entry
     else Cbox->comboBox = gtk_combo_box_text_new();
     // Position x et y du combo box
     Cbox->posx = posx;
     Cbox->posy = posy;
     return(ComboBox*)Cbox;
}



/**
   FONCTION : Ajouter_Element_Combobox();
   Entree: Un combo boc , text du nouvelle element , id du nouvelle element
   Sortie : L'ajout de l'element au combo box (a la fin)
**/
void Ajouter_Element_Combobox(ComboBox*box,const gchar *ElemText, const gchar *Elemid)
{
    // Si le combo box n'existe pas, message d'erreur et sortir de la fonction
    if(!box)
    {
        g_print("Combo box n'existe pas ");
        exit(0);
    }
    // L'ajout du nouvel element au combo box
    gtk_combo_box_text_append(box->comboBox,Elemid,ElemText);
}



/**
   FONCTION: Ajouter_Element_Combobox_Position();
   Entree: Combo box, text du nouvel element , id du nouvel element , position(debut = 0)
   Sortie: Ajout du nouvel element a la position specifie du combo box
**/
void Ajouter_Element_Combobox_Position(ComboBox *box, const gchar*Elemtext, const gchar *ElemId,gint elemposition)
{
    // Si le combo box n'existe pas, message d'erreur et sortir du programme
    if(!box)
    {
        g_print("Box n'existe pas ");
        exit(0);
    }
    // Insertion a la position specifiee
    gtk_combo_box_text_insert(box->comboBox,elemposition,ElemId,Elemtext);
}

/*************************M E N U ***************************************************************/
Menubar*creer_init_bar(gint x)
{
    Menubar*mb;
    mb=(Menubar*)malloc(sizeof(Menubar));
    if(!mb)
    {
        printf("\nErreur d'allocation!\n");
        exit(0);
    }
    mb->positionbar=x;
    mb->bar=gtk_menu_bar_new();
    switch(mb->positionbar)
    {
    case 1:
        gtk_menu_bar_set_pack_direction(mb->bar,GTK_PACK_DIRECTION_LTR);
        break;
    case 2:
        gtk_menu_bar_set_pack_direction(mb->bar,GTK_PACK_DIRECTION_RTL);
        break;
    case 3:
        gtk_menu_bar_set_pack_direction(mb->bar,GTK_PACK_DIRECTION_TTB);
        break;
    case 4:
        gtk_menu_bar_set_pack_direction(mb->bar,GTK_PACK_DIRECTION_BTT);
        break;
    default:
        break;
    }
    return((Menubar*)mb);
}

Menu*init_struct_menu(GtkWidget*emplacement,gchar*n,gchar*ic)
{
    Menu*mn;
    mn=(Menu*)malloc(sizeof(Menu));
    if(!mn)
    {
        printf("\nErreur d'allocation!\n");
        exit(0);
    }
    if(n)
    {
        mn->nom=(gchar*)malloc(30*sizeof(gchar));
        mn->nom=n;
    }
    if(ic)
    {
        mn->icone=(gchar*)malloc(30*sizeof(gchar));
        mn->icone=ic;
    }
    mn->item=NULL;
    mn->menu=emplacement;
    return((Menu*)mn);
}
void creer_menu(Menu*mn)
{
    if(mn->nom)
    {
        mn->item=gtk_menu_item_new_with_label(mn->nom);
        
    }
    if(mn->icone)
    {
        mn->item=gtk_image_menu_item_new_from_stock(mn->icone,NULL);
        gtk_image_menu_item_set_always_show_image(mn->item,TRUE);
        gtk_menu_item_set_label(mn->item,mn->nom);
    }
    if(!mn->menu) mn->menu=gtk_menu_new();
    gtk_menu_shell_append(GTK_MENU_SHELL(mn->menu),mn->item);
}
void creer_sous_menu(Menu*mn,Menu*sm)
{

    gtk_menu_item_set_submenu(GTK_MENU_SHELL(mn->item),sm->menu);

}

void position_menu(Menu*mn, gint case_gche, gint case_h)
{
    gtk_menu_attach(mn->menu, mn->item, (case_gche), (case_gche + 1), (case_h), (case_h + 1));
}



gboolean PresDuDanger(gint x, gint y, gint x1, gint y1)
{
    for(int i=0;i<2;i++)
    {
        if((abs(x1-x) <= 40)&&(abs(y1-y) <= 40)) return TRUE;
        if((abs(x1-x) <= 40)&&(abs(y-y1) <= 40)) return TRUE;
        if((abs(x-x1) <= 40)&&(abs(y1-y) <= 40)) return TRUE;
        if((abs(x-x1) <= 40)&&(abs(y-y1) <= 40)) return TRUE;
    }
    return FALSE;
}





DataSTR *Creer_DataSTR()
{
     DataSTR *nvelem;
     nvelem = (DataSTR*)malloc(sizeof(DataSTR));
     if(!nvelem)
     {
         g_print("Erreur d'allocation Creer_DataSTR");
         exit(0);
     }
     nvelem->DataFixed = NULL;
     for(int i=0;i<4;i++ )nvelem->DataImage[i] = NULL;
     return(DataSTR*)nvelem;
}


/***----------------------t o o l b a r----------------------------------------------------------------------------------*/

/*ToolBar *init_toolbar(int type)
{
  ToolBar *T;
  T=(ToolBar*)malloc(sizeof(ToolBar));
  //T->container=cont;
  //T->separateur=sep;
  T->type_item=type;

  return (ToolBar*)T;
}

ToolBar *create_toolbar(ToolBar *T)
{
    T->toolbar=gtk_toolbar_new();
    gtk_toolbar_set_style(GTK_TOOLBAR(T->toolbar), GTK_TOOLBAR_ICONS);

   switch(T->type_item)
    {
    case 0:{T->Item = gtk_tool_button_new_from_stock(GTK_STOCK_NEW);
           gtk_toolbar_insert(GTK_TOOLBAR(T->toolbar), T->Item, -1);
           break;
           }
    case 1: {  T->Item = gtk_tool_button_new_from_stock(GTK_STOCK_OPEN);
              gtk_toolbar_insert(GTK_TOOLBAR(T->toolbar),T->Item, -1);
            break;
            }
    case 2:{  T->Item = gtk_tool_button_new_from_stock(GTK_STOCK_SAVE);
              gtk_toolbar_insert(GTK_TOOLBAR(T->toolbar),T->Item, -1);
              break;
            }
   case 3: {  T->Item = gtk_tool_button_new_from_stock(GTK_STOCK_QUIT);
              gtk_toolbar_insert(GTK_TOOLBAR(T->toolbar), T->Item, -1);
               break;
           }
   case 4 :{  T->Item= gtk_tool_button_new_from_stock(GTK_STOCK_UNDO);
              gtk_widget_set_name(GTK_WIDGET(T->Item), "undo");
              gtk_toolbar_insert(GTK_TOOLBAR(T->toolbar),T->Item, -1);
              break;
           }
   case 5 :{T->Item = gtk_tool_button_new_from_stock(GTK_STOCK_REDO);
            gtk_toolbar_insert(GTK_TOOLBAR(T->toolbar),T->Item, -1);
            break;
           }
   case 6:{ T->Item = gtk_separator_tool_item_new();
            gtk_toolbar_insert(GTK_TOOLBAR(T->toolbar),T->Item, -1);
            break;
   }
    }
    return (ToolBar*)T;
}

ToolBar * Ajouter_Item_toolbar(int type,ToolBar*T,GtkToolItem *item)
{
   switch(type)
    {
    case 0:{item = gtk_tool_button_new_from_stock(GTK_STOCK_NEW);
           gtk_toolbar_insert(GTK_TOOLBAR(T->toolbar), item, -1);
           break;
           }
    case 1: {  item = gtk_tool_button_new_from_stock(GTK_STOCK_OPEN);
              gtk_toolbar_insert(GTK_TOOLBAR(T->toolbar),item, -1);
            break;
            }
    case 2:{  item = gtk_tool_button_new_from_stock(GTK_STOCK_SAVE);
              gtk_toolbar_insert(GTK_TOOLBAR(T->toolbar),item, -1);
              break;
            }
   case 3: {  item = gtk_tool_button_new_from_stock(GTK_STOCK_QUIT);
              gtk_toolbar_insert(GTK_TOOLBAR(T->toolbar), item, -1);
               break;
           }
   case 4 :{  item= gtk_tool_button_new_from_stock(GTK_STOCK_UNDO);
              gtk_widget_set_name(GTK_WIDGET(item), "undo");
              gtk_toolbar_insert(GTK_TOOLBAR(T->toolbar),item, -1);
              break;
           }
   case 5 :{item = gtk_tool_button_new_from_stock(GTK_STOCK_REDO);
            gtk_toolbar_insert(GTK_TOOLBAR(T->toolbar),item, -1);
            break;
           }
   case 6:{ item = gtk_separator_tool_item_new();
            gtk_toolbar_insert(GTK_TOOLBAR(T->toolbar),item, -1);
            break;
   }
    }
    return (ToolBar*)T;
}
*/

IP_ScrolledWindow  *IP_ScrolledWindow_init(GtkWidget *racine,
                                                  //gchar *nom,
                                                  gint hori_barre,
                                                  gint ver_barre
                                                  //gint shadow
                                                  )
{
   /*Allocation de l'espace memoire pour la structure*/
  IP_ScrolledWindow  *Monobjet =
            (IP_ScrolledWindow*) malloc (sizeof (IP_ScrolledWindow));
    /*Initialisation du conteneur*/
    Monobjet->parent = racine;
    /*Initialisation du nom*/
   /* if (nom)
    {
        Monobjet->nom = (gchar*) malloc (35*sizeof (gchar));
        strcpy (Monobjet->nom, nom);
    }
    else Monobjet->nom = NULL;*/
    /*Initialisation de la politique de la barre horizontale*/
    Monobjet->hbarre = hori_barre;
    /*Initialisation de la politique de la barre verticale*/
    Monobjet->vbarre = ver_barre;
    //sw->shadow  = shadow;
    return ((IP_ScrolledWindow*) Monobjet);
}

/***********************************************************************
Nom de la fonction:  IP_ScrolledWindow_create
Description: Cette fonction permet de créer une fenêtre avec des barres.
Entrée: un objet de type ‘IP_ScrolledWindow’.
Sortie: un objet de type  ‘IP_ScrolledWindow’.
***********************************************************************/


IP_ScrolledWindow *IP_ScrolledWindow_create(IP_ScrolledWindow *widget)
{
    /*Creation de l'objet GtkScrolledWindow:*/
    widget->scrolledWindow = gtk_scrolled_window_new (NULL,NULL);

    /*L'existance des barres*/
    //Deux variables de types GtkPolicyType pour la politique des barres:
    GtkPolicyType hscroll_policy,vscroll_policy;
    //la politique de la barre Horizontale
    switch(widget->hbarre)
    {
    //Toujours avoir la barre;
    case 1:hscroll_policy=GTK_POLICY_ALWAYS ;break;
    //Avoirs la barre si c'est necessaire.
    case 2:hscroll_policy=GTK_POLICY_AUTOMATIC ;break;
    //N'afficher pas la barre.
    case 3:hscroll_policy=GTK_POLICY_NEVER ;break;
    }
    //la politique de la barre Verticale.
     switch(widget->vbarre)
    {
         //Toujours avoir la barre;
    case 1:vscroll_policy=GTK_POLICY_ALWAYS ;break;
    //Avoirs la barre si c'est necessaire.
    case 2:vscroll_policy=GTK_POLICY_AUTOMATIC ;break;
     //N'afficher pas la barre.
    case 3:vscroll_policy=GTK_POLICY_NEVER ;break;
    }
    /*L'insertion des barres*/
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW(widget->scrolledWindow),
           hscroll_policy, vscroll_policy);

    /*gtk_scrolled_window_set_shadow_type (
                                    GTK_SCROLLED_WINDOW(sw->scrolledWindow),
                                    sw->shadow);
     */
    //sw->fixed=gtk_fixed_new();

    return ((IP_ScrolledWindow*) widget);
}

/***********************************************************************
Nom de la fonction: IP_ScrolledWindow _add
Description: Cette fonction permet l'ajout d'un widget enfant à la fenêtre défilée.
Entrée: > un objet de type ‘IP_ScrolledWindow’
              > wchild: le widget enfant ajouté
Sortie: aucun paramètre.
***********************************************************************/

void   IP_ScrolledWindow_add(IP_ScrolledWindow *sw,
                                   GtkWidget *wchild)
{
    gtk_container_add(GTK_CONTAINER(sw->scrolledWindow), wchild);
}

/*******************************************************************
Nom_de_fonction   : IP_Message_init
Entre       :   -flag:
                        1 = GTK_DIALOG_MODAL
                        2 = GTK_DIALOG_DESTROY_WITH_PARENT
                -type:
                        1 = GTK_MESSAGE_INFO
                        2 = GTK_MESSAGE_WARNING
                        3 = GTK_MESSAGE_QUESTION
                        4 = GTK_MESSAGE_ERROR
                -type_boutton
                        0 = GTK_BUTTONS_NONE
                        1 = GTK_BUTTONS_OK
                        2 = GTK_BUTTONS_CLOSE
                        3 = GTK_BUTTONS_CANCEL
                        4 = GTK_BUTTONS_YES_NO
                        5 = GTK_BUTTONS_OK_CANCEL
                - message a informer
Sortie  : Notre boite de Message bien initaliser
Description :  Cette fonction peremet d'allouer et initialiser la structure
                IP_Message
********************************************************************/
IP_Message    *IP_Message_init(int flag,int type,
                                    int type_boutton,
                                    char *message_afficher)
{
    //allocation_dynamique_de_l'espace_memoire_pour_la_boite_de_message
    IP_Message *b=(IP_Message*)malloc(sizeof(IP_Message));
    //allocation_de_l'espace_memoire_pour_le_message
    b->message_a_afficher=(char*)malloc(300*sizeof(char));
    //insertion_du_flag
    b->flag=flag;
    //insertion_du_type_de_message
    b->type_message=type;
    //insertion_du_tupe_de_bouton
    b->type_boutton=type_boutton;
    //insertion_du_message
    if(message_afficher)
    strcpy(b->message_a_afficher,message_afficher);
    //retourner_la_boite_de_message
    return ((IP_Message*)b);
}
/********************************************************************
Nom_de_fonction   : IP_Message_create
Entre   :    Une variable de type IP_Message deja initaliser
Sortie  :    retourner la variable IP_Message  apres la creation
            desirable
Description :  Cette fonction permet de creer une boite de message
                avec certains critaire citer dans l'initialisation
********************************************************************/
GtkWidget    *IP_Message_create(IP_Message *dialog)
{
    //declaration_des_variables
   GtkDialogFlags flag;
   GtkMessageType type;
   GtkButtonsType btn;
   //creer_une_fenetre_pour_notre_boite
   dialog->pere=gtk_window_new(GTK_WINDOW_TOPLEVEL);
   //lier_la_boite_avec_son_racine
   gtk_window_set_icon_from_file(GTK_WINDOW(dialog->pere),
                                 "p.jpg",NULL);
    //test_sur_la_valeur_du_flag
  switch(dialog->flag)
   {
        case 1: flag=GTK_DIALOG_MODAL;break;
        case 2: flag=GTK_DIALOG_DESTROY_WITH_PARENT;break;
        default: flag=GTK_DIALOG_DESTROY_WITH_PARENT;break;
   }
   //test_sur_la_valeur_de_type_de_message
   switch(dialog->type_message)
   {
   case 1:
       //d'information
        type=GTK_MESSAGE_INFO ;break;
   case 2:
       //message_d'erreur
       type=GTK_MESSAGE_WARNING;break;
   case 3:
       //messsage_de_question
       type=GTK_MESSAGE_QUESTION;break;
   case 4:
       //messaga_d'erreur
       type=GTK_MESSAGE_ERROR;break;
       //message_d'information_par_deffaut
   default:type=GTK_MESSAGE_INFO;break;
   }
   //test_sur_la_valeur_de_type_de_bouton
   switch(dialog->type_boutton)
   {
   case 0:btn=GTK_BUTTONS_NONE;break;
   //un_bouton_ok
   case 1:btn=GTK_BUTTONS_OK;break;
   //un_bouton_fermer
   case 2:btn=GTK_BUTTONS_CLOSE;break;
   //un_bouton_annuler
   case 3:btn=GTK_BUTTONS_CANCEL;break;
   //un_bouton_oui_ou_non
   case 4:btn=GTK_BUTTONS_YES_NO;break;
   //un_bouton_oui_ou_annuler
   case 5:btn=GTK_BUTTONS_OK_CANCEL;break;
   //aucune_bouton_par_deffaut
    default:btn=GTK_BUTTONS_NONE;break;
   }


    if(dialog->type_boutton==0)
    {
      if(dialog->pere)
        dialog->message= gtk_message_dialog_new(GTK_WINDOW(dialog->pere),
                                                flag,type,btn,
                                                dialog->message_a_afficher);
      else
        dialog->message= gtk_message_dialog_new(NULL,flag,type,btn,
                                                dialog->message_a_afficher);
    }


    if(0 < dialog->type_boutton && dialog->type_boutton < 4)
    {
        if(dialog->pere)
            dialog->message= gtk_message_dialog_new(GTK_WINDOW(dialog->pere),
                                                    flag,type,btn,
                                                    dialog->message_a_afficher);
        else
            dialog->message= gtk_message_dialog_new(NULL,flag,type,btn,
                                                    dialog->message_a_afficher);
    }

    if(3 < dialog->type_boutton)
    {
        if(dialog->pere)
            dialog->message=
               gtk_message_dialog_new(GTK_WINDOW(dialog->pere),
                                                 flag,type,btn,
                                                 dialog->message_a_afficher);
        else
            dialog->message=
                gtk_message_dialog_new(NULL,flag,type,btn,
                                       dialog->message_a_afficher);
    }
    //retourner_la_boite_de_message
    return ((IP_Message*)dialog->message);
}


/*********************************************** S C R O L L    W I N D O W*******************************************/


scrollWindow* initi_scrollwindow(GtkWidget* container,int h_policy,int v_policy,int shadow)
{
    scrollWindow*s;
    s=(scrollWindow*)malloc(sizeof(scrollWindow));
    if(!s)
    {
        printf("erreur d'allocation :scroll window");
        exit(-1);
    }
    s->container=container;
    s->H_policy=h_policy;
    s->V_policy=v_policy;
    s->shadow=shadow;

    return(scrollWindow*)s;
}


scrollWindow* create_scrollwindow(scrollWindow* s)
{
    GtkShadowType type;
    GtkPolicyType hpolice,vpolice;

    s->scrollWindow = gtk_scrolled_window_new (NULL, NULL);
    switch(s->H_policy)
    {
        case 0:{ hpolice=GTK_POLICY_ALWAYS  ;break;}
        case 1:{ hpolice=GTK_POLICY_AUTOMATIC  ;break;}
        case 2:{ hpolice=GTK_POLICY_NEVER  ;break;}
        case 3:{ hpolice=GTK_POLICY_EXTERNAL  ;break;}
    }

    switch(s->V_policy)
    {
        case 0:{ vpolice=GTK_POLICY_ALWAYS  ;break;}
        case 1:{ vpolice=GTK_POLICY_AUTOMATIC  ;break;}
        case 2:{ vpolice=GTK_POLICY_NEVER  ;break;}
        case 3:{ vpolice=GTK_POLICY_EXTERNAL  ;break;}
    }

    switch(s->shadow)
   {
     case 0: {  type=GTK_SHADOW_NONE;break;}
     case 1: {  type=GTK_SHADOW_IN;break;}
     case 2: {  type=GTK_SHADOW_OUT ;break;}
     case 3: {  type=GTK_SHADOW_ETCHED_IN;break;}
     case 4: {  type=GTK_SHADOW_ETCHED_OUT;break;}
   }
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(s->scrollWindow),hpolice,  vpolice);
    gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW(s->scrollWindow),type);
      gtk_container_set_border_width(GTK_CONTAINER (s->scrollWindow), 10);
    return (scrollWindow*)s;
}



void add_scrollwindow(scrollWindow*s,GtkWidget*a)
{
    gtk_container_add(GTK_SCROLLED_WINDOW (s->scrollWindow), a);
}


/************************************** C S S ***************************************************/
void style(GtkWidget*a,gchar* name)
{
  GtkStyleContext *context;
  GtkCssProvider *cssProvider = gtk_css_provider_new();
  context = gtk_widget_get_style_context (a);

  gtk_css_provider_load_from_path (cssProvider,"gtk_css.css", NULL);
  gtk_style_context_add_provider (context,GTK_STYLE_PROVIDER(cssProvider),GTK_STYLE_PROVIDER_PRIORITY_USER);

  gtk_style_context_add_class(context,name);

}



/*********************************** LAYOUT ******************************************************/
layout* init_layout(gchar* image,GtkWidget* cont)
{
    layout*l;
    l=(layout*)malloc(sizeof(layout));
    if(!l)
    {
        printf("erreur d'allocation : layout");
        exit(-1);
    }
    l->container=cont;
    l->image=image;

    return(layout*)l;
}

layout* create_layout(layout*l)
{
    l->layout = gtk_layout_new(NULL, NULL);
    gtk_layout_put(GTK_LAYOUT(l->layout), l->layout, 0, 0);
        gtk_container_add(GTK_CONTAINER (l->container), l->layout);
        gtk_widget_show(l->layout);
    return(layout*)l;
}

TOOLbar *initi_toolbar(GtkToolbarStyle style,gint show_arrow,gchar orientation){
    TOOLbar *T=NULL;
    T = (TOOLbar*)malloc(sizeof(TOOLbar)); //allocation de la memoire
    // Test d'allocation
    if(!T)
    {
       printf("\nErreur d'allocation !!!\n");
       exit(1);
    }
    //initialisation des champs
    T->style=style;
    T->show_arrow=show_arrow;
    T->orientation=orientation;

    return ((TOOLbar*)T);
}
/*********************************************************************************/
void create_toolbar(TOOLbar *T){

     //si la barre d'outil n'existe pas
     if(!T)
     {
        printf("Erreur");
        exit(-1);
     }//fin if
     //sinon creation du toolbar
     T->toolbar=gtk_toolbar_new();
     //ajout des caracteristiques de la barre
     //GTK_TOOLBAR_ICONS ,GTK_TOOLBAR_TEXT ,GTK_TOOLBAR_BOTH ,GTK_TOOLBAR_BOTH_HORIZ
     gtk_toolbar_set_style(GTK_TOOLBAR(T->toolbar), T->style);

     //l'affichage des toolitems au cas de changer la taille de la fenetre
     if(T->show_arrow==1)
        gtk_toolbar_set_show_arrow(GTK_TOOLBAR(T->toolbar),TRUE);

     //pour une orientation verticale ou horizontale
     if((T->orientation=='H')||(T->orientation=='h'))
        gtk_orientable_set_orientation( GTK_ORIENTABLE( T->toolbar ),GTK_ORIENTATION_HORIZONTAL );

     if((T->orientation=='V')||(T->orientation=='v'))
         gtk_orientable_set_orientation( GTK_ORIENTABLE( T->toolbar ),GTK_ORIENTATION_VERTICAL );
}
/**********************************************************************************/
GtkToolItem *creer_toolitem(TOOLbar *T,gint pos,gchar *img,gchar *nom){

    GtkToolItem *toolitem;
    //on cree l'icone
    GtkWidget *icon = gtk_image_new_from_icon_name( img,GTK_ICON_SIZE_DIALOG);
    //on cree le toolitem
    toolitem = gtk_tool_button_new( icon , nom);
    //on insere le toolitem dans la barre
    gtk_toolbar_insert(GTK_TOOLBAR(T->toolbar),toolitem,pos);
    return toolitem;
}
///********************************************************** --------- ***********************************************************
///********************************************************** T A B L E ***********************************************************
///********************************************************** --------- ***********************************************************
TABLE* init_table(gboolean homogeneous,int nb_ligne,int nb_col)
{
    TABLE*t;
    t=(TABLE*)malloc(sizeof(TABLE));
    if(!t)
    {
        printf("erreur d'allocation : table");
        exit(-1);
    }
    t->homogeneous=homogeneous;
    t->colonnes=nb_col;
    t->lignes=nb_ligne;
    return(TABLE*)t;
}

TABLE* create_table(TABLE*t)
{
    t->table=gtk_table_new(t->lignes,t->colonnes,t->homogeneous);
    return(TABLE*)t;
}

void add_to_table(TABLE*t,GtkWidget* fils,int left,int right,int top,int bottom )
{
    gtk_table_attach(GTK_TABLE(t->table),fils,left,right,top,bottom,GTK_FILL,GTK_FILL,0,0);
}


//-------------------------- gtk_widget_set_size_request--------------------------------
void set_size(GtkWidget*a,int l,int h)
{
    gtk_widget_set_size_request(a,l,h);
}
Fenetre* create_window2(Fenetre *WO)
{
    WO->Mafenetre=gtk_window_new(GTK_WINDOW_TOPLEVEL);
//Creation de la fenetre
gtk_widget_set_name(WO->Mafenetre,WO->name);
// Attribution d'un titre
if(WO->Titre)
gtk_window_set_title(GTK_WINDOW(WO->Mafenetre),WO->Titre);
// Si le user introduit une hauteur et une largeur
if((WO->Hauteur) && (WO->Longueur))
{
gtk_window_set_default_size(GTK_WINDOW(WO->Mafenetre),
(WO->Longueur),(WO->Hauteur));
}
if(WO->Resizable)
gtk_window_set_resizable(GTK_WINDOW(WO->Mafenetre),TRUE);
else //Si res = false, redimensionnement = FAUX
gtk_window_set_resizable(GTK_WINDOW(WO->Mafenetre),FALSE);
return (Fenetre*)WO;
}





CelluleIndiv *Creer_Individu(gint Id , const gchar *NomComplet,gint posx,gint posy,gint TypeMv,gint Age,
                             gint Genetiquement, gint Diabete, gint Cardiaque, gint Poumons,
                             gint Cancers, gint Tar, gint Djmalade, gint MaladeCovid,
                             gint TypeCovid, gint Sexe , gint Avatar
                             )
{
     CelluleIndiv *nvelem;
     nvelem = (CelluleIndiv*)malloc(sizeof(CelluleIndiv));
     if(!nvelem)
     {
        g_print("Erreur de creation d'un individu!");
        exit(0);
     }
     strcpy(nvelem->Nomcomplet,NomComplet);
     nvelem->Id = Id;
     nvelem->Pos_x = posx;
     nvelem->Pos_y = posy;
     nvelem->Age = Age;
     nvelem->Sexe = Sexe;
     nvelem->TypeMv = TypeMv;
     nvelem->Suivant = NULL;
     nvelem->IndivImage = NULL;
     nvelem->MvH =0;
     nvelem->MvV =0;
     nvelem->Cancers = Cancers;
     nvelem->Cardiaque = Cardiaque;
     nvelem->Diabete = Diabete;
     nvelem->DjCovid = Djmalade;
     nvelem->Genetiquement = Genetiquement;
     nvelem->MaladeCovid = MaladeCovid;
     nvelem->Poumons = Poumons;
     nvelem->Tar = Tar;
     nvelem->TypeCovid = TypeCovid;
     nvelem->ActiveSignalId = -1;
     nvelem->SuppressionSignalId = -1;
     nvelem->Score=0;
     nvelem->Avatar = Avatar;
     nvelem->EstMort = 0;
     nvelem->TempsCpt = 0;
     nvelem->ValDeMort=1;
     return(CelluleIndiv*)nvelem;
}



void AjouterIndivBaseInfo(CelluleIndiv *nvindiv,CelluleIndiv *BaseDonnees[2])
{
     CelluleIndiv *Ptcrt;
     Ptcrt = BaseDonnees[nvindiv->MaladeCovid];
     if(!nvindiv)
     {
         g_print("Individu n'existe pas !");
         exit(0);
     }
     if(!BaseDonnees)
     {
         g_print("Base d'info n'existe pas !");
         exit(0);
     }
     if(!BaseDonnees[nvindiv->MaladeCovid])
     {
         BaseDonnees[nvindiv->MaladeCovid] = nvindiv;
         return;
     }
     while(Ptcrt->Suivant) Ptcrt = Ptcrt->Suivant;
     Ptcrt->Suivant = nvindiv;
}



EntriesListe *Creer_Entries_Liste(GtkWidget *Nom,GtkWidget *PosX,GtkWidget *PosY,GtkWidget *Age,GtkWidget *TypeMv)
{
    EntriesListe *nvelem;
    nvelem = (EntriesListe*)malloc(sizeof(EntriesListe));
    if(!nvelem)
    {
        g_print("Erreur d'allocation Entries liste");
        exit(0);
    }
    nvelem->NomEntry = Nom;
    nvelem->PosXEntry = PosX;
    nvelem->PosYEntry = PosY;
    nvelem->Age = Age;
    nvelem->TypeMv = TypeMv;
    return(EntriesListe*)nvelem;
}





ListeInfos *CreerListeInfos(gint IndivId, const gchar *Nom,const gchar *MaladeCovid,const gchar *Sexe, const gchar *Age, gint Pos_X, gint Pos_Y, const gchar *TypeMv)
{
    ListeInfos *nvelem;
    gchar Id[10];
    itoa(IndivId,Id,10);
    gchar PositionVar[20]="{";
    gchar Buff[20];
    itoa(Pos_X,Buff,10);
    strcat(PositionVar,Buff);
    strcat(PositionVar,",");
    itoa(Pos_Y,Buff,10);
    strcat(PositionVar,Buff);
    strcat(PositionVar,"}");
    nvelem = (ListeInfos*)malloc(sizeof(ListeInfos));
    if(!nvelem)
    {
        g_print("Erreur d'allocation LISTE INFOS");
        exit(0);
    }

    /** IDENTIFIANT LABEL **/
    nvelem->IndivIdLb = Creation_Initialisation_Structure_Label(Id,"",0,0,0,0);
    nvelem->IndivIdLb = Creer_Label(nvelem->IndivIdLb);

    /** NOM LABEL **/
    nvelem->IndivNomLb = Creation_Initialisation_Structure_Label(Nom,"",0,0,0,0);
    nvelem->IndivNomLb = Creer_Label(nvelem->IndivNomLb);

    /** MALADE COVID LABEL **/
    nvelem->IndivMaladeCovidLb = Creation_Initialisation_Structure_Label(MaladeCovid,"",0,0,0,0);
    nvelem->IndivMaladeCovidLb = Creer_Label(nvelem->IndivMaladeCovidLb);

    /** SEXE LABEL **/
    nvelem->IndivSexeLb = Creation_Initialisation_Structure_Label(Sexe,"",0,0,0,0);
    nvelem->IndivSexeLb = Creer_Label(nvelem->IndivSexeLb);

    /** AGE LABEL **/
    nvelem->AgeLb = Creation_Initialisation_Structure_Label(Age,"",0,0,0,0);
    nvelem->AgeLb = Creer_Label(nvelem->AgeLb);

    /** POSITION INITIALE LABEL **/
    nvelem->PositionLb = Creation_Initialisation_Structure_Label(PositionVar,"",0,0,0,0);
    nvelem->PositionLb = Creer_Label(nvelem->PositionLb);

    /** TYPE MOUVEMENT LABEL **/
    nvelem->TypeMvLb = Creation_Initialisation_Structure_Label(TypeMv,"",0,0,0,0);
    nvelem->TypeMvLb = Creer_Label(nvelem->TypeMvLb);

    /** MODIFIER BOUTTON **/
    nvelem->ModifierIndivBtn = initialise_simple_button("ModifierIndivBtn","Modifier",FALSE,NULL);
    nvelem->ModifierIndivBtn = Creer_Button(nvelem->ModifierIndivBtn);

    nvelem->Suivant = NULL;
    return(ListeInfos*)nvelem;
}




CelluleIndiv* AjouterElemListeInfos(ListeInfos *nvelem,ListeInfos *ListeInf)
{
    ListeInfos *Ptcrt;
    Ptcrt = ListeInf;
    if(!nvelem)
    {
        g_print("Element n'existe pas !");
        exit(0);
    }
    if(!ListeInf) return(CelluleIndiv*)nvelem;
    while(Ptcrt->Suivant) Ptcrt = Ptcrt->Suivant;
    Ptcrt->Suivant = nvelem;
    return(CelluleIndiv*)ListeInf;
}



CelluleIndiv *ChercherIndivParId(gint IndivId, CelluleIndiv *BaseDonnees[2])
{
    CelluleIndiv *Ptcrt;
    if(!BaseDonnees)
    {
        g_print("Base n'existe pas (ChercherIndivParId)");
        exit(0);
    }
    g_print("\n%d",IndivId);
    if(IndivId == 0)
    {
        g_print("Id invalide (Chercher indivparid)");
        exit(0);
    }
    Ptcrt = BaseDonnees[0];
    while(Ptcrt)
    {
        if(IndivId == Ptcrt->Id) return (CelluleIndiv*)Ptcrt;
        Ptcrt = Ptcrt->Suivant;
    }
    Ptcrt = BaseDonnees[1];
    while(Ptcrt)
    {
        if(IndivId == Ptcrt->Id) return (CelluleIndiv*)Ptcrt;
        Ptcrt = Ptcrt->Suivant;
    }
    g_print("Indiv n'existe pas !");
    return(CelluleIndiv*)NULL;

}



void ModifierIndivInfos(gint IndivId, CelluleIndiv *BaseDonnees[2], const gchar *NvNom, gint NvPosX, gint NvPosy, gint NvSexe, gint NvAge)
{
    CelluleIndiv *Ptcrt;
    if(!BaseDonnees)
    {
        g_print("Base n'existe pas !");
        exit(0);
    }
    Ptcrt = BaseDonnees[0];
    while(Ptcrt)
    {
        if(Ptcrt->Id == IndivId)
        {
            strcpy(Ptcrt->Nomcomplet,NvNom);
            Ptcrt->Pos_x = NvPosX;
            Ptcrt->Pos_y = NvPosy;
            Ptcrt->Sexe = NvSexe;
            Ptcrt->Age = NvAge;
            return;
        }
        Ptcrt = Ptcrt->Suivant;
    }
    Ptcrt = BaseDonnees[1];
    while(Ptcrt)
    {
        if(Ptcrt->Id == IndivId)
        {
            strcpy(Ptcrt->Nomcomplet,NvNom);
            Ptcrt->Pos_x = NvPosX;
            Ptcrt->Pos_y = NvPosy;
            Ptcrt->Sexe = NvSexe;
            Ptcrt->Age = NvAge;
            return;
        }
        Ptcrt = Ptcrt->Suivant;
    }
}
void SupprimerIndivParId(gint IndivId, CelluleIndiv *BaseDonnees[2])
{
    CelluleIndiv *Ptcrt,*SuppIndiv;
    if(!BaseDonnees)
    {
        g_print("Base n'existe pas !!");
        exit(0);
    }
    Ptcrt = BaseDonnees[0];
    if(Ptcrt->Id == IndivId)
    {
        BaseDonnees[0] = BaseDonnees[0]->Suivant;
        free(Ptcrt);
        return;
    }
    while(Ptcrt->Suivant)
    {
        if(Ptcrt->Suivant->Id == IndivId)
        {
            SuppIndiv = Ptcrt->Suivant;
            Ptcrt->Suivant = Ptcrt->Suivant->Suivant;
            free(SuppIndiv);
            return;
        }
        Ptcrt = Ptcrt->Suivant;
    }

    Ptcrt = BaseDonnees[1];
    if(Ptcrt->Id == IndivId)
    {
        BaseDonnees[1] = BaseDonnees[1]->Suivant;
        free(Ptcrt);
        return;
    }
    while(Ptcrt->Suivant)
    {
        if(Ptcrt->Suivant->Id == IndivId)
        {
            SuppIndiv = Ptcrt->Suivant;
            Ptcrt->Suivant = Ptcrt->Suivant->Suivant;
            free(SuppIndiv);
            return;
        }
        Ptcrt = Ptcrt->Suivant;
    }

}

/*selection_fichier_dialog*creer_init_selection_dialog(const gchar*titre)
{
    selection_fichier_dialog*boiteD;
    boiteD=(selection_fichier_dialog*)malloc(sizeof(selection_fichier_dialog));
    if(!boiteD)
    {
        printf("\nerreur d'allocation [selection_fichier_dialog]");
        exit(0);
    }
    boiteD->titre=titre;
    boiteD->dialog=gtk_file_chooser_dialog_new(titre,GTK_WINDOW(boiteD->fenetre)
                                                                                    ,GTK_FILE_CHOOSER_ACTION_OPEN,
                                                                                    GTK_STOCK_OK,GTK_RESPONSE_OK,
                                                                                    GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,
                                                                                    NULL);
    gtk_widget_show_all(boiteD->dialog);
    gint resp=gtk_dialog_run(GTK_DIALOG(boiteD->dialog));
    if(resp==GTK_RESPONSE_OK)
        boiteD->nomFichier=gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(boiteD->dialog));
    else
        printf("\nVous avez rien choisi");
    gtk_widget_destroy(boiteD->dialog);

}*/

gint ChercherMaxIdBaseInfos(CelluleIndiv *Based[2])
{
    gint MaxId = 0;
    CelluleIndiv *Ptcrt;
    if(!Based)
    {
        g_print("Base d'infos n'existe pas !");
        exit(0);
    }
    Ptcrt = Based[0];
    while(Ptcrt)
    {
        if(Ptcrt->Id > MaxId) MaxId = Ptcrt->Id;
        Ptcrt = Ptcrt->Suivant;
    }
    Ptcrt = Based[1];
    while(Ptcrt)
    {
        if(Ptcrt->Id > MaxId) MaxId = Ptcrt->Id;
        Ptcrt = Ptcrt->Suivant;
    }
    return(gint)MaxId;
}






void AfficherInfosIndiv(gint IndivId, CelluleIndiv *Based[2],gchar *Buffer)
{
    CelluleIndiv *Ptcrt;
    if(!Based)
    {
        g_print("Base info n'existe pas !");
        exit(0);
    }
    Ptcrt = Based[0];
    while(Ptcrt)
    {
        if(Ptcrt->Id == IndivId)
        {
            switch(Ptcrt->TypeMv)
            {
                case 0: sprintf(Buffer,
                        "Identifiant: %d\n"
                        "Nom complet : %s\n"
                        "Type mouvement: Aleatoirement"
                        ,Ptcrt->Id,Ptcrt->Nomcomplet);
                        break;
                case 1: sprintf(Buffer,
                        "Identifiant: %d\n"
                        "Nom complet : %s\n"
                        "Type mouvement: Horizontalement"
                        ,Ptcrt->Id,Ptcrt->Nomcomplet);
                        break;
                 case 2: sprintf(Buffer,
                        "Identifiant: %d\n"
                        "Nom complet : %s\n"
                        "Type mouvement: Verticalement"
                        ,Ptcrt->Id,Ptcrt->Nomcomplet);
                        break;
                 default: sprintf(Buffer,
                        "Identifiant: %d\n"
                        "Nom complet : %s\n"
                        "Type mouvement: Aleatoirement"
                        ,Ptcrt->Id,Ptcrt->Nomcomplet);
                        break;
            }
            return;
        }
        Ptcrt = Ptcrt->Suivant;
    }
    Ptcrt = Based[1];
    while(Ptcrt)
    {
        if(Ptcrt->Id == IndivId)
        {
            switch(Ptcrt->TypeMv)
            {
                case 0: sprintf(Buffer,
                        "Identifiant: %d\n"
                        "Nom complet : %s\n"
                        "Type mouvement: Aleatoirement"
                        ,Ptcrt->Id,Ptcrt->Nomcomplet);
                        break;
                case 1: sprintf(Buffer,
                        "Identifiant: %d\n"
                        "Nom complet : %s\n"
                        "Type mouvement: Horizontalement"
                        ,Ptcrt->Id,Ptcrt->Nomcomplet);
                        break;
                 case 2: sprintf(Buffer,
                        "Identifiant: %d\n"
                        "Nom complet : %s\n"
                        "Type mouvement: Verticalement"
                        ,Ptcrt->Id,Ptcrt->Nomcomplet);
                        break;
                 default: sprintf(Buffer,
                        "Identifiant: %d\n"
                        "Nom complet : %s\n"
                        "Type mouvement: Aleatoirement"
                        ,Ptcrt->Id,Ptcrt->Nomcomplet);
                        break;
            }
            return;
        }
        Ptcrt = Ptcrt->Suivant;
    }
    sprintf(Buffer,"Indiv n'existe pas !");
}



void InfoMessagePlayarea(CelluleIndiv *Based[2], gint IndivId, gchar *Buffer)
{
    CelluleIndiv *Ptcrt;
    gchar Age[30];
    gchar TypeMv[30];
    gchar Sexe[15];
    if(!Based)
    {
        g_print("Base d'infos n'existe pas !");
        exit(0);
    }
    Ptcrt = Based[0];
    while(Ptcrt)
    {
        if(Ptcrt->Id == IndivId)
        {
                /** DEFINIR TYPE DE MOUVEMENT **/
                switch(Ptcrt->TypeMv)
                  {
                       case 0: strcpy(TypeMv,"Aleatoirement");
                       break;
                       case 1: strcpy(TypeMv,"Horizontalement");
                       break;
                       case 2: strcpy(TypeMv,"Verticalement");
                       break;
                       default: strcpy(TypeMv,"Aleatoirement");
                       break;
                   }

                /** DEFINIR AGE **/
                switch(Ptcrt->Age)
                  {
                       case 0: strcpy(Age,"Age <= 12");
                       break;
                       case 1: strcpy(Age,"12 < Age <= 25");
                       break;
                       case 2: strcpy(Age,"25 < Age <= 40");
                       break;
                       case 3: strcpy(Age,"40 < Age <= 65");
                       break;
                       case 4: strcpy(Age,"65 < Age");
                        break;
                       default: strcpy(Age,"Non defini");
                       break;
                   }

                   /** DEFINIR LE SEXE **/
                   switch(Ptcrt->Sexe)
                   {
                       case 0: strcpy(Sexe,"Homme");
                               break;
                       case 1: strcpy(Sexe,"Femme");
                               break;
                       default: strcpy(Sexe,"Non defini");
                               break;
                   }
                   sprintf(Buffer,"Identifiant : %d\n"
                                  "Nom complet : %s\n"
                                  "Type Mouvement : %s\n"
                                  "Age : %s\n"
                                  "Sexe: %s\n"
                           ,Ptcrt->Id,Ptcrt->Nomcomplet,TypeMv,Age,Sexe);
                  return;

         }
         Ptcrt = Ptcrt->Suivant;
    }

    Ptcrt = Based[1];
    while(Ptcrt)
    {
        if(Ptcrt->Id == IndivId)
        {
                /** DEFINIR TYPE DE MOUVEMENT **/
                switch(Ptcrt->TypeMv)
                  {
                       case 0: strcpy(TypeMv,"Aleatoirement");
                       break;
                       case 1: strcpy(TypeMv,"Horizontalement");
                       break;
                       case 2: strcpy(TypeMv,"Verticalement");
                       break;
                       default: strcpy(TypeMv,"Aleatoirement");
                       break;
                   }

                /** DEFINIR AGE **/
                switch(Ptcrt->Age)
                  {
                       case 0: strcpy(Age,"Age <= 12");
                       break;
                       case 1: strcpy(Age,"12 < Age <= 25");
                       break;
                       case 2: strcpy(Age,"25 < Age <= 40");
                       break;
                       case 3: strcpy(Age,"40 < Age <= 65");
                       break;
                       case 4: strcpy(Age,"65 < Age");
                        break;
                       default: strcpy(Age,"Non defini");
                       break;
                   }

                   /** DEFINIR LE SEXE **/
                   switch(Ptcrt->Sexe)
                   {
                       case 0: strcpy(Sexe,"Homme");
                               break;
                       case 1: strcpy(Sexe,"Femme");
                               break;
                       default: strcpy(Sexe,"Non defini");
                               break;
                   }
                   sprintf(Buffer,"Identifiant : %d\n"
                                  "Nom complet : %s\n"
                                  "Type Mouvement : %s\n"
                                  "Age : %s\n"
                                  "Sexe: %s\n"
                           ,Ptcrt->Id,Ptcrt->Nomcomplet,TypeMv,Age,Sexe);
                    return;

         }
         Ptcrt = Ptcrt->Suivant;
    }

}

void calcul_score(CelluleIndiv *Base[2])
{
    CelluleIndiv*ptcr;
    if(!Base)
    {
        g_print("Base d'infos n'existe pas !");
        exit(0);
    }
    ptcr = Base[0];
    while(ptcr)
    {
        ptcr->Score=(int)(1+ptcr->Age+ptcr->Genetiquement+ptcr->Diabete+ptcr->Cardiaque+ptcr->Poumons+ptcr->Cancers+ptcr->Tar+ptcr->DjCovid+ptcr->TypeCovid);
        ptcr=ptcr->Suivant;
    }
}



void DeplacerIndivNMaladeVersMaladeBaseInfos(gint IndivId, CelluleIndiv *BaseD[2])
{
    CelluleIndiv *Ptcrt, *Indiv;
    if(!BaseD)
    {
        g_print("Erreur base infos n'existe pas !");
        exit(0);
    }
    Ptcrt = BaseD[1];
    if(Ptcrt->Id == IndivId)
    {
        Indiv = Ptcrt;
        BaseD[1] = BaseD[1]->Suivant;
        Indiv->MaladeCovid = 0;
        AjouterIndivBaseInfo(Indiv,BaseD);
        return;
    }
    while(Ptcrt->Suivant)
    {
        if(Ptcrt->Suivant->Id == IndivId)
        {
            Indiv = Ptcrt->Suivant;
            SupprimerIndivParId(IndivId,BaseD);
            Indiv->MaladeCovid = 0;
            AjouterIndivBaseInfo(Indiv,BaseD);
            return;
        }
        Ptcrt = Ptcrt->Suivant;
    }
}







void Moving_Fixed(FIXED *MvF,int x, int y,CelluleIndiv *Indiv, CelluleIndiv *BaseD[2])
{
    CelluleIndiv *Ptcrt,*IndivSupp;
    gboolean MaladePresNMalade = FALSE;
    gboolean NMaladePresMalade = FALSE;
     if(!MvF)
     {
        g_print("Erreur fonction Moving_Fixed! Fixed n'existe pas");
        exit(0);
     }
     if(x > 1500) return;
     if(x < 100) return;
     if(y < 100) return;
     if(y > 900) return;
     switch(Indiv->MaladeCovid)
     {
         case 0: Ptcrt = BaseD[1];
                 while(Ptcrt)
                 {
                     MaladePresNMalade = PresDuDanger(Indiv->Pos_x,Indiv->Pos_y,Ptcrt->Pos_x,Ptcrt->Pos_y);
                     if(MaladePresNMalade) break;
                     Ptcrt = Ptcrt->Suivant;
                 }
                 if(MaladePresNMalade)
                 {
                     DeplacerIndivNMaladeVersMaladeBaseInfos(Ptcrt->Id,BaseD);
                     Ptcrt->VirusImage = Image_init("greenvirus.png",0,0);
                     Ptcrt->VirusImage = Image_create(Ptcrt->VirusImage);
                     creer_fixed(Ptcrt->Pos_x +10,Ptcrt->Pos_y -20,MvF,Ptcrt->VirusImage->ImageEbox,NULL);
                     gtk_widget_show_all(Ptcrt->VirusImage->ImageEbox);
                 }
                 gtk_fixed_move(MvF->fixed,Indiv->IndivImage->ImageEbox,x,y);
                 gtk_fixed_move(MvF->fixed,Indiv->VirusImage->ImageEbox,x+10,y-20);
                 break;
        case 1: gtk_fixed_move(MvF->fixed,Indiv->IndivImage->ImageEbox,x,y);
                break;
     }
     /**gtk_fixed_move(MvF->fixed,Indiv->IndivImage->ImageEbox,x,y);
     if(Indiv->MaladeCovid == 0) gtk_fixed_move(MvF->fixed,Indiv->VirusImage->ImageEbox,x+10,y-20);**/
     Indiv->Pos_x = x;
     Indiv->Pos_y = y;
}







