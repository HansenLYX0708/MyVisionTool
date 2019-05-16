#pragma once


// SubpixelDlg dialog

class SubpixelDlg : public CDialogEx
{
	DECLARE_DYNAMIC(SubpixelDlg)

public:
	SubpixelDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~SubpixelDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SUBPIXEL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
