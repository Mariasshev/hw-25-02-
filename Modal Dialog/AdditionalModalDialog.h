#pragma once
#include "header.h"
const int numInputSign = 4;

class SignUpDlg
{
public:
	int inputIdsSignUp[numInputSign] = { IDC_EDIT1, IDC_EDIT3, IDC_EDIT4, IDC_EDIT5};
	HWND hEditSignUp[numInputSign] = { 0 };
	HWND hButtonSignUp;

	SignUpDlg(void);
	SignUpDlg(LPCTSTR);
	~SignUpDlg();
	bool isLoginExist(HWND hwnd, const _TCHAR* login);
	static INT_PTR CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp);
	static SignUpDlg* ptr;

	BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
	void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
	void Cls_OnClose(HWND hwnd);
};
