class CClipEMFFrameWnd : public CFrameWnd
{
public:
	CClipEMFFrameWnd();
	virtual ~CClipEMFFrameWnd();

protected:
	CStatic m_static;
	CClipboardWatchWnd m_watch;
	CIconMenu m_menu;
	CEnhMetaFile m_emf;
	CStatusBar m_statusBar;
	CAccel m_accel;

	virtual BOOL PreTranslateMessage(MSG *pMsg);

	mzc_msg INT OnCreate(LPCREATESTRUCT lpCreateStruct);
	mzc_msg VOID OnDestroy();
	mzc_msg VOID CommandSaveAs();
	mzc_msg VOID CommandReadMe();
	mzc_msg VOID CommandExit();
	mzc_msg VOID OnClipChanged();
	mzc_msg VOID OnSize(UINT nType, INT cx, INT cy);

	DECLARE_MESSAGE_MAP()
};
