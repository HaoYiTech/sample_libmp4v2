
// sample_libmp4v2Dlg.h : ͷ�ļ�
//

#pragma once


// Csample_libmp4v2Dlg �Ի���
class Csample_libmp4v2Dlg : public CDialogEx
{
// ����
public:
	Csample_libmp4v2Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_SAMPLE_LIBMP4V2_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};
