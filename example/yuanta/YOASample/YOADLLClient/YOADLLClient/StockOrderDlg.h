#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "afxdtctl.h"

class CYOADLLClientDlg;

// CStockOrderDlg 대화 상자입니다.

class CStockOrderDlg : public CDialog
{
	DECLARE_DYNAMIC(CStockOrderDlg)

public:
	CStockOrderDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CStockOrderDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_STOCKORDER_DIALOG };

// Attributes
private:
	CYOADLLClientDlg* m_pMainDlg;
	int m_nOrderType;
	CMapStringToString m_mapAccount;
	int m_nReqID_300001;
	int m_nReqID_mesu;
	int m_nReqID_medo;
	int m_nReqID_210006;
	int m_nReqID_201007;

	int m_nCurJukaColor;
	int m_nStartJukaColor;
	int m_nHighJukaColor;
	int m_nLowJukaColor;
	int m_nMedoHokaColor;
	int m_nMesuHokaColor;

	CArray<int, int> m_arrJongTypeColor1;
	CArray<int, int> m_arrJongTypeColor2;

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

	void CalcTotPrice( long nOrderPrice, long nOrderQuantity );
	void Process300001();
	void Process210006();
	void Process201007();

	void RegistAuto( CString strAutoID, CString strCode );
	void UnregistAuto();
	void ProcessAuto11();
	void ProcessAuto70();
	void ProcessAuto74();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnNMCustomdrawListJongInfo(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCbnSelchangeComboAccount();
	afx_msg void OnCbnSelchangeComboOrderType();
	afx_msg void OnEnChangeEditOrderPrice();
	afx_msg void OnEnChangeEditOrderQuantity();
	afx_msg void OnBnClickedButtonSearch();
	afx_msg void OnBnClickedButtonSearchMiChegyul();
	afx_msg void OnBnClickedButtonSearchChegyul();
	afx_msg void OnBnClickedButtonOrder();
	afx_msg void OnNMCustomdrawListMiChegyul(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawListChegyul(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTcnSelchangeTabMedosu(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinPrice(NMHDR *pNMHDR, LRESULT *pResult);
	LRESULT OnReceiveError(WPARAM wParam, LPARAM lParam);
	LRESULT OnReceiveData(WPARAM wParam, LPARAM lParam);
	LRESULT OnReceiveRealData(WPARAM wParam, LPARAM lParam);

public:
	CListCtrl m_ctrlJongInfo;
	CListCtrl m_ctrlMiChegyulHeader;
	CListCtrl m_ctrlMiChegyul;
	CListCtrl m_ctrlChegyulHeader;
	CListCtrl m_ctrlChegyul;
	
	CComboBox m_cbAccount;
	CMFCButton m_btnMesu;
	
	CString m_strJongCode;
	CComboBox m_cbOrderType;
	
	long m_nOrderPrice;
	long m_nOrderQuantity;
	CString m_strAcctPassword;
	CTabCtrl m_tabMedosu;
	
	CSpinButtonCtrl m_spinQty;
	CDateTimeCtrl m_ctrlDatePicker;
	afx_msg void OnLvnItemchangedListJongInfo(NMHDR *pNMHDR, LRESULT *pResult);
};
