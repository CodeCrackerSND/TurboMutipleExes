// TurboMutipleExesDlg.h : header file
//
#include "ResourceStr.h"

#if !defined(AFX_TURBOMUTIPLEEXESDLG_H__D13B20A6_CB96_4BEB_B70D_B7AAFCDAFAEA__INCLUDED_)
#define AFX_TURBOMUTIPLEEXESDLG_H__D13B20A6_CB96_4BEB_B70D_B7AAFCDAFAEA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTurboMutipleExesDlg dialog

class CTurboMutipleExesDlg : public CDialog
{
// Construction
public:
	CTurboMutipleExesDlg(CWnd* pParent = NULL);	// standard constructor
	bool AddIcon(LPSTR exeFile, LPSTR iconFile);
// Dialog Data
	//{{AFX_DATA(CTurboMutipleExesDlg)
	enum { IDD = IDD_TURBOMUTIPLEEXES_DIALOG };
	CEdit	m_edit2;
	CListBox	m_ctlListBox;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTurboMutipleExesDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTurboMutipleExesDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	afx_msg void OnButton4();
	afx_msg void OnButton1();
	afx_msg void OnButton5();
	afx_msg void OnButton6();
	virtual void OnOK();
	afx_msg void OnButton7();
	afx_msg void OnButton8();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TURBOMUTIPLEEXESDLG_H__D13B20A6_CB96_4BEB_B70D_B7AAFCDAFAEA__INCLUDED_)
