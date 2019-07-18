
// YOADLLClient_MultiByteDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"


// CYOADLLClient_MultiByteDlg ��ȭ ����
class CYOADLLClient_MultiByteDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CYOADLLClient_MultiByteDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_YOADLLCLIENT_MULTIBYTE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.

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

// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
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
