// DialogImage.cpp : implementation file
//

#include "stdafx.h"
#include "PgmImage2.h"
#include "DialogImage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogImage dialog


CDialogImage::CDialogImage(CImageReelle* pImage, CWnd* pParent /*=NULL*/)
	: CDialog(CDialogImage::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogImage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
		ptImage = pImage;
		width=pImage->NbColonnes;
		length=pImage->NbLignes;
	
}
CDialogImage::CDialogImage(int largeur, int longueur, CImageReelle* pImage, CWnd* pParent /*=NULL*/)
	: CDialog(CDialogImage::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogImage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
		ptImage = pImage;
		width=largeur;
		length=longueur;
}


void CDialogImage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogImage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogImage, CDialog)
	//{{AFX_MSG_MAP(CDialogImage)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogImage message handlers

void CDialogImage::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	int HorizontalShift=20;  //decalages entre les bords de la boite de dialogue et l'image
	int VerticalShift=20;
	int i, j; // compteurs
	float valeur; //valeur du niveau de gris en un point
	CClientDC ClientDC(this);

    for (j=0;j<width;j++){
	  for (i=0;i<length;i++){
	    if (ptImage->matrice[i][j]>=0)
			valeur = ptImage->matrice[i][j];
		else 
			valeur = 256+ptImage->matrice[i][j];
	    ClientDC.SetPixelV(j+HorizontalShift, i+VerticalShift, RGB(valeur, valeur,valeur));
		
	  
	  }
    }

}

void CDialogImage::OnLButtonDown(UINT nFlags, CPoint point)
{
	CClientDC ClientDC(this);

	int HorizontalShift=20;  //decalages entre les bords de la boite de dialogue et l'image
	int VerticalShift=20;
	int i, j; // compteurs
	float valeur; //valeur du niveau de gris en un point

	int h[256];
	int max;

	for(i=0;i<256;i++)
		h[i] = 0;

    for (j=0;j<width;j++){
	  for (i=0;i<length;i++){
	    if (ptImage->matrice[i][j]>=0)
			valeur = ptImage->matrice[i][j];
		else 
			valeur = 256+ptImage->matrice[i][j];
	  //  ClientDC.SetPixelV(j+HorizontalShift, i+VerticalShift, RGB(valeur, valeur,valeur));
		
		h[(int)valeur]++;
	  }
    }

	// Trouver le max de h 
	max = 0;
	for(i=0;i<256;i++)
	{
		if(h[i] > max)
			max = h[i ];
	}

	CPen pen;
	CPen penLine;
	CBrush brush;

	penLine.CreatePen(PS_SOLID, 2, RGB(0,0,255));
	ClientDC.SelectObject(&penLine);

	pen.CreatePen(PS_SOLID, 2, RGB(255,0,0));
	ClientDC.SelectObject(&pen);

	brush.CreateSolidBrush(RGB(0,255,0));
	
	ClientDC.SelectObject(&brush);
	ClientDC.Ellipse(HorizontalShift+width-1+i,200-(VerticalShift-1+(int)((float)h[0]/max*200.0)),HorizontalShift+width+1+i,200-(VerticalShift+1+(int)((float)h[0]/max*200.0)));
	ClientDC.MoveTo(HorizontalShift+width,200-(VerticalShift+(int)((float)h[0]/max*200.0)));
	for(i=1;i<256;i++)
	{
		ClientDC.SelectObject(&penLine);
		ClientDC.LineTo(HorizontalShift+width+i,200-(VerticalShift+(int)((float)h[i]/max*200.0)));


		ClientDC.MoveTo(HorizontalShift+width+i,200-(VerticalShift+(int)((float)h[i]/max*200.0)));
		ClientDC.SelectObject(&brush);
		ClientDC.Ellipse(HorizontalShift+width-1+i,200-(VerticalShift-1+(int)((float)h[i]/max*200.0)),HorizontalShift+width+1+i,200-(VerticalShift+1+(int)((float)h[i]/max*200.0)));
	}		

	

	CDialog::OnLButtonDown(nFlags, point);
}

void CDialogImage::OnRButtonDown(UINT nFlags, CPoint point)
{

	CClientDC ClientDC(this);
	int HorizontalShift=20;  //decalages entre les bords de la boite de dialogue et l'image
	int VerticalShift=20;
	int i, valeur=255;
	float x,y;
	float listeX[10000];
	float listeY[10000];
	int nbPt=0;
	int xc,yc;
	int a,b;
	float A,B,C,D,F,G;
	float p1,p2;
	float theta;
	//xc=538; //671
	//yc=628; //357
	//a=458; //33
	//b=628; //38

	xc=671; //671
	yc=357; //357
	a=33; //33
	b=38; //38
	theta=-10.0;

	A = 1.833189e-6;
	B = 1.57982e-8/2.0;
	C = 1.36399925e-6;
	D = -0.002464/2.0;
	F = -0.0009835/2.0;
	G = 0.9999965;

	xc = (C*D-B*F)/(B*B-A*C);
	yc = (A*F-B*D)/(B*B-A*C);


	a = (int)pow((2.0*(A*F*F+C*D*D+G*B*B-2.0*B*D*F-A*C*G))/((B*B-A*C)*(pow((A-C)*(A-C) + 4.0*B*B,0.5)-(A+C))),0.5);
	b = (int)pow((2.0*(A*F*F+C*D*D+G*B*B-2.0*B*D*F-A*C*G))/((B*B-A*C)*((-1)*pow((A-C)*(A-C) + 4.0*B*B,0.5)-(A+C))),0.5);

	theta = 3.14159/4.0 - atan((A-C)/(2.0*B))/2.0;
	if(A > C)
		theta += 3.14159/2.0;

	theta = -theta*90/3.14159; // theta en degre

	//printf("\n xc = %d \t yc = %d \t a = %d \t b = %d \t theta = %lf ",xc,yc,a,b,theta);


	x=0;y=b; 

	listeX[nbPt] = xc+x;
	listeY[nbPt++]= yc+y;
	listeX[nbPt] = xc-x;
	listeY[nbPt++]= yc+y;
	listeX[nbPt] = xc+x;
	listeY[nbPt++]= yc-y;
	listeX[nbPt] = xc-x;
	listeY[nbPt++]= yc-y;

	p1=(b*b)-(a*a*b)+(a*a)/4;
	while((2.0*b*b*x)<=(2.0*a*a*y))
	{
		x++;
		if(p1<=0)
		p1=p1+(2.0*b*b*x)+(b*b);
		else
		{
			y--;
			p1=p1+(2.0*b*b*x)+(b*b)-(2.0*a*a*y);
		}

		listeX[nbPt] = xc+x;
		listeY[nbPt++]= yc+y;
		listeX[nbPt] = xc-x;
		listeY[nbPt++]= yc+y;
		listeX[nbPt] = xc+x;
		listeY[nbPt++]= yc-y;
		listeX[nbPt] = xc-x;
		listeY[nbPt++]= yc-y;
		x=-x;
		listeX[nbPt] = xc+x;
		listeY[nbPt++]= yc+y;
		listeX[nbPt] = xc-x;
		listeY[nbPt++]= yc+y;
		listeX[nbPt] = xc+x;
		listeY[nbPt++]= yc-y;
		listeX[nbPt] = xc-x;
		listeY[nbPt++]= yc-y;
		x=-x;
	}
	x=a;
	y=0;

	listeX[nbPt] = xc+x;
	listeY[nbPt++]= yc+y;
	listeX[nbPt] = xc-x;
	listeY[nbPt++]= yc+y;
	listeX[nbPt] = xc+x;
	listeY[nbPt++]= yc-y;
	listeX[nbPt] = xc-x;
	listeY[nbPt++]= yc-y;

	p2=(a*a)+2.0*(b*b*a)+(b*b)/4;
	while((2.0*b*b*x)>(2.0*a*a*y))
	{
		y++;
		if(p2>0)
			p2=p2+(a*a)-(2.0*a*a*y);
		else
		{
			x--;
			p2=p2+(2.0*b*b*x)-(2.0*a*a*y)+(a*a);
		}

		listeX[nbPt] = xc+x;
		listeY[nbPt++]= yc+y;
		listeX[nbPt] = xc-x;
		listeY[nbPt++]= yc+y;
		listeX[nbPt] = xc+x;
		listeY[nbPt++]= yc-y;
		listeX[nbPt] = xc-x;
		listeY[nbPt++]= yc-y;

		y=-y;

		listeX[nbPt] = xc+x;
		listeY[nbPt++]= yc+y;
		listeX[nbPt] = xc-x;
		listeY[nbPt++]= yc+y;
		listeX[nbPt] = xc+x;
		listeY[nbPt++]= yc-y;
		listeX[nbPt] = xc-x;
		listeY[nbPt++]= yc-y;

		y=-y;

	}


	for(i=0;i<nbPt;i++)
	{
		x= (xc-listeX[i])*cos(theta*3.14159/180.0)-(yc-listeY[i])*sin(theta*3.14159/180.0)+xc;
		y= (xc-listeX[i])*sin(theta*3.14159/180.0)+ (yc-listeY[i])*cos(theta*3.14159/180.0)+yc;
		ClientDC.SetPixelV(x+HorizontalShift, y+VerticalShift, RGB(valeur, 0,0));
	}



	CDialog::OnRButtonDown(nFlags, point);
}
