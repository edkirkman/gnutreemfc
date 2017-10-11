
// gnutreemfcView.cpp : implementation of the CgnutreemfcView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "gnutreemfc.h"
#endif

#include "gnutreemfcDoc.h"
#include "gnutreemfcView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CgnutreemfcView

IMPLEMENT_DYNCREATE(CgnutreemfcView, CView)

BEGIN_MESSAGE_MAP(CgnutreemfcView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CgnutreemfcView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CgnutreemfcView construction/destruction

CgnutreemfcView::CgnutreemfcView()
{
	// TODO: add construction code here

}

CgnutreemfcView::~CgnutreemfcView()
{
}

BOOL CgnutreemfcView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CgnutreemfcView drawing

void CgnutreemfcView::OnDraw(CDC* pDC)
{
	CgnutreemfcDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	CString s = _T("Ed was here");   // Returns a CString
	CRect rect;
	GetClientRect(&rect);

	pDC->SetTextAlign(TA_BASELINE | TA_CENTER);
	pDC->TextOut(rect.right / 2, rect.bottom / 2, s, s.GetLength());
	// TODO: add draw code for native data here
}


// CgnutreemfcView printing


void CgnutreemfcView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CgnutreemfcView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CgnutreemfcView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CgnutreemfcView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CgnutreemfcView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CgnutreemfcView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CgnutreemfcView diagnostics

#ifdef _DEBUG
void CgnutreemfcView::AssertValid() const
{
	CView::AssertValid();
}

void CgnutreemfcView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CgnutreemfcDoc* CgnutreemfcView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CgnutreemfcDoc)));
	return (CgnutreemfcDoc*)m_pDocument;
}
#endif //_DEBUG


// CgnutreemfcView message handlers
