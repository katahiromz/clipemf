class CClipEMF : public CWinApp
{
public:
	CClipEMF();
	virtual ~CClipEMF();

	virtual BOOL InitInstance();

protected:
	CClipEMFFrameWnd m_myFrameWnd;
};
