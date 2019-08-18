// TurboMutipleExesDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TurboMutipleExes.h"
#include "TurboMutipleExesDlg.h"

#include <windows.h>   
#include <Winuser.h>
#include <string>
#include <shlobj.h>
#include <io.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define BIF_USENEWUI           0x0040   // Use the new dialog layout with the ability to resize.
#define INVALID_FILE_ATTRIBUTES ((DWORD)-1) 

// Copy source:
// https://github.com/poidasmith/winrun4j/blob/master/WinRun4J/src/common/Resource.cpp
// https://docs.microsoft.com/en-us/windows/win32/menurc/using-resources
// https://pastebin.com/zHbA2TFA
// http://www.cplusplus.com/forum/windows/118538/
// https://www.codeproject.com/Articles/8340/Using-UpdateResource-to-change-a-string-resource

/////////////////////////////////////////////////////////////////////////////
// CTurboMutipleExesDlg dialog

CTurboMutipleExesDlg::CTurboMutipleExesDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTurboMutipleExesDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTurboMutipleExesDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTurboMutipleExesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTurboMutipleExesDlg)
	DDX_Control(pDX, IDC_EDIT2, m_edit2);
	DDX_Control(pDX, IDC_LIST1, m_ctlListBox);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTurboMutipleExesDlg, CDialog)
	//{{AFX_MSG_MAP(CTurboMutipleExesDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON5, OnButton5)
	ON_BN_CLICKED(IDC_BUTTON6, OnButton6)
	ON_BN_CLICKED(IDC_BUTTON7, OnButton7)
	ON_BN_CLICKED(IDC_BUTTON8, OnButton8)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTurboMutipleExesDlg message handlers

BOOL CTurboMutipleExesDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTurboMutipleExesDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTurboMutipleExesDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

// szSSPath = path to .exe file - destination file
// istring1 = Turbo Studio virtual exe
// istring2 = argument to exe
// StringId = resource string table
BOOL AddStrings(LPCTSTR szSSPath, LPCTSTR istring1, LPCTSTR istring2, int StringId)
{
  HANDLE h = ::BeginUpdateResource(szSSPath,FALSE);
  if(!h)
  {
    // BeginUpdateResource failed
    return FALSE;
  }

  // First string convert to unicode:
  CString sNewString1 = istring1;
  int iCharCount1 = sNewString1.GetLength() + 1;
  LPWSTR pUnicodeString = new WCHAR[iCharCount1];
  if(!pUnicodeString)
  {
    // new failed
    return FALSE;
  }
  DWORD dwUnicodeCharCount1 = 
     MultiByteToWideChar(CP_ACP, NULL, sNewString1.GetBuffer(0), 
                               -1, pUnicodeString, iCharCount1);

  // Second string convert to unicode:
  CString sNewString2 = istring2;
  int iCharCount2 = sNewString2.GetLength() + 1;
  LPWSTR pUnicodeString2 = new WCHAR[iCharCount2];
  if(!pUnicodeString2)
  {
    // new failed
    return FALSE;
  }
  DWORD dwUnicodeCharCount2 = 
     MultiByteToWideChar(CP_ACP, NULL, sNewString2.GetBuffer(0), 
                               -1, pUnicodeString2, iCharCount2);


  HGLOBAL hGlob =
     GlobalAlloc(GHND, (dwUnicodeCharCount1 + 4) * sizeof(WCHAR)+
					   (dwUnicodeCharCount2 + 4) * sizeof(WCHAR)
	 
	 );


  if(!hGlob)
  {
    // GlobalAlloc failed
    delete pUnicodeString;
    delete pUnicodeString2;
    return FALSE;
  }
  LPWSTR pBufStart = (LPWSTR)GlobalLock(hGlob);
  if(!pBufStart)
  {
    // GlobalLock failed
    GlobalFree(hGlob);
    delete pUnicodeString;
    delete pUnicodeString2;
    return FALSE;
  }

  LPWSTR pBuf = pBufStart;
  pBuf++;
  // offset to make it string ID=1. Increment by more
  // to change to a different string ID

  // Copy First string to buffer
  // next 2 bytes is string length
  *(pBuf++) = (WCHAR)dwUnicodeCharCount1-1;
  for(int j=0; j<(int)dwUnicodeCharCount1-1; j++)
    // remaining bytes are string in wide chars (2 bytes each)
    *(pBuf++) = pUnicodeString[j];
  delete pUnicodeString;
  if(++dwUnicodeCharCount1 % 1)
    // make sure we write an even number
    dwUnicodeCharCount1++;


  // Copy Second string to buffer
  // next 2 bytes is string length
  *(pBuf++) = (WCHAR)dwUnicodeCharCount2-1;
  for(int i=0; i<(int)dwUnicodeCharCount2-1; i++)
    // remaining bytes are string in wide chars (2 bytes each)
    *(pBuf++) = pUnicodeString2[i];
  delete pUnicodeString2;
  if(++dwUnicodeCharCount2 % 1)
    // make sure we write an even number
    dwUnicodeCharCount2++;


  BOOL bSuccess = TRUE;
  if(!::UpdateResource(h, RT_STRING, MAKEINTRESOURCE(StringId), 
      MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US), 
      pBufStart, dwUnicodeCharCount1 * sizeof(WCHAR)+
	  dwUnicodeCharCount2 * sizeof(WCHAR) ) )
  {
    // UpdateResource failed
    bSuccess = FALSE;
  }

  GlobalUnlock(hGlob);
  GlobalFree(hGlob);
  ::EndUpdateResource(h, FALSE); // write changes 
  return bSuccess; 
}

int icons_count = 0;
LPCTSTR* icons_names;

int group_icon_count = 0;
LPCTSTR* group_icon_names;

int version_count = 0;
LPCTSTR* version_names;

BOOL ResNames(HMODULE hModule, LPCTSTR lpType, LPTSTR lpName, LONG lParam)
{
       if( lpType == RT_ICON)
	   {
		icons_names[icons_count] = lpName;
		icons_count++;
	   }

	   if( lpType == RT_GROUP_ICON)
	   {
		group_icon_names[group_icon_count] = lpName;
		group_icon_count++;
	   }

	   if( lpType == RT_VERSION)
	   {
		version_names[version_count] = lpName;
		version_count++;
	   }

	   
        return true;
}

void MyEnumerateResource(HMODULE hm)
{

	icons_count = 0;
	icons_names = new LPCTSTR[200];
	EnumResourceNames(hm, RT_ICON, (ENUMRESNAMEPROC)ResNames, 0);

	group_icon_count = 0;
	group_icon_names = new LPCTSTR[200];
	EnumResourceNames(hm, RT_GROUP_ICON, (ENUMRESNAMEPROC)ResNames, 0);

	version_count = 0;
	version_names = new LPCTSTR[200];
	EnumResourceNames(hm, RT_VERSION, (ENUMRESNAMEPROC)ResNames, 0);
	//

}


bool CTurboMutipleExesDlg::AddIcon(LPSTR exeFile, LPSTR iconFile)
{


	HMODULE hm = LoadLibraryEx(iconFile, NULL, LOAD_LIBRARY_AS_DATAFILE_EXCLUSIVE);
	if(!hm) {
		MessageBox("Could not load exe to add resources!", "Error!", MB_OK);
		return false;
	}

	// Enumerate resources
	MyEnumerateResource(hm);

HANDLE hUpdate = BeginUpdateResource(exeFile, TRUE);

/*
If you use BeginUpdateResource(path, true);
then UpdateResource will replace the existing resource,
but it will delete everything on the current resource not only
the "TYPE" you use in UpdateResource.

*/


	int i=0;
	for (i=0;i<icons_count;i++)
	{

HRSRC hRes = FindResource(hm, MAKEINTRESOURCE(icons_names[i]), RT_ICON);
if (hRes != NULL)  // resource id = 1 - start with 1
{

HGLOBAL hResLoad = LoadResource(hm, hRes);
LPVOID lpResLock = LockResource(hResLoad);
int result = UpdateResource(hUpdate,    // update resource handle
    RT_ICON,                         // change icon resource
    MAKEINTRESOURCE(icons_names[i]),         // icon id
    MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL),  // neutral language
    lpResLock,                         // ptr to resource info
    SizeofResource(hm, hRes));       // size of resource info

FreeResource(hResLoad);  // free resource

}

	}

	for (i=0;i<group_icon_count;i++)
	{

HRSRC hRes = FindResource(hm, MAKEINTRESOURCE(group_icon_names[i]), RT_GROUP_ICON);
if (hRes != NULL)  // resource id = 1 - start with 1
{

HGLOBAL hResLoad = LoadResource(hm, hRes);
LPVOID lpResLock = LockResource(hResLoad);
int result = UpdateResource(hUpdate,    // update resource handle
    RT_GROUP_ICON,                         // change icon resource
    MAKEINTRESOURCE(group_icon_names[i]),         // icon id
    MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL),  // neutral language
    lpResLock,                         // ptr to resource info
    SizeofResource(hm, hRes));       // size of resource info

FreeResource(hResLoad);  // free resource

}

	}


	
	for (i=0;i<version_count;i++)
	{

HRSRC hRes = FindResource(hm, MAKEINTRESOURCE(version_names[i]), RT_VERSION);
if (hRes != NULL)  // resource id = 1 - start with 1
{

HGLOBAL hResLoad = LoadResource(hm, hRes);
LPVOID lpResLock = LockResource(hResLoad);
int result = UpdateResource(hUpdate,    // update resource handle
    RT_VERSION,                         // change icon resource
    MAKEINTRESOURCE(version_names[i]),         // icon id
    MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL),  // neutral language
    lpResLock,                         // ptr to resource info
    SizeofResource(hm, hRes));       // size of resource info

FreeResource(hResLoad);  // free resource

}

	}



// Commit the changes
	EndUpdateResource(hUpdate, FALSE);

	FreeLibrary(hm);
	return true;


}


void WriteResourceData(int res_id, char* filename)
{

char* data = NULL;
HINSTANCE hInst = GetModuleHandle(NULL);  // get exe in memory
HRSRC hRes = FindResource(hInst, MAKEINTRESOURCE(res_id), MAKEINTRESOURCE(10)); // 10 = RT_RCDATA
if (NULL != hRes)
{
    HGLOBAL hData = LoadResource(hInst, hRes);
    if (hData)
    {
        DWORD dataSize = SizeofResource(hInst, hRes);
        data = (char*)LockResource(hData);
		FreeResource(hData);  // free resource


	// Finnaly write resource data to file:
    FILE* pFile = fopen(filename, "wb");
    fwrite(data, 1, dataSize, pFile);  // 1 = size in bytes of each element
    fclose(pFile);


    }
    else
    {
		MessageBox(0, "hData is null", "Error!", MB_OK);
    }

}
else
	MessageBox(0, "hRes is null", "Error!", MB_OK);
}

void CTurboMutipleExesDlg::OnButton2() 
{
	// TODO: Add your control notification handler code here

	CWnd *pWnd = GetDlgItem(IDC_EDIT1);
	char* txt = new char[400];
	::GetWindowText(pWnd->m_hWnd, txt, 400);  // get window text

	if (strlen(txt)>0)
	m_ctlListBox.AddString(txt); // add string to listbox

}



void CTurboMutipleExesDlg::OnButton3() 
{
	// TODO: Add your control notification handler code here
	m_ctlListBox.ResetContent();  // remove items

}


void AppendTextToEditCtrl(CEdit& edit, LPCTSTR pszText)
{
   // get the initial text length
   int nLength = edit.GetWindowTextLength();
   // put the selection at the end of text
   edit.SetSel(nLength, nLength);
   // replace the selection
   edit.ReplaceSel(pszText);
}

void AppendLineToMultilineEditCtrl(CEdit& edit, LPCTSTR pszText)
{
   CString strLine;
   // add CR/LF to text
   strLine.Format(_T("%s\r\n"), pszText);
   AppendTextToEditCtrl(edit, strLine);
}

CString GetShortFileName(CString input)
{
		CString str;
		char * pch = strrchr(input,'\\');
		if (pch!=NULL&&strlen(pch)>0)
		{
		str = CString(pch);
		str.Delete(0, 1);  // remove first char (\)
		}
		else
		{
		str = input;
		}

		return str;

}

void CTurboMutipleExesDlg::OnButton4() 
{
	// TODO: Add your control notification handler code here
	CWnd *pWnd = GetDlgItem(IDC_EDIT2);
	CString strText;
	m_edit2.SetWindowText("");  // remove existing text

	for (int i = 0; i < m_ctlListBox.GetCount(); i++)
    {
		m_ctlListBox.GetText(i,strText);
		if (!strText.IsEmpty()&&strText.GetLength()>0)
		{
		CString shortName = GetShortFileName(strText);
		AppendLineToMultilineEditCtrl(m_edit2, shortName);

		}

    }

}

void CTurboMutipleExesDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
static char szFilter[] = "Executable Files (*.exe)|*.exe";   
CFileDialog FileDlg(TRUE, ".exe", NULL, 0, szFilter);
if( FileDlg.DoModal() == IDOK )
{
   CString strFile = FileDlg.GetPathName();
   CWnd *pWnd = GetDlgItem(IDC_EDIT1);
   pWnd->SetWindowText(strFile);

}
}

void CTurboMutipleExesDlg::OnButton5() 
{
	// TODO: Add your control notification handler code here
static char szFilter[] = "All Files (*.*)|*.*";   
CFileDialog FileDlg(TRUE, ".*", NULL, 0, szFilter);
if( FileDlg.DoModal() == IDOK )
{
   CString strFile = FileDlg.GetFileName();
   CWnd *pWnd = GetDlgItem(IDC_EDIT3);
   pWnd->SetWindowText(strFile);

}
}

void CTurboMutipleExesDlg::OnButton6() 
{
	// TODO: Add your control notification handler code here
	
static char szFilter[] = "Executable Files (*.exe)|*.exe";   
CFileDialog FileDlg(TRUE, ".exe", NULL, 0, szFilter);
if( FileDlg.DoModal() == IDOK )
{
   CString strFile = FileDlg.GetPathName();
   CWnd *pWnd = GetDlgItem(IDC_EDIT4);
   pWnd->SetWindowText(strFile);

}

}

bool GetFolder(std::string& folderpath, 
               const char* szCaption = NULL, 
               HWND hOwner = NULL)
{
   bool retVal = false;

   // The BROWSEINFO struct tells the shell 
   // how it should display the dialog.
   BROWSEINFO bi;
   memset(&bi, 0, sizeof(bi));

   bi.ulFlags   = BIF_USENEWUI;
   bi.hwndOwner = hOwner;
   bi.lpszTitle = szCaption;

   // must call this if using BIF_USENEWUI
   ::OleInitialize(NULL);

   // Show the dialog and get the itemIDList for the 
   // selected folder.
   LPITEMIDLIST pIDL = ::SHBrowseForFolder(&bi);

   if(pIDL != NULL)
   {
      // Create a buffer to store the path, then 
      // get the path.
      char buffer[900] = {'\0'};
      if(::SHGetPathFromIDList(pIDL, buffer) != 0)
      {
         // Set the string value.
         folderpath = buffer;
         retVal = true;
      }

      // free the item id list
      CoTaskMemFree(pIDL);
   }

   ::OleUninitialize();

   return retVal;
}

BOOL DirectoryExists(LPCTSTR szPath)
{
  DWORD dwAttrib = GetFileAttributes(szPath);

  return (dwAttrib != INVALID_FILE_ATTRIBUTES && 
         (dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}

BOOL DirectoryExists(std::string szPath)
{

  DWORD dwAttrib = GetFileAttributes(szPath.c_str());

  return (dwAttrib != INVALID_FILE_ATTRIBUTES && 
         (dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}

bool FileExists( CString Filename )
{
    return access( Filename.GetBuffer(0), 0 ) == 0;
}

void CTurboMutipleExesDlg::OnButton7() 
{
	// TODO: Add your control notification handler code here
	std::string szPath("");
	if (GetFolder(szPath, "Select dest folder") == true) 
	{
	CString OutPath = szPath.c_str();
    CWnd *pWnd = GetDlgItem(IDC_EDIT5);
    pWnd->SetWindowText(OutPath);
	}
}


// when you choose to create exe:
void CTurboMutipleExesDlg::OnOK() 
{
	// TODO: Add extra validation here

	std::string szPath("");
	CWnd *status = GetDlgItem(IDC_STATUS);

	CWnd *pWnd = GetDlgItem(IDC_EDIT5);
	char* txt = new char[900];
	::GetWindowText(pWnd->m_hWnd, txt, 900);  // get window text

	bool ShouldSelectFolder = false;

	CWnd *pWndStartupExe = GetDlgItem(IDC_EDIT3);
	char* StartupExetxt = new char[900];
	::GetWindowText(pWndStartupExe->m_hWnd, StartupExetxt, 900);  // get window text

	if (StartupExetxt==NULL||strlen(StartupExetxt)<=0)
	{
	status->SetWindowText("StartupExe is mandatory!");
	return;
	}

	CWnd *NewEntryPointResources = GetDlgItem(IDC_EDIT4);
	char* NewEntryPointRestxt = new char[900];
	::GetWindowText(NewEntryPointResources->m_hWnd, NewEntryPointRestxt, 900); // get window text


	if (txt!=NULL&&strlen(txt)>0)
	{
	szPath = std::string(txt);
	ShouldSelectFolder = !DirectoryExists(txt);
	}
	else
	ShouldSelectFolder = true;

	if (ShouldSelectFolder&&GetFolder(szPath, "Select dest folder") == true) 
	szPath = szPath.c_str();

	if (DirectoryExists(szPath))  // only if output directory exist:
	{

	CStringArray EntriesToStart;
	EntriesToStart.SetSize(20);
	int EntriesCount = 0;

	pWnd = GetDlgItem(IDC_EDIT2);
	::GetWindowText(pWnd->m_hWnd, txt, 900);  // get window text

	if ((txt==NULL||strlen(txt)<=0)&&m_ctlListBox.GetCount()==0)
	{
	status->SetWindowText("No entry point specified!");
	return;
	}

	if (txt!=NULL&&strlen(txt)>0)
	{
	char * pch = strtok (txt,"\r\n");

	 while (pch != NULL)
	 {
		if (pch != NULL && strlen(pch)>0)
		{
		EntriesToStart[EntriesCount] = CString(pch);

	if (m_ctlListBox.GetCount()<=0)  // if there isn't any full name entered
	{
		CString OutFileName = CString(szPath.c_str())+"\\"+EntriesToStart[EntriesCount];
		WriteResourceData(300, OutFileName.GetBuffer(0));  // write exe
		AddStrings(OutFileName.GetBuffer(0), StartupExetxt, EntriesToStart[EntriesCount], 626);
		// we can't copy old resources - there is no file source
	}

		EntriesCount++;
		}

        pch = strtok (NULL, "\r\n");
	 }
	}

	// Copy entry points resources to files
	for (int i = 0; i < m_ctlListBox.GetCount(); i++)
    {
		m_ctlListBox.GetText(i,txt);
		if (txt!=NULL && strlen(txt)>0)
		{
		CString shortName = GetShortFileName(txt);
		if (!EntriesToStart[i].IsEmpty()&&EntriesToStart[i].GetLength()==0)
		shortName = EntriesToStart[i];

		CString OutFileName = CString(szPath.c_str())+"\\"+shortName;
		WriteResourceData(300, OutFileName.GetBuffer(0));  // write exe
		AddIcon(OutFileName.GetBuffer(0), txt);  // copy resources

		AddStrings(OutFileName.GetBuffer(0), StartupExetxt, shortName, 626);
		

		}

    }



	CString NewEntryPointOutFileName = CString(szPath.c_str())+"\\"+"NewEntryPoint.exe";
	WriteResourceData(301, NewEntryPointOutFileName.GetBuffer(0));  // write exe
	if (FileExists(NewEntryPointRestxt))
	AddIcon(NewEntryPointOutFileName.GetBuffer(0), 	NewEntryPointRestxt);  // copy resources


	status->SetWindowText("Done!");
	}
	else
	{
	status->SetWindowText("Output directory doesn't exist!");
	}

}


void CTurboMutipleExesDlg::OnButton8() 
{
	// TODO: Add your control notification handler code here
	int selected_index = m_ctlListBox.GetCurSel();
	if (selected_index>=0)
	m_ctlListBox.DeleteString(selected_index);

}
