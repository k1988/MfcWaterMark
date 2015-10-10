
// MfcWaterMarkDlg.h : ͷ�ļ�
//

#pragma once

#include "WaterEffect.h"
#include "DIB.h"

#define ID_EFFECTTIMER 1111
#define ID_DROPTIMER 1112

// CMfcWaterMarkDlg �Ի���
class CMfcWaterMarkDlg : public CDialogEx
{
// ����
public:
	CMfcWaterMarkDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCWATERMARK_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
	CWaterEffect m_waterEffect;
	CDib m_renderSrc;
	CDib m_renderDest;
};
