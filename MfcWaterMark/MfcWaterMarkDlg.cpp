
// MfcWaterMarkDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MfcWaterMark.h"
#include "MfcWaterMarkDlg.h"
#include "afxdialogex.h"
#include "Resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMfcWaterMarkDlg 对话框



CMfcWaterMarkDlg::CMfcWaterMarkDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFCWATERMARK_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMfcWaterMarkDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMfcWaterMarkDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CMfcWaterMarkDlg 消息处理程序

BOOL CMfcWaterMarkDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	//CPictureHolder tmpPic;
	//tmpPic.CreateFromBitmap(IDB_BITMAP1);
	
	CBitmap tmpPic;
	BOOL result = tmpPic.LoadBitmapW(IDB_BITMAP1);
	m_renderSrc.Create32BitFromPicture(tmpPic, 700, 200);
	m_renderDest.Create32BitFromPicture(tmpPic, 700, 200);

	m_waterEffect.Create(700, 200);
	SetTimer(ID_EFFECTTIMER, 40, NULL);
	SetTimer(ID_DROPTIMER, 1500, NULL);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMfcWaterMarkDlg::OnPaint()
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
HCURSOR CMfcWaterMarkDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMfcWaterMarkDlg::OnTimer(UINT_PTR nIDEvent)
{
	//CClientDC dc(this);
	//CPoint ptOrigin(15, 20);
	//m_renderDest.Draw(&dc, ptOrigin);

	if (nIDEvent == ID_EFFECTTIMER)
	{
		m_waterEffect.Render((DWORD*)m_renderSrc.GetDIBits(), (DWORD*)m_renderDest.GetDIBits());
		CClientDC dc(this);
		CPoint ptOrigin(15, 20);
		m_renderDest.Draw(&dc, ptOrigin);
	}
	if (nIDEvent == ID_DROPTIMER)
	{
		CRect r;
		r.left = 15;
		r.top = 20;
		r.right = r.left + m_renderSrc.GetWidth();
		r.bottom = r.top + m_renderSrc.GetHeight();
		m_waterEffect.Blob(random(r.left, r.right), random(r.top, r.bottom), 10, 800, m_waterEffect.m_iHpage);
	}
	__super::OnTimer(nIDEvent);
}

void CMfcWaterMarkDlg::OnMouseMove(UINT nFlags, CPoint point)
{
    CRect r;
    r.left = 15;
    r.top = 20;
    r.right = r.left + m_renderSrc.GetWidth();
    r.bottom = r.top + m_renderSrc.GetHeight();

#define image_height 200
    if(r.PtInRect(point) == TRUE)
    {
        // dibs are drawn upside down...
        point.y -= 20;
        point.y = image_height-point.y;

        if (nFlags & MK_LBUTTON)
            m_waterEffect.Blob(point.x -15,point.y,15, 1200,m_waterEffect.m_iHpage);
        else
            m_waterEffect.Blob(point.x -15,point.y,7,50,m_waterEffect.m_iHpage);

    }
	__super::OnMouseMove(nFlags, point);
}
