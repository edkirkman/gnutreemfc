
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

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
