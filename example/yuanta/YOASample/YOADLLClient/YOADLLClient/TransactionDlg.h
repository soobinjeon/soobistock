#pragma once


class CYOADLLClientDlg;

// CTransactionDlg 대화 상자입니다.

class CTransactionDlg : public CDialog
{
	DECLARE_DYNAMIC(CTransactionDlg)

public:
	CTransactionDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CTransactionDlg();
	
// 대화 상자 데이터입니다.
	enum { IDD = IDD_TRANSACTION_DIALOG };

// Attributes
private:
	CYOADLLClientDlg* m_pMainDlg;

	int m_nReqID;

	CString m_strDSO;

	CString m_strInBlockName;
	CString m_strInFieldName;
	CString m_strInFieldValue;
	CString m_strOutBlockName;
	CString m_strOutFieldName;
	CString m_strOutArrayBlockName;
	CString m_strOutArrayFieldName;

	int m_nInArrayIndex;
	int m_nOutArrayIndex;
	CListCtrl m_ctrlInBlocks;
	CListCtrl m_ctrlOutBlocks;
	CListCtrl m_ctrlOutArrayBlock;

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

private:
	void AddBlockItem( CString strBlockName, CString strFieldName, CString strFieldValue, int nIndex = 0, BOOL bInBlock = TRUE );

public:
	LRESULT OnReceiveError(WPARAM wParam, LPARAM lParam);
	LRESULT OnReceiveData(WPARAM wParam, LPARAM lParam);

	afx_msg void OnBnClickedButtonDsoInit();
	afx_msg void OnBnClickedButtonRequest();
	afx_msg void OnBnClickedButtonNextRequest();
	afx_msg void OnBnClickedButtonInAdd();
	afx_msg void OnBnClickedButtonInDel();
	afx_msg void OnBnClickedButtonOutAdd();
	afx_msg void OnBnClickedButtonOutDel();
	afx_msg void OnBnClickedButtonOutArrayAdd();
	afx_msg void OnBnClickedButtonOutArrayDel();
	afx_msg void OnHdnItemclickListArrayOutblock(NMHDR *pNMHDR, LRESULT *pResult);

	DECLARE_MESSAGE_MAP()
};
