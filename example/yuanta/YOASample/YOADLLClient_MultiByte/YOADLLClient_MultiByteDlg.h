
// YOADLLClient_MultiByteDlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"


// CYOADLLClient_MultiByteDlg 대화 상자
class CYOADLLClient_MultiByteDlg : public CDialogEx
{
// 생성입니다.
public:
	CYOADLLClient_MultiByteDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_YOADLLCLIENT_MULTIBYTE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.

// Attributes
private:
	int	m_nReqID_300001;
	BOOL m_bStruct;

public:
	void LogMessage(CString strMsg, int nType = 0, BOOL bTimeStamp = TRUE);
	BOOL CheckAPI();
	BOOL CheckInit();
	BOOL CheckLogin();
	CString AccountFormat( TCHAR* pData );

// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	afx_msg LRESULT OnReceiveSystemMessage(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnReceiveError(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnLoginComplete(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnReceiveData(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnReceiveRealData(WPARAM wParam, LPARAM lParam);

	afx_msg void OnBnClickedButtonInitial();
	afx_msg void OnBnClickedButtonLogin();
	afx_msg void OnBnClickedButtonLogout();
	afx_msg void OnBnClickedButtonGetAccounts();

	afx_msg void OnBnClickedButtonSearch();
	afx_msg void OnBnClickedButtonSearch2();
	afx_msg void OnBnClickedButtonAutoRegist();
	afx_msg void OnBnClickedButtonAutoUnRegist();

	afx_msg void OnDestroy();

	DECLARE_MESSAGE_MAP()

public:	
	CListBox m_lbLog;
	CString m_strLoginID;
	CString m_strLoginPwd;
	CString m_strCertPwd;
	CButton m_btnInitial;
	CButton m_btnLogin;
	CButton m_btnLogout;
	CButton m_btnGetAcctList;
	CListCtrl m_listAccount;
	CString m_strJongCode;
	
	CComboBox m_cbServer;
};
