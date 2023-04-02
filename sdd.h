
/**Structure d'une fenetre **/
typedef struct FN
{
     GtkWidget *Mafenetre;
     int Position_x;
     int Position_y;
     int Hauteur;
     int Longueur;
     const gchar* Titre;
     const gchar* Fichier_icon;
     //Icons de manipulation
     gchar* name;
     gboolean Popable;
     gboolean Resizable;
     gboolean Type;
     GdkColor Fenetre_Couleur;
     //Bordure
     //Taille de bordure
     struct FN *Fenetre_Mere;
} Fenetre;



/** Structure d'un Grid****/
typedef struct
{
    GtkWidget *Mongrid;
    GtkWidget *Contenaire;
    GtkWidget *Dernier_Fils;
    gint baseline_row;
    gboolean colonne_homoge;
    gint espace_colonne;
    gboolean ligne_homoge;
    gint espace_ligne;
    gint fils_hauteur;
    gint fils_gauche_attach;
    gint fils_haut_attach;
    gint fils_longueur;
}Grid;


/** Structure d'un button **/
typedef struct
{
    GtkWidget *MonBoutton;
    GtkWidget *Contenaire;
    const gchar *Titre;
    const gchar *OnClickMsg;
    gboolean Mnemonic;
    gchar* name;

}Button;

/** Structure d'un boutton de couleur **/
typedef struct
{
    GtkWidget *Monboutton;
    GtkWidget *Contenaire;
    const gchar *Titre;
    gint Hauteur;
    gint Largeur;
}Couleur_Boutton;


/** Structure d'un boutton check
typedef struct
{
    GtkWidget *Monboutton; // Le widget boutton check
    GtkWidget *Contenaire; // Le contenaire du boutton
    const gchar *Label; // Label du boutton
    gboolean Mnemonic; // Avec/Sans Mnemonic
    gchar *adricone;//adresse de l'icone a afficher au bouton
}Check_Boutton;**/




typedef struct
{
    GtkWidget *checkbutton; //L'objet checkboutton
    gchar *name; //Nom
    gchar *label; //text du button
} checkbuttonobj;

/** Structure d'un box **/
typedef struct
{
    GtkWidget *Monbox;
    gint Box_Type;
    gint Espace_Fils;
}Box;

/** Structure d'une label **/
typedef struct
{
    GtkWidget *Label; // Widget de la label
    GtkWidget *Contenaire; // Le contenaire du Label
     gchar *Label_Text; // Text de la label
    const gchar *Label_Pattern; // Pattern
    //GtkJustification Type_Position; // Type: Droite,Milieu,Gauche,ou occuper tous l'espace possible
    /*
    0:GTK_JUSTIFY_RIGHT
    The text is placed at the right edge of the label.
    1:GTK_JUSTIFY_CENTER
    The text is placed in the center of the label.
    2:GTK_JUSTIFY_FILL
    The text is placed is distributed across the label.
    3:GTK_JUSTIFY_LEFT
    The text is placed at the left edge of the label.*/
    gfloat Alignement_x;
    gfloat Alignement_y;
    gint Hauteur; // La hauteur du widget
    gint Largeur; // La largeur du widget
    ///PangoEllipsizeMode Ellipsize_Mode;
}Label;


typedef struct fil
{
GtkWidget *fils;
gint left_attach;
gint right_attach;
gint top_attach;
gint bottom_attach;
GtkAttachOptions xoptions ;
GtkAttachOptions yoptions;//gtk_fill
gint xpadding ;
gint ypadding;
struct fil *svt;
}fils_table;


/**Structure d'une table*/
typedef struct
{
  GtkWidget *table;        // la table
  gboolean homogeneous;  // TRUE,si toutes cellule du tableau est redimmensionnes selon la taille de la cellule contenant la plus grande widget
  int lignes;//nb ligne
  int colonnes;//nb colonne
  int left_attach; // espace entre les lignes de la table
  int right_attach; // espace entre les colonnes de la table
  int top_attach;
  int bottom_attach;
}TABLE ;




/**Structure d'un radio button*/
typedef struct
{
GtkWidget *radio;//widget radio button
GtkWidget *contenaire;//Le contenaire
gchar *label; //Le texte du boutton radio
gboolean mnemonic; //TRUE si creation avec mnemonic, FALSE sinon
gchar *adricone;//adresse de l'icone au cas de son insertion
GSList *group; /*Le goupe*/
}RadioButton;

/**Structure d'un toggle button*/
typedef struct
{
GtkWidget *Toggle;//widget du toggle button
GtkWidget *Contenaire;
gchar *label;
gboolean mnemonic;
int posx;
int posy;
}ToggleButton;



/**structure de l'image**/

typedef struct
{
GtkWidget* image; //widget image
gchar* adrimage; //adresse de l'image a afficher
GtkWidget *ImageEbox;// Event box
gint posx; //Position de l'mage :x
gint posy; //Position de l'mage :y
}Image;

/**structure de l'icone**/
typedef struct
{
GtkWidget* Contenaire;//le contenaire du widgeticone
const gchar* adricone; //L'adresse de l'icone
}Icone;

/**structure de l'entree**/
typedef struct
{
	GtkWidget   *entry;             //  widget entry
    GtkWidget   *contenaire;            //  Le conteneur du widget
    gboolean       visibility;         // TRUE si les caracteres saisis visibles et FALSE sinon

}Entry;

/**structure de Scale**/
/*
GtkWidget *
gtk_scale_new_with_range (GtkOrientation orientation,gdouble min,gdouble max,gdouble step);*/
typedef struct
{
GtkWidget* scale; //Le widget scale
GtkWidget* contenaire;//Le contenaire du widget
int orient; //orientation du scale 0 pour (horizontal) et 1 pour (verticale)
gdouble pas; //Le pas deplacement
gdouble Min; //Valeur minimale
gdouble Max; //Valeur maximale
}Scale;

/**structure de frame**/
typedef struct
{
    GtkWidget *frame;//widget frame
    GtkWidget *contenaire;//le contenaire du frame
    gchar *label;//libell� de la frame
    gint shadow;// type du contour de frame
    /**GTK_SHADOW_NONE: pas de bordure.
     0=GTK_SHADOW_IN: le contour est biseaut� vers l�int�rieur.
     1=GTK_SHADOW_OUT: le contour est biseaut� vers l'int�rieur comme un bouton.
     2=GTK_SHADOW_ETCHED_IN: le contour a une apparence 3D enfonc�e.
     3=GTK_SHADOW_ETCHED_OUT: le contour a une apparence en 3D en relief.
     **/
    int Hauteur; //Hauteur
    int Largeur; //Largeur
    gfloat align_x;
    gfloat align_y;
}frame;


typedef struct
{
    GtkWidget   *comboBox;  // notre objet
    GtkWidget   *contenaire;    // le conteneur
    int posx;//la position x
    int posy;//la position x
    int entry;
}ComboBox;

typedef struct
{
    gint pos_x;
    gint pos_y;
}Position;

typedef struct
{
    GtkWidget * fixed;
    Position P;
}FIXED;

typedef struct
{
    GtkWidget*bar;
    gint positionbar;
}Menubar;

typedef struct
{
    GtkWidget*menu;
    GtkWidget*item;
    GSList*radio;
    gchar*nom;
    gchar*icone;
}Menu;

typedef struct
{
    Image *DataImage[4];
    FIXED *DataFixed;
    Fenetre *DataWindow;
}DataSTR;










/*
typedef struct
{
    GtkWidget *toolbar;
    GtkToolItem *Item;
    GtkWidget *container;
    int type_item;
                /* 0: pour un nouveau fichier (GTK_STOCK_NEW)
                   1: pour ouvrir fichier (GTK_STOCK_OPEN)
                   2: pour sauvgarder fichier (GTK_STOCK_SAVE)
                   3: pour quitter (GTK_STOCK_QUIT)
                   4: pour UNDO (GTK_STOCK_UNDO)
                   5: pour REDO (GTK_STOCK_REDO)
                   6: pour separateur
}ToolBar;*/
typedef struct{
  GtkWidget *toolbar;//barre d'outile
  GtkToolbarStyle style;//style de la barre d'outile
  gint show_arrow;//
  gchar orientation;//h:horizontale, v:verticale
}TOOLbar;

typedef struct
{
    GtkWidget   *scrolledWindow;      // la fenetre défilée
    GtkWidget   *parent;              // l'objet conteneur
    //GtkWidget   *fixed;             // le fixed container
    //gchar       *nom;                 // nom de l'objet
    gint        hbarre;               // politique pour la barre horizontale
    gint        vbarre;               // politique pour la barre verticale
    //IlisiPos    *pox;               // la position de l'objet
}IP_ScrolledWindow;

typedef struct IlisiMessage
{
  GtkWidget *message;           /* l'objet creer message*/
  GtkWidget *pere;              /* le conteneur de l'objet*/
  int flag;                    /* valeurs possibles:
                                    1: MODAL ( separer )
                                    2: DESTROY_WITH_PARENT
                                        ( en relation avec le pere);*/
  int type_message;            /* valeurs possibles:
                                    i: GTK_MESSAGE_INFO;
                                    w: GTK_MESSAGE_WARNING;
                                    q: GTK_MESSAGE_QUESTION
                                    e: GTK_MESSAGE_ERROR*/
  int type_boutton;             /*
                                    0 : sans button
                                    1 : OK
                                    2 : CLOSE
                                    3 : CANCEL
                                    4 : YES_NO
                                    5 : OK_CANCEL*/

  char *message_a_afficher;     // le message a afficher
}IP_Message;
/*typedef struct
{
    GtkWidget*dialog;
    GtkWidget*fenetre;
    const gchar*nomFichier;
    const gchar *titre;
}selection_fichier_dialog;*/
typedef struct
{

    GtkWidget   *scrollWindow;
    GtkWidget   *container;
    int        H_policy;
    int        V_policy;
    /**0:GTK_POLICY_ALWAYS 	 The scrollbar is always visible. The view size is independent of the content.
      1:GTK_POLICY_AUTOMATIC The scrollbar will appear and disappear as necessary.
                              For example, when all of a GtkTreeView can not be seen.
      2:GTK_POLICY_NEVER: The scrollbar should never appear. In this mode the content determines the size.
      3:GTK_POLICY_EXTERNAL Don’t show a scrollbar, but don’tforce the
                            size to follow the content. This can be used e.g. to make multiple scrolled windows share
                             a scrollbar**/
    int shadow;
        /**GTK_SHADOW_NONE: pas de bordure.
     0=GTK_SHADOW_IN: le contour est biseaut� vers l�int�rieur.
     1=GTK_SHADOW_OUT: le contour est biseaut� vers l'int�rieur comme un bouton.
     2=GTK_SHADOW_ETCHED_IN: le contour a une apparence 3D enfonc�e.
     3=GTK_SHADOW_ETCHED_OUT: le contour a une apparence en 3D en relief.
     **/
}scrollWindow;



typedef struct
{
    GtkWidget *layout;
    GtkWidget* container;
    gchar *image;

}layout;

typedef struct IlisiTable
{
  GtkWidget *table;             // l'objet table
  GtkWidget *pere;              // le contenaire
  int nbr_lignes;               // nombre de ligne
  int nbr_colonnes;             // nombre de collone
  int homogene;                 /*  TRUE , 0: pour FALSE */
} IlisiTable;


typedef struct celindiv
{
     gint Id;
     gchar Nomcomplet[26];
     gint Pos_x;
     gint Pos_y;
     gint TypeMv;
     gint Age;
     gint Sexe;
     gint MvH;
     gint MvV;
     gint Genetiquement;
     gint Diabete;
     gint Cardiaque;
     gint Poumons;
     gint Cancers;
     gint Tar;
     gint DjCovid;
     gint MaladeCovid;
     gint TypeCovid;
     gint Score;
     gint MvStop;
     gint ActiveSignalId;
     gint SuppressionSignalId;
     gint Avatar;
     gint EstMort;
     gint ValDeMort;
     gint TempsCpt;
     Image *IndivImage;
     Image *VirusImage;
     struct celindiv* Suivant;
}CelluleIndiv;

typedef struct ETL
{
    GtkWidget *NomEntry;
    GtkWidget *PosXEntry;
    GtkWidget *PosYEntry;
    GtkWidget *Age;
    GtkWidget *TypeMv;
    struct ETL *Suivant;
}EntriesListe;



typedef struct cel
{
    Label *IndivIdLb;
    Label *IndivNomLb;
    Label *IndivMaladeCovidLb;
    Label *IndivSexeLb;
    Label *PositionLb;
    Label *AgeLb;
    Label *TypeMvLb;
    Button *ModifierIndivBtn;
    struct cel *Suivant;
}ListeInfos;

