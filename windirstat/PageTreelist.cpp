// PageTreelist.cpp		- Implementation of CPageTreelist
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

#include "stdafx.h"
#include "windirstat.h"
#include ".\pagetreelist.h"


IMPLEMENT_DYNAMIC(CPageTreelist, CPropertyPage)

CPageTreelist::CPageTreelist()
	: CPropertyPage(CPageTreelist::IDD)
	, m_treelistGrid(FALSE)
{
}

CPageTreelist::~CPageTreelist()
{
}

void CPageTreelist::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_TREELISTGRID, m_treelistGrid);
	for (int i=0; i < TREELISTCOLORCOUNT; i++)
	{
		DDX_Control(pDX, IDC_COLORBUTTON0 + i, m_colorButton[i]);
		if (pDX->m_bSaveAndValidate)
			m_treelistColor[i]= m_colorButton[i].GetColor();
		else
			m_colorButton[i].SetColor(m_treelistColor[i]);
	}
	DDX_Control(pDX, IDC_SLIDER, m_slider);
}


BEGIN_MESSAGE_MAP(CPageTreelist, CPropertyPage)
	ON_BN_CLICKED(IDC_TREELISTGRID, OnBnClickedTreelistgrid)
	ON_NOTIFY_RANGE(COLBN_CHANGED, IDC_COLORBUTTON0, IDC_COLORBUTTON7, OnColorChanged)
	ON_WM_VSCROLL()
END_MESSAGE_MAP()


BOOL CPageTreelist::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	m_treelistGrid= GetOptions()->IsTreelistGrid();
	m_treelistColorCount= GetOptions()->GetTreelistColorCount();
	GetOptions()->GetTreelistColors(m_treelistColor);

	m_slider.SetRange(1, TREELISTCOLORCOUNT);
	m_slider.SetPos(m_treelistColorCount);

	EnableButtons();

	UpdateData(false);
	return TRUE;
}

void CPageTreelist::OnOK()
{
	UpdateData();
	GetOptions()->SetTreelistGrid(m_treelistGrid);
	GetOptions()->SetTreelistColorCount(m_treelistColorCount);
	GetOptions()->SetTreelistColors(m_treelistColor);
	CPropertyPage::OnOK();
}

void CPageTreelist::OnBnClickedTreelistgrid()
{
	SetModified();
}

void CPageTreelist::OnColorChanged(UINT, NMHDR *, LRESULT *)
{
	SetModified();
}

void CPageTreelist::EnableButtons()
{
	for (int i=0; i < m_treelistColorCount; i++)
		m_colorButton[i].EnableWindow(true);
	for (; i < TREELISTCOLORCOUNT; i++)
		m_colorButton[i].EnableWindow(false);
}


void CPageTreelist::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if ((CSliderCtrl *)pScrollBar == &m_slider)
	{
		int pos= m_slider.GetPos();
		ASSERT(pos > 0);
		ASSERT(pos <= TREELISTCOLORCOUNT);

		m_treelistColorCount= pos;
		EnableButtons();
		SetModified();
	}
	CPropertyPage::OnVScroll(nSBCode, nPos, pScrollBar);
}
