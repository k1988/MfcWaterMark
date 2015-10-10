
// MfcWaterMarkDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MfcWaterMark.h"
#include "MfcWaterMarkDlg.h"
#include "afxdialogex.h"
#include "Resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMfcWaterMarkDlg �Ի���



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


// CMfcWaterMarkDlg ��Ϣ�������

BOOL CMfcWaterMarkDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	//CPictureHolder tmpPic;
	//tmpPic.CreateFromBitmap(IDB_BITMAP1);
	
	CBitmap tmpPic;
	BOOL result = tmpPic.LoadBitmapW(IDB_BITMAP1);
	m_renderSrc.Create32BitFromPicture(tmpPic, 700, 200);
	m_renderDest.Create32BitFromPicture(tmpPic, 700, 200);

	m_waterEffect.Create(700, 200);
	SetTimer(ID_EFFECTTIMER, 40, NULL);
	SetTimer(ID_DROPTIMER, 1500, NULL);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMfcWaterMarkDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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
