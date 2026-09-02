#include<Windows.h>
#include<stdio.h> //sprintf();
#include"resource.h"

CONST CHAR* g_sz_VALUES[] = { "This", "is", "my", "first", "List", "box" };

BOOL CALLBACK DlgProc(HWND, UINT uMsg, WPARAM wParam, LPARAM lParam);
//Dlgproc - это процедура окна, она обрабатывает любые действия пользователя.
//Процедура окна - это самая обычная функция, которая неявно вызывается при запуске окна.

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc, NULL);
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		HWND hListBox = GetDlgItem(hwnd, IDC_LIST1);
		for (int i = 0; i < sizeof(g_sz_VALUES) / sizeof(g_sz_VALUES[0]); i++)
			SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)g_sz_VALUES[i]);
	}
	break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDOK: 
		{
			HWND hListBox = GetDlgItem(hwnd, IDC_LIST1);
			INT i = SendMessage(hListBox, LB_GETCURSEL, 0, 0); // Get Current Selection
			CHAR sz_buffer[256] = {};
			SendMessage(hListBox, LB_GETTEXT, i, (WPARAM)sz_buffer);
			CHAR sz_message[256] = {};
			sprintf(sz_message, "Вы выбрали вариант №%i со значением '%s'.", i, sz_buffer);
			MessageBox(hwnd, sz_buffer, "Выбранный элемент", MB_OK | MB_ICONINFORMATION);
		}
			break;
		case IDCANCEL: EndDialog(hwnd, 0);
		}
	}
		break;
	case WM_CLOSE: EndDialog(hwnd, 0);
		break;
	}
	return FALSE;
}
