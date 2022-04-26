// PgmImage2.h : main header file for the PGMIMAGE2 application
//

#if !defined(AFX_PGMIMAGE2_H__68D41218_FDBB_411B_AF9A_442F9A2E1DFF__INCLUDED_)
#define AFX_PGMIMAGE2_H__68D41218_FDBB_411B_AF9A_442F9A2E1DFF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CPgmImage2App:
// See PgmImage2.cpp for the implementation of this class
//

class CPgmImage2App : public CWinApp
{
public:
	CPgmImage2App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPgmImage2App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CPgmImage2App)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PGMIMAGE2_H__68D41218_FDBB_411B_AF9A_442F9A2E1DFF__INCLUDED_)
