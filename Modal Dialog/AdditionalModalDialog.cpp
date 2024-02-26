
#include "AdditionalModalDialog.h"

SignUpDlg* SignUpDlg::ptr = NULL;

SignUpDlg::SignUpDlg(void) {
	ptr = this;
}
SignUpDlg::SignUpDlg(LPCTSTR lpStr) {
	ptr = this;
	//TEXTcscpy(text, lpStr);
}

SignUpDlg::~SignUpDlg() {
}

void SignUpDlg::Cls_OnClose(HWND hwnd) {
	EndDialog(hwnd, IDCANCEL);
}

BOOL SignUpDlg::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam) {
	for (int i = 0; i < numInputSign; i++) {
		hEditSignUp[i] = GetDlgItem(hwnd, inputIdsSignUp[i]);
	}

	hButtonSignUp = GetDlgItem(hwnd, IDOK);

	return TRUE;
}

void SignUpDlg::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify) {
	if (IDOK == id) {
		TCHAR buff[256] = TEXT("");
		int length = SendMessage(hEditSignUp[3], WM_GETTEXTLENGTH, 0, 0);
		GetWindowText(hEditSignUp[3], buff, length + 1);

		if (!isLoginExist(hwnd, buff)) {
			int index = MessageBox(hwnd, TEXT("Õîòèòå àâòîðèçîâàòüñÿ?"), TEXT("Òàêîé ëîãèí óæå åñòü!"), MB_YESNO);

			if (index == IDYES) {
				SignUpDlg dlg;
				INT_PTR result = DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG3), hwnd, SignUpDlg::DlgProc);
			}

			return;
		}

		ifstream out(TEXT("info.txt"));

		for (int i = 0; i < numInputSign; i++) {
			length = SendMessage(hEditSignUp[i], WM_GETTEXTLENGTH, 0, 0);

			if (length == 0) {
				MessageBox(hwnd, TEXT("Çàïîëíèòå âñå ïîëÿ!"), TEXT("Ïðåäóïðåæäåíèå!"), 0);
				break;
			}

			GetWindowText(hEditSignUp[i], buff, length + 1);

			i == 0 ? out << "[ " << buff << " | " :
				i != numInputSign - 1 ? out << buff << " | " :
				out << buff << " ]\n";
		}
	}
}

INT_PTR CALLBACK SignUpDlg::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
	}

	return FALSE;
}

bool SignUpDlg::isLoginExist(HWND hwnd, const TCHAR* login) {
	ifstream in("info.txt");

	const int max_size = 255;
	int counter = 0;

	wstring temp[4];
	wstring tempChar;
	int index = 0;

	TCHAR buff[max_size] = TEXT("");

	do {
		in >> buff[index];

		if (buff[index] == ']') {
			buff[index + 1] = '\0';

			for (int j = 0; j < wcslen(buff); j++) {
				if (buff[j] != ' ' && buff[j] != '[' && buff[j] != '|' && buff[j] != ']') {
					tempChar += buff[j];
				}
				else if (buff[j] == '|') {
					temp[counter++] = tempChar;
					tempChar = TEXT("");
				}
			}

			tempChar = TEXT("");
			counter = 0;
			index = 0;
		}
		else {
			index++;
		}

		if (wcscmp(login, temp[3].c_str()) == 0)
			return false;
	} while (in);

	return true;
}