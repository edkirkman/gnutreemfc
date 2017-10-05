
// gnutreemfcView.h : interface of the CgnutreemfcView class
//

#pragma once


class CgnutreemfcView : public CView
{
protected: // create from serialization only
	CgnutreemfcView();
	DECLARE_DYNCREATE(CgnutreemfcView)

// Attributes
public:
	CgnutreemfcDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CgnutreemfcView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in gnutreemfcView.cpp
inline CgnutreemfcDoc* CgnutreemfcView::GetDocument() const
   { return reinterpret_cast<CgnutreemfcDoc*>(m_pDocument); }
#endif

