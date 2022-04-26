// PgmImage2Doc.cpp : implementation of the CPgmImage2Doc class
//

#include "stdafx.h"
#include "PgmImage2.h"

#include "PgmImage2Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPgmImage2Doc

IMPLEMENT_DYNCREATE(CPgmImage2Doc, CDocument)

BEGIN_MESSAGE_MAP(CPgmImage2Doc, CDocument)
	//{{AFX_MSG_MAP(CPgmImage2Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPgmImage2Doc construction/destruction

CPgmImage2Doc::CPgmImage2Doc()
{
	// TODO: add one-time construction code here

}

CPgmImage2Doc::~CPgmImage2Doc()
{
}

BOOL CPgmImage2Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CPgmImage2Doc serialization

void CPgmImage2Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CPgmImage2Doc diagnostics

#ifdef _DEBUG
void CPgmImage2Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPgmImage2Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPgmImage2Doc commands
