// ImageReelle.cpp : implementation file
//

#include "stdafx.h"

#include "ImageReelle.h"
//#include "DialogImage.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include <math.h>

/******************************************************************/
/*Fonctions utiles						  */
/******************************************************************/
//fonction retournant true si une valeur est suffisament petite


/****************************************************************/
/*Implementation des fonctions membres de la classe image reelle*/
/****************************************************************/
//constructeur de image reelle avec initialisation
CImageReelle::CImageReelle(int width, int length, double maxGris, double minGris){
	int i;
	NbColonnes = width;
	NbLignes = length;

	matrice = new double*[length];
	for (i=0; i<length; i++)
		matrice[i] = new double[width];
}
//constructeur simple de image reelle
CImageReelle::CImageReelle()
{
	NbColonnes = 0;
	NbLignes = 0;
	matrice = NULL;
}
//initialisation d'une image reelle

//destructeur de image reelle
CImageReelle::~CImageReelle()
{
	//liberer la memoire
	if (matrice){
		for (int i=0; i<NbLignes; i++)
			if (matrice[i])
				delete matrice[i];
		delete matrice;
	}

}

void CImageReelle::initialiser(int width, int length)
{
	int i;
	NbColonnes = width;
	NbLignes = length;
	MaxNivGris = 1.;

	matrice = new double*[length];
	for (i=0; i<length; i++)
		matrice[i] = new double[width];
}

//lecture d'une image a partir du disque dans la memoire
bool CImageReelle::lecture(CString pNomFichier)
{
  int i, j, n; // compteurs
  char TypeFichier[3] ; //sert a lire la premiere ligne: type de fichier
  char Createur[256];  //sert a lire la deuxieme ligne: createur du fichier, commentaire
  int c;
	
  if( (fichier = fopen(pNomFichier , "r+b" )) == NULL ) 
  {	  
	  AfxMessageBox("Le fichier ne peut etre ouvert en lecture");
	  return false;
  }
  else
  {	  //lecture de la premiere ligne: type du fichier
	  fscanf(fichier,"%s", TypeFichier);
      fgetc(fichier);
      if (strcmp("P5", TypeFichier) != 0)
	  {//l'extension est pgm mais pas le contenu
        AfxMessageBox ("Fichier pas du type pgm");
	     return false;
      } 
	  else
	  {
	      //lecture des lignes de commentaires qui commencent par # 
	      while (fscanf(fichier,"#%[^\n]", Createur)) //lecture jusqu'a la fin de ligne
		  fgetc(fichier);
	      //lecture de la ligne suivante: NbColonnes et NbLignes de l'image
	      fscanf(fichier,"%i %i", &NbColonnes, &NbLignes);
	      fgetc(fichier);		
	      //lecture de la quatrieme ligne: Maximum de niveaux de gris
	      fscanf(fichier, "%i" ,&MaxNivGris);
          fgetc(fichier);
		  //Initialisation de l'image
		  initialiser(NbColonnes, NbLignes);
		  // Lire le contenu de l'image 
		  n=0;
		  c=' ';//valeur bidon
		  for (i=0; i<NbLignes; i++)
		  {
			for (j=0; j<NbColonnes; j++)
			{
				c= fgetc(fichier);
				matrice[i][j]=  (double)(c);
				if (matrice[i][j]<0) 
					matrice[i][j]=256+matrice[i][j];
			}
		  }	  
		  return true;
	  }
  }
  fclose(fichier);
}


