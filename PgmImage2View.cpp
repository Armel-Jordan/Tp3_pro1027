// PgmImage2View.cpp : implementation of the CPgmImage2View class
//

#include "stdafx.h"
#include "PgmImage2.h"

#include "PgmImage2Doc.h"
#include "PgmImage2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPgmImage2View

IMPLEMENT_DYNCREATE(CPgmImage2View, CView)

BEGIN_MESSAGE_MAP(CPgmImage2View, CView)
	//{{AFX_MSG_MAP(CPgmImage2View)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPgmImage2View construction/destruction

CPgmImage2View::CPgmImage2View()
{
	// TODO: add construction code here

}

CPgmImage2View::~CPgmImage2View()
{
}

BOOL CPgmImage2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CPgmImage2View drawing

void CPgmImage2View::OnDraw(CDC* pDC)
{
	CPgmImage2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CPgmImage2View diagnostics

#ifdef _DEBUG
void CPgmImage2View::AssertValid() const
{
	CView::AssertValid();
}

void CPgmImage2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPgmImage2Doc* CPgmImage2View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPgmImage2Doc)));
	return (CPgmImage2Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPgmImage2View message handlers
