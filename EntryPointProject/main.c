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
#include <unistd.h> // for access

/** Prototypes **************************************************************/
static LRESULT WINAPI MainWndProc(HWND, UINT, WPARAM, LPARAM);

/****************************************************************************
 *                                                                          *
 * Function: WinMain                                                        *
 *                                                                          *
 * Purpose : main function of program - first started method                *
 *                                                                          *
 * History : Date      Reason                                               *
 *           00/00/00  Created                                              *
 *                                                                          *
 ****************************************************************************/

char turbo_virtualized_exe[200];
char exe_To_start[200];

int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
LoadString(hInstance, 10001, turbo_virtualized_exe, 200);  // exe to shell execute
LoadString(hInstance, 10002, exe_To_start, 200); // command line parameter of turbo_virtualised_exe

int AnyError = 0;
int string_len = strlen(turbo_virtualized_exe);
if (string_len<=0)
{
MessageBox(NULL, "Turbo virtualized exe can't be empty!", "Error!",MB_OK);
AnyError = 1;
}

int result = access(turbo_virtualized_exe, F_OK); // F_OK tests existence also (R_OK,W_OK,X_OK).
                                  // for readable, writeable, executable
      
if ((AnyError==0)&&(result!=0))
{
MessageBox(NULL, "Turbo virtualized exe don't exist!", "Error!",MB_OK);
AnyError = 1;
}


string_len = strlen(exe_To_start);
if (string_len<=0)
{
MessageBox(NULL, "Command line parameter can't be empty!", "Error!",MB_OK);
AnyError = 1;
}

if (AnyError==0)  // if there isn't any error
ShellExecute(NULL, "open", turbo_virtualized_exe, exe_To_start, NULL, SW_SHOWNORMAL);

return 1;
}


