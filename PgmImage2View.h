// PgmImage2View.h : interface of the CPgmImage2View class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PGMIMAGE2VIEW_H__8B448013_41A5_4137_ABEA_3A85C9ADED74__INCLUDED_)
#define AFX_PGMIMAGE2VIEW_H__8B448013_41A5_4137_ABEA_3A85C9ADED74__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CPgmImage2View : public CView
{
protected: // create from serialization only
	CPgmImage2View();
	DECLARE_DYNCREATE(CPgmImage2View)

// Attributes
public:
	CPgmImage2Doc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPgmImage2View)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPgmImage2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CPgmImage2View)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in PgmImage2View.cpp
inline CPgmImage2Doc* CPgmImage2View::GetDocument()
   { return (CPgmImage2Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PGMIMAGE2VIEW_H__8B448013_41A5_4137_ABEA_3A85C9ADED74__INCLUDED_)
