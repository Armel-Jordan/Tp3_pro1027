#if !defined(AFX_DIALOGIMAGE_H__7D8FC2BD_E66A_4306_A18B_924A83B05B12__INCLUDED_)
#define AFX_DIALOGIMAGE_H__7D8FC2BD_E66A_4306_A18B_924A83B05B12__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogImage.h : header file
//
#include "ImageReelle.h"
#include <math.h>
#include <malloc.h>

/////////////////////////////////////////////////////////////////////////////
// CDialogImage dialog

class CDialogImage : public CDialog
{
// Construction
public:
	CDialogImage(CImageReelle* pImage,CWnd* pParent = NULL);   // standard constructor
	CDialogImage(int, int, CImageReelle* pImage, CWnd* pParent = NULL);   // constructeur avec redimensionnement

// Dialog Data
	//{{AFX_DATA(CDialogImage)
	enum { IDD = IDD_DIALOG_IMAGE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogImage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogImage)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	CImageReelle * ptImage;
	int width, length;

public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void btnCubicSplintClicked();
	afx_msg void btnLoadDataClicked();
	afx_msg void btnExtremumsClicked();
	afx_msg void btnApproximationClicked();
	void affichageSplint(double* yInterpol, int width, int length, int nbSteps, int dataSize);
	double* calculerDerivees();
	void remplirSystemeApprox(double** a, double* b);
	double sumMatrix(int exposant);
	double sumVector(int exposant);
	double calculerApprox(double abs);
	void affichageApprox(double * y, int width, int length, int nbSteps, int dataSize);
	double calculerIntegraleApprox(int polDegree);
	double ecartTypeCalc(int nbSteps);
	void affichageExtremums(double* derivees, int nbSteps);
	double integrData();
	void integrerSplineAll(double* deriv2Splines, double* dataAngles, int length, double h, double intlimit);
	double polDegree;
	double dbl_pasApprox;
private:
	bool fichierOuvert = false;
	double* dataTemps;
	double* dataAngles;
	double* deriv2Splines;
	double* yInterpol;
	double* xInterpol;
	double* yApprox;
	double* xApprox;
	double* x;
	int int_xmin;
	int int_xmax;
	double dbl_pasInt;
	int vecLength;
public:
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedCancel();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGIMAGE_H__7D8FC2BD_E66A_4306_A18B_924A83B05B12__INCLUDED_)
