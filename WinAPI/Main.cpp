#include<Windows.h>

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	MessageBox
	(
		NULL, //Родительское окно.
		"Hello WinAPI!", //сообщение выводимое пользователю.
		"Hello", //Название окно.
		//Флаги, которые определяют значек, выводимый в окне, набор кнопок, и некоторый одполнительные параметры.
		MB_YESNOCANCEL | MB_HELP | MB_ICONQUESTION | MB_DEFBUTTON3 | MB_SYSTEMMODAL
	);
}