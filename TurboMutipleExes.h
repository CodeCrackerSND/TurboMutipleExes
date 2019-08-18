// TurboMutipleExes.h : main header file for the TURBOMUTIPLEEXES application
//

#if !defined(AFX_TURBOMUTIPLEEXES_H__BF8D17A1_A244_46A3_8B5D_8BF7AD9CDB66__INCLUDED_)
#define AFX_TURBOMUTIPLEEXES_H__BF8D17A1_A244_46A3_8B5D_8BF7AD9CDB66__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTurboMutipleExesApp:
// See TurboMutipleExes.cpp for the implementation of this class
//

class CTurboMutipleExesApp : public CWinApp
{
public:
	CTurboMutipleExesApp();


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTurboMutipleExesApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTurboMutipleExesApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TURBOMUTIPLEEXES_H__BF8D17A1_A244_46A3_8B5D_8BF7AD9CDB66__INCLUDED_)
