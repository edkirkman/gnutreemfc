#include "stdafx.h"
#include "MainFrm.h"

// file to output to the Build tab of the Output window
//extern CgnutreemfcApp theApp;

//class mainframe m_wndoutput
void WriteBuildWindow()
{

//	CWnd* m_pMainWnd;       // main window (usually same AfxGetApp()->m_pMainWnd)
	//m_pMainWnd = pMainFrame;
//	m_pMainWnd = AfxGetApp()->m_pMainWnd;


	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	COutputWnd   wndOutput =     pMainFrame->m_wndOutput;


	m_wndOutputBuild.AddString(_T("Build output is being displayed here."));
	m_wndOutputBuild.AddString(_T("The output is being displayed in rows of a list view"));
	m_wndOutputBuild.AddString(_T("but you can change the way it is displayed as you wish..."));
}
