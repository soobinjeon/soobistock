#pragma once
#include "afxwin.h"


class CYOADLLClientDlg;

// CRealtimeDlg ��ȭ �����Դϴ�.

class CRealtimeDlg : public CDialog
{
	DECLARE_DYNAMIC(CRealtimeDlg)

public:
	CRealtimeDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CRealtimeDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_REALTIME_DIALOG };

// Attributes
private:
	CYOADLLClientDlg* m_pMainDlg;

	CString m_strAutoID;

	CString m_strInBlockName;
	CString m_strInFieldName;
	CString m_strInFieldValue;
	CString m_strOutBlockName;
	CString m_strOutFieldName;

	CListCtrl m_ctrlInBlocks;
	CListCtrl m_ctrlOutBlocks;

// Operations
public:
	void SetMainDlg( CYOADLLClientDlg* pMainDlg ) { m_pMainDlg = pMainDlg; }
	void InitControl();
	void SetSample();
	BOOL CheckAPI();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();

public:
	LRESULT OnReceiveError(WPARAM wParam, LPARAM lParam);
	LRESULT OnReceiveRealData(WPARAM wParam, LPARAM lParam);

	afx_msg void OnBnClickedButtonAutoInit();
	afx_msg void OnBnClickedButtonAutoRegist();
	afx_msg void OnBnClickedButtonAutoUnregist();
	afx_msg void OnBnClickedButtonAutoInAdd();
	afx_msg void OnBnClickedButtonAutoInDel();
	afx_msg void OnBnClickedButtonAutoOutAdd();
	afx_msg void OnBnClickedButtonAutoOutDel();

	DECLARE_MESSAGE_MAP()
	CListBox m_ctrlLog;
};
