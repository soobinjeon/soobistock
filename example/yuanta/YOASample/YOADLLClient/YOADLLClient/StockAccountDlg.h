#pragma once


class CYOADLLClientDlg;

// CStockAccountDlg 대화 상자입니다.

class CStockAccountDlg : public CDialog
{
	DECLARE_DYNAMIC(CStockAccountDlg)

public:
	CStockAccountDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CStockAccountDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_STOCKACCOUNT_DIALOG };

// Attributes
private:
	CYOADLLClientDlg* m_pMainDlg;
	CMapStringToString m_mapAccount;

	int	m_nReqID_204006;
	int	m_nReqID_211010;

// Operations
public:
	void SetMainDlg( CYOADLLClientDlg* pMainDlg ) { m_pMainDlg = pMainDlg; }
	void InitControl();
	void InitAccount();
	void AddAccount( TCHAR* strAccount, TCHAR* strAcctName );

	BOOL CheckAPI();
	CString Commify( TCHAR* pData );
	CString Commify( long nData );
	CString Commify( double dData );
	void Process204006();
	void Process211010();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeComboAccount();
	afx_msg void OnBnClickedButtonSearch();
	afx_msg void OnNMCustomdrawListInfo1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawListInfo2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawListInfo3_4(NMHDR *pNMHDR, LRESULT *pResult);
	DECLARE_MESSAGE_MAP()
	LRESULT OnReceiveError(WPARAM wParam, LPARAM lParam);
	LRESULT OnReceiveData(WPARAM wParam, LPARAM lParam);
	LRESULT OnReceiveRealData(WPARAM wParam, LPARAM lParam);

public:
	CComboBox m_cbAccount;
	CString m_strAcctPassword;
	CListCtrl m_ctrlInfoHeader1;
	CListCtrl m_ctrlInfo1;
	CListCtrl m_ctrlInfo2;
	CListCtrl m_ctrlInfo3;
	CListCtrl m_ctrlInfo4;
};
