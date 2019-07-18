#pragma once
#include "afxwin.h"


class CYOADLLClientDlg;

// CRealtimeDlg 대화 상자입니다.

class CRealtimeDlg : public CDialog
{
	DECLARE_DYNAMIC(CRealtimeDlg)

public:
	CRealtimeDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CRealtimeDlg();

// 대화 상자 데이터입니다.
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
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
