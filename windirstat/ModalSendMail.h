// modalsendmail.h		- Declaration of CModalSendMail
//
// WinDirStat - Directory Statistics
// Copyright (C) 2003 Bernhard Seifert
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
// Author: bseifert@users.sourceforge.net, bseifert@daccord.net

#pragma once

#include "modalapishuttle.h"


//
// CModalSendMail. For "Send mail to owner". Modal version of MAPISendMail.
// See comment on CModalApiShuttle.
//
class CModalSendMail: public CModalApiShuttle
{
public:
	CModalSendMail();

	static bool IsSendMailAvailable();
	bool SendMail(LPCTSTR recipient, LPCTSTR subject, LPCTSTR body);

protected:
	virtual void DoOperation();

	CMapi32Api m_api;		// Dynamically linked mapi32.dll
	CString m_recipient;	// Empty, if no recipient
	CString m_subject;		// Subject-line of e-mail
	CString m_body;			// Text of e-mail
	UINT m_result;
};
