// DialogImage.cpp : implementation file
//

#include "stdafx.h"
#include "PgmImage2.h"
#include "DialogImage.h"
#include "Util.h"
#include <math.h>
#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogImage dialog

void SendKey(HWND hWndTargetWindow, BYTE virtualKey)
{
	keybd_event(virtualKey, 0, 0, 0);
	keybd_event(virtualKey, 0, KEYEVENTF_KEYUP, 0);
}


CDialogImage::CDialogImage(CImageReelle* pImage, CWnd* pParent /*=NULL*/)
	: CDialog(CDialogImage::IDD, pParent)
	, int_xmin(0)
	, int_xmax(0)
	, dbl_pasInt(0)
	, polDegree(0)
	, dbl_pasApprox(0)
{
		ptImage = pImage;
		width=pImage->NbColonnes;
		length=pImage->NbLignes;
	
}
CDialogImage::CDialogImage(int largeur, int longueur, CImageReelle* pImage, CWnd* pParent /*=NULL*/)
	: CDialog(CDialogImage::IDD, pParent)
{
		ptImage = pImage;
		width=largeur;
		length=longueur;
}


void CDialogImage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, int_xmin);
	DDX_Text(pDX, IDC_EDIT2, int_xmax);
	DDX_Text(pDX, IDC_EDIT3, dbl_pasInt);
	DDX_Text(pDX, IDC_EDIT4, polDegree);
	DDX_Text(pDX, IDC_EDIT5, dbl_pasApprox);
}


BEGIN_MESSAGE_MAP(CDialogImage, CDialog)
	//{{AFX_MSG_MAP(CDialogImage)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_BN_CLICKED(IDC_BUTTON1, &CDialogImage::btnLoadDataClicked)
	ON_BN_CLICKED(IDC_BUTTON2, &CDialogImage::btnCubicSplintClicked)
	ON_BN_CLICKED(IDC_BUTTON3, &CDialogImage::btnExtremumsClicked)
	ON_BN_CLICKED(IDC_BUTTON4, &CDialogImage::btnApproximationClicked)
	ON_EN_CHANGE(IDC_EDIT1, &CDialogImage::OnEnChangeEdit1)
	ON_BN_CLICKED(IDCANCEL, &CDialogImage::OnBnClickedCancel)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogImage message handlers


void CDialogImage::OnPaint() 
{
}


void CDialogImage::OnLButtonDown(UINT nFlags, CPoint point)
{	
	CDialog::OnLButtonDown(nFlags, point);
}


void CDialogImage::OnRButtonDown(UINT nFlags, CPoint point)
{
	CDialog::OnRButtonDown(nFlags, point);
}


//Creer et remplir les 2 vecteurs de donnees (temps et angles) avec les donnees du fichier HGN200mg.txt
void CDialogImage::btnLoadDataClicked()
{
	Util util;

	if (fichierOuvert) {
		MessageBox("Les donnees ont deja ete chargees");
		return;
	}
	std::string input;
	int i = 0;

	static char BASED_CODE szFilter[] = "Fichiers .txt |*.txt||";
	CFileDialog dlg(TRUE, "txt", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter); 
	if (dlg.DoModal() == IDOK) { //ouvrir la boite de dialogue d'ouverture de fichier
		CString strFileExtension = dlg.GetFileExt();
		strFileExtension.MakeUpper();
		if (strFileExtension == "TXT") { //on veut un fichier txt
			CString pPathName = dlg.GetPathName();
			std::ifstream file1(pPathName);
			if (file1.is_open()) //si le fichier s'est bien ouvert
			{
				fichierOuvert = true;	
				std::getline(file1, input); //prendre une ligne et la stocket dans input
				vecLength = stoi(input); //la 1ere entree est le nombre de donn�es, on le converti en int
				dataAngles = util.nrvector(1, vecLength); //cr�ation des 2 vecteurs de donn�es x et y
				dataTemps = util.nrvector(1, vecLength);
				i++;			

				while (file1.good())
				{
					std::getline(file1, input);
					dataAngles[i] = stod(input); //convertir la donnee lue (angle) en double
					dataTemps[i] = i; //les donnees sont prises à temps fixe
					i++;
				}
			}
		}
		else MessageBox("Le fichier n'est pas de type TXT: le fichier n'a pas ete ouvert");
	}
	else MessageBox("aucun fichier n'a ete ouvert");
}


void CDialogImage::btnCubicSplintClicked()
{
	Util util;

	if (!fichierOuvert) {
		MessageBox("Les donnees n'ont pas ete chargees");
		return;
	}

	UpdateData(true);
	UpdateData(false);
	
	deriv2Splines = util.nrvector(1,int_xmax);

	if (int_xmin<=0||int_xmax>vecLength||dbl_pasInt<=0) {
		MessageBox("Les valeurs entrees sont hors limites.");
		return;
	}

	//Trouver les derivees secondes des splines cubiques
	double yp1 = (dataAngles[2] - dataAngles[1]) / (dataTemps[1] - dataTemps[2]);
	double ypn = (dataAngles[vecLength] - dataAngles[vecLength -1]) / (dataTemps[vecLength] - dataTemps[vecLength - 1]);
	util.spline(dataTemps, dataAngles, int_xmax, 0,0, deriv2Splines);

	//Interpoler les valeurs à chaque pas d'interpolation
	int nbSteps = (int_xmax - int_xmin) / dbl_pasInt;
	
	double y;
	yInterpol = util.nrvector(int_xmin,int_xmin+nbSteps);

	for (int i = int_xmin; i <= (int_xmin+nbSteps); i++) {
		util.splint(dataTemps, dataAngles, deriv2Splines,vecLength, i*dbl_pasInt, &y);
		yInterpol[i]=y;
	}
	//Afficher les pts de controle et les splines
	affichageSplint(yInterpol,510,510,nbSteps, vecLength);

	if (int_xmin ==1 && int_xmax==51) {

		integrerSplineAll(deriv2Splines, dataAngles, vecLength, 1, vecLength);
	}
}

void CDialogImage::affichageSplint(double * y, int width, int length, int nbSteps, int dataSize)
{
	//1. Affichage des points de controle
	CClientDC ClientDC(this);
	CPen pen;
	CPen penLine;
	CBrush brush;
	penLine.CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	pen.CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	ClientDC.SelectObject(&pen);
	brush.CreateSolidBrush(RGB(255, 0, 0));
	ClientDC.SelectObject(&brush);
	double tempX, tempY;
	int posX, posY;
	int horizontalShift = 20;
	int verticalShift = 20;
	int j = 0;

	tempX = j*(width / nbSteps); //numero de la donnee * nbr de pixel par donnee en x=position x de la donnee
	tempY = dataAngles[int_xmin] * (length / dataSize); //nbr de pixel par donnee en y
	if (tempX - (int)tempX > 0.5)
		posX = (int)(ceil(tempX));
	else
		posX = (int)tempX;
	if (tempY - (int)tempY > 0.5)
		posY = (int)(ceil(tempY));
	else
		posY = (int)tempY;
	ClientDC.MoveTo(horizontalShift, length - posY - verticalShift);
	ClientDC.SelectObject(&pen);
	ClientDC.SelectObject(&penLine);
	ClientDC.SelectObject(&pen);
	ClientDC.Ellipse(posX + horizontalShift - 2, length - posY - verticalShift + 2, posX + horizontalShift + 2, length - posY - verticalShift - 2); //Tracer un cercle qui repr�sente le point de contr�le 0
	j++;
	int compteurControle = 1;

	for (int i = int_xmin+1; i <= (int_xmin+nbSteps); i++) {
		tempX = j*(width / nbSteps); //numero de la donnee * nbr de pixel par donnee en x=position x de la donnee
		tempY = y[i] * (length / dataSize); //nbr de pixel par donnee en y
		if (tempX - (int)tempX > 0.5)
			posX = (int)(ceil(tempX));
		else
			posX = (int)tempX;
		if (tempY - (int)tempY > 0.5)
			posY = (int)(ceil(tempY));
		else
			posY = (int)tempY;

		if (compteurControle==(int)(1/dbl_pasInt)) {//nous sommes a un point de controle
			compteurControle = 0;
			ClientDC.SelectObject(&pen);
			ClientDC.Ellipse(posX + horizontalShift - 2, length - posY - verticalShift + 2, posX + horizontalShift + 2, length - posY - verticalShift - 2); //Tracer un cercle qui repr�sente le point de contr�le i
		}

		ClientDC.SelectObject(&penLine);
		ClientDC.LineTo(horizontalShift + posX, length - verticalShift - posY );
		ClientDC.MoveTo(horizontalShift + posX, length - verticalShift - posY);
		compteurControle++;
		j++;
	}
}

double* CDialogImage::calculerDerivees()
{
	Util util;

	int nbSteps = (int_xmax - int_xmin) / dbl_pasInt;
	double* derivees = util.nrvector(int_xmin, int_xmin + nbSteps);
	int start = int_xmin;
	int end = int_xmin + nbSteps;

	if (int_xmin == 1) {
		start = 2; //ne pas iterer sur le point de controle 1
		derivees[int_xmin] = (dataAngles[2] - dataAngles[1]) / (dataTemps[2] - dataTemps[1]); //Les derivees des bords
	}
	if (int_xmax==vecLength) {
		end = int_xmin + nbSteps - 1; //ne pas iterer sur le point de controle 51
		derivees[int_xmin + nbSteps] = (dataAngles[vecLength] - dataAngles[vecLength - 1]) / (dataTemps[vecLength] - dataTemps[vecLength - 1]);
	}

	//calculer les derivees de chaque point
	for (int i = start; i <= end; i++) {
		derivees[i] = (yInterpol[i] - yInterpol[i - 1]) / (i*dbl_pasInt - (i-1)*dbl_pasInt);
	}

	return derivees;
}


void CDialogImage::btnExtremumsClicked()
{
	int nbSteps = (int_xmax - int_xmin) / dbl_pasInt;
	//1. Calculer la derivee de yInterpol
	double* derivees = calculerDerivees();
	//2. affichage des extremums
	affichageExtremums(derivees, nbSteps);
	
}

void CDialogImage::affichageExtremums(double* derivees, int nbSteps) {

	CClientDC ClientDC(this);
	CPen pen;
	CPen penLine;
	CBrush brush;
	penLine.CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
	pen.CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
	ClientDC.SelectObject(&pen);
	brush.CreateSolidBrush(RGB(0, 0, 255));
	ClientDC.SelectObject(&brush);
	double tempX, tempY;
	int posX, posY;
	int horizontalShift = 20;
	int verticalShift = 20;
	int j = 0;
	int num;
	bool isExtremum;
	width = 510;
	length = 510;

	for (int i = int_xmin;i <= int_xmin + nbSteps; i++) {

		isExtremum = false;

		if (derivees[i]>0&&derivees[i+1]<0 || derivees[i]<0 && derivees[i + 1]>0) { //passage par 0 direct
			//PASSAGE PAR 0 -> TRACER LIGNE BLEUE
			isExtremum = true;
		}
		else if (derivees[i] == 0) { //nous sommes sur un plateau -> aller voir a droite tant qu'il n'y a pas de changement de signe
			num = i;
			if (derivees[i-1]<0) { 
				while (!derivees[num]<0 || !derivees[num]>0) {
					num++;
				}
				if (derivees[num]>0) {
					//PASSAGE PAR 0 -> TRACER LIGNE BLEUE
					isExtremum = true;
				}
			}
			else if (derivees[i - 1]>0) {
				num = i;
				if (derivees[i - 1]>0) {
					while (!derivees[num]<0 || !derivees[num]>0)
						num++;
					if (derivees[num]<0) {
						//PASSAGE PAR 0 -> TRACER LIGNE BLEUE
						isExtremum = true;
					}
				}
			}
		}

		if(isExtremum)
		{
			tempX = j*(width / nbSteps); //numero de la donnee * nbr de pixel par donnee en x=position x de la donnee
			tempY = yInterpol[i] * (length / vecLength); //nbr de pixel par donnee en y
			if (tempX - (int)tempX > 0.5)
				posX = (int)(ceil(tempX));
			else
				posX = (int)tempX;
			if (tempY - (int)tempY > 0.5)
				posY = (int)(ceil(tempY));
			else
				posY = (int)tempY;

			ClientDC.MoveTo(horizontalShift + posX-6, length - posY - verticalShift);
			ClientDC.SelectObject(&penLine);
			ClientDC.LineTo(horizontalShift + posX+6, length - verticalShift - posY);
		}
		j++;	
	}
}

void CDialogImage::btnApproximationClicked()
{
	Util util;
	CClientDC ClientDC(this);
	UpdateData(true);
	UpdateData(false);
	if (!fichierOuvert) {
		MessageBox("Les donnees doivent etre chargees");
		return;
	}
	if (dbl_pasApprox <= 0 || polDegree >= 5 || dbl_pasApprox<0.1) {
		MessageBox("Les champs pour le pas et le degre doivent etre remplis correctement");
		return;
	}


	//Effacer l'image de depart
	for (int j = 0; j<510; j++)
	{
		for (int i = 0; i < 510; i++)
			ClientDC.SetPixelV(j + 20, i + 20, RGB(240, 240, 240));
	}

	//1. Construire le systeme d'equations ax=b
	//Systeme ax=b
	double** a = util.matrix(1,polDegree+1,1,polDegree+1);
	double* b = util.nrvector(1,polDegree+1);
	double wmax = 0, wmin = 0;

	remplirSystemeApprox(a,b);

	//2. Le resoudre
	x = util.nrvector(1,polDegree+1);//le vecteur solution
	double** v = util.matrix(1, polDegree+1, 1, polDegree+1); //pour svd
	double* w = util.nrvector(1,polDegree+1);//pour svd

	util.svdcmp(a, polDegree + 1, polDegree+1, w, v); //Decomposer la matrice a en 3 matrices

	//Ce bloc s'assure que a ne soit pas singuliere [svbksb() ignore les w=0]
	wmax = 0.0;
	for (int j = 1; j <= polDegree+1;j++) {
		if (w[j] > wmax)
			wmax = w[j];
	}
	wmin = wmax*1.0e-6;
	for (int j = 1; j <= polDegree+1;j++) {
		if (w[j] < wmin)
			w[j] = 0.0;
	}
	
	util.svbksb(a,w,v, polDegree + 1, polDegree+1, b,x); //Resout le systeme ax=b connaissant les 3 matrices correspondant  a

	//a ce point nous connaissons les coefficients du polynome de degre int_polDegree

	//Remplir le vecteur de valeurs approximees (en y)
	int nbSteps = vecLength / dbl_pasApprox;

	double y;
	yApprox = util.nrvector(1, nbSteps);

	for (int i = 1; i <= nbSteps; i++) 
		yApprox[i] = calculerApprox((i)*dbl_pasApprox);

	affichageApprox(yApprox, 510, 510, nbSteps, vecLength);

	//Integration des donnees non approximees par methode du trapeze
	double S = ecartTypeCalc(nbSteps);
	double sigma = S/(vecLength-polDegree-1);

	//Integration polynome approxime:
	double integrApprox = calculerIntegraleApprox(polDegree);

	//Integration methode du trapeze:
	double integrDonnees = integrData();

	//Affichage des resultats
	CString result;
	result.Format("Valeur de S: %f\nValeur de sigma2: %f\n\nIntegrale du polynome: %f\nMethode du trapeze: %f\nDifference entre trapeze et l'integrale du pol.: %f",S,sigma,integrApprox, integrDonnees, integrApprox- integrDonnees);
	MessageBox(result);
	/*
	Pour pouvoir avoir l'affichage des resultats qui sont affichés dans la petite fenetre, appuyer sur la touche "ALT" du clavier.*/
}


void CDialogImage::integrerSplineAll(double* deriv2Splines, double* dataAngles, int length, double h , double intlimit ) {

	double sum = 0;

	double a , b, c,d ,zi, zip1;
	int i = 1;

	//chacun des interval jusqu'au dernier
	while((i+h)<=intlimit ){
		//spline naturelle
		if (i == 1) {
			zi = 0;
		}
		else {
			zi = deriv2Splines[i];
		}
		zip1 = deriv2Splines[i+1];

		a = (zip1 - zi) / (6.0 * h);
		b = zi / 2.0;
		c = (dataAngles[i + 1] - dataAngles[i]) / h - (2 * h*zi + h*zip1) / (6.0);
		d = dataAngles[i];

		sum += (a / 4.0)*h*h*h*h + (b / 3.0)*h*h*h + (c / 2) * h*h + d*h;
		i++;
	}
	
	if (intlimit  != length*h) {
		double dh = (intlimit - i*h);
		i++;

		a = (zip1 - zi) / (6.0 * h);
		b = zi / 2.0;
		c = (dataAngles[i + 1] - dataAngles[i]) / h - (2 * h*zi + h*zip1) / (6.0);
		d = dataAngles[i];

		sum += (a / 4.0)*dh*dh*dh*dh + (b / 3.0)*dh*dh*dh + (c / 2) *dh*dh + d*dh;

		CString result;
		result.Format("L'integrale n'est pas jusqua la derniere borne ", sum);
		MessageBox(result);
	}

	//Affichage des resultats
	CString result;
	result.Format("L'integrale de la spline vaut: %f", sum);
	MessageBox(result);
}


double CDialogImage::integrData()
{
	double integrDonnees = 0;
	Util util;
	for(int i=1;i<vecLength;i++)
		integrDonnees += util.trapzd(dataAngles,i,i+1,1);
	return integrDonnees;
}

double CDialogImage::ecartTypeCalc(int nbSteps) {
	double s = 0;
	for (int i = 1; i <= vecLength; i++) {

		int index = (int)(i-1)/dbl_pasApprox+1;
		s += (yApprox[index] - dataAngles[i])*(yApprox[index] - dataAngles[i]);
	}
	return s;
}



double CDialogImage::calculerIntegraleApprox(int polDegree) {
	double integrApprox=0;
	for (int i = 1;i <= polDegree+1;i++) {
		integrApprox += (x[i]*(pow(vecLength,i)- pow(0, i)))/i;
	}
	return integrApprox;
}


void CDialogImage::affichageApprox(double * y, int width, int length, int nbSteps, int dataSize)
{
	CClientDC ClientDC(this);
	CPen pen;
	CPen penLine;
	CBrush brush;
	penLine.CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	pen.CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	ClientDC.SelectObject(&pen);
	brush.CreateSolidBrush(RGB(255, 0, 0));
	ClientDC.SelectObject(&brush);
	double tempX, tempY;
	int posX, posY;
	int horizontalShift = 20;
	int verticalShift = 20;
	int j = 0;

	tempX = j*(width / nbSteps);
	tempY = y[1] * (length / dataSize); 
	if (tempX - (int)tempX > 0.5)
		posX = (int)(ceil(tempX));
	else
		posX = (int)tempX;
	if (tempY - (int)tempY > 0.5)
		posY = (int)(ceil(tempY));
	else
		posY = (int)tempY;
	ClientDC.MoveTo(horizontalShift, length - posY - verticalShift);
	ClientDC.SelectObject(&pen);
	ClientDC.SelectObject(&penLine);
	j++;

	for (int i = 1;i <= vecLength;i++)
	{
		tempX = (i - 1)*(width / vecLength); //numero de la donnee * nbr de pixel par donnee en x=position x de la donnee
		tempY = dataAngles[i] * (length / vecLength); //nbr de pixel par donnee en y

		if (tempX - (int)tempX > 0.5)
			posX = (int)(ceil(tempX));
		else
			posX = (int)tempX;
		if (tempY - (int)tempY > 0.5)
			posY = (int)(ceil(tempY));
		else
			posY = (int)tempY;

		ClientDC.SelectObject(&pen);
		ClientDC.Ellipse(posX + horizontalShift - 2, length - posY - verticalShift + 2, posX + horizontalShift + 2, length - posY - verticalShift - 2); //Tracer un cercle qui represente le point de controle i
		ClientDC.SelectObject(&penLine);
		ClientDC.LineTo(horizontalShift + posX, length - verticalShift - posY);
		ClientDC.MoveTo(horizontalShift + posX, length - verticalShift - posY);
	}
	for (int i =2; i <= (nbSteps); i++) {
		tempX = j*(width / nbSteps); //numero de la donnee * nbr de pixel par donnee en x=position x de la donnee
		tempY = y[i] * (length / dataSize); //nbr de pixel par donnee en y

		if (tempX - (int)tempX > 0.5)
			posX = (int)(ceil(tempX));
		else
			posX = (int)tempX;
		if (tempY - (int)tempY > 0.5)
			posY = (int)(ceil(tempY));
		else
			posY = (int)tempY;

		ClientDC.SelectObject(&penLine);
		ClientDC.LineTo(horizontalShift + posX, length - verticalShift - posY);
		ClientDC.MoveTo(horizontalShift + posX, length - verticalShift - posY);
		j++;
	}
}

void CDialogImage::remplirSystemeApprox(double** a, double* b)
{
	for(int i=1;i<=polDegree+1;i++)
	{
		for(int j=1;j<=polDegree+1;j++)
		{
			a[i][j]=sumMatrix(i+j-2);
		}
		b[i]=sumVector(i-1);	
	}
}

double CDialogImage::sumMatrix(int exposant)
{
	double sum=0;
	for(int i=1;i<=vecLength;i++)
		sum+=pow(dataTemps[i],exposant);
	return sum;	
}

double CDialogImage::sumVector(int exposant)
{
	double sum=0;
	for(int i=1;i<=vecLength;i++)
		sum+=pow(dataTemps[i],exposant)*dataAngles[i];
	return sum;	
}

double CDialogImage::calculerApprox(double abs)
{
	double y=0;
	for (int i = 1; i <= polDegree+1 + 1;i++)
		y += x[i] * pow(abs,i-1);
	return y;
}





void CDialogImage::OnEnChangeEdit1()
{
}


void CDialogImage::OnBnClickedCancel()
{
	CDialog::OnCancel();
}
