#include "stdafx.h"

CClipEMF::CClipEMF()
	: CWinApp()
{
}

/*virtual*/ CClipEMF::~CClipEMF()
{
}

/*virtual*/ BOOL CClipEMF::InitInstance()
{
	if (!CWinApp::InitInstance())
		return FALSE;

	if (!CreateCommandImageList(ILC_COLOR8 | ILC_MASK))
		return FALSE;

	static UINT anCommands[] =
	{
		MZC_ID_NEW,
		MZC_ID_OPEN,
		MZC_ID_SAVE,
		MZC_ID_CUT,
		MZC_ID_COPY,
		MZC_ID_PASTE,
		MZC_ID_FIND,
		MZC_ID_FIND_NEXT,
		MZC_ID_FIND_PREV,
		MZC_ID_FONT,
		MZC_ID_PRINT,
		MZC_ID_HELP_CONTENTS
	};

	if (!AddCommandImages(MZC_IDR_MAINFRAME,
		_countof(anCommands), anCommands))
	{
		return FALSE;
	}

	if (!m_myFrameWnd.CreateEx(0, CString(MZC_IDS_APPNAME),
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, 300, 300))
	{
		return FALSE;
	}

	m_myFrameWnd.ShowWindow(mzcApp->m_nCmdShow);
	m_myFrameWnd.UpdateWindow();

	return TRUE;
}

CClipEMF theApp;
