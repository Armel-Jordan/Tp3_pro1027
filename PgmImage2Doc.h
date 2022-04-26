// PgmImage2Doc.h : interface of the CPgmImage2Doc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PGMIMAGE2DOC_H__2072F55B_EF09_4A23_B5DF_BFFC8B906DFF__INCLUDED_)
#define AFX_PGMIMAGE2DOC_H__2072F55B_EF09_4A23_B5DF_BFFC8B906DFF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CPgmImage2Doc : public CDocument
{
protected: // create from serialization only
	CPgmImage2Doc();
	DECLARE_DYNCREATE(CPgmImage2Doc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPgmImage2Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPgmImage2Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CPgmImage2Doc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PGMIMAGE2DOC_H__2072F55B_EF09_4A23_B5DF_BFFC8B906DFF__INCLUDED_)
