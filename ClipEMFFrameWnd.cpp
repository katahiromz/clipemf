#include "stdafx.h"

BEGIN_MESSAGE_MAP(CClipEMFFrameWnd, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_COMMAND(MZC_ID_SAVE_AS, CommandSaveAs)
	ON_MESSAGE_VOID(MZC_WM_CLIPCHANGED, OnClipChanged)
	ON_WM_SIZE()
	ON_COMMAND(MZC_ID_OPEN_README_TXT, CommandReadMe)
	ON_COMMAND(MZC_ID_EXIT, CommandExit)
END_MESSAGE_MAP()

CClipEMFFrameWnd::CClipEMFFrameWnd()
{
}

/*virtual*/ CClipEMFFrameWnd::~CClipEMFFrameWnd()
{
}

mzc_msg VOID CClipEMFFrameWnd::CommandSaveAs()
{
	if (!m_emf)
		return;

	CFileDialog dlg(FALSE, _T("emf"), _T("無題"),
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("拡張メタファイル (*.emf)|*.emf|"), m_hWnd);
	if (dlg.DoModal() == IDOK)
	{
		LPCTSTR pszFileName = dlg.GetFileName();
		::DeleteFile(pszFileName);
		::DeleteEnhMetaFile(::CopyEnhMetaFile(m_emf, pszFileName));
	}
}

mzc_msg INT CClipEMFFrameWnd::OnCreate(LPCREATESTRUCT /*lpCreateStruct*/)
{
	BOOL b;
	DWORD style;

	ASSERT(m_hWnd != NULL);

	VERIFY(EnableDocking(BL_TOP | BL_BOTTOM));

	style = SS_ENHMETAFILE | WS_CHILD | WS_VISIBLE | WS_TABSTOP;
	b = m_static.CreateChildEx(WS_EX_CLIENTEDGE, NULL, style, CRect(), m_hWnd, 1);
	ASSERT(b);
	if (!b)
		return -1;

	b = m_watch.CreateChild(m_hWnd, 1);
	ASSERT(b);
	if (!b)
		return -1;

	style = WS_CHILD | WS_VISIBLE;
	b = m_statusBar.CreateChild(style, CRect(), m_hWnd, MZC_IDW_STATUSBAR);
	ASSERT(b);
	if (!b)
		return -1;

	b = m_accel.LoadAccelerators(MZC_IDR_MAINFRAME);
	ASSERT(b);
	if (!b)
		return -1;

	b = m_menu.LoadMenu(MZC_IDR_MAINFRAME);
	ASSERT(b);
	if (!b)
		return -1;

	SetInnerWnd(m_static);
	SetStatusBar(&m_statusBar);

	m_strDefaultStatusText = _T("他のプログラムで図形をコピーして下さい。");

	SetMenu(m_menu);
	OnClipChanged();

	return 0;
}

mzc_msg VOID CClipEMFFrameWnd::OnDestroy()
{
	SetMenu(NULL);
	::PostQuitMessage(0);
}

mzc_msg VOID CClipEMFFrameWnd::OnClipChanged()
{
	if (!!m_emf)
		m_emf.Delete();

	if (::IsClipboardFormatAvailable(CF_ENHMETAFILE))
	{
		if (::OpenClipboard(m_hWnd))
		{
			HEMF hEMF = (HEMF) ::GetClipboardData(CF_EMF);
			m_emf = hEMF;
			::CloseClipboard();
			ASSERT(!!m_emf);
		}
	}

	if (!!m_emf)
	{
		m_menu.EnableMenuItem(MZC_ID_SAVE_AS, MF_ENABLED);
		m_strDefaultStatusText = _T("[ファイル]メニューの[EMFとして保存...]を選んで下さい。");
	}
	else
	{
		m_menu.EnableMenuItem(MZC_ID_SAVE_AS, MF_GRAYED);
		m_strDefaultStatusText = _T("他のプログラムで図形をコピーして下さい。");
	}
	m_statusBar.SetText(m_strDefaultStatusText, 0);
	
	m_static.SetEnhMetaFile(m_emf);
}

mzc_msg VOID CClipEMFFrameWnd::OnSize(UINT nType, INT cx, INT cy)
{
	CFrameWnd::OnSize(nType, cx, cy);
	m_static.Invalidate();
}

mzc_msg VOID CClipEMFFrameWnd::CommandReadMe()
{
	TCHAR szFile[MAX_PATH];
	::GetModuleFileName(NULL, szFile, MAX_PATH);
	lstrcpy(MzcGetFileTitle(szFile), _T("ReadMe.txt"));
	::ShellExecute(m_hWnd, NULL, szFile, NULL, NULL, SW_SHOWNORMAL);
}

mzc_msg VOID CClipEMFFrameWnd::CommandExit()
{
	SendMessage(WM_CLOSE);
}

/*virtual*/ BOOL CClipEMFFrameWnd::PreTranslateMessage(MSG *pMsg)
{
	if (m_accel.TranslateAccelerator(m_hWnd, pMsg))
		return TRUE;
	return CFrameWnd::PreTranslateMessage(pMsg);
}
