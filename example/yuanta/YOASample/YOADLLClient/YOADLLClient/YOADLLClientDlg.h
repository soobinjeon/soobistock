
// YOADLLClientDlg.h : ��� ����
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"

class CBasicTestDlg;
class CStockSiseDlg;
class CStockOrderDlg;
class CStockAccountDlg;
class CTransactionDlg;
class CRealtimeDlg;

// CYOADLLClientDlg ��ȭ ����
class CYOADLLClientDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CYOADLLClientDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_YOADLLCLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.

private:
	CMap<int, int, CString, CString>	m_mapReqID;
	
	CBasicTestDlg*						m_pBasicTestDlg;
	CStockSiseDlg*						m_pStockSiseDlg;
	CStockOrderDlg*						m_pStockOrderDlg;
	CStockAccountDlg*					m_pStockAccountDlg;
	CTransactionDlg*					m_pTransactionDlg;
	CRealtimeDlg*						m_pRealtimeDlg;

public:
	void LogMessage(CString strMsg, int nType = 0, BOOL bTimeStamp = TRUE);
	void InitControl();
	BOOL CheckAPI();
	BOOL CheckInit();
	BOOL CheckLogin();
	CString AccountFormat( TCHAR* pData );
	CString Commify( TCHAR* pData );
	CString Commify( long nData );
	CString Commify( double dData );

	void LoadUserInfo();

// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void OnDestroy();
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	afx_msg LRESULT OnReceiveSystemMessage(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnReceiveError(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnLoginComplete(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnReceiveData(WPARAM wParam, LPARAM lParam);

	afx_msg void OnBnClickedButtonInitial();
	afx_msg void OnBnClickedButtonLogin();
	afx_msg void OnTcnSelchangeTabPanel(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonGetAccounts();
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
	CTabCtrl m_ctrlTab;

	CComboBox m_cbServer;
};
