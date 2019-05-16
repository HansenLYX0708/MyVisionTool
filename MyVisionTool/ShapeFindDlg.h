#pragma once


// ShapeFindDlg dialog

class ShapeFindDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ShapeFindDlg)

public:
	ShapeFindDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~ShapeFindDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SHAPE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonFindcircle();
};
