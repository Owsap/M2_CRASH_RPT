/// 1.
// Search
void OpenLogFile(bool bUseLogFIle)

// Add above
const char* GetLogFileDate()
{
	time_t llTime;
	struct tm* sTimeInfo;
	char szBuffer[80];
	time(&llTime);
	sTimeInfo = localtime(&llTime);
	strftime(szBuffer, sizeof(szBuffer), "syserr/%Y%m%d.txt", sTimeInfo);
	return szBuffer;
}

/// 2.
// Search
void OpenLogFile(bool bUseLogFIle)

// Replace entire function with
void OpenLogFile(bool bUseLogFIle)
{
	const char* c_szLogDir = "syserr";
	CreateDirectory(c_szLogDir, NULL);

	time_t llTime;
	struct tm* sTimeInfo;
	char szBuffer[80];
	time(&llTime);
	sTimeInfo = localtime(&llTime);

	strftime(szBuffer, sizeof(szBuffer), "./syserr/%Y%m%d.txt", sTimeInfo);
	const char* c_szPath(szBuffer);

#ifndef _DISTRIBUTE 
	auto aFile = freopen(c_szPath, "w", stderr);

	if (bUseLogFIle)
	{
		isLogFile = true;
		CLogFile::Instance().Initialize();
	}
#endif
}
