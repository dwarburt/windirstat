// commonhelpers.cpp - Implementation of common global helper functions
//
// WinDirStat - Directory Statistics
// Copyright (C) 2003-2005 Bernhard Seifert
// Copyright (C) 2004-2006 Oliver Schneider (assarbad.net)
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// Author(s): - bseifert -> bseifert@users.sourceforge.net, bseifert@daccord.net
//            - assarbad -> http://assarbad.net/en/contact
//
// $Header$

#ifndef WINVER				// Allow use of features specific to Windows 95 and Windows NT 4 or later.
#define WINVER 0x0400		// Change this to the appropriate value to target Windows 98 and Windows 2000 or later.
#endif

#include <afxwin.h> // MFC core and standard components
#include <atlbase.h> // CComPtr, USES_CONVERSION

#include "mdexceptions.h"

#include "commonhelpers.h"


CString GetShellExecuteError(UINT u)
{
	CString s;

	switch (u)
	{
	case 0:
		{
			s = TEXT("The operating system is out of memory or resources.");
		}
		break;
	case ERROR_FILE_NOT_FOUND:
		{
			s = TEXT("The specified file was not found.");
		}
		break;
	case ERROR_PATH_NOT_FOUND:
		{
			s = TEXT("The specified path was not found.");
		}
		break;
	case ERROR_BAD_FORMAT:
		{
			s = TEXT("The .exe file is invalid (non-Microsoft Win32 .exe or error in .exe image).");
		}
		break;
	case SE_ERR_ACCESSDENIED:
		{
			s = TEXT("The operating system denied access to the specified file.");
		}
		break;
	case SE_ERR_ASSOCINCOMPLETE:
		{
			s = TEXT("The file name association is incomplete or invalid.");
		}
		break;
	case SE_ERR_DDEBUSY:
		{
			s = TEXT("The Dynamic Data Exchange (DDE) transaction could not be completed because other DDE transactions were being processed.");
		}
		break;
	case SE_ERR_DDEFAIL:
		{
			s = TEXT("The DDE transaction failed.");
		}
		break;
	case SE_ERR_DDETIMEOUT:
		{
			s = TEXT("The DDE transaction could not be completed because the request timed out.");
		}
		break;
	case SE_ERR_DLLNOTFOUND:
		{
			s = TEXT("The specified dynamic-link library (DLL) was not found.");
		}
		break;
	case SE_ERR_NOASSOC:
		{
			s = TEXT("There is no application associated with the given file name extension. This error will also be returned if you attempt to print a file that is not printable.");
		}
		break;
	case SE_ERR_OOM:
		{
			s = TEXT("There was not enough memory to complete the operation.");
		}
		break;
	case SE_ERR_SHARE:
		{
			s = TEXT("A sharing violation occurred");
		}
		break;
	default:
		{
			s.Format(TEXT("Error Number %d"), u);
		}
		break;
	}

	return s;
}


CString MyStrRetToString(const LPITEMIDLIST pidl, const STRRET *strret)
{
	// StrRetToStr() is not always available (e.g. on Windows 98).
	// So we use an own function instead.
	USES_CONVERSION;

	CString s;

	switch (strret->uType)
	{
	case STRRET_CSTR:
		{
			s = strret->cStr;
		}
		break;
	case STRRET_OFFSET:
		{
			s = A2T((char *)pidl + strret->uOffset);
		}
		break;
	case STRRET_WSTR:
		{
			s = W2T(strret->pOleStr);
		}
		break;
	}

	return s;
}

void MyShellExecute(HWND hwnd, LPCTSTR lpOperation, LPCTSTR lpFile, LPCTSTR lpParameters, LPCTSTR lpDirectory, INT nShowCmd) throw (CException *)
{
	CWaitCursor wc;

	UINT h = (UINT)ShellExecute(hwnd, lpOperation, lpFile, lpParameters, lpDirectory, nShowCmd);
	if(h <= 32)
	{
		MdThrowStringExceptionF(TEXT("ShellExecute failed: %1!s!"), GetShellExecuteError(h));
	}
}


CString GetBaseNameFromPath(LPCTSTR path)
{
	CString s = path;
	int i = s.ReverseFind(chrBackslash);
	if(i < 0)
	{
		return s;
	}
	return s.Mid(i + 1);
}

bool FileExists(LPCTSTR path)
{
	CFileFind finder;
	BOOL b = finder.FindFile(path);
	if(b)
	{
		finder.FindNextFile();
		return !finder.IsDirectory();
	}
	else
	{
		return false;
	}
}

CString LoadString(UINT resId)
{
	return MAKEINTRESOURCE(resId);
}

CString GetAppFileName()
{
	CString s;
	VERIFY(GetModuleFileName(NULL, s.GetBuffer(_MAX_PATH), _MAX_PATH));
	s.ReleaseBuffer();
	return s;
}

CString GetAppFolder()
{
	CString s = GetAppFileName();
	int i = s.ReverseFind(chrBackslash);
	ASSERT(i >= 0);
	s = s.Left(i);
	return s;
}

CString MyGetFullPathName(LPCTSTR relativePath)
{
	LPTSTR dummy;
	CString buffer;

	DWORD len = _MAX_PATH;

    DWORD dw = GetFullPathName(relativePath, len, buffer.GetBuffer(len), &dummy);
	buffer.ReleaseBuffer();

	while(dw >= len)
	{
		len += _MAX_PATH;
		dw = GetFullPathName(relativePath, len, buffer.GetBuffer(len), &dummy);
		buffer.ReleaseBuffer();
	}

	if(0 == dw)
	{
		TRACE("GetFullPathName(%s) failed: GetLastError returns %u\r\n", relativePath, GetLastError());
		return relativePath;
	}

	return buffer;
}


// $Log$
// Revision 1.7  2006/07/04 23:37:39  assarbad
// - Added my email address in the header, adjusted "Author" -> "Author(s)"
// - Added CVS Log keyword to those files not having it
// - Added the files which I forgot during last commit
//
// Revision 1.6  2006/07/04 22:49:18  assarbad
// - Replaced CVS keyword "Date" by "Header" in the file headers
//
// Revision 1.5  2006/07/04 20:45:16  assarbad
// - See changelog for the changes of todays previous check-ins as well as this one!
//
// Revision 1.4  2004/11/05 16:53:05  assarbad
// Added Date and History tag where appropriate.
//
