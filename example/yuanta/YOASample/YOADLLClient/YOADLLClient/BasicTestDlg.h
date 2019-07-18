#pragma once
#include "afxwin.h"


class CYOADLLClientDlg;

// CBasicTestDlg 대화 상자입니다.

class CBasicTestDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CBasicTestDlg)

public:
	CBasicTestDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CBasicTestDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_BASICTEST_DIALOG };

// Attributes
private:
	CYOADLLClientDlg* m_pMainDlg;
	int	m_nReqID_300001;
	int	m_nReqID_160001;

// Operations
public:
	void SetMainDlg( CYOADLLClientDlg* pMainDlg ) { m_pMainDlg = pMainDlg; }
	void LogMessage( CString strMsg );

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedButtonSearch();
	afx_msg void OnBnClickedButtonAutoRegist();
	afx_msg void OnBnClickedButtonAutoUnRegist();
	LRESULT OnReceiveError(WPARAM wParam, LPARAM lParam);
	LRESULT OnReceiveData(WPARAM wParam, LPARAM lParam);
	LRESULT OnReceiveRealData(WPARAM wParam, LPARAM lParam);
public:
	CString m_strJongCode;
	CListBox m_lbLog;
};
