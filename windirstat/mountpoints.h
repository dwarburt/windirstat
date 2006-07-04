// mountpoints.h - Declaratio of CMountPoins
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

#pragma once

#include "../common/wds_constants.h"

class CMountPoints
{
	struct SPointVolume
	{
		CString point;	// Path like "mount\backup\"
		CString volume;	// Volume identifier
	};

	typedef CArray<SPointVolume, SPointVolume&> PointVolumeArray;

public:
	~CMountPoints();
	void Initialize();
	bool IsMountPoint(CString path);
	bool IsJunctionPoint(CString path);

private:
	void Clear();
	void GetDriveVolumes();
	void GetAllMountPoints();

	bool IsVolumeMountPoint(CString volume, CString path);

	CVolumeApi m_va;

	// m_drive contains the volume identifiers of the Drives A:, B: etc.
	// mdrive[0] = Volume identifier of A:\.
	CArray<CString, LPCTSTR> m_drive;

	// m_volume maps all volume identifiers to PointVolumeArrays
	CMap<CString, LPCTSTR, PointVolumeArray *, PointVolumeArray *> m_volume;	
};

// $Log$
// Revision 1.7  2006/07/04 23:37:39  assarbad
// - Added my email address in the header, adjusted "Author" -> "Author(s)"
// - Added CVS Log keyword to those files not having it
// - Added the files which I forgot during last commit
//
// Revision 1.6  2006/07/04 22:49:20  assarbad
// - Replaced CVS keyword "Date" by "Header" in the file headers
//
// Revision 1.5  2006/07/04 20:45:23  assarbad
// - See changelog for the changes of todays previous check-ins as well as this one!
//
// Revision 1.4  2004/11/05 16:53:07  assarbad
// Added Date and History tag where appropriate.
//
