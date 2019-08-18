/****************************************************************************
 *                                                                          *
 * File    : main.c                                                         *
 *                                                                          *
 * Purpose : Generic Win32 application.                                     *
 *                                                                          *
 * History : Date      Reason                                               *
 *           00/00/00  Created                                              *
 *                                                                          *
 ****************************************************************************/

#define WIN32_LEAN_AND_MEAN  /* speed up compilations */
#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <tchar.h>
#include "main.h"
#include "shellapi.h"

#define NELEMS(a)  (sizeof(a) / sizeof((a)[0]))

/** Prototypes **************************************************************/
static LRESULT WINAPI MainWndProc(HWND, UINT, WPARAM, LPARAM);

/****************************************************************************
 *                                                                          *
 * Function: WinMain                                                        *
 *                                                                          *
 * Purpose : Initialize the application.  Register a window class,          *
 *           create and display the main window and enter the               *
 *           message loop.                                                  *
 *                                                                          *
 * History : Date      Reason                                               *
 *           00/00/00  Created                                              *
 *                                                                          *
 ****************************************************************************/

int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
if (strlen(lpszCmdLine)<=0)
MessageBox(NULL, "Command line parameter can't be empty!", "Error!",MB_OK);
else
ShellExecute(NULL, "open", lpszCmdLine, NULL, NULL, SW_SHOWNORMAL);

    return 1;
}



