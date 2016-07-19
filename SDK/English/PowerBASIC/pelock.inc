'///////////////////////////////////////////////////////////////////////////////
'//
'// PELock header file
'//
'// Version        : PELock v2.0
'// Language       : PowerBASIC
'// Author         : Bartosz W�jcik (support@pelock.com)
'// Web page       : https://www.pelock.com
'//
'////////////////////////////////////////////////////////////////////////////////

#IF NOT %DEF(%PELOCK_INC)
%PELOCK_INC = 1

' it's not possible to redefine SIZEOF() operator in PowerBASIC instead
' PELOCK_SIZEOF macro is introduced and you can use it as an replacement
' for the SIZEOF() operator
%PELOCK_SIZEOF = 1
#IF %DEF(%PELOCK_SIZEOF)
MACRO PELOCK_SIZEOF(x) = PELOCK_DWORD(SIZEOF(x))
#ENDIF

' max. size of registered user name stored in the keyfile, including terminating null at the end
%PELOCK_MAX_USERNAME = 8193

' license key system API

' get registration key status information
MACRO GetKeyStatus() = GetWindowText( CDWD(-17), BYVAL %NULL, 256)

' return codes for GetKeyStatus()
%PELOCK_KEY_NOT_FOUND  = 0 ' key not found
%PELOCK_KEY_OK         = 1 ' key is valid
%PELOCK_KEY_INVALID    = 2 ' invalid key format
%PELOCK_KEY_STOLEN     = 3 ' key is stolen
%PELOCK_KEY_WRONG_HWID = 4 ' hardware id doesn't match
%PELOCK_KEY_EXPIRED    = 5 ' key is expired

' retrieve registration name from license key file
MACRO GetRegistrationName(szRegistrationName, nMaxCount) = GetWindowText( CDWD(-1), szRegistrationName, nMaxCount)

' get raw registration data (read username as a raw byte array)
MACRO GetRawRegistrationName(lpRegistrationRawName, nMaxCount) = GetWindowText( CDWD(-21), BYVAL VARPTR(lpRegistrationRawName), nMaxCount)

' set license key path (other than application's directory)
MACRO SetRegistrationKey(szRegistrationKeyPath) = GetWindowText( CDWD(-2), szRegistrationKeyPath, 0)

' set license data buffer
MACRO SetRegistrationData(lpBuffer, nSize) = GetWindowText( CDWD(-7), BYVAL STRPTR(lpBuffer), nSize)

' set license data from the text buffer (in MIME Base64 format)
MACRO SetRegistrationText(szRegistrationKey) = GetWindowText( CDWD(-22), szRegistrationKey, 0)

' disable current registration key, do not allow to set a new key again
MACRO DisableRegistrationKey(bPermamentLock) = GetWindowText( CDWD(-14), BYVAL %NULL, bPermamentLock)

' reload registration key from the default search locations
MACRO ReloadRegistrationKey = GetWindowText( CDWD(-16), BYVAL %NULL, 256)

' get user defined key data
MACRO GetKeyData(iValue) = GetWindowText( CDWD(-3), BYVAL %NULL, iValue)

' get user defined key features
MACRO IsFeatureEnabled(iIndex) = IIF( GetWindowText( CDWD(-6), BYVAL %NULL, iIndex) <> 0, %TRUE, %FALSE)

' get hardware id
MACRO GetHardwareId(szHardwareId, nMaxCount) = GetWindowText( CDWD(-4), szHardwareId, nMaxCount)

' set hardware id callback routine
MACRO SetHardwareIdCallback(lpHardwareIdFunc) = GetWindowText( CDWD(-20), BYVAL CODEPTR(lpHardwareIdFunc), 256)

' get key expiration date
MACRO GetKeyExpirationDate(lpSystemTime) = GetWindowText( CDWD(-5), BYVAL VARPTR(lpSystemTime), 256)

' get key creation date
MACRO GetKeyCreationDate(lpSystemTime) = GetWindowText( CDWD(-15), BYVAL VARPTR(lpSystemTime), 256)

' get key running time (since it was set)
MACRO GetKeyRunningTime(lpRunningTime) = GetWindowText( CDWD(-23), BYVAL VARPTR(lpRunningTime), 256)

' get key integers (from 1-16)
MACRO GetKeyInteger(iIndex) = CDWD( GetWindowText( CDWD(-8), BYVAL %NULL, iIndex) )

' return codes for time trial procedures
%PELOCK_TRIAL_ABSENT  = 0 ' time trial protection not used, or the application is already registered
%PELOCK_TRIAL_ACTIVE  = 1 ' trial period active
%PELOCK_TRIAL_EXPIRED = 2 ' trial period expired (returned when "Allow application to expire" option is used

' get trial days
MACRO GetTrialDays(dwTotalDays, dwLeftDays) = GetWindowText( CDWD(-10), BYVAL VARPTR(dwTotalDays), BYVAL VARPTR(dwLeftDays) )

' get trial executions
MACRO GetTrialExecutions(dwTotalExecutions, dwLeftExecutions) = GetWindowText( CDWD(-11), BYVAL VARPTR(dwTotalExecutions), BYVAL VARPTR(dwLeftExecutions) )

' get expiration date
MACRO GetExpirationDate(lpExpirationDate) = GetWindowText( CDWD(-12), BYVAL VARPTR(lpExpirationDate), 512 )

' get trial period
MACRO GetTrialPeriod(lpPeriodBegin, lpPeriodEnd) = GetWindowText( CDWD(-13), BYVAL VARPTR(lpPeriodBegin), BYVAL VARPTR(lpPeriodEnd) )

' encryption functions (stream cipher)
MACRO EncryptData(lpKey, dwKeyLen, lpBuffer, nSize) = DeferWindowPos( BYVAL STRPTR(lpKey), CDWD(-1), dwKeyLen, BYVAL STRPTR(lpBuffer), nSize, 1, 0, 0 )
MACRO DecryptData(lpKey, dwKeyLen, lpBuffer, nSize) = DeferWindowPos( BYVAL STRPTR(lpKey), CDWD(-1), dwKeyLen, BYVAL STRPTR(lpBuffer), nSize, 0, 0, 0 )

' encrypt memory with current session keys
MACRO EncryptMemory(lpBuffer, nSize) = DeferWindowPos( BYVAL %NULL, CDWD(-1), BYVAL %NULL, BYVAL STRPTR(lpBuffer), nSize, 1, 0, 0 )
MACRO DecryptMemory(lpBuffer, nSize) = DeferWindowPos( BYVAL %NULL, CDWD(-1), BYVAL %NULL, BYVAL STRPTR(lpBuffer), nSize, 0, 0, 0 )

' protections checks, don't change the params!
MACRO IsPELockPresent1 = IIF( GetAtomName(0, BYVAL %NULL, 256) <> 0, %TRUE, %FALSE)
MACRO IsPELockPresent2 = IIF( LockFile(%NULL, 128, 0, 512, 0) <> 0, %TRUE, %FALSE)
MACRO IsPELockPresent3 = IIF( MapViewOfFile(BYVAL %NULL, %FILE_MAP_COPY, 0, 0, 1024) <> %NULL, %TRUE, %FALSE)
MACRO IsPELockPresent4 = IIF( SetWindowRgn(BYVAL %NULL, BYVAL %NULL, %FALSE) <> 0, %TRUE, %FALSE)
MACRO IsPELockPresent5 = IIF( GetWindowRect(BYVAL %NULL, BYVAL %NULL) <> 0, %TRUE, %FALSE)
MACRO IsPELockPresent6 = IIF( GetFileAttributes(BYVAL %NULL) <> &HFFFFFFFF, %TRUE, %FALSE)
MACRO IsPELockPresent7 = IIF( GetFileTime(BYVAL %NULL, BYVAL %NULL, BYVAL %NULL, BYVAL %NULL) <> 0, %TRUE, %FALSE)
MACRO IsPELockPresent8 = IIF( SetEndOfFile(BYVAL %NULL), %TRUE, %FALSE)

' don't change this code (params)!
FUNCTION GetPELockDWORD SDECL(BYVAL dwValue AS DWORD, BYVAL dwRandomizer AS DWORD, BYVAL dwMagic1 AS DWORD, BYVAL dwMagic2 AS DWORD) AS DWORD

    DIM dwReturnValue AS DWORD
    DIM dwParams(3) AS DWORD
    DIM dwDecodedValue AS DWORD

    dwDecodedValue =  dwValue - dwRandomizer

    dwReturnValue = 0

    dwParams(0) = dwValue
    dwParams(1) = dwMagic1
    dwParams(2) = dwMagic2

    IF (GetWindowText( CDWD(-9), BYVAL VARPTR(dwReturnValue), BYVAL VARPTR(dwParams(0))) = 0) THEN dwReturnValue = dwDecodedValue

    FUNCTION = dwReturnValue

END FUNCTION

' PELock protected constants (don't change the params)
MACRO PELOCK_DWORD(dwValue) = GetPELockDWORD(dwValue, 0, &H11223344, &H44332211)

' encryption markers and other macros

MACRO SKIP_START = ! DB &HEB,&H06,&H8B,&HE4,&H8B,&HC0,&HEB,&HFC
MACRO SKIP_END   = ! DB &HEB,&H06,&H8B,&HC0,&H8B,&HE4,&HEB,&HFA

MACRO DEMO_START = ! DB &HEB,&H07,&HEB,&HFC,&HEB,&HFA,&HEB,&HFA,&HC7
MACRO DEMO_END
! DB &HEB,&H06,&HEB,&HFB,&HEB,&HFA,&HEB,&HFC,&HEB
! DB &H06,&HCD,&H20,&HEB,&HFD,&HCD,&H20,&HEB,&H07
! DB &HEB,&HFB,&HEB,&HFA,&HEB,&HFC,&HC8
END MACRO

MACRO DEMO_START_MT = ! DB &HEB,&H07,&HEB,&HFC,&HEB,&HFA,&HEB,&HFA,&HD7
MACRO DEMO_END_MT
! DB &HEB,&H06,&HEB,&HFB,&HEB,&HFA,&HEB,&HFC,&HEB
! DB &H06,&HCD,&H20,&HEB,&HFD,&HCD,&H20,&HEB,&H07
! DB &HEB,&HFB,&HEB,&HFA,&HEB,&HFC,&HD8
END MACRO

MACRO FEATURE_1_START  = ! DB &HEB,&H08,&HEB,&HFC,&HEB,&H00,&HFA,&HEB,&HFA,&HCA
MACRO FEATURE_2_START  = ! DB &HEB,&H08,&HEB,&HFC,&HEB,&H01,&HFA,&HEB,&HFA,&HCA
MACRO FEATURE_3_START  = ! DB &HEB,&H08,&HEB,&HFC,&HEB,&H02,&HFA,&HEB,&HFA,&HCA
MACRO FEATURE_4_START  = ! DB &HEB,&H08,&HEB,&HFC,&HEB,&H03,&HFA,&HEB,&HFA,&HCA
MACRO FEATURE_5_START  = ! DB &HEB,&H08,&HEB,&HFC,&HEB,&H04,&HFA,&HEB,&HFA,&HCA
MACRO FEATURE_6_START  = ! DB &HEB,&H08,&HEB,&HFC,&HEB,&H05,&HFA,&HEB,&HFA,&HCA
MACRO FEATURE_7_START  = ! DB &HEB,&H08,&HEB,&HFC,&HEB,&H06,&HFA,&HEB,&HFA,&HCA
MACRO FEATURE_8_START  = ! DB &HEB,&H08,&HEB,&HFC,&HEB,&H07,&HFA,&HEB,&HFA,&HCA
MACRO FEATURE_9_START  = ! DB &HEB,&H08,&HEB,&HFC,&HEB,&H08,&HFA,&HEB,&HFA,&HCA
MACRO FEATURE_10_START = ! DB &HEB,&H08,&HEB,&HFC,&HEB,&H09,&HFA,&HEB,&HFA,&HCA
MACRO FEATURE_11_START = ! DB &HEB,&H08,&HEB,&HFC,&HEB,&H0A,&HFA,&HEB,&HFA,&HCA
MACRO FEATURE_12_START = ! DB &HEB,&H08,&HEB,&HFC,&HEB,&H0B,&HFA,&HEB,&HFA,&HCA
MACRO FEATURE_13_START = ! DB &HEB,&H08,&HEB,&HFC,&HEB,&H0C,&HFA,&HEB,&HFA,&HCA
MACRO FEATURE_14_START = ! DB &HEB,&H08,&HEB,&HFC,&HEB,&H0D,&HFA,&HEB,&HFA,&HCA
MACRO FEATURE_15_START = ! DB &HEB,&H08,&HEB,&HFC,&HEB,&H0E,&HFA,&HEB,&HFA,&HCA
MACRO FEATURE_16_START = ! DB &HEB,&H08,&HEB,&HFC,&HEB,&H0F,&HFA,&HEB,&HFA,&HCA
MACRO FEATURE_17_START = ! DB &HEB,&H08,&HEB,&HFC,&HEB,&H10,&HFA,&HEB,&HFA,&HCA
MACRO FEATURE_18_START = ! DB &HEB,&H08,&HEB,&HFC,&HEB,&H11,&HFA,&HEB,&HFA,&HCA
MACRO FEATURE_19_START = ! DB &HEB,&H08,&HEB,&HFC,&HEB,&H12,&HFA,&HEB,&HFA,&HCA
MACRO FEATURE_20_START = ! DB &HEB,&H08,&HEB,&HFC,&HEB,&H13,&HFA,&HEB,&HFA,&HCA
MACRO FEATURE_21_START = ! DB &HEB,&H08,&HEB,&HFC,&HEB,&H14,&HFA,&HEB,&HFA,&HCA
MACRO FEATURE_22_START = ! DB &HEB,&H08,&HEB,&HFC,&HEB,&H15,&HFA,&HEB,&HFA,&HCA
MACRO FEATURE_23_START = ! DB &HEB,&H08,&HEB,&HFC,&HEB,&H16,&HFA,&HEB,&HFA,&HCA
MACRO FEATURE_24_START = ! DB &HEB,&H08,&HEB,&HFC,&HEB,&H17,&HFA,&HEB,&HFA,&HCA
MACRO FEATURE_25_START = ! DB &HEB,&H08,&HEB,&HFC,&HEB,&H18,&HFA,&HEB,&HFA,&HCA
MACRO FEATURE_26_START = ! DB &HEB,&H08,&HEB,&HFC,&HEB,&H19,&HFA,&HEB,&HFA,&HCA
MACRO FEATURE_27_START = ! DB &HEB,&H08,&HEB,&HFC,&HEB,&H1A,&HFA,&HEB,&HFA,&HCA
MACRO FEATURE_28_START = ! DB &HEB,&H08,&HEB,&HFC,&HEB,&H1B,&HFA,&HEB,&HFA,&HCA
MACRO FEATURE_29_START = ! DB &HEB,&H08,&HEB,&HFC,&HEB,&H1C,&HFA,&HEB,&HFA,&HCA
MACRO FEATURE_30_START = ! DB &HEB,&H08,&HEB,&HFC,&HEB,&H1D,&HFA,&HEB,&HFA,&HCA
MACRO FEATURE_31_START = ! DB &HEB,&H08,&HEB,&HFC,&HEB,&H1E,&HFA,&HEB,&HFA,&HCA
MACRO FEATURE_32_START = ! DB &HEB,&H08,&HEB,&HFC,&HEB,&H1F,&HFA,&HEB,&HFA,&HCA

MACRO FEATURE_END
! DB &HEB,&H06,&HEB,&HF1,&HEB,&HF2,&HEB,&HF3,&HEB
! DB &H06,&HCD,&H20,&HEB,&HFD,&HCD,&H20,&HEB,&H07
! DB &HEB,&HFB,&HEB,&HFA,&HEB,&HFC,&HCA
END MACRO

MACRO FEATURE_1_START_MT  = ! DB &HEB,&H08,&HEB,&HFC,&HEB,&H00,&HFA,&HEB,&HFA,&HDA
MACRO FEATURE_2_START_MT  = ! DB &HEB,&H08,&HEB,&HFC,&HEB,&H01,&HFA,&HEB,&HFA,&HDA
MACRO FEATURE_3_START_MT  = ! DB &HEB,&H08,&HEB,&HFC,&HEB,&H02,&HFA,&HEB,&HFA,&HDA
MACRO FEATURE_4_START_MT  = ! DB &HEB,&H08,&HEB,&HFC,&HEB,&H03,&HFA,&HEB,&HFA,&HDA
MACRO FEATURE_5_START_MT  = ! DB &HEB,&H08,&HEB,&HFC,&HEB,&H04,&HFA,&HEB,&HFA,&HDA
MACRO FEATURE_6_START_MT  = ! DB &HEB,&H08,&HEB,&HFC,&HEB,&H05,&HFA,&HEB,&HFA,&HDA
MACRO FEATURE_7_START_MT  = ! DB &HEB,&H08,&HEB,&HFC,&HEB,&H06,&HFA,&HEB,&HFA,&HDA
MACRO FEATURE_8_START_MT  = ! DB &HEB,&H08,&HEB,&HFC,&HEB,&H07,&HFA,&HEB,&HFA,&HDA
MACRO FEATURE_9_START_MT  = ! DB &HEB,&H08,&HEB,&HFC,&HEB,&H08,&HFA,&HEB,&HFA,&HDA
MACRO FEATURE_10_START_MT = ! DB &HEB,&H08,&HEB,&HFC,&HEB,&H09,&HFA,&HEB,&HFA,&HDA
MACRO FEATURE_11_START_MT = ! DB &HEB,&H08,&HEB,&HFC,&HEB,&H0A,&HFA,&HEB,&HFA,&HDA
MACRO FEATURE_12_START_MT = ! DB &HEB,&H08,&HEB,&HFC,&HEB,&H0B,&HFA,&HEB,&HFA,&HDA
MACRO FEATURE_13_START_MT = ! DB &HEB,&H08,&HEB,&HFC,&HEB,&H0C,&HFA,&HEB,&HFA,&HDA
MACRO FEATURE_14_START_MT = ! DB &HEB,&H08,&HEB,&HFC,&HEB,&H0D,&HFA,&HEB,&HFA,&HDA
MACRO FEATURE_15_START_MT = ! DB &HEB,&H08,&HEB,&HFC,&HEB,&H0E,&HFA,&HEB,&HFA,&HDA
MACRO FEATURE_16_START_MT = ! DB &HEB,&H08,&HEB,&HFC,&HEB,&H0F,&HFA,&HEB,&HFA,&HDA
MACRO FEATURE_17_START_MT = ! DB &HEB,&H08,&HEB,&HFC,&HEB,&H10,&HFA,&HEB,&HFA,&HDA
MACRO FEATURE_18_START_MT = ! DB &HEB,&H08,&HEB,&HFC,&HEB,&H11,&HFA,&HEB,&HFA,&HDA
MACRO FEATURE_19_START_MT = ! DB &HEB,&H08,&HEB,&HFC,&HEB,&H12,&HFA,&HEB,&HFA,&HDA
MACRO FEATURE_20_START_MT = ! DB &HEB,&H08,&HEB,&HFC,&HEB,&H13,&HFA,&HEB,&HFA,&HDA
MACRO FEATURE_21_START_MT = ! DB &HEB,&H08,&HEB,&HFC,&HEB,&H14,&HFA,&HEB,&HFA,&HDA
MACRO FEATURE_22_START_MT = ! DB &HEB,&H08,&HEB,&HFC,&HEB,&H15,&HFA,&HEB,&HFA,&HDA
MACRO FEATURE_23_START_MT = ! DB &HEB,&H08,&HEB,&HFC,&HEB,&H16,&HFA,&HEB,&HFA,&HDA
MACRO FEATURE_24_START_MT = ! DB &HEB,&H08,&HEB,&HFC,&HEB,&H17,&HFA,&HEB,&HFA,&HDA
MACRO FEATURE_25_START_MT = ! DB &HEB,&H08,&HEB,&HFC,&HEB,&H18,&HFA,&HEB,&HFA,&HDA
MACRO FEATURE_26_START_MT = ! DB &HEB,&H08,&HEB,&HFC,&HEB,&H19,&HFA,&HEB,&HFA,&HDA
MACRO FEATURE_27_START_MT = ! DB &HEB,&H08,&HEB,&HFC,&HEB,&H1A,&HFA,&HEB,&HFA,&HDA
MACRO FEATURE_28_START_MT = ! DB &HEB,&H08,&HEB,&HFC,&HEB,&H1B,&HFA,&HEB,&HFA,&HDA
MACRO FEATURE_29_START_MT = ! DB &HEB,&H08,&HEB,&HFC,&HEB,&H1C,&HFA,&HEB,&HFA,&HDA
MACRO FEATURE_30_START_MT = ! DB &HEB,&H08,&HEB,&HFC,&HEB,&H1D,&HFA,&HEB,&HFA,&HDA
MACRO FEATURE_31_START_MT = ! DB &HEB,&H08,&HEB,&HFC,&HEB,&H1E,&HFA,&HEB,&HFA,&HDA
MACRO FEATURE_32_START_MT = ! DB &HEB,&H08,&HEB,&HFC,&HEB,&H1F,&HFA,&HEB,&HFA,&HDA

MACRO FEATURE_END_MT
! DB &HEB,&H06,&HEB,&HF1,&HEB,&HF2,&HEB,&HF3,&HEB
! DB &H06,&HCD,&H20,&HEB,&HFD,&HCD,&H20,&HEB,&H07
! DB &HEB,&HFB,&HEB,&HFA,&HEB,&HFC,&HDA
END MACRO

MACRO UNREGISTERED_START = ! DB &HEB,&H07,&HEB,&H02,&HEB,&HFA,&HEB,&H01,&HCB

MACRO UNREGISTERED_END
! DB &HEB,&H06,&HEB,&H04,&HEB,&H02,&HEB,&H00,&HEB
! DB &H06,&HCD,&H22,&HEB,&HFC,&HCD,&H22,&HEB,&H07
! DB &HEB,&HFC,&HEB,&HFC,&HEB,&H01,&HCB
END MACRO

MACRO UNREGISTERED_START_MT = ! DB &HEB,&H07,&HEB,&H02,&HEB,&HFA,&HEB,&H01,&HDB

MACRO UNREGISTERED_END_MT
! DB &HEB,&H06,&HEB,&H04,&HEB,&H02,&HEB,&H00,&HEB
! DB &H06,&HCD,&H22,&HEB,&HFC,&HCD,&H22,&HEB,&H07
! DB &HEB,&HFC,&HEB,&HFC,&HEB,&H01,&HDB
END MACRO

MACRO CRYPT_START = ! DB &HEB,&H07,&HEB,&H05,&HEB,&H03,&HEB,&H01,&HC7
MACRO CRYPT_END
! DB &HEB,&H06,&HEB,&H00,&HEB,&H00,&HEB,&H00,&HEB
! DB &H06,&HCD,&H20,&HEB,&HFD,&HCD,&H20,&HEB,&H07
! DB &HEB,&H05,&HEB,&H03,&HEB,&H01,&HC8
END MACRO

MACRO CRYPT_START_MT = ! DB &HEB,&H07,&HEB,&H05,&HEB,&H03,&HEB,&H01,&HD7
MACRO CRYPT_END_MT
! DB &HEB,&H06,&HEB,&H00,&HEB,&H00,&HEB,&H00,&HEB
! DB &H06,&HCD,&H20,&HEB,&HFD,&HCD,&H20,&HEB,&H07
! DB &HEB,&H05,&HEB,&H03,&HEB,&H01,&HD8
END MACRO

MACRO CLEAR_START = ! DB &HEB,&H07,&HEB,&HFC,&HEB,&H00,&HEB,&H01,&HC9
MACRO CLEAR_END
! DB &HEB,&H06,&HEB,&H02,&HEB,&HFC,&HEB,&H00,&HEB
! DB &H06,&HCD,&H21,&HEB,&HFA,&HCD,&H21,&HEB,&H07
! DB &HEB,&HFC,&HEB,&HFC,&HEB,&H01,&HC9
END MACRO

MACRO CLEAR_START_MT = ! DB &HEB,&H07,&HEB,&HFC,&HEB,&H00,&HEB,&H01,&HD9
MACRO CLEAR_END_MT
! DB &HEB,&H06,&HEB,&H02,&HEB,&HFC,&HEB,&H00,&HEB
! DB &H06,&HCD,&H21,&HEB,&HFA,&HCD,&H21,&HEB,&H07
! DB &HEB,&HFC,&HEB,&HFC,&HEB,&H01,&HD9
END MACRO

MACRO FILE_CRYPT_START = ! DB &HEB,&H07,&HEB,&H02,&HEB,&HFC,&HEB,&H01,&HCA
MACRO FILE_CRYPT_END
! DB &HEB,&H06,&HEB,&HFC,&HEB,&HFC,&HEB,&H00,&HEB
! DB &H06,&HCD,&H20,&HEB,&HFD,&HCD,&H20,&HEB,&H07
! DB &HEB,&HFC,&HEB,&H03,&HEB,&HFC,&HCA
END MACRO

MACRO FILE_CRYPT_START_MT = ! DB &HEB,&H07,&HEB,&H02,&HEB,&HFC,&HEB,&H01,&HDA
MACRO FILE_CRYPT_END_MT
! DB &HEB,&H06,&HEB,&HFC,&HEB,&HFC,&HEB,&H00,&HEB
! DB &H06,&HCD,&H20,&HEB,&HFD,&HCD,&H20,&HEB,&H07
! DB &HEB,&HFC,&HEB,&H03,&HEB,&HFC,&HDA
END MACRO

MACRO UNPROTECTED_START = ! DB &HEB,&H06,&H8B,&HE4,&H89,&HED,&HEB,&HFC
MACRO UNPROTECTED_END   = ! DB &HEB,&H06,&H89,&HED,&H8B,&HE4,&HEB,&HFA

MACRO TRIAL_EXPIRED = ! DB &HEB,&H08,&H00,&H11,&H22,&H33,&H33,&H22,&H11,&H00

MACRO TRIAL_TOTAL_EXPIRED = ! DB &HEB,&H08,&H01,&H11,&H22,&H33,&H33,&H22,&H11,&H00

MACRO PELOCK_CHECKPOINT
! DB &HEB,&H7E,&H0D,&H0A,&H54,&H68,&H72,&H6F,&H75,&H67,&H68,&H20,&H74,&H68,&H65,&H20
! DB &H64,&H61,&H72,&H6B,&H20,&H6F,&H66,&H20,&H66,&H75,&H74,&H75,&H72,&H65,&H73,&H20
! DB &H70,&H61,&H73,&H74,&H21,&H0D,&H0A,&H54,&H68,&H65,&H20,&H6D,&H61,&H67,&H69,&H63
! DB &H69,&H61,&H6E,&H20,&H6C,&H6F,&H6E,&H67,&H73,&H20,&H74,&H6F,&H20,&H73,&H65,&H65
! DB &H21,&H0D,&H0A,&H4F,&H6E,&H65,&H20,&H63,&H68,&H61,&H6E,&H74,&H73,&H20,&H6F,&H75
! DB &H74,&H20,&H62,&H65,&H74,&H77,&H65,&H65,&H6E,&H20,&H74,&H77,&H6F,&H20,&H77,&H6F
! DB &H72,&H6C,&H64,&H73,&H21,&H0D,&H0A,&H46,&H49,&H52,&H45,&H20,&H57,&H41,&H4C,&H4B
! DB &H20,&H57,&H49,&H54,&H48,&H20,&H4D,&H45,&H21,&H0D,&H0A,&H42,&H4F,&H42,&H0D,&H0A
END MACRO

MACRO PELOCK_MEMORY_GAP_HELPER
! DD 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
! DD 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
! DD 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
! DD 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
! DD 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
! DD 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
! DD 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
! DD 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
! DD 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
! DD 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
! DD 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
! DD 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
! DD 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
! DD 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
! DD 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
! DD 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
END MACRO

MACRO PELOCK_MEMORY_GAP
! DB &HE9,&H04,&H20,&H00,&H00,&H8F,&HF1,&H12,&H34
PELOCK_MEMORY_GAP_HELPER
PELOCK_MEMORY_GAP_HELPER
PELOCK_MEMORY_GAP_HELPER
PELOCK_MEMORY_GAP_HELPER
END MACRO

MACRO PELOCK_WATERMARK
! DB &HEB,&H7E,&H44,&H6F,&H77,&H6E,&H20,&H69,&H6E,&H20,&H74,&H68,&H65,&H20,&H70,&H61
! DB &H72,&H6B,&H0D,&H0A,&H57,&H68,&H65,&H72,&H65,&H20,&H74,&H68,&H65,&H20,&H63,&H68
! DB &H61,&H6E,&H74,&H20,&H69,&H73,&H20,&H64,&H65,&H61,&H74,&H68,&H2C,&H20,&H64,&H65
! DB &H61,&H74,&H68,&H2C,&H20,&H64,&H65,&H61,&H74,&H68,&H0D,&H0A,&H55,&H6E,&H74,&H69
! DB &H6C,&H20,&H74,&H68,&H65,&H20,&H73,&H75,&H6E,&H20,&H63,&H72,&H69,&H65,&H73,&H20
! DB &H6D,&H6F,&H72,&H6E,&H69,&H6E,&H67,&H0D,&H0A,&H44,&H6F,&H77,&H6E,&H20,&H69,&H6E
! DB &H20,&H74,&H68,&H65,&H20,&H70,&H61,&H72,&H6B,&H20,&H77,&H69,&H74,&H68,&H20,&H66
! DB &H72,&H69,&H65,&H6E,&H64,&H73,&H20,&H6F,&H66,&H20,&H6D,&H69,&H6E,&H65,&H0D,&H0A
END MACRO

MACRO PELOCK_CPUID
! DB &HEB,&H7E,&H0D,&H0A,&H0D,&H0A,&H43,&H6F,&H6D,&H65,&H20,&H61,&H73,&H20,&H79,&H6F
! DB &H75,&H20,&H61,&H72,&H65,&H2C,&H20,&H61,&H73,&H20,&H79,&H6F,&H75,&H20,&H77,&H65
! DB &H72,&H65,&H0D,&H0A,&H41,&H73,&H20,&H49,&H20,&H77,&H61,&H6E,&H74,&H20,&H79,&H6F
! DB &H75,&H20,&H74,&H6F,&H20,&H62,&H65,&H0D,&H0A,&H41,&H73,&H20,&H61,&H20,&H66,&H72
! DB &H69,&H65,&H6E,&H64,&H2C,&H20,&H61,&H73,&H20,&H61,&H20,&H66,&H72,&H69,&H65,&H6E
! DB &H64,&H0D,&H0A,&H41,&H73,&H20,&H61,&H6E,&H20,&H6F,&H6C,&H64,&H20,&H65,&H6E,&H65
! DB &H6D,&H79,&H0D,&H0A,&H54,&H61,&H6B,&H65,&H20,&H79,&H6F,&H75,&H72,&H20,&H74,&H69
! DB &H6D,&H65,&H2C,&H20,&H68,&H75,&H72,&H72,&H79,&H20,&H75,&H70,&H0D,&H0A,&H0D,&H0A
END MACRO

MACRO PELOCK_INIT_CALLBACK
! DB &HEB,&H08,&H10,&H11,&H22,&H33,&H33,&H22,&H11,&H00
END MACRO

MACRO HARDWARE_ID_CALLBACK = ! DB &HEB,&H08,&H4F,&H5A,&HF7,&H38,&H31,&HCD,&HE0,&H53

MACRO FEATURE_1_END = FEATURE_END
MACRO FEATURE_2_END = FEATURE_END
MACRO FEATURE_3_END = FEATURE_END
MACRO FEATURE_4_END = FEATURE_END
MACRO FEATURE_5_END = FEATURE_END
MACRO FEATURE_6_END = FEATURE_END
MACRO FEATURE_7_END = FEATURE_END
MACRO FEATURE_8_END = FEATURE_END
MACRO FEATURE_9_END = FEATURE_END
MACRO FEATURE_10_END = FEATURE_END
MACRO FEATURE_11_END = FEATURE_END
MACRO FEATURE_12_END = FEATURE_END
MACRO FEATURE_13_END = FEATURE_END
MACRO FEATURE_14_END = FEATURE_END
MACRO FEATURE_15_END = FEATURE_END
MACRO FEATURE_16_END = FEATURE_END
MACRO FEATURE_17_END = FEATURE_END
MACRO FEATURE_18_END = FEATURE_END
MACRO FEATURE_19_END = FEATURE_END
MACRO FEATURE_20_END = FEATURE_END
MACRO FEATURE_21_END = FEATURE_END
MACRO FEATURE_22_END = FEATURE_END
MACRO FEATURE_23_END = FEATURE_END
MACRO FEATURE_24_END = FEATURE_END
MACRO FEATURE_25_END = FEATURE_END
MACRO FEATURE_26_END = FEATURE_END
MACRO FEATURE_27_END = FEATURE_END
MACRO FEATURE_28_END = FEATURE_END
MACRO FEATURE_29_END = FEATURE_END
MACRO FEATURE_30_END = FEATURE_END
MACRO FEATURE_31_END = FEATURE_END
MACRO FEATURE_32_END = FEATURE_END

MACRO FEATURE_1_END_MT = FEATURE_END_MT
MACRO FEATURE_2_END_MT = FEATURE_END_MT
MACRO FEATURE_3_END_MT = FEATURE_END_MT
MACRO FEATURE_4_END_MT = FEATURE_END_MT
MACRO FEATURE_5_END_MT = FEATURE_END_MT
MACRO FEATURE_6_END_MT = FEATURE_END_MT
MACRO FEATURE_7_END_MT = FEATURE_END_MT
MACRO FEATURE_8_END_MT = FEATURE_END_MT
MACRO FEATURE_9_END_MT = FEATURE_END_MT
MACRO FEATURE_10_END_MT = FEATURE_END_MT
MACRO FEATURE_11_END_MT = FEATURE_END_MT
MACRO FEATURE_12_END_MT = FEATURE_END_MT
MACRO FEATURE_13_END_MT = FEATURE_END_MT
MACRO FEATURE_14_END_MT = FEATURE_END_MT
MACRO FEATURE_15_END_MT = FEATURE_END_MT
MACRO FEATURE_16_END_MT = FEATURE_END_MT
MACRO FEATURE_17_END_MT = FEATURE_END_MT
MACRO FEATURE_18_END_MT = FEATURE_END_MT
MACRO FEATURE_19_END_MT = FEATURE_END_MT
MACRO FEATURE_20_END_MT = FEATURE_END_MT
MACRO FEATURE_21_END_MT = FEATURE_END_MT
MACRO FEATURE_22_END_MT = FEATURE_END_MT
MACRO FEATURE_23_END_MT = FEATURE_END_MT
MACRO FEATURE_24_END_MT = FEATURE_END_MT
MACRO FEATURE_25_END_MT = FEATURE_END_MT
MACRO FEATURE_26_END_MT = FEATURE_END_MT
MACRO FEATURE_27_END_MT = FEATURE_END_MT
MACRO FEATURE_28_END_MT = FEATURE_END_MT
MACRO FEATURE_29_END_MT = FEATURE_END_MT
MACRO FEATURE_30_END_MT = FEATURE_END_MT
MACRO FEATURE_31_END_MT = FEATURE_END_MT
MACRO FEATURE_32_END_MT = FEATURE_END_MT

#ENDIF ' #IF NOT %DEF(%PELOCK_INC)