/// 1.
// Add
#if !defined(_DEBUG)
#	define ENABLE_CRASH_RPT /// < Enable CrashRPT (Crash reports)
#	if defined(ENABLE_CRASH_RPT)
#		define CRASH_RPT_EMAIL_TO "owsap@mail.com" //!< E-mail address of crash reports recipient.
#		define CRASH_RPT_EMAIL_SUBJECT "Game Client Crash" //!< Subject of crash report e-mail.
#		define CRASH_RPT_URL "https://owsap-productions.com/crashrpt/crashrpt.php" //!< URL of server-side script (used in HTTP connection).
#	endif
#endif
