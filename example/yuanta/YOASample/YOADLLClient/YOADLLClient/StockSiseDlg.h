#pragma once
#include "afxcmn.h"
#include "afxwin.h"


class CYOADLLClientDlg;

// CStockSiseDlg 대화 상자입니다.

class CStockSiseDlg : public CDialog
{
	DECLARE_DYNAMIC(CStockSiseDlg)

public:
	CStockSiseDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CStockSiseDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_STOCKSISE_DIALOG };

// Attributes
private:
	CYOADLLClientDlg* m_pMainDlg;
	
	long m_nPrevLastPrice;
	long m_nMedoDebiTot;
	long m_nMesuDebiTot;
	long m_nMedoTot;
	long m_nMesuTot;

	int m_nCurJukaColor;
	int m_nStartJukaColor;
	int m_nHighJukaColor;
	int m_nLowJukaColor;
	int	m_nDebiColor;
	int m_nDebiRateColor;

	int	m_nReqID_300001;
	int	m_nReqID_300002;
	int	m_nReqID_301004;
	BOOL m_bNext_301004;

	CArray<int, int> m_arrHogaColor;
	CArray<int, int> m_arrMedosuDebiColor;

// Operations
public:
	void SetMainDlg( CYOADLLClientDlg* pMainDlg ) { m_pMainDlg = pMainDlg; }
	void InitControl();

	BOOL CheckAPI();
	CString Commify( TCHAR* pData );
	CString Commify( long nData );
	CString Commify( double dData );
	void Process300001();
	void Process300002();
	void Process301004();
	
	void RegistAuto( CString strAutoID, CString strCode );
	void UnregistAuto();
	void ProcessAuto11();
	void ProcessAuto12();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedButtonSearch();
	afx_msg void OnBnClickedButtonNext();
	afx_msg void OnNMCustomdrawListHoga(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawListHogaFooter(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawListConTick(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawListDaily(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	LRESULT OnReceiveError(WPARAM wParam, LPARAM lParam);
	LRESULT OnReceiveData(WPARAM wParam, LPARAM lParam);
	LRESULT OnReceiveRealData(WPARAM wParam, LPARAM lParam);

public:
	CListCtrl m_ctrlHogaHeader;
	CListCtrl m_ctrlHoga;
	CListCtrl m_ctrlHogaFooter;
	CListCtrl m_ctrlConTickHeader;
	CListCtrl m_ctrlConTick;
	CListCtrl m_ctrlDailyHeader;
	CListCtrl m_ctrlDaily;
	CString m_strJongCode;
	CStatic m_ctrlJongName;

};
