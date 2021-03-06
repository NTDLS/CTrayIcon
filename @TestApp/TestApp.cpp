#ifndef _TESTAPP_CPP
#define _TESTAPP_CPP
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Windows.H>
#include <Stdio.H>
#include <Stdlib.H>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "../CTrayIcon.H"

#include "Resource.H"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define ID_CANCEL      WM_USER + 1
#define ID_EXIT        WM_USER + 2

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void MyTrayIconProc(CTrayIcon *lpTI, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if(uMsg == WM_COMMAND)
    {
        if(LOWORD(wParam) == ID_EXIT)
        {
            DestroyWindow(hWnd);
        }
		else if(LOWORD(wParam) == ID_CANCEL)
        {
			//Do nothing.
        }
    }
    else if(uMsg == WM_SHELLNOTIFY)
    {
		if(lParam == WM_LBUTTONDBLCLK)
		{
			//Could do somthing here.
		}
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

DWORD WINAPI NewTrayIconThread(LPVOID lpVoid)
{
	CTrayIcon MyTray;

    HMENU hPopupMenu = CreateMenu();
    AppendMenu(hPopupMenu, MF_STRING, ID_CANCEL, "&Cancel");
    AppendMenu(hPopupMenu, MF_SEPARATOR, 0, "");
	AppendMenu(hPopupMenu, MF_STRING, ID_EXIT, "E&xit");

	MyTray.Create(IDI_MAIN, "My Test Tray Icon", hPopupMenu, &MyTrayIconProc);

	MyTray.Destroy();

	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(void)
{
	for(int iTI = 0; iTI < 5; iTI++)
	{
		CreateThread(NULL, NULL, NewTrayIconThread, NULL, 0, NULL);
	}

	system("Pause");

	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif

