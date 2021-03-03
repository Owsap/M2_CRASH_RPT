/// 1.
// Search
extern bool SetDefaultCodePage(DWORD codePage);

// Add above
#if defined(ENABLE_CRASH_RPT)
#	include <crashrpt/CrashRpt.h>
#	pragma comment(lib, "CrashRpt.lib")
#
// Define the crash callback
int CALLBACK CrashCallback(CR_CRASH_CALLBACK_INFO* pInfo)
{
	// Do something...

	// Proceed with crash report generation. 
	// This return code also makes CrashRpt to not call this callback function for 
	// the next crash report generation stage.
	return CR_CB_DODEFAULT;
}

void CrashRptUnregister()
{
	// Uninitialize CrashRpt before exiting the main function
	crUninstall();
}

void CrashRptInit()
{
	// Define CrashRpt configuration parameters
	CR_INSTALL_INFO info;
	memset(&info, 0, sizeof(CR_INSTALL_INFO));
	info.cb = sizeof(CR_INSTALL_INFO);
	info.pszAppName = ApplicationStringTable_GetStringz(IDS_APP_NAME, "APP_NAME");
	info.pszAppVersion = VER_FILE_VERSION_STR;
	info.pszEmailSubject = CRASH_RPT_EMAIL_SUBJECT;
	info.pszEmailTo = CRASH_RPT_EMAIL_TO;
	info.pszUrl = CRASH_RPT_URL;
	info.uPriorities[CR_HTTP] = 3; // First try send report over HTTP
	info.uPriorities[CR_SMTP] = 2; // Second try send report over SMTP
	info.uPriorities[CR_SMAPI] = 1; // Third try send report over Simple MAPI
	// Install all available exception handlers
	info.dwFlags |= CR_INST_ALL_POSSIBLE_HANDLERS;
	// Restart the app on crash
	info.dwFlags |= CR_INST_APP_RESTART;
	info.dwFlags |= CR_INST_SEND_QUEUED_REPORTS;
	info.pszRestartCmdLine = "/restart";
	// Define the Privacy Policy URL
	//info.pszPrivacyPolicyURL = CRASH_RPT_POLICY_URL;

	// Install crash reporting
	int nResult = crInstall(&info);
	if (nResult != 0)
	{
		// Something goes wrong. Get error message.
		char szErrorMsg[512] = "";
		crGetLastErrorMsg(szErrorMsg, 512);
		TraceError("%s\n", szErrorMsg);
	}

	// Set crash callback function
	crSetCrashCallback(CrashCallback, NULL);
	// Add our log file to the error report

	char szLogFile[256];
	::GetCurrentDirectory(sizeof(szLogFile), szLogFile);
	if (szLogFile[lstrlen(szLogFile) - 1] != '\\')
		strcat(szLogFile, "\\");
	strcat(szLogFile, GetLogFileDate());

	crAddFile2(szLogFile, NULL, "Log File", CR_AF_MAKE_FILE_COPY);

	// We want the screenshot of the entire desktop is to be added on crash
	crAddScreenshot2(CR_AS_VIRTUAL_SCREEN, CR_AV_QUALITY_LOW);
}
#endif

/// 2.
// Search
	DWORD dwRandSeed = time(NULL) + DWORD(GetCurrentProcess());

// Add above
#if defined(ENABLE_CRASH_RPT)
	CrashRptInit();
#endif
