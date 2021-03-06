
// MyVisionToolDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "MyVisionTool.h"
#include "MyVisionToolDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

RNG rng(12345);

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMyVisionToolDlg 对话框



CMyVisionToolDlg::CMyVisionToolDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MYVISIONTOOL_DIALOG, pParent)
	, m_bIsContinPro(FALSE)
	, m_bIsDstSave(FALSE)
	, m_strStateInfo(_T(""))
	, m_size(0)
	, m_blurPram1(0)
	, m_blurPram2(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyVisionToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PIC_STATIC, m_PicStatic);
	DDX_Check(pDX, IDC_CHECK_CONPRO, m_bIsContinPro);
	DDX_Check(pDX, IDC_CHECK_DST_SAVE, m_bIsDstSave);
	DDX_Text(pDX, IDC_EDIT_STATEINFO, m_strStateInfo);
	DDV_MaxChars(pDX, m_strStateInfo, 200);
	DDX_Text(pDX, IDC_EDIT_SIZE, m_size);
	DDV_MinMaxInt(pDX, m_size, 1, 51);
	DDX_Text(pDX, IDC_EDIT_PRAM1, m_blurPram1);
	DDX_Text(pDX, IDC_EDIT_PRAM2, m_blurPram2);
	//DDX_Control(pDX, IDC_TAB_PROCFUNC, m_tabProcFunc);
	DDX_Control(pDX, IDC_TAB1, m_tab);
}

BEGIN_MESSAGE_MAP(CMyVisionToolDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_LOADIMAGE, &CMyVisionToolDlg::OnBnClickedBtnLoadSourceimage)
	ON_BN_CLICKED(IDC_BTN_SHOWSRC, &CMyVisionToolDlg::OnBnClickedBtnShowsrc)
	ON_BN_CLICKED(IDC_BTN_SHOWPRO, &CMyVisionToolDlg::OnBnClickedBtnShowpro)
	ON_BN_CLICKED(IDC_BTN_SHOWDST, &CMyVisionToolDlg::OnBnClickedBtnShowdst)
	ON_BN_CLICKED(IDC_BTN_FILTER2D, &CMyVisionToolDlg::OnBnClickedBtnFilter2d)
	ON_BN_CLICKED(IDC_CHECK_CONPRO, &CMyVisionToolDlg::OnBnClickedCheckConpro)
	ON_BN_CLICKED(IDC_CHECK_DST_SAVE, &CMyVisionToolDlg::OnBnClickedCheckDstSave)
	ON_BN_CLICKED(IDC_BTN_CVTCOLOR, &CMyVisionToolDlg::OnBnClickedBtnCvtcolor)
	ON_BN_CLICKED(IDC_BTN_SAVE, &CMyVisionToolDlg::OnBnClickedBtnSave)
	ON_BN_CLICKED(IDC_BTN_BLUR, &CMyVisionToolDlg::OnBnClickedBtnBlur)
	ON_BN_CLICKED(IDC_BTN_GSBLUR, &CMyVisionToolDlg::OnBnClickedBtnGsblur)
	ON_BN_CLICKED(IDC_BTN_MEDIANBLUR, &CMyVisionToolDlg::OnBnClickedBtnMedianblur)
	ON_BN_CLICKED(IDC_BTN_BILATERALFILTER, &CMyVisionToolDlg::OnBnClickedBtnBilateralfilter)

	ON_BN_CLICKED(IDC_BTN_THRESHOLD_TRIANGLE, &CMyVisionToolDlg::OnBnClickedBtnThreshold)
	ON_BN_CLICKED(IDC_BTN_THRESHOLD_OTSU, &CMyVisionToolDlg::OnBnClickedBtnThreshold)

	ON_BN_CLICKED(IDC_BTN_ERODE, &CMyVisionToolDlg::OnBnClickedBtnmorphologyEx)
	ON_BN_CLICKED(IDC_BTN_DILATE, &CMyVisionToolDlg::OnBnClickedBtnmorphologyEx)
	ON_BN_CLICKED(IDC_BTN_MOROPEN, &CMyVisionToolDlg::OnBnClickedBtnmorphologyEx)
	ON_BN_CLICKED(IDC_BTN_MORCLOSE, &CMyVisionToolDlg::OnBnClickedBtnmorphologyEx)
	ON_BN_CLICKED(IDC_BTN_BLACKHAT, &CMyVisionToolDlg::OnBnClickedBtnmorphologyEx)
	ON_BN_CLICKED(IDC_BTN_TOPHAT, &CMyVisionToolDlg::OnBnClickedBtnmorphologyEx)
	ON_BN_CLICKED(IDC_BTN_GRADIENT, &CMyVisionToolDlg::OnBnClickedBtnmorphologyEx)

	ON_BN_CLICKED(IDC_BTN_BITAND, &CMyVisionToolDlg::OnBnClickedBtnBitwise)
	ON_BN_CLICKED(IDC_BTN_BITOR, &CMyVisionToolDlg::OnBnClickedBtnBitwise)
	ON_BN_CLICKED(IDC_BTN_BITXOR, &CMyVisionToolDlg::OnBnClickedBtnBitwise)
	ON_BN_CLICKED(IDC_BTN_BITNOT, &CMyVisionToolDlg::OnBnClickedBtnBitwise)

	ON_BN_CLICKED(IDC_BTN_PYRUP, &CMyVisionToolDlg::OnBnClickedResize)
	ON_BN_CLICKED(IDC_BTN_PYRDOWN, &CMyVisionToolDlg::OnBnClickedResize)
	ON_BN_CLICKED(IDC_BTN_RESIZE, &CMyVisionToolDlg::OnBnClickedResize)
	ON_BN_CLICKED(IDC_BTN_SOBELX, &CMyVisionToolDlg::OnBnClickedBtnSobel)
	ON_BN_CLICKED(IDC_BTN_SOBELY, &CMyVisionToolDlg::OnBnClickedBtnSobel)
	ON_BN_CLICKED(IDC_BTN_SOBEL, &CMyVisionToolDlg::OnBnClickedBtnSobel)
	ON_BN_CLICKED(IDC_BTN_LAPLACIAN, &CMyVisionToolDlg::OnBnClickedBtnLaplacian)

	ON_BN_CLICKED(IDC_BTN_SHOWPREPRO, &CMyVisionToolDlg::OnBnClickedBtnShowprepro)
	ON_BN_CLICKED(IDC_BTN_CANNY, &CMyVisionToolDlg::OnBnClickedBtnCanny)
	ON_BN_CLICKED(IDC_BTN_HOUGHLINES, &CMyVisionToolDlg::OnBnClickedBtnHoughlines)
	ON_BN_CLICKED(IDC_BTN_HOUGHCIRCLE, &CMyVisionToolDlg::OnBnClickedBtnHoughcircle)
	ON_BN_CLICKED(IDC_BTN_PLATEEXTRACT, &CMyVisionToolDlg::OnBnClickedBtnPlateextract)
	ON_BN_CLICKED(IDC_PictureTransferToVideo, &CMyVisionToolDlg::OnBnClickedPicturetransfertovideo)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CMyVisionToolDlg::OnTcnSelchangeTab1)
	ON_BN_CLICKED(IDC_BUTTON_UNDOALL, &CMyVisionToolDlg::OnBnClickedButtonUndoall)
	ON_BN_CLICKED(IDC_BTN_SURF, &CMyVisionToolDlg::OnBnClickedBtnSurf)
	ON_BN_CLICKED(IDC_BTN_HIST, &CMyVisionToolDlg::OnBnClickedBtnHist)
	ON_BN_CLICKED(IDC_BTN_EqualizeHIST, &CMyVisionToolDlg::OnBnClickedBtnEqualizehist)
	ON_BN_CLICKED(IDOK, &CMyVisionToolDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMyVisionToolDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BTN_FINDCONTOURS, &CMyVisionToolDlg::OnBnClickedBtnFindcontours)
	ON_BN_CLICKED(IDC_BTN_MINRECT, &CMyVisionToolDlg::OnBnClickedBtnMinrect)
	ON_BN_CLICKED(IDC_BTN_THRESHOLD_ADAPT, &CMyVisionToolDlg::OnBnClickedBtnThresholdAdapt)
	ON_BN_CLICKED(IDC_BTN_CORNERS, &CMyVisionToolDlg::OnBnClickedBtnCorners)
	ON_BN_CLICKED(IDC_BTN_HULL, &CMyVisionToolDlg::OnBnClickedBtnHull)
END_MESSAGE_MAP()


// CMyVisionToolDlg 消息处理程序

BOOL CMyVisionToolDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// Tab control init
	m_tab.InsertItem(0, "Find Shape");
	m_tab.InsertItem(1, "Subpixel");
	m_shapeFindDlg.Create(IDD_DIALOG_SHAPE, &m_tab);
	m_subpixelDlg.Create(IDD_DIALOG_SUBPIXEL, &m_tab);
	CRect rc;
	m_tab.GetClientRect(rc);
	rc.top += 30;
	rc.bottom -= 0;
	rc.left += 0;
	rc.right -= 0;
	m_shapeFindDlg.MoveWindow(&rc);
	m_subpixelDlg.MoveWindow(&rc);
	//把对话框对象指针保存起来
	pDialog[0] = &m_shapeFindDlg;
	pDialog[1] = &m_subpixelDlg;
	//显示初始页面
	pDialog[0]->ShowWindow(SW_SHOW);
	pDialog[1]->ShowWindow(SW_HIDE);
	//保存当前选择
	m_curSelTab = 0;



	Init();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMyVisionToolDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMyVisionToolDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMyVisionToolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

#pragma region Process
void CMyVisionToolDlg::Init()
{
	namedWindow("view", WINDOW_AUTOSIZE);
	HWND hWnd = (HWND)cvGetWindowHandle("view");
	HWND hParent = ::GetParent(hWnd);
	::SetParent(hWnd, GetDlgItem(IDC_PIC_STATIC)->m_hWnd);
	::ShowWindow(hParent, SW_HIDE);

	m_bIsContinPro = true;
	m_bIsDstSave = true;

	m_size = 3;
	m_blurPram1 = 5.0;
	m_blurPram2 = 5.0;

	UpdateData(false);
}

void CMyVisionToolDlg::ShowImage(int type)
{
	Mat image;
	string strInfo = "";
	if (type == SHOW_SRC)
	{
		image = src;
		strInfo = "src";
	}
	else if (type == SHOW_PRO)
	{
		image = pro;
		strInfo = "pro";
	}
	else if (type == SHOW_DST)
	{
		image = dst;
		strInfo = "dst";
	}
	else if (type == SHOW_PREPRO)
	{
		image = prePro;
		strInfo = "prePro";
	}
	else
	{
		return;
	}
	if (!image.data)
	{
		string info = "could not load " + strInfo + " image...\n";
		StateInfo(info, STATE_ERROR);
		return;
	}
	//以下操作获取图形控件尺寸并以此改变图片尺寸，按比例缩放
	CRect rect;
	GetDlgItem(IDC_PIC_STATIC)->GetClientRect(&rect);
	Rect dst(rect.left, rect.top, rect.right, rect.bottom);
	double fx = (double)rect.Width() / image.cols;
	double fy = (double)rect.Height() / image.rows;
	if (fx > fy)
	{
		fx = fy;
	}
	Mat imagedst;
	resize(image, imagedst, Size(0, 0), fx, fx);
	// 清除图片后再显示
	CStatic* pStatic = (CStatic*)GetDlgItem(IDC_PIC_STATIC);
	pStatic->SetBitmap(NULL);
	imshow("view", imagedst);
}

void CMyVisionToolDlg::CheckFlag()
{
	if (m_bIsContinPro)
	{
		prePro = pro.clone();
	}
	if (m_bIsDstSave)
	{
		dst = pro.clone();
	}
}

void CMyVisionToolDlg::StateInfo(string info, int type)
{
	if (info.empty())
	{
		return;
	}
	string strHead = "";
	switch (type)
	{
	case STATE_INFO:
		strHead = "INFO:";
		break;
	case STATE_ERROR:
		strHead = "ERROR:";
		break;
	case STATE_DEBUG:
		strHead = "DEBUG:";
		break;
	default:
		break;
	}
	info = strHead + info;
	// string to CString
	m_strStateInfo.Format("%s", info.c_str());
	UpdateData(FALSE);
}




void CMyVisionToolDlg::CheckWindowValue()
{
	UpdateData(TRUE);
}
#pragma endregion

void CMyVisionToolDlg::OnBnClickedBtnLoadSourceimage()
{
	CString picPath;
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_ALLOWMULTISELECT, NULL, this);
	if (dlg.DoModal() == IDOK)
	{
		picPath = dlg.GetPathName();
	}
	// CString to string
	string imageSrcPath1 = picPath.GetBuffer(0);
	src = imread(imageSrcPath1);
	prePro = src.clone();
	ShowImage(SHOW_PREPRO);
}

void CMyVisionToolDlg::OnBnClickedButtonUndoall()
{
	prePro = src.clone();
	if(!pro.data)
		pro.release();
	if (!dst.data)
		dst.release();
	ShowImage(SHOW_PREPRO);
}

void CMyVisionToolDlg::OnBnClickedBtnSave()
{
	if (!dst.data)
	{
		string info = "Error: The dst picture cannot be empty\n";
		StateInfo(info, STATE_ERROR);
		return;
	}
	imwrite("dst.png", dst);
}

// TODO : 考虑合并显示函数
void CMyVisionToolDlg::OnBnClickedBtnShowsrc()
{
	ShowImage(SHOW_SRC);
}

void CMyVisionToolDlg::OnBnClickedBtnShowpro()
{
	ShowImage(SHOW_PRO);
}

void CMyVisionToolDlg::OnBnClickedBtnShowdst()
{
	ShowImage(SHOW_DST);
}

void CMyVisionToolDlg::OnBnClickedBtnShowprepro()
{
	ShowImage(SHOW_PREPRO);
}

// TODO : OnBnClickedCheckConpro 和 OnBnClickedCheckDstSave 功能有重复，考虑合并
void CMyVisionToolDlg::OnBnClickedCheckConpro()
{
	UpdateData(TRUE);
}

void CMyVisionToolDlg::OnBnClickedCheckDstSave()
{
	UpdateData(TRUE);
}

void CMyVisionToolDlg::OnBnClickedBtnFilter2d()
{
	if (!prePro.data)
	{
		string info = "Error: The picture cannot be empty";
		StateInfo(info, STATE_ERROR);
		return;
	}
	Mat kernel = (Mat_<char>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
	filter2D(prePro, pro, prePro.depth(), kernel);
	CheckFlag();
	ShowImage(SHOW_PRO);
	StateInfo("Success", STATE_INFO);
}

void CMyVisionToolDlg::OnBnClickedBtnCvtcolor()
{
	if (!prePro.data)
	{
		string info = "Error::The picture cannot be empty";
		StateInfo(info, STATE_ERROR);
		return;
	}
	else if (prePro.channels() <= 1)
	{
		string info = "Error::The picture channels cannot be less than 1";
		StateInfo(info, STATE_ERROR);
		return;
	}
	cvtColor(prePro, pro, CV_BGR2GRAY);
	CheckFlag();
	ShowImage(SHOW_PRO);
	StateInfo("BGR2GRAY Success", STATE_INFO);
}

void CMyVisionToolDlg::OnBnClickedBtnThreshold()
{
	if (!prePro.data)
	{
		string info = "Error::The picture cannot be empty";
		StateInfo(info, STATE_ERROR);
		return;
	}
	else if (prePro.channels() > 1)
	{
		string info = "Error::The picture channels cannot be greater than 1";
		StateInfo(info, STATE_ERROR);
		return;
	}
	CWnd *pWnd = GetFocus();
	int nPortID = pWnd->GetDlgCtrlID();
	int type;
	string info;
	switch (nPortID)
	{
	case IDC_BTN_THRESHOLD_OTSU:
		type = THRESH_OTSU;
		info = "threshold OTSU success";
		break;
	case IDC_BTN_THRESHOLD_TRIANGLE:
		type = THRESH_TRIANGLE;
		info = "threshold TRIANGLE success";
		break;
	default:
		break;
	}
	threshold(prePro, pro, 0, 255, type | THRESH_BINARY_INV);// THRESH_TRIANGLE // THRESH_OTSU
	CheckFlag();
	ShowImage(SHOW_PRO);
	StateInfo(info, STATE_INFO);
}

void CMyVisionToolDlg::OnBnClickedBtnBlur()
{
	CheckWindowValue();
	if (!prePro.data)
	{
		string info = "Error::The picture cannot be empty";
		StateInfo(info, STATE_ERROR);
		return;
	}
	blur(prePro, pro, Size(m_size, m_size), Point(-1, -1));
	CheckFlag();
	ShowImage(SHOW_PRO);
	StateInfo("blur Success", STATE_INFO);
}

void CMyVisionToolDlg::OnBnClickedBtnGsblur()
{
	CheckWindowValue();
	if (!prePro.data)
	{
		string info = "Error::The picture cannot be empty";
		StateInfo(info, STATE_ERROR);
		return;
	}
	GaussianBlur(prePro, pro, Size(m_size, m_size), m_blurPram1, m_blurPram2);
	CheckFlag();
	ShowImage(SHOW_PRO);
	StateInfo("GaussianBlur Success", STATE_INFO);
}

void CMyVisionToolDlg::OnBnClickedBtnMedianblur()
{
	CheckWindowValue();
	if (!prePro.data)
	{
		string info = "Error::The picture cannot be empty";
		StateInfo(info, STATE_ERROR);
		return;
	}
	medianBlur(prePro, pro, m_size);
	CheckFlag();
	ShowImage(SHOW_PRO);
	StateInfo("medianBlur Success", STATE_INFO);
}

void CMyVisionToolDlg::OnBnClickedBtnBilateralfilter()
{
	CheckWindowValue();
	if (!prePro.data)
	{
		string info = "Error::The picture cannot be empty";
		StateInfo(info, STATE_ERROR);
		return;
	}
	bilateralFilter(prePro, pro, 15, 100, 5);
	CheckFlag();
	ShowImage(SHOW_PRO);
	StateInfo("bilateralFilter Success", STATE_INFO);
}

void CMyVisionToolDlg::OnBnClickedBtnmorphologyEx()
{
	CheckWindowValue();
	if (!prePro.data)
	{
		string info = "Error::The picture cannot be empty";
		StateInfo(info, STATE_ERROR);
		return;
	}
	CWnd *pWnd = GetFocus();
	int nPortID = pWnd->GetDlgCtrlID();

	int type;
	string info;
	switch (nPortID)
	{
	case IDC_BTN_ERODE:
		type = CV_MOP_ERODE;
		info = "Erode Success";
		break;
	case IDC_BTN_DILATE:
		type = CV_MOP_DILATE;
		info = "Dilate Success";
		break;
	case IDC_BTN_MOROPEN:
		type = CV_MOP_OPEN;
		info = "Moropen Success";
		break;
	case IDC_BTN_MORCLOSE:
		type = CV_MOP_CLOSE;
		info = "Morclose Success";
		break;
	case IDC_BTN_BLACKHAT:
		type = CV_MOP_BLACKHAT;
		info = "BlackHat Success";
		break;
	case IDC_BTN_TOPHAT:
		type = CV_MOP_TOPHAT;
		info = "Tophat Success";
		break;
	case IDC_BTN_GRADIENT:
		type = CV_MOP_GRADIENT;
		info = "Tophat Success";
		break;
	default:
		break;
	}
	Mat structureElement = getStructuringElement(MORPH_RECT, Size(m_size, m_size), Point(-1, -1)); // MORPH_RECT  MORPH_CORSS  MORPH_ELLIPSE
	morphologyEx(prePro, pro, type, structureElement, Point(-1, -1), 1);
	CheckFlag();
	ShowImage(SHOW_PRO);
	StateInfo(info, STATE_INFO);
}

void CMyVisionToolDlg::OnBnClickedBtnBitwise()
{
	string info = "";
	CWnd *pWnd = GetFocus();
	int nPortID = pWnd->GetDlgCtrlID();
	switch (nPortID)
	{
		// TODO : Add and or xor
	case IDC_BTN_BITAND:
		break;
	case IDC_BTN_BITOR:
		break;
	case IDC_BTN_BITXOR:
		break;
	case IDC_BTN_BITNOT:
		bitwise_not(prePro, pro);
		info = "bit not success";
		break;
	default:
		break;
	}
	CheckFlag();
	ShowImage(SHOW_PRO);
	StateInfo(info, STATE_INFO);
}

void CMyVisionToolDlg::OnBnClickedResize()
{
	CheckWindowValue();
	if (!prePro.data)
	{
		string info = "Error::The picture cannot be empty";
		StateInfo(info, STATE_ERROR);
		return;
	}
	CWnd *pWnd = GetFocus();
	int nPortID = pWnd->GetDlgCtrlID();
	int type;
	string info;
	switch (nPortID)
	{
	case IDC_BTN_RESIZE:
		resize(prePro, pro,Size(), 0.5, 0.5);
		info = "RESIZE Success";
		break;
	case IDC_BTN_PYRUP:
		pyrUp(prePro, pro, Size(prePro.cols / 2, prePro.rows / 2));
		info = "PYRUP Success";
		break;
	case IDC_BTN_PYRDOWN:
		pyrDown(prePro, pro, Size(prePro.cols * 2, prePro.rows * 2));
		info = "PYRDOWN Success";
		break;
	default:
		break;
	}
	CheckFlag();
	ShowImage(SHOW_PRO);
	StateInfo(info, STATE_INFO);
}

void CMyVisionToolDlg::OnBnClickedBtnSobel()
{
	CheckWindowValue();
	if (!prePro.data)
	{
		string info = "Error::The picture cannot be empty";
		StateInfo(info, STATE_ERROR);
		return;
	}
	CWnd *pWnd = GetFocus();
	int nPortID = pWnd->GetDlgCtrlID();
	double type_x, type_y;
	string info;
	switch (nPortID)
	{
	case IDC_BTN_SOBELX:
		type_x = 1;
		type_y = 0;
		info = "SOBELX Success";
		break;
	case IDC_BTN_SOBELY:
		type_x = 0;
		type_y = 1;
		info = "SOBELY Success";
		break;
	case IDC_BTN_SOBEL:
		type_x = 0.5;
		type_y = 0.5;
		info = "SOBEL Success";
		break;
	default:
		break;
	}
	if (type_x == 0.5 && type_y == 0.5)
	{
		Mat xgrad, ygrad;
		Sobel(prePro, xgrad, CV_16S, 1, 0, m_size);
		Sobel(prePro, ygrad, CV_16S, 0, 1, m_size);
		convertScaleAbs(xgrad, xgrad);
		convertScaleAbs(ygrad, ygrad);
		addWeighted(xgrad, type_x, ygrad, type_y, 0, pro);
	}
	else
	{
		Sobel(prePro, pro, CV_16S, type_x, type_y, m_size);
	}
	convertScaleAbs(pro, pro);
	CheckFlag();
	ShowImage(SHOW_PRO);
	StateInfo(info, STATE_INFO);
}

void CMyVisionToolDlg::OnBnClickedBtnLaplacian()
{
	CheckWindowValue();
	if (!prePro.data)
	{
		string info = "Error::The picture cannot be empty";
		StateInfo(info, STATE_ERROR);
		return;
	}
	else if (prePro.channels() > 1)
	{
		string info = "Error::The picture channels cannot be greater than 1";
		StateInfo(info, STATE_ERROR);
		return;
	}
	Laplacian(prePro, pro, CV_16S, m_size);
	convertScaleAbs(pro, pro);
	string info = "Laplacian Success";
	CheckFlag();
	ShowImage(SHOW_PRO);
	StateInfo(info, STATE_INFO);
}

int t1_value = 50;

void CMyVisionToolDlg::OnBnClickedBtnCanny()
{
	if (!prePro.data)
	{
		string info = "Error::The picture cannot be empty";
		StateInfo(info, STATE_ERROR);
		return;
	}
	else if (prePro.channels() > 1)
	{
		string info = "Error::The picture channels cannot be greater than 1";
		StateInfo(info, STATE_ERROR);
		return;
	}
	Canny(prePro, pro, t1_value, t1_value * 2, 3, false);
	string info = "Canny success";
	CheckFlag();
	ShowImage(SHOW_PRO);
	StateInfo(info, STATE_INFO);
}

void CMyVisionToolDlg::OnBnClickedBtnHoughlines()
{
	if (!prePro.data)
	{
		string info = "Error::The picture cannot be empty";
		StateInfo(info, STATE_ERROR);
		return;
	}
	vector<Vec2f> lines;
	HoughLines(prePro, lines, 1, CV_PI / 180, 150, 0, 0);
	for (size_t i = 0; i < lines.size(); i++) {
		float rho = lines[i][0]; // 极坐标中的r长度
		float theta = lines[i][1]; // 极坐标中的角度
		Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a * rho, y0 = b * rho;
		// 转换为平面坐标的四个点
		pt1.x = cvRound(x0 + 1000 * (-b));
		pt1.y = cvRound(y0 + 1000 * (a));
		pt2.x = cvRound(x0 - 1000 * (-b));
		pt2.y = cvRound(y0 - 1000 * (a));
		line(pro, pt1, pt2, Scalar(0, 0, 255), 1, CV_AA);
	}
	string info = "hough lines success";
	CheckFlag();
	ShowImage(SHOW_PRO);
	StateInfo(info, STATE_INFO);
}

void CMyVisionToolDlg::OnBnClickedBtnHoughcircle()
{
	if (!prePro.data)
	{
		string info = "Error::The picture cannot be empty";
		StateInfo(info, STATE_ERROR);
		return;
	}
	vector<Vec3f> pcircles;
	HoughCircles(prePro, pcircles, CV_HOUGH_GRADIENT, 1, 10, 100, 30, 100, 500);
	src.copyTo(dst);
	for (size_t i = 0; i < pcircles.size(); i++) {
		Vec3f cc = pcircles[i];
		circle(pro, Point(cc[0], cc[1]), cc[2], Scalar(255, 255, 255), 2, LINE_AA);
		//circle(pro, Point(cc[0], cc[1]), 2, Scalar(198, 23, 155), 2, LINE_AA);
	}
	string info = "hough Circles success";
	CheckFlag();
	ShowImage(SHOW_PRO);
	StateInfo(info, STATE_INFO);
}


void CMyVisionToolDlg::OnBnClickedBtnPlateextract()
{
	//灰度化
	Mat  gray_image;

	cvtColor(prePro, gray_image, CV_RGB2GRAY);

	//imshow("test", gray_image);

	//Candy/sobel 边缘检测：
	Mat candy_image;
	Canny(gray_image, candy_image, 500, 200, 3);
	//imshow("test", candy_image);

	//形态学处理
	//图片膨胀处理
	Mat dilate_image, erode_image;
	//自定义 核进行 x 方向的膨胀腐蚀
	Mat elementX = getStructuringElement(MORPH_RECT, Size(25, 1));
	Mat elementY = getStructuringElement(MORPH_RECT, Size(1, 19));
	Point point(-1, -1);
	dilate(candy_image, dilate_image, elementX, point, 2);
	erode(dilate_image, erode_image, elementX, point, 4);
	dilate(erode_image, dilate_image, elementX, point, 2);

	//自定义 核进行 Y 方向的膨胀腐蚀
	erode(dilate_image, erode_image, elementY, point, 1);
	dilate(erode_image, dilate_image, elementY, point, 2);
	//imshow("test", dilate_image);
	//waitKey(1000);
	imwrite("dilate_image.jpg", dilate_image);
	//噪声处理
	//平滑处理 中值滤波
	Mat blurr_image;
	medianBlur(dilate_image, blurr_image, 15);
	medianBlur(blurr_image, blurr_image, 15);
	//imshow("test", blurr_image);

	//矩形轮廓查找与筛选：
	Mat contour_image;
	//深拷贝  查找轮廓会改变源图像信息，需要重新 拷贝 图像
	contour_image = blurr_image.clone();
	vector<vector<Point>> contours;
	findContours(contour_image, contours, CV_RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	//画出轮廓
	drawContours(contour_image, contours, -1, Scalar(255), 1);
	//轮廓表示为一个矩形  车牌提取
	Mat  roi_image;
	vector<Point> rectPoint;
	for (int i = 0; i < contours.size(); i++) {
		Rect r = boundingRect(Mat(contours[i]));
		//RotatedRect r = minAreaRect(Mat(contours[i]));
		cout << "contours " << i << "  height = " << r.height << "  width = " << r.width << "rate = " << ((float)r.width / r.height) << endl;
		if ((float)r.width / r.height >= 2.2 && (float)r.width / r.height <= 3.6) {
			cout << "r.x = " << r.x << "  r.y  = " << r.y << endl;
			rectangle(contour_image, r, Scalar(0, 0, 255), 2);
			for (int j = 0; j < contours[i].size(); j++) {
				cout << "point = " << contours[i][j] << endl;
			}
			//rectangle(image, r, Scalar(0, 0, 255), 3);
			roi_image = prePro(r);
		}
	}
	imshow("test", roi_image);
	waitKey(1000);
	imwrite("roi_image.jpg", roi_image);
	//图片放大
	Mat large_image;
	int col = roi_image.cols, row = roi_image.rows;
	resize(roi_image, large_image, Size(300, 300 * row / col));
	imshow("test", large_image);
	waitKey(2000);
	//车牌分割
	//灰度化 
	Mat  roi_gray_image;
	cvtColor(large_image, roi_gray_image, CV_RGB2GRAY);
	imshow("test", roi_gray_image);
	waitKey(1000);

	//中值滤波 增强边缘




	//Candy 边缘检测
	Mat candy_roi_image;
	Canny(roi_gray_image, candy_roi_image, 450, 120, 3);
	imshow("test", candy_roi_image);
	imwrite("candy_roi_image.jpg", candy_roi_image);
	waitKey(1000);
	//二值化
	Mat roi_threadhold_image;
	threshold(candy_roi_image, roi_threadhold_image, 50, 255, CV_THRESH_BINARY);
	imshow("test", roi_threadhold_image);
	waitKey(1000);
	imwrite("roi_threadhold_image.jpg", roi_threadhold_image);
	//平滑处理 中值滤波
	//Mat roi_blurr_image;
	//medianBlur(roi_threadhold_image, roi_blurr_image, 1);
	//imshow("test", roi_blurr_image);
	//waitKey(1000);


	//查找轮廓
	Mat roi_contours_image;
	vector<vector<Point>> roi_contours;
	roi_contours_image = roi_threadhold_image.clone();
	findContours(roi_contours_image, roi_contours, CV_RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	//画出轮廓
	//drawContours(roi_contours_image, roi_contours, -1, Scalar(255), 2);
	//imshow("test", roi_contours_image);
	//waitKey(1000);


	//轮廓表示成矩形
	//轮廓表示为一个矩形  车牌提取
	vector<Point> roi_rectPoint;
	for (int i = 0; i < roi_contours.size(); i++) {
		Rect r = boundingRect(Mat(roi_contours[i]));
		//RotatedRect r = minAreaRect(Mat(contours[i]));
		cout << "contours " << i << "  height = " << r.height << "  width = " << r.width << "rate = " << ((float)r.width / r.height) << endl;
		cout << "r.x = " << r.x << "  r.y  = " << r.y << endl;




		//rectangle(large_image, r, Scalar(0, 0, 255), 1);
		Point p1, p2, p3, p4;
		p1.x = r.x;
		p1.y = r.y;
		p2.x = r.x + r.width;
		p2.x = r.y;
		p3.x = r.x + r.width;
		p3.y = r.y + r.height;
		p4.x = r.x;
		p4.y = r.y + r.height;


		roi_rectPoint.push_back(p1);
		roi_rectPoint.push_back(p2);
		roi_rectPoint.push_back(p3);
		roi_rectPoint.push_back(p4);
		for (int j = 0; j < roi_contours[i].size(); j++) {
			cout << "point = " << roi_contours[i][j] << endl;
		}
	}
	imshow("test", roi_threadhold_image);
	waitKey(1000);


	//矩形轮廓特征提取
	int contours_height[30], contours_width[30];
	for (int i = 0; i < roi_contours.size(); i++) {
		Rect r = boundingRect(Mat(roi_contours[i]));
		contours_height[i] = r.height;
		contours_width[i] = r.width;
		cout << "contours_height = " << r.height << " contours_width = " << r.width << endl;
	}


	//判断字符水平位置
	int roi_col = roi_threadhold_image.cols, roi_row = roi_threadhold_image.rows, position1[50], position2[50], roi_width[50];
	uchar pix;
	//cout << roi_threadhold_image << endl;

	//确认为1 的像素
	int pixrow[1000];
	for (int i = 0; i < roi_col - 1; i++) {
		for (int j = 0; j < roi_row - 1; j++) {
			pix = roi_threadhold_image.at<uchar>(j, i);
			pixrow[i] = 0;
			if (pix > 0) {
				pixrow[i] = 1;
				break;
			}
		}
	}
	//对数组进行滤波，减少突变概率
	for (int i = 2; i < roi_col - 1 - 2; i++) {
		if ((pixrow[i - 1] + pixrow[i - 2] + pixrow[i + 1] + pixrow[i + 2]) >= 3) {
			pixrow[i] = 1;
		}
		else if ((pixrow[i - 1] + pixrow[i - 2] + pixrow[i + 1] + pixrow[i + 2]) <= 1) {
			pixrow[i] = 0;
		}
	}
	//确认字符位置
	int count = 0;
	bool flage = false;
	for (int i = 0; i < roi_col - 1; i++) {
		pix = pixrow[i];
		if (pix == 1 && !flage) {
			flage = true;
			position1[count] = i;
			continue;
		}
		if (pix == 0 && flage) {
			flage = false;
			position2[count] = i;
			count++;
		}
		if (i == (roi_col - 2) && flage) {
			flage = false;
			position2[count] = i;
			count++;
		}
	}
	//记录所有字符宽度
	for (int n = 0; n < count; n++) {
		cout << " position1 = " << position2[n] << " position2 = " << position2[n] << "distance =" << (position2[n] - position1[n]) << endl;
		roi_width[n] = position2[n] - position1[n];
	}
	// 减去最大值，最小值
	int max = roi_width[0], max_index = 0;
	int min = roi_width[0], min_index = 0;
	for (int n = 1; n < count; n++) {
		if (max < roi_width[n]) {
			max = roi_width[n];
			max_index = n;
		}
		if (min > roi_width[n]) {
			min = roi_width[n];
			min_index = n;
		}
	}
	int index = 0;
	int new_roi_width[50];
	for (int i = 0; i < count; i++) {
		if (i == min_index || i == max_index) {


		}
		else {
			new_roi_width[index] = roi_width[i];
			index++;
		}
	}
	cout << "count = " << count << endl;
	for (int i = 0; i < count - 2; i++) {
		cout << "new roi width = " << new_roi_width[i] << endl;
	}
	//取后面三个值的平均值：
	int avgre = (int)((new_roi_width[count - 3] + new_roi_width[count - 4] + new_roi_width[count - 5]) / 3.0);
	cout << avgre << endl;
	//for (int i = count-3; i < count - 6; i--) {
	//if (i < 0) {
	// break;
	//}
	//cout << "count = " << new_roi_width[i] << endl;
	//}
	//字母位置信息确认
	int licenseX[10], licenseW[10], licenseNum = 0;
	int countX = 0;
	for (int i = 0; i < count; i++) {
		if (roi_width[i] >(avgre - 8) && roi_width[i] < (avgre + 8)) {
			licenseX[licenseNum] = position1[i];
			licenseW[licenseNum] = roi_width[i];
			licenseNum++;
			cout << "licenseX = " << licenseX[i] << "  roi_width  =" << roi_width[i] << endl;
			continue;
		}
		if (roi_width[i] > (avgre * 2 - 10) && roi_width[i] < (avgre * 2 + 10)) {
			licenseX[licenseNum] = position1[i];
			licenseW[licenseNum] = roi_width[i];
			licenseNum++;
			cout << "licenseX = " << licenseX[i] << "  roi_width  =" << roi_width[i] << endl;
		}
	}


	//判断字符垂直位置
	int licenseY[10], licenseH[10];
	int position3[10], position4[10];
	//确认为1 的像素
	int countYY = 0;
	int pixcol[1000], row_height[10];
	for (int temp = 0; temp < licenseNum; temp++) {
		for (int i = 0; i < roi_row - 1; i++) {
			for (int j = licenseX[temp]; j < (licenseX[temp] + licenseW[temp]); j++) {
				pix = roi_threadhold_image.at<uchar>(i, j);
				pixcol[i] = 0;
				if (pix > 0) {
					pixcol[i] = 1;
					break;
				}
			}
		}
		//对数组进行滤波，减少突变概率
		for (int i = 2; i < roi_row - 1 - 2; i++) {
			if ((pixcol[i - 1] + pixcol[i - 2] + pixcol[i + 1] + pixcol[i + 2]) >= 3) {
				pixcol[i] = 1;
			}
			else if ((pixcol[i - 1] + pixcol[i - 2] + pixcol[i + 1] + pixcol[i + 2]) <= 1) {
				pixcol[i] = 0;
			}
		}
		//确认字符位置
		int countY = 0;
		bool flage2 = false;
		for (int i = 0; i < roi_row - 1; i++) {
			pix = pixcol[i];
			if (pix == 1 && !flage2) {
				flage2 = true;
				position3[countY] = i;
				continue;
			}
			if (pix == 0 && flage2) {
				flage2 = false;
				position4[countY] = i;
				countY++;
			}
		}

		//记录所有字符宽度
		for (int n = 0; n < countY; n++) {
			cout << " position3 = " << position3[n] << " position4 = " << position4[n] << "distance =" << (position4[n] - position3[n]) << endl;
			row_height[countYY] = position4[n] - position3[n];
			licenseY[countYY] = position3[n];
			licenseH[countYY] = row_height[countYY];
		}
		countYY++;
	}

	//截取字符
	Mat licenseN = Mat(Scalar(0));
	cout << "countYY = " << countYY << endl;
	for (int i = 0; i < countYY; i++) {
		Rect rect(licenseX[i], licenseY[i], licenseW[i], licenseH[i]);
		cout << "position = " << licenseX[i] << "  " << licenseY[i] << "  " << licenseW[i] << "  " << licenseH[i] << endl;
		licenseN = large_image(rect);
		imshow("test1" + i, licenseN);
		ostringstream oss;
		oss << "licenseN" << i << ".jpg";
		imwrite(oss.str(), licenseN);
		waitKey(1000);
	}



	cout << "license plate process" << endl;






}

/*
void CMyVisionToolDlg::OnBnClickedBtnPlateextract()
{
	if (!prePro.data)
	{
		string info = "Error::The picture cannot be empty";
		StateInfo(info, STATE_ERROR);
		return;
	}
	else if (prePro.channels() > 1)
	{
		string info = "Error::The picture channels cannot be greater than 1";
		StateInfo(info, STATE_ERROR);
		return;
	}
	Mat stretchImage;
	stretchImage = Mat::zeros(prePro.size(), prePro.type());
	// 拉伸，标定为0.1   0.9
	Stretch(prePro, stretchImage, 0, 255);

	Mat erodeImage;
	Mat structureElement = getStructuringElement(MORPH_RECT, Size(m_size, m_size), Point(-1, -1));
	erode(prePro, erodeImage, structureElement);

	// 拉伸和腐蚀的绝对差值
	Mat subImage;
	absdiff(stretchImage, erodeImage, subImage);

	// OSTU 二值化
	Mat binaryImage;
	threshold(subImage, binaryImage, 0, 255, THRESH_OTSU);

	// 对图像进行中值滤波，核采用矩阵(1,1,1,1,1)的转置
	// 定义中值滤波图像
	Mat filterImage;
	// 先复制一下要进行中值滤波的图像，因为前两行和最后两行没有进行处理
	filterImage = binaryImage.clone();
	MiddleSmooth(binaryImage, filterImage);

	// 对二值图像做腐蚀处理，去除噪声，采用矩阵（1,1,1）的转置作为核
	// 定义腐蚀后的图像
	Mat kernelErodeImage;
	structureElement = getStructuringElement(MORPH_RECT, Size(1, 3), Point(-1, -1));
	erode(filterImage, kernelErodeImage, structureElement, Point(-1, -1), 2);

	// 对二值图像做膨胀处理，去除噪声，采用矩阵（1,1,1）的转置作为核
	// 定义膨胀后的图像
	Mat kernelDilateImage;
	dilate(kernelErodeImage, kernelDilateImage, structureElement, Point(-1, -1), 1);

	// 对车辆图像做水平投影
	// 定义像素累加和数组，图像高度不应大于2048
	int level_shadow[2048];
	int height = prePro.rows;
	int width = prePro.cols;
	Scalar shadow;
	memset(level_shadow, 0, sizeof(level_shadow));

	// 遍历图像做水平投影
	for (int y = height - 1; y >= 0; y--)
	{
		for (int x = 0; x<width; x++)
		{
			shadow = kernelDilateImage.at<uchar>(y, x);
			if (shadow.val[0] != 0)
				level_shadow[y]++; //统计每行不为零的像素的个数				
		}
	}

	// 对图像水平投影的值做聚类，如果小行数值除以大行数值的商大于小于0.6，
	// 则认为这两行不是一类，将小行数值置为0
	for (int y = height - 1; y >= 1; y--)
	{
		if (level_shadow[y - 1] != 0)
		{
			if ((float(level_shadow[y])) / (float(level_shadow[y - 1]))<0.6)
				level_shadow[y] = 0;
		}
	}

	//统计水平投影中不为零的区间
	for (int y = height - 1; y >= 0; y--)
	{
		if (level_shadow[y] != 0)
			level_shadow[y] = level_shadow[y + 1] + 1;
	}

	//求出水平投影数组中连续不为零的最大区间，此即认为是车牌大致高度
	int Y_min = 0;//车牌高度小坐标
	int Y_max = 0;//车牌高度大坐标
	int M_max_value = 0;
	M_max_value = level_shadow[0]; //把level_shadow的第一个值赋给M_max_value
	for (int y = 0; y<height; y++)
	{
		if (level_shadow[y]>M_max_value)
		{
			M_max_value = level_shadow[y];
			Y_min = y;
			Y_max = Y_min + M_max_value;
		}
	}

	if (M_max_value<10)
		AfxMessageBox("提取车牌高度失败!");

	//定义ROI区域，切割出车牌的高度
	Rect ROI_Plate_Height;
	ROI_Plate_Height.x = 0;
	ROI_Plate_Height.y = Y_min;
	ROI_Plate_Height.width = prePro.cols;
	ROI_Plate_Height.height = M_max_value;
	Mat imageRoi = kernelDilateImage(ROI_Plate_Height);

	
	pro = kernelDilateImage.clone();
	CheckFlag();
	ShowImage(SHOW_PRO);

	return;

	//对车牌高度区域做闭运算，得出车牌的矩形区域，以切割出车牌
	//运算核大小采用（车牌的高度*0.6)）
	int Copy_M_max_value = M_max_value; //复制此值，
	int Close_width = 0;
	int Close_height = 0;

	//核大小规定为奇数
	while ((Copy_M_max_value % 3) != 0)
	{
		Copy_M_max_value--;
	}
	Close_width = int(Copy_M_max_value*0.6);
	Close_height = Copy_M_max_value;
	Mat structureElement2 = getStructuringElement(MORPH_RECT, Size(Close_width, Close_height), Point(-1, -1));
	morphologyEx(imageRoi, imageRoi, CV_MOP_CLOSE, structureElement, Point(-1, -1), 1);

	// 求联通区域的最大宽度，定位车牌的横坐标
	int X_min = 0;// 车牌宽度小坐标
	int X_max = 0;// 车牌宽度大坐标
	int M_row_max_value = 0;
	int count_row[2048];// 图像宽度不应大于2048
	memset(count_row, 0, sizeof(count_row));

	//取车牌中间的一条直线进行检测,求此直线上连续不为0的像素的最大宽度，此即为车牌宽度
	int mid_height = M_max_value / 2;
	uchar* ptr_mid = imageRoi.ptr<uchar>(mid_height);
	for (int x = width - 1; x >= 0; x--)
	{
		if (ptr_mid[x] != 0)
			count_row[x] = count_row[x + 1] + 1;
	}

	// 求出count_row数组中的最大值
	int Max_value_count_row = 0;
	Max_value_count_row = count_row[0];
	for (int x = 0; x<width; x++)
	{
		if (count_row[x]>Max_value_count_row)
		{
			Max_value_count_row = count_row[x];
			X_min = x;
			X_max = X_min + Max_value_count_row;
		}
	}
	//车牌的宽度应大于高度的三倍，对切割出的车牌进行验证
	if (float(Max_value_count_row) / float(M_max_value)<3 || float(Max_value_count_row) / float(M_max_value)>6)
		AfxMessageBox("提取车牌失败!");

	//切割出车牌,对边界区域适当调整
	Rect ROI_Plate;
	ROI_Plate.x = X_min + 2;
	ROI_Plate.y = Y_min + 5;
	ROI_Plate.width = Max_value_count_row - 6;
	ROI_Plate.height = M_max_value + 3;

	//判断车牌定位区域是否合法
	if (ROI_Plate.x<0 || ROI_Plate.x>width)
		AfxMessageBox("提取车牌失败!");
	if (ROI_Plate.y<0 || ROI_Plate.y>height)
		AfxMessageBox("提取车牌失败!");
	if ((ROI_Plate.x + ROI_Plate.width)>width)
		AfxMessageBox("提取车牌失败!");
	if ((ROI_Plate.y + ROI_Plate.height)>height)
		AfxMessageBox("提取车牌失败!");

	Mat roiPlate = prePro(ROI_Plate);





	
	pro = roiPlate.clone();
	ShowImage(SHOW_PRO);
}
*/
void CMyVisionToolDlg::Stretch(Mat src, Mat dst, int min, int max)
{
	int rows = src.rows;
	int cols = src.cols;
	int low_value = min;
	int high_value = max;
	float rate = 0;
	// 清空三个数组
	float stretch_p[256], stretch_p1[256], stretch_num[256];
	memset(stretch_p, 0, sizeof(stretch_p));
	memset(stretch_p1, 0, sizeof(stretch_p1));
	memset(stretch_num, 0, sizeof(stretch_num));

	// 遍历统计各个灰度级出现次数
	for (int i = 0; i < rows; i++)
	{
		const uchar* pixel = src.ptr<uchar>(i);
		for (int j = 0; j < cols; j++)
		{
			stretch_num[pixel[j]]++;
		}
	}

	// 计算各个灰度级概率
	for (int i = 0; i<256; i++)
	{
		stretch_p[i] = stretch_num[i] / (rows*cols);
	}

	// 求存放各个灰度级卷积和
	for (int i = 0; i<256; i++)
	{
		for (int k = 0; k <= i; k++)
			stretch_p1[i] += stretch_p[k];
	}
	// 统计出两个阈值点的值
	for (int i = 0; i<256; i++)
	{
		if (stretch_p1[i]<0.1) // low_value 取接近10%的总像素的灰度值
		{
			low_value = i;
		}
		if (stretch_p1[i]>0.9) // high_value取接近90%的总像素的灰度值
		{
			high_value = i;
			break;
		}
	}
	rate = (float)255 / (high_value - low_value + 1);
	// 进行灰度拉伸
	for (int y = 0; y < rows; y++)
	{
		uchar * ptr_src = src.ptr<uchar>(y);
		uchar * ptr_dst = dst.ptr<uchar>(y);
		for (int x = 0; x < cols; x++)
		{
			if (ptr_src[x]<low_value)
			{
				ptr_dst[x] = 0;
			}
			else if (ptr_src[x]<high_value)
			{
				ptr_dst[x] = (uchar)((ptr_src[x] - low_value)*rate + 0.5);
				if (ptr_dst[x]>255)
					ptr_dst[x] = high_value;
			}
			else if (ptr_src[x] >= high_value)
			{
				ptr_dst[x] = 255;
			}
		}
	}
}

void CMyVisionToolDlg::MiddleSmooth(Mat src, Mat dst)
{
	int temp = 0;// 中间变量
	int flag = 0;//循环变量
	int pFilter_Image_Pixel[5];//窗口像素值
	int mid_pixel_value = 0;  // 中值

	//清空数组并赋初始值为0
    memset(pFilter_Image_Pixel,0,sizeof(pFilter_Image_Pixel));

	//中值滤波
	for (int i = 2; i < dst.rows - 2; i++)
	{
		uchar* pixel = src.ptr<uchar>(i);
		for (int j = 0; j < dst.cols; j++)
		{
			//把5*1屏蔽窗口的所有像素值放入pFilter_Image_Pixel[m]
			int m = 0;
			for (int y = i - 2; y <= i + 2; y++)
			{
				const uchar* pixel2 = src.ptr<uchar>(y);
				for (int x = i; x <= i; x++)
				{
					pFilter_Image_Pixel[m] = pixel2[i];
					m++;
				}
			}
			//把pFilter_Image_Pixel[m]中的值按降序排列
			do {
				flag = 0;
				for (int m = 0; m<4; m++)
				{
					if (pFilter_Image_Pixel[m]<pFilter_Image_Pixel[m + 1])
					{
						temp = pFilter_Image_Pixel[m];
						pFilter_Image_Pixel[m] = pFilter_Image_Pixel[m + 1];
						pFilter_Image_Pixel[m + 1] = temp;
						flag = 1;
					}
				}
			} while (flag == 1);
			mid_pixel_value = pFilter_Image_Pixel[2];//求中值mid_pixel_value
			pixel[j] = mid_pixel_value;//将中值赋给目标图像的当前点
		}
	}
}

void CMyVisionToolDlg::OnBnClickedPicturetransfertovideo()
{
	// Tip : 输入图像要和视频宽高一致
	// C:\Users\1000250081\Pictures\photo\2018-10-12\New folder
	// C://Users//1000250081//Pictures//photo//2018-10-12//New folder//
	Image_To_Video(10, "C://Users//1000250081//Pictures//photo//2018-10-12//New folder//", "*.jpg", "C://Users//1000250081//Pictures//photo//2018-10-12//New folder//test.avi", 30, 6000, 4000, 1);
}

// p_num : 保留字段
void CMyVisionToolDlg::Image_To_Video(int p_num, string inputPath, string inputFormat, string outputPath, int fps, int width, int height, int isColor)
{
	string picName, picPath;
	VideoWriter writer;
	writer = VideoWriter(outputPath, CV_FOURCC('X', 'V', 'I', 'D'), fps, Size(width, height), isColor);
	Mat img;
	CFileFind finder;
	string pathTemp = inputPath + inputFormat;
	// switch format  std::string 2 LPCSTR
	LPCSTR path = pathTemp.c_str();
	BOOL bWorking = finder.FindFile(path);
	while (bWorking)
	{ 
		bWorking = finder.FindNextFile();
		picName = finder.GetFileName();
		picPath = inputPath + picName;
		img = imread(picPath);
		if (!img.data)
		{
			StateInfo("Could not load image file..." + picName, STATE_INFO);
		}
		else
		{
			// TODO : Need check width and height
			// Test
			//imshow("test", img);
			writer.write(img);
		}
		if (cv::waitKey(30) == 27)
		{
			StateInfo("ESC Quit", STATE_INFO);
			break;
		}
	}
}

void CMyVisionToolDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	//把当前的页面隐藏起来
	pDialog[m_curSelTab]->ShowWindow(SW_HIDE);
	//得到新的页面索引
	m_curSelTab = m_tab.GetCurSel();
	//把新的页面显示出来
	pDialog[m_curSelTab]->ShowWindow(SW_SHOW);

	*pResult = 0;
}




void CMyVisionToolDlg::OnBnClickedBtnSurf()
{
	// TODO: Add your control notification handler code here
	Mat srcImg1 = imread("1.bmp", 1);
	Mat srcImg2 = imread("2.bmp", 1);

	if (!srcImg1.data || !srcImg2.data)
	{
		printf("Error 1");
	}

	GaussianBlur(srcImg1, srcImg1, Size(3, 3), 0.5);
	GaussianBlur(srcImg2, srcImg2, Size(3, 3), 0.5);


	Ptr<Feature2D>f2d = xfeatures2d::SURF::create(700);
	vector<KeyPoint> keyPoint1;
	vector<KeyPoint> keyPoint2;
	f2d->detect(srcImg1, keyPoint1);
	f2d->detect(srcImg2, keyPoint2);

	drawKeypoints(srcImg1, keyPoint1, srcImg1, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
	drawKeypoints(srcImg2, keyPoint2, srcImg2, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

	namedWindow("KP of src 1", 0);
	namedWindow("KP of src 2", 0);
	imshow("KP of src 1", srcImg1);
	imshow("KP of src 2", srcImg2);

	// kp match
	Mat descriptors_1, descriptors_2;
	f2d->compute(srcImg1, keyPoint1, descriptors_1);
	f2d->compute(srcImg2, keyPoint2, descriptors_2);

	BFMatcher matcher;
	vector<DMatch>matches;
	matcher.match(descriptors_1, descriptors_2, matches);

	Mat imageOutput;
	drawMatches(srcImg1, keyPoint1, srcImg2, keyPoint2, matches, imageOutput);

	namedWindow("picture of matching", 0);
	imshow("picture of matching", imageOutput);
	waitKey(0);
}


void CMyVisionToolDlg::OnBnClickedBtnHist()
{
	if (!prePro.data)
	{
		string info = "Error::The picture cannot be empty";
		StateInfo(info, STATE_ERROR);
		return;
	}
	//Mat hsv;
	//cvtColor(prePro, hsv, cv::COLOR_BGR2HSV);
	float h_ranges[] = {0, 180};
	float s_ranges[] = {0, 256};
	const float* ranges[] = {h_ranges, s_ranges};
	int histSize[] = { 30, 32 }, ch[] = { 0 };

	Mat hist;
	// compute the histogram
	//
	calcHist(&prePro, 1, ch, cv::noArray(), hist, 2, histSize, ranges, true );
	normalize(hist, hist, 0, 255, cv::NORM_MINMAX);

	int scale = 10;
	Mat hist_img(histSize[0] * scale, histSize[1] * scale, CV_8UC3);
	// Draw the histogram
	//
	for (int h = 0; h < histSize[0]; h++)
	{
		for (int s = 0; s < histSize[1]; s++)
		{
			float hval = hist.at<float>(h, s);
			cv::rectangle(
			hist_img,
			cv::Rect(h*scale, s*scale, scale, scale),
			cv::Scalar::all(hval),
		    -1
			);
		}
	}
	//cv::imshow("image", src);
	cv::imshow("H-S histogram", hist_img);
	cv::waitKey();
}



void CMyVisionToolDlg::OnBnClickedBtnEqualizehist()
{
	CheckWindowValue();
	if (!prePro.data)
	{
		string info = "Error::The picture cannot be empty";
		StateInfo(info, STATE_ERROR);
		return;
	}
	else if (prePro.channels() > 1)
	{
		string info = "Error::The picture channels cannot be greater than 1";
		StateInfo(info, STATE_ERROR);
		return;
	}
	equalizeHist(prePro, pro);
	CheckFlag();
	ShowImage(SHOW_PRO);
	StateInfo("equalize hist Success", STATE_INFO);
}


void CMyVisionToolDlg::OnBnClickedOk()
{
	ReleaseData();
	CDialogEx::OnOK();
}


void CMyVisionToolDlg::OnBnClickedCancel()
{
	ReleaseData();
	CDialogEx::OnCancel();
}

void CMyVisionToolDlg::ReleaseData()
{
	if (!src.data)
		src.release();
	if (!dst.data)
		dst.release();
	if (!prePro.data)
		prePro.release();
	if (!pro.data)
		pro.release();

}

void CMyVisionToolDlg::OnBnClickedBtnFindcontours()
{
	if (!prePro.data)
	{
		string info = "Error: The picture cannot be empty";
		StateInfo(info, STATE_ERROR);
		return;
	}

	vector<vector<cv::Point>> contours;
	findContours(prePro, contours, cv::noArray(), cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
	pro = prePro.clone();
	pro = cv::Scalar::all(0);

	int index = 0;
	double tmpLen = arcLength(contours[0], true);
	for (int i = 1; i < contours.size(); i++)
	{
		if (arcLength(contours[i], true) > tmpLen)
		{
			tmpLen = arcLength(contours[i], true);
			index = i;
		}
	}

	cv::drawContours(pro, contours, index, cv::Scalar::all(255));

	CheckFlag();
	ShowImage(SHOW_PRO);
	StateInfo("find contours Success", STATE_INFO);
}


void CMyVisionToolDlg::OnBnClickedBtnMinrect()
{
	if (!prePro.data)
	{
		string info = "Error: The picture cannot be empty";
		StateInfo(info, STATE_ERROR);
		return;
	}

	vector<vector<cv::Point>> contours;
	findContours(prePro, contours, cv::noArray(), cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE, Point(0,0));
	vector<RotatedRect> minRect(contours.size());
	vector<RotatedRect> minEllipse(contours.size());

	vector<vector<cv::Point>> maxContours;
	maxContours = contours;
	for (int i = 1; i < contours.size(); i++)
	{
		if (arcLength(contours[i], true) > arcLength(maxContours[0], true) )
		{
			maxContours[0] = contours[i];
		}
	}
	contours = maxContours;

	for (int i = 0; i < 1 ; i++) // contours.size()
	{
		minRect[i] = minAreaRect(Mat(contours[i]));
		if (contours[i].size() > 5)
		{
			minEllipse[i] = fitEllipse(Mat(contours[i]));
		}
	}

	//pro = prePro.clone();
	//pro = cv::Scalar::all(0);
	pro = src.clone();

	for (int i = 0; i < 1; i++) //contours.size()
	{
		Scalar color1 = cv::Scalar(255, 0, 0);
		Scalar color2 = cv::Scalar(0, 255, 0);

		//cv::drawContours(pro, contours, i, color, 1, 8, vector<Vec4i>(), 0, Point());
		//ellipse(pro, minEllipse[i], color1, 2, 8);
		Point2f rect_points[4];
		minRect[i].points(rect_points);
		for (int j = 0; j < 4; j++)
			line(pro, rect_points[j], rect_points[(j + 1) % 4], color2, 1, 8);
	}

	CheckFlag();
	ShowImage(SHOW_PRO);
	StateInfo("find contours Success", STATE_INFO);
}


void CMyVisionToolDlg::OnBnClickedBtnThresholdAdapt()
{
	string info = "";
	if (!prePro.data)
	{
		info = "Error::The picture cannot be empty";
		StateInfo(info, STATE_ERROR);
		return;
	}
	else if (prePro.channels() > 1)
	{
		info = "Error::The picture channels cannot be greater than 1";
		StateInfo(info, STATE_ERROR);
		return;
	}
	adaptiveThreshold(prePro, pro, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 5, 0);// THRESH_TRIANGLE // THRESH_OTSU
	CheckFlag();
	ShowImage(SHOW_PRO);
	StateInfo(info, STATE_INFO);
}


void CMyVisionToolDlg::OnBnClickedBtnCorners()
{
	string info = "";
	if (!prePro.data)
	{
		info = "Error::The picture cannot be empty";
		StateInfo(info, STATE_ERROR);
		return;
	}
	else if (prePro.channels() > 1)
	{
		info = "Error::The picture channels cannot be greater than 1";
		StateInfo(info, STATE_ERROR);
		return;
	}
	vector<Point2f> corners;
	int max_corners = 50;
	double quality_level = 0.1;
	double min_distance = 20;
	int block_size = 15;
	bool use_harris = true;
	double k = 0.04;
	goodFeaturesToTrack(prePro,
		corners,
		max_corners,
		quality_level,
		min_distance,
		Mat(),
		block_size,
		use_harris,
		k);
	for (int i = 0; i < corners.size(); i++)
	{
		circle(pro, corners[i], 10, Scalar(255, 255, 255), 2, 8, 0);
	}

	// test find rectange
	for (int i = 0; i < corners.size(); i++)
	{
		for (intr j = 0; j < length; j++)
		{

		}
	}

	CheckFlag();
	ShowImage(SHOW_PRO);
	StateInfo(info, STATE_INFO);
}


void CMyVisionToolDlg::OnBnClickedBtnHull()
{
	string info = "";
	if (!prePro.data)
	{
		info = "Error::The picture cannot be empty";
		StateInfo(info, STATE_ERROR);
		return;
	}
	else if (prePro.channels() > 1)
	{
		info = "Error::The picture channels cannot be greater than 1";
		StateInfo(info, STATE_ERROR);
		return;
	}
	vector<vector<cv::Point>> contours;
	findContours(prePro, contours, cv::noArray(), cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE, Point(0, 0));
	vector<vector<Point>> hull(contours.size());
	for (size_t i = 0; i < contours.size(); i++)
	{
		convexHull(contours[i], hull[i], false);
	}
	pro = prePro.clone();
	pro = cv::Scalar::all(0);
	for (size_t i = 0; i < contours.size(); i++)
	{
		Scalar color = Scalar(255, 255, 255);
		//drawContours(pro, contours, (int)i, color, 1, 8, vector<Vec4i>(), 0, Point());
		drawContours(pro, hull, (int)i, color, 1, 8, vector<Vec4i>(), 0, Point());
	}

	CheckFlag();
	ShowImage(SHOW_PRO);
	StateInfo(info, STATE_INFO);
}
