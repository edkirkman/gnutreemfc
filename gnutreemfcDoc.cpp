#include "stdafx.h"

// gnutreemfcDoc.cpp : implementation of the CgnutreemfcDoc class
//
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


#include <boost/scoped_ptr.hpp>

/*
Public interface of the MySQL Connector/C++.
You might not use it but directly include directly the different
headers from cppconn/ and mysql_driver.h + mysql_util.h
(and mysql_connection.h). This will reduce your build time!
*/

#ifndef MYSQL_PUBLIC_IFACE_H_
#define MYSQL_PUBLIC_IFACE_H_
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/warning.h>
#include <cppconn/metadata.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/resultset_metadata.h>
#include <cppconn/statement.h>
/*#include <cppconn/connection.h"*/
#include "mysql_driver.h"
#include "mysql_connection.h"

//#include <cppconn/types.h>

#endif /* MYSQL_PUBLIC_IFACE_H_ */
/*
Public interface of the MySQL Connector/C++.
You might not use it but directly include directly the different
headers from cppconn/ and mysql_driver.h + mysql_util.h
(and mysql_connection.h). This will reduce your build time!
*/
// #include <driver/mysql_public_iface.h>
/* Connection parameter and sample data */
#include "examples.h"

using namespace std;


// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "gnutreemfc.h"
#endif

#include "gnutreemfcDoc.h"

#include <propkey.h>
#include "MainFrm.h"
#include "OutputWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CgnutreemfcDoc

IMPLEMENT_DYNCREATE(CgnutreemfcDoc, CDocument)

BEGIN_MESSAGE_MAP(CgnutreemfcDoc, CDocument)
	ON_COMMAND(ID_FILE_SEND_MAIL, &CgnutreemfcDoc::OnFileSendMail)
	ON_UPDATE_COMMAND_UI(ID_FILE_SEND_MAIL, &CgnutreemfcDoc::OnUpdateFileSendMail)
END_MESSAGE_MAP()


// CgnutreemfcDoc construction/destruction

CgnutreemfcDoc::CgnutreemfcDoc()
{
	// TODO: add one-time construction code here
	string url(EXAMPLE_HOST);
	const string user(EXAMPLE_USER);
	const string pass(EXAMPLE_PASS);
	const string database(EXAMPLE_DB);

	/* sql::ResultSet.rowsCount() returns size_t */
	size_t row;
	stringstream sql;
	stringstream msg;
	int i, affected_rows;
	CString str;
	CStringW atl;
	string dbstr1, dbstr2, dbstr3, dbstr4, dbstr5;


	Write_to_output(_T("# Connector/C++ connect basic usage example.."));

try {
	sql::Driver * driver = sql::mysql::get_driver_instance();
	/* Using the Driver to create a connection */
	boost::scoped_ptr< sql::Connection > con(driver->connect(url, user, pass));

	/* Creating a "simple" statement - "simple" = not a prepared statement */
	boost::scoped_ptr< sql::Statement > stmt(con->createStatement());

	/* Create a test table demonstrating the use of sql::Statement.execute() */
	stmt->execute("USE " + database);



	/*
	Run a query which returns exactly one result set like SELECT
	Stored procedures (CALL) may return more than one result set
	*/
	stmt->execute("DROP TABLE IF EXISTS acctreeguid");
	stmt->execute("create temporary table acctreeguid "
		"select t2.name as levl1, t2.guid as guid1, t3.name as levl2, t3.guid as guid2, t4.name levl3, t4.guid as guid3, t5.name levl4, t5.guid as guid4, t6.name levl5, t6.guid as guid5, t7.name levl6, t7.guid guid6 "
		"from accounts as t1 "
		"left join accounts as t2 on t2.parent_guid = t1.guid "
		"left join accounts as t3 on t3.parent_guid = t2.guid "
		"left join accounts as t4 on t4.parent_guid = t3.guid "
		"left join accounts as t5 on t5.parent_guid = t4.guid "
		"left join accounts as t6 on t6.parent_guid = t5.guid "
		"left join accounts as t7 on t7.parent_guid = t6.guid "
		"where t1.name = 'Root Account' "

		"order  by levl1,levl2,levl3,levl4,levl5,levl6; ");
	boost::scoped_ptr< sql::ResultSet > res(stmt->executeQuery(
		"select levl1,levl2,levl3,levl4,levl5,levl6 from acctreeguid"));

	// use the acctreeguid table levels to build the accounts tree

/*	boost::scoped_ptr< sql::ResultSet > res(stmt->executeQuery(
		"select acctreeguid.levl1, acctreeguid.levl2, acctreeguid.levl3, acctreeguid.levl4, acctreeguid.levl5, acctreeguid.levl6, transactions.post_date, transactions.description, splits.account_guid, splits.value_num / splits.value_denom from transactions "
		"INNER JOIN "
		"splits ON splits.tx_guid = transactions.guid "
		"INNER JOIN "
		"acctreeguid ON acctreeguid.guid1 = splits.account_guid or acctreeguid.guid2 = splits.account_guid or acctreeguid.guid3 = splits.account_guid or acctreeguid.guid4 = splits.account_guid or acctreeguid.guid5 = splits.account_guid "
		"order by levl1, levl2, levl3, levl4, levl5, post_date;"));
				//			boost::scoped_ptr< sql::ResultSet > res(stmt->executeQuery("SELECT id, label FROM test ORDER BY id ASC"));*/
	Write_to_output(_T("#\t Running 'SELECT name FROM accounts'\n"));

	/* Number of rows in the result set */
	Write_to_output(_T("#\t\t Number of rows\t"));

	str.Format(_T("res->rowsCount() = %d \n"), res->rowsCount());
	Write_to_output(str);
	/*			if (res->rowsCount() != EXAMPLE_NUM_TEST_ROWS) {
	msg.str("");
	msg << "Expecting " << EXAMPLE_NUM_TEST_ROWS << "rows, found " << res->rowsCount();
	throw runtime_error(msg.str());
	}
	*/

	/* Fetching data */
	row = 0;
	InitTree();
	FillRoot(_T("Accounts"), 0, 0);
	while (res->next()) {

//		str.Format(_T("Fetching row %d"), row);
//		Write_to_output(str);
//		cout << "#\t\t Fetching row " << row << "\t";
		/* You can use either numeric offsets... */
		//cout << "name = " << res->getString(1);

/*		dbstr = res->getString(1);
		//get str from databases
		atl = CA2W(dbstr.c_str(), CP_UTF8);
		str.Format(_T("name = %s"), atl);
		Write_to_output(str);
*/
		/* ... or column names for accessing results. The latter is recommended. */
		//cout << ", name = '" << res->getString("name") << "'" << endl;
		dbstr1 = res->getString("levl1");
//		dbstr = res->getString("name");
		//get str from databases
		atl1 = CA2W(dbstr1.c_str(), CP_UTF8);
		dbstr2 = res->getString("levl2");
		atl2 = CA2W(dbstr2.c_str(), CP_UTF8);
		dbstr3 = res->getString("levl3");
		atl3 = CA2W(dbstr3.c_str(), CP_UTF8);
		dbstr4 = res->getString("levl4");
		atl4 = CA2W(dbstr4.c_str(), CP_UTF8);
		dbstr5 = res->getString("levl5");
		atl5 = CA2W(dbstr5.c_str(), CP_UTF8);
		if (atl3 == L"")
		str.Format(_T("%s_%s"), atl1, atl2);
		else if (atl4 == L"")
		str.Format(_T("%s_%s_%s"), atl1, atl2, atl3);
		else if (atl5 == L"")
		str.Format(_T("%s_%s_%s_%s"), atl1, atl2, atl3, atl4);
		else 
		str.Format(_T("%s_%s_%s_%s_%s"), atl1, atl2, atl3, atl4, atl5);

			Write_to_output(str);
			AddToTree();

		row++;
	}
	ExpandTree();
	str.Format(_T("Accounts processed = %d \n"), row);
	Write_to_output(str);

}

catch (sql::SQLException &e) {
	/*
	The MySQL Connector/C++ throws three different exceptions:

	- sql::MethodNotImplementedException (derived from sql::SQLException)
	- sql::InvalidArgumentException (derived from sql::SQLException)
	- sql::SQLException (derived from std::runtime_error)
	*/
	Write_to_output(_T("# ERR: SQLException in "));
//	cout << "# ERR: " << e.what();
	atl = CA2W(e.what(), CP_UTF8);

	str.Format(_T("name = %s"), atl);
	Write_to_output(str);

//	cout << " (MySQL error code: " << e.getErrorCode();
//	cout << ", SQLState: " << e.getSQLState() << " )" << endl;


#if 0
	cout << "# ERR: SQLException in " << __FILE__;
	cout << "(" << EXAMPLE_FUNCTION << ") on line " << __LINE__ << endl;
	/* Use what() (derived from std::runtime_error) to fetch the error message */
	cout << "# ERR: " << e.what();
	cout << " (MySQL error code: " << e.getErrorCode();
	cout << ", SQLState: " << e.getSQLState() << " )" << endl;
	cout << "not ok 1 - examples/connect.php" << endl;
#endif
}




}

CgnutreemfcDoc::~CgnutreemfcDoc()
{
}

BOOL CgnutreemfcDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	// just send a message to show this is called
	Write_to_output(_T("Ed output from DOC class"));

	return TRUE;
}

void CgnutreemfcDoc::Write_to_output(LPCTSTR lpszItem)
{
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();

	(pMainFrame->m_wndOutput).WriteBuildWindow(lpszItem);
	return;
}
void CgnutreemfcDoc::InitTree()
{
	// Init atl1.....atl6 account names as Empty and handles hatl1.....hatl6 as null
	// Init catl1..........catl6 current account names as Empty
	atl1.Empty(), atl2.Empty(), atl3.Empty(), atl4.Empty(), atl5.Empty(), atl6.Empty();
	catl1.Empty(), catl2.Empty(), catl3.Empty(), catl4.Empty(), catl5.Empty(), catl6.Empty();
	hl1 = NULL, hl2 = NULL, hl3 = NULL, hl4 = NULL, hl5 = NULL, hl6 = NULL;
}

void CgnutreemfcDoc::FillRoot(LPCTSTR level, int nImage, int nSelectedImage)
{
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();

	// insert level0
	hRoot = (pMainFrame->m_wndFileView).m_wndFileView.GetTreeCtrl().InsertItem(level, nImage, nSelectedImage); //, TVI_ROOT, TVI_SORT???
	(pMainFrame->m_wndFileView).m_wndFileView.GetTreeCtrl().SetItemState(hRoot, TVIS_BOLD, TVIS_BOLD);
}

void CgnutreemfcDoc::ExpandTree()
{
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	(pMainFrame->m_wndFileView).m_wndFileView.GetTreeCtrl().Expand(hRoot, TVE_EXPAND);
}



	void CgnutreemfcDoc::AddToTree()
{
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	// AddToTree()
//level1:
	// level1	If atl1 is null      all levels done, reset catl1, return
	if (atl1.IsEmpty())
	{
		catl1.Empty();
		return;
	}
	// If atl1 != catl, new level1, so insert in hroot and save hatl1 and catl1
	if (atl1 != catl1)
	{
	hl1 = (pMainFrame->m_wndFileView).m_wndFileView.GetTreeCtrl().InsertItem(atl1, 0, 0, hRoot);
	(pMainFrame->m_wndFileView).m_wndFileView.SetItemText(hRoot, 1, _T("atl1 Total"));
	catl1 =atl1;
	catl2.Empty(), catl3.Empty(), catl4.Empty(), catl5.Empty(), catl6.Empty();
	}
	//			goto level2
	//
//level2:
	// level2   If atl2 is null      all level 2 done, so reset catl2, return
	if (atl2.IsEmpty())
	{
		catl2.Empty();
		return;
	}
	//			If atl2 != cat2, new level2, so insert in hatl1 and save hatl2 and catl2
	if (atl2 != catl2)
	{
		hl2 = (pMainFrame->m_wndFileView).m_wndFileView.GetTreeCtrl().InsertItem(atl2, 0, 0, hl1);
		(pMainFrame->m_wndFileView).m_wndFileView.SetItemText(hl1, 1, _T("atl2 Total"));
		catl2 = atl2;
		catl3.Empty(), catl4.Empty(), catl5.Empty(), catl6.Empty();
	}
	//			goto level3
	//
//level3:
	// level3   If atl3 is null      all level 3 done, so reset catl3, return
	if (atl3.IsEmpty())
	{
		catl3.Empty();
		return;
	}
	//			If atl3 != cat3, new level3, so insert in hatl2 and save hatl3 and catl3
	if (atl3 != catl3)
	{
		hl3 = (pMainFrame->m_wndFileView).m_wndFileView.GetTreeCtrl().InsertItem(atl3, 0, 0, hl2);
		(pMainFrame->m_wndFileView).m_wndFileView.SetItemText(hl2, 1, _T("atl3 Total"));
		catl3 = atl3;
		catl4.Empty(), catl5.Empty(), catl6.Empty();
	}
	//			goto level4
	//
//level4:
	// level4   If atl4 is null      all level 4 done, so reset catl4, return
	if (atl4.IsEmpty())
	{
		catl4.Empty();
		return;
	}
	//			If atl4 != cat4, new level4, so insert in hatl3 and save hatl4 and catl4
	if (atl4 != catl4)
	{
		hl4 = (pMainFrame->m_wndFileView).m_wndFileView.GetTreeCtrl().InsertItem(atl4, 0, 0, hl3);
		(pMainFrame->m_wndFileView).m_wndFileView.SetItemText(hl3, 1, _T("atl4 Total"));
		catl4 = atl4;
		catl5.Empty(), catl6.Empty();
	}
	//			goto level5
	//
//level5:
	// level5   If atl5 is null      all level 5 done, so reset catl5, return
	if (atl5.IsEmpty())
	{
		catl5.Empty();
		return;
	}
	//			If atl5 != cat5, new level5, so insert in hatl4 and save hatl5 and catl5
	if (atl5 != catl5)
	{
		hl5 = (pMainFrame->m_wndFileView).m_wndFileView.GetTreeCtrl().InsertItem(atl5, 0, 0, hl4);
		catl5 = atl5;
		catl6.Empty();
	}
	//			goto level6
	//
//level6:
	// level6   If atl6 is null      all level 6 done, so reset catl6, return
	if (atl6.IsEmpty())
	{
		catl6.Empty();
		return;
	}
	//			If atl6 != cat6, new level6, so insert in hatl5 and save hatl6 and catl6
	if (atl6 != catl6)
	{
		hl6 = (pMainFrame->m_wndFileView).m_wndFileView.GetTreeCtrl().InsertItem(atl6, 0, 0, hl5);
		catl6 = atl6;
	}
	//			put out error message "too many levels" and return
	Write_to_output(_T("too many levels"));
	return;


}


//void HTREEITEM CgnutreemfcDoc::InsertItem(CStringW level, int, int, HTREEITEM hParent)
HTREEITEM CgnutreemfcDoc::InsertItem(LPCTSTR level, int, int, HTREEITEM hParent)
{
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();

	// insert level1
//	(pMainFrame->m_wndFileView).m_wndFileView.InsertItem
	HTREEITEM hEd = (pMainFrame->m_wndFileView).m_wndFileView.GetTreeCtrl().InsertItem(level, 0, 0);
	return hEd;

};

// CgnutreemfcDoc serialization

void CgnutreemfcDoc::Serialize(CArchive& ar)
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

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CgnutreemfcDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CgnutreemfcDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data. 
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CgnutreemfcDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CgnutreemfcDoc diagnostics

#ifdef _DEBUG
void CgnutreemfcDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CgnutreemfcDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CgnutreemfcDoc commands
