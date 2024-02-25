#include "AdditionalModalDialog.h"

CAdditionalModalDialog* CAdditionalModalDialog::ptr = NULL;

CAdditionalModalDialog::CAdditionalModalDialog(void)
{
	ptr = this;
}

CAdditionalModalDialog::CAdditionalModalDialog(LPCTSTR lpStr)
{
	ptr = this;
	_tcscpy(text, lpStr);
}

CAdditionalModalDialog::~CAdditionalModalDialog(void)
{

}

void CAdditionalModalDialog::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, IDCANCEL);
}

BOOL CAdditionalModalDialog::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam) 
{
	hEdit = GetDlgItem(hwnd, IDC_EDIT1);
	hEdit3 = GetDlgItem(hwnd, IDC_EDIT3);
	hEdit4 = GetDlgItem(hwnd, IDC_EDIT4);
	hEdit5 = GetDlgItem(hwnd, IDC_EDIT5);
	hStatic = GetDlgItem(hwnd, IDC_STATIC1);
	SetWindowText(hStatic, text);
	SetWindowText(hwnd, TEXT("Регистрация"));
	SetWindowText(hEdit, TEXT("Введите свой логин"));
	return TRUE;
}


void CAdditionalModalDialog::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	if(id == IDOK)
	{
		TCHAR buffer[200];
		GetWindowText(hEdit, buffer, 200);
		_tcscpy(text, buffer);
		HWND hParent = GetParent(hwnd);
		SetWindowText(hParent, TEXT("Ïðèâåò îò äî÷åðíåãî îêíà!"));
		EndDialog(hwnd, IDOK);

		LPCWSTR fileName = L"example.txt";

		// Открытие или создание файла для записи
		HANDLE hFile = CreateFile(
			fileName,             
			GENERIC_WRITE,        
			0,                    
			NULL,                 
			CREATE_ALWAYS,        
			FILE_ATTRIBUTE_NORMAL, 
			NULL                 
		);

		if (hFile == INVALID_HANDLE_VALUE) 
		{
			MessageBox(NULL, L"Не удалось создать файл", L"Ошибка", MB_OK | MB_ICONERROR);
			
		}


		TCHAR data[556];
		DWORD bytesWritten;

			GetWindowText(hEdit, data, 12);
			WriteFile(hFile, data, sizeof(data), &bytesWritten, NULL);

			GetWindowText(hEdit3, data, 12);
			WriteFile(hFile, data, sizeof(data), &bytesWritten, NULL);

			GetWindowText(hEdit4, data, 24);
			WriteFile(hFile, data, sizeof(data), &bytesWritten, NULL);

			GetWindowText(hEdit5, data, 12);
			WriteFile(hFile, data, sizeof(data), &bytesWritten, NULL);
		

		// Закрытие файла
		CloseHandle(hFile);

		MessageBox(NULL, L"Файл успешно создан", L"Информация", MB_OK | MB_ICONINFORMATION);
	}
	else if(id == IDCANCEL)
	{
		EndDialog(hwnd, IDCANCEL);
	}
}

BOOL CALLBACK CAdditionalModalDialog::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
	}
	return FALSE;
}
