
// gnutreemfcDoc.h : interface of the CgnutreemfcDoc class
//


#pragma once


class CgnutreemfcDoc : public CDocument
{
protected: // create from serialization only
	CgnutreemfcDoc();
	DECLARE_DYNCREATE(CgnutreemfcDoc)

// Attributes
public:

// Operations
public:
	void Write_to_output(LPCTSTR lpszItem);
	HTREEITEM CgnutreemfcDoc::InsertItem(LPCTSTR level, int, int, HTREEITEM hParent);
// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CgnutreemfcDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	// Tree building
	CStringW atl1, atl2, atl3, atl4, atl5, atl6;
	CStringW catl1, catl2, catl3, catl4, catl5, catl6;
	HTREEITEM hRoot, hl1, hl2, hl3, hl4, hl5, hl6;

	void InitTree();
	void FillRoot(LPCTSTR level, int nImage, int nSelectedImage);
	void AddToTree();
	void ExpandTree();



// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
