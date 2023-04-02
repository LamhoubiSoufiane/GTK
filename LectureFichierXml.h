
#include<libxml/parser.h>
#include<libxml/tree.h>
#ifndef LECTUREFICHIER_H
#define LECTUREFICHIER_H

typedef union
{
	Fenetre *Mafenetre;
	Menu *MonMenu;
	Box *Monbox;
	Button *Monbutton;
	Combobox *MonCombo;
}MonUnion;

typedef struct cel
{
	MonUnion Information;
	struct cel *Frere;
	struct cel *Fils;
}Mastructure;

Mastructure *Creer_Init_Cellule_Mastructure(MonUnion Inf)
{
	Mastructure *Nvstr;
	Nvstr = (Mastructure*)malloc(sizeof(Mastructure));
	if (!Nvstr)
	{
		printf("\nErreur d allocation [Mastructure]!!");
		exit(0);
	}
	Nvstr->Information = Inf;
	Nvstr->Fils = Nvstr->Frere = NULL;
	return((Mastructure*)Nvstr);
}

Mastructure *Inserer_Fenetre(Mastructure *str, Mastructure *nv)
{
	Mastructure *ptr=NULL;
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
	Mastructure *combo,*ptr=NULL;
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
	combo = Creer_Init_Cellule_Mastructure(Info);
	for (Elmcb = child->children; Elmcb != NULL; Elmcb = Elmcb->next)
	{
		if (child->type == XML_ELEMENT_NODE)
		{
			if (!strcmp(child->name, "Elem")) Ajouter_Elem_Combobox(combo->Information.MonCombo,
				(char*)xmlGetProp(child, "Titre"),
				atoi((char*)xmlGetProp(child, "id")));
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

}

Mastructure *Traitement_ButtonSimple(Mastructure *box, xmlNodePtr child)
{
	Mastructure *button, *ptr = NULL;
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
	button = Creer_Init_Cellule_Mastructure(Info);
	if (box->Fils)
	{
		ptr = box->Fils;
		while (ptr->Frere) ptr = ptr->Frere;
		ptr->Frere = button;
	}
	else box->Fils = button;
	return((Mastructure*)box);
}



Mastructure *Traitement_Box(Mastructure *fen,xmlNodePtr fils)
{	
	Mastructure *nvbox,*ptr=NULL;
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
	nvbox = Creer_Init_Cellule_Mastructure(Info);
	for (child = fils->children; child != NULL; child = child->next)
	{
		if (child->type == XML_ELEMENT_NODE)
		{
			if (!strcmp(child->name, "Button")) nvbox = Traitement_ButtonSimple(nvbox, child);
			else if (!strcmp(child->name, "Combobox")) nvbox = Traitement_Combobox(nvbox, child);
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

/*Mastructure *Traitement_Menu(Mastructure *fen, xmlNodePtr fils)
{
	Mastructure* nvbox, * ptr = NULL;
	MonUnion Info;
	if (!fen)
	{
		printf("\nErreur, Fenetre n existe pas[Traitement_Menu]!!");
		exit(0);
	}
	Info.MonMenu = Init_Barre_Menu(atoi((char*)xmlGetProp(fils, "TypeBarre")));

}*/

Mastructure *Lirefichier()
{
	xmlDocPtr doc;
	xmlNodePtr root;
	xmlNodePtr noeud;
	xmlNodePtr fils;
	Mastructure *nv, *str=NULL,*ptr=NULL;
	MonUnion Info;
	doc = xmlParseFile("Donnee.xml");
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
				Info.Mafenetre = Init_Personnalise_Fenetre(atoi((char*)xmlGetProp(noeud, "Hauteur")),
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
				nv = Creer_Init_Cellule_Mastructure(Info);
				for (fils = noeud->children; fils != NULL; fils = fils->next)
				{
					if (fils->type == XML_ELEMENT_NODE)
					{
						if (!strcmp(fils->name, "Box")) nv = Traitement_Box(nv, fils);
						//else if (!strcmp(noeud->name, "Menu")) nv=Traitement_Menu(nv,fils);
						//else if (!strcmp(noeud->name, "Combobox")) nv = Traitement_Combobox(nv);
						str = Inserer_Fenetre(str, nv);
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


/*void Creer_Afficher_Structure(Mastructure* str)
{
	if (str)
	{
		if(str)
		Creer_Afficher_Structure(str->Fils);
	}
}*/

#endif
