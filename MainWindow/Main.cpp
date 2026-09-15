#include<Windows.h>

CONST CHAR g_szMYWindowClass[] = "My Window Class";
INT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI  WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	//1) Регистрация класса окна:
	WNDCLASSEX wClass;
	ZeroMemory(&wClass, sizeof(wClass));
	wClass.style = NULL;
	wClass.cbSize = sizeof(wClass);
	wClass.cbClsExtra = 0;
	wClass.cbWndExtra = 0;

	//wClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	//wClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wClass.hIcon = (HICON)LoadImage
	(hInstance, "litecoin.ico", 
	IMAGE_ICON, LR_DEFAULTSIZE, 
	LR_DEFAULTSIZE, LR_LOADFROMFILE);
	wClass.hIconSm = (HICON)LoadImage
	(
		hInstance, "team_fortress.ico",
		IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE,
		LR_LOADFROMFILE
	);
	wClass.hCursor = (HCURSOR)LoadImage
	(
		hInstance, 
		"starcraft-original\\Working In Background.ani", 
		IMAGE_CURSOR, 32, 32,
		LR_LOADFROMFILE
	);
	//wClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	
	wClass.lpszClassName = g_szMYWindowClass;
	wClass.lpszMenuName = NULL;
	wClass.lpfnWndProc = (WNDPROC)WndProc;
	wClass.hInstance = hInstance;

	if (!RegisterClassEx(&wClass))
	{
		MessageBox(NULL, "Class registration failed", NULL, MB_OK | MB_ICONERROR);
		return 0;
	}

	//2) Создание окна:
	HWND hwnd = CreateWindowEx
	(
		NULL,				//exStyle
		g_szMYWindowClass,	//Class name
		g_szMYWindowClass,	//Window title
		WS_OVERLAPPEDWINDOW,//Window style
		200,150,	//Position
		1110,555,	//Window size
		NULL,	//Parent Window
		NULL,	//hMenu. Для главного окна сюда передаются RESOURCE_ID главного меню.
				//Для дочерного окна в hMenu передаются RESOURCE_ID создаваемого элемента главного окна,
				//По этому RESOURCE_ID мы сможем находить HWND нужного элемента при помощи функции GetDlgItem(hwnd, RESOURCE_ID);
				//Абсолютно любой RESOURCE_ID представляет собой целое число.
		hInstance,
		NULL
	);
	if (hwnd == NULL)
	{
		MessageBox(NULL, "Window creation failed", NULL, MB_OK | MB_ICONERROR);
		return 0;
	}
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	//3) Запуск цикла сообщений:
	MSG msg;

	while (GetMessage(&msg, 0, 0, NULL) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

INT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
	{

		HWND hStatic = CreateWindowEx
		(
			NULL,
			"Static",
			"Этот StaticText создан при помощи функций CreateWindow()",
			WS_CHILD | WS_VISIBLE,
			10, 10, 
			500,25,
			hwnd, 
			(HMENU)1000,
			GetModuleHandle(NULL), //hInstance
			NULL
		);

		HWND hEdit = CreateWindowEx
		(
			NULL,
			"Edit",
			"Этот текстовое поле создано при помощи функций CreateWindowEx()",
			WS_CHILD | WS_VISIBLE | WS_BORDER,
			//WS_ - Window Style 
			//ES_ - Edit Style
			10, 38,
			500, 22,
			hwnd,
			(HMENU)1001,
			GetModuleHandle(NULL),
			NULL
		);

		HWND hButton = CreateWindowEx
		(
			NULL,
			"Button",
			"Применить",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			//BS_ - Button Style
			400,67,
			100,32,
			hwnd,
			(HMENU)1002,	//Compatibility - Совместимость;
							//Compatible	-	Совместимый;
							//Incompatible  - Несовместимый;
			GetModuleHandle(NULL),
			NULL
		);
	}
	break;
	case WM_COMMAND:
	{
		CHAR sz_buffer[256] = {};
		switch (LOWORD(wParam))
		{
		case 1002:
		{
			CHAR sz_buffer[256] = {};
			HWND hStatic = GetDlgItem(hwnd, 1000);
			HWND hEdit = GetDlgItem(hwnd, 1001);
			SendMessage(hEdit, WM_GETTEXT, 256, (LPARAM)sz_buffer);
			SendMessage(hStatic, WM_SETTEXT, 0, (LPARAM)sz_buffer);
			SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)sz_buffer);
		}
			break;
		}
	}
		break;
	case WM_DESTROY:PostQuitMessage(0); break;
	case WM_CLOSE: DestroyWindow(hwnd); break;
	default: return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;
}