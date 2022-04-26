#if !defined(AFX_IMAGEREELLE_H__0DFAC956_0738_11D5_AA78_0050FC20AEF7__INCLUDED_)
#define AFX_IMAGEREELLE_H__0DFAC956_0738_11D5_AA78_0050FC20AEF7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ImageReelle.h : header file
//

#include "ImageReelle.h"
#include <windows.h>


// definition de la classe image reelle
class CImageReelle{
 
public:
    CImageReelle(int width, int length, double maxGris, double minGris);   // constructeur avec initialisation
	CImageReelle();   // constructeur simple
    ~CImageReelle();  //destructeur
	void initialiser(int width, int length); 
	bool lecture(CString pNomFcihier);
	void ecriture();

public :
	FILE *fichier;  //fichier lu
	int NbLignes,NbColonnes;
	double MaxNivGris;
	double **matrice; 
};

#endif // !defined(AFX_IMAGEREELLE_H__0DFAC956_0738_11D5_AA78_0050FC20AEF7__INCLUDED_)
