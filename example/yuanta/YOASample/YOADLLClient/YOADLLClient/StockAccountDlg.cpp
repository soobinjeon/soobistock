// StockAccountDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "YOADLLClient.h"
#include "StockAccountDlg.h"
#include "afxdialogex.h"
#include "../../include/MessageDef.h"
#include "YOADLLClientDlg.h"


// CStockAccountDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CStockAccountDlg, CDialog)

CStockAccountDlg::CStockAccountDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStockAccountDlg::IDD, pParent)
	, m_strAcctPassword(_T(""))
{
	m_pMainDlg = NULL;

	m_nReqID_204006 = -1;
	m_nReqID_211010 = -1;
}

CStockAccountDlg::~CStockAccountDlg()
{
}

void CStockAccountDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_ACCOUNT, m_cbAccount);
	DDX_Text(pDX, IDC_EDIT_ACCOUNT_PWD, m_strAcctPassword);
	DDX_Control(pDX, IDC_LIST_INFOHEADER1, m_ctrlInfoHeader1);
	DDX_Control(pDX, IDC_LIST_INFO1, m_ctrlInfo1);
	DDX_Control(pDX, IDC_LIST_INFO2, m_ctrlInfo2);
	DDX_Control(pDX, IDC_LIST_INFO3, m_ctrlInfo3);
	DDX_Control(pDX, IDC_LIST_INFO4, m_ctrlInfo4);
}

BEGIN_MESSAGE_MAP(CStockAccountDlg, CDialog)
	ON_MESSAGE(WMU_RECEIVE_ERROR, OnReceiveError)
	ON_MESSAGE(WMU_RECEIVE_DATA, OnReceiveData)
	ON_MESSAGE(WMU_RECEIVE_REAL_DATA, OnReceiveRealData)
	ON_CBN_SELCHANGE(IDC_COMBO_ACCOUNT, &CStockAccountDlg::OnCbnSelchangeComboAccount)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, &CStockAccountDlg::OnBnClickedButtonSearch)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST_INFO1, &CStockAccountDlg::OnNMCustomdrawListInfo1)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST_INFO2, &CStockAccountDlg::OnNMCustomdrawListInfo2)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST_INFO3, &CStockAccountDlg::OnNMCustomdrawListInfo3_4)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST_INFO4, &CStockAccountDlg::OnNMCustomdrawListInfo3_4)
END_MESSAGE_MAP()

void CStockAccountDlg::InitControl()
{
	m_cbAccount.AddString( _T("���¹�ȣ") );
	m_cbAccount.SetCurSel( 0 );

	m_ctrlInfoHeader1.InsertColumn(0, _T(""), LVCFMT_CENTER, 0);
	m_ctrlInfoHeader1.InsertColumn(1, _T("����"), LVCFMT_CENTER, 125);
	m_ctrlInfoHeader1.InsertColumn(2, _T("���� ������"), LVCFMT_CENTER,	150);
	m_ctrlInfoHeader1.InsertColumn(3, _T("�ż� �ŵ� ����"), LVCFMT_CENTER,	150);
	m_ctrlInfoHeader1.InsertColumn(4, _T("��ü ���� �ҿ��"), LVCFMT_CENTER,	150);

	m_ctrlInfo1.SetExtendedStyle( m_ctrlInfo1.GetExtendedStyle() | LVS_EX_GRIDLINES );
	m_ctrlInfo1.InsertColumn(0, _T(""), LVCFMT_CENTER, 0);
	m_ctrlInfo1.InsertColumn(1, _T("����"), LVCFMT_CENTER, 124);
	m_ctrlInfo1.InsertColumn(2, _T("���� ������"), LVCFMT_RIGHT,	150);
	m_ctrlInfo1.InsertColumn(3, _T("�ż� �ŵ� ����"), LVCFMT_RIGHT,	150);
	m_ctrlInfo1.InsertColumn(4, _T("��ü ���� �ҿ��"), LVCFMT_RIGHT,	150);
	m_ctrlInfo1.InsertItem( 0, _T("") );
	m_ctrlInfo1.InsertItem( 1, _T("") );
	m_ctrlInfo1.InsertItem( 2, _T("") );
	m_ctrlInfo1.SetItemText( 0, 1, _T("D+1") );
	m_ctrlInfo1.SetItemText( 1, 1, _T("D+2") );

	m_ctrlInfo2.SetExtendedStyle( m_ctrlInfo2.GetExtendedStyle() | LVS_EX_GRIDLINES );
	m_ctrlInfo2.InsertColumn(0, _T(""), LVCFMT_CENTER, 0);
	m_ctrlInfo2.InsertColumn(1, _T("��Ź�Ѿ�"), LVCFMT_CENTER, 124);
	m_ctrlInfo2.InsertColumn(2, _T(""), LVCFMT_RIGHT,	150);
	m_ctrlInfo2.InsertColumn(3, _T("ELW����⺻��Ź��"), LVCFMT_CENTER,	150);
	m_ctrlInfo2.InsertColumn(4, _T(""), LVCFMT_RIGHT,	150);
	m_ctrlInfo2.InsertItem( 0, _T("") );
	m_ctrlInfo2.SetItemText( 0, 1, _T("��Ź�Ѿ�") );
	m_ctrlInfo2.SetItemText( 0, 3, _T("ELW����⺻��Ź��") );

	m_ctrlInfo3.SetExtendedStyle( m_ctrlInfo2.GetExtendedStyle() | LVS_EX_GRIDLINES );
	m_ctrlInfo3.InsertColumn(0, _T(""), LVCFMT_LEFT, 0);
	m_ctrlInfo3.InsertColumn(1, _T("����"), LVCFMT_LEFT, 115);
	m_ctrlInfo3.InsertColumn(2, _T(""), LVCFMT_RIGHT,	137);

	m_ctrlInfo4.SetExtendedStyle( m_ctrlInfo2.GetExtendedStyle() | LVS_EX_GRIDLINES );
	m_ctrlInfo4.InsertColumn(0, _T(""), LVCFMT_LEFT, 0);
	m_ctrlInfo4.InsertColumn(1, _T("����"), LVCFMT_LEFT, 115);
	m_ctrlInfo4.InsertColumn(2, _T(""), LVCFMT_RIGHT,	137);

	TCHAR* title3[] = {	_T("  ������"), 
						_T("  ��Ź��������"), 
						_T("  ��Ź���Ŵ��"), 
						_T("  ���ݹ̼�"), 
						_T("  ����"), 
						_T("  �����ֹ���"), 
						_T("  �ֹ����ɱݾ�"), 
						_T("  ��ݰ��ɱݾ�"), 
						_T("  ��ǥ�Աݾ�"), 
						_T("  ��Ÿ��ǥ�ݾ�"), 
						NULL };
	TCHAR* title4[] = {	_T("  �ſ뼳��������"), 
						_T("  �ſ뺸������"), 
						_T("  �ſ뺸�����"), 
						_T("  �ſ�㺸����"), 
						_T("  �ſ�㺸���"), 
						_T("  �߰��㺸����"), 
						_T("  �߰��㺸���"), 
						_T("  �Ǹ�����"), 
						_T("  ���ڱ��հ�"), 
						_T("  ���ֱ��հ�"), 
						NULL };
	for ( int i = 0; i < 10; i++ )
	{
		m_ctrlInfo3.InsertItem( i, _T("") );
		m_ctrlInfo4.InsertItem( i, _T("") );

		m_ctrlInfo3.SetItemText( i, 1, title3[i] );
		m_ctrlInfo4.SetItemText( i, 1, title4[i] );
	}
}

void CStockAccountDlg::InitAccount()
{
	m_mapAccount.RemoveAll();
	m_cbAccount.ResetContent();

	m_cbAccount.AddString( _T("���¹�ȣ") );
	m_cbAccount.SetCurSel( 0 );
}

void CStockAccountDlg::AddAccount( TCHAR* strAccount, TCHAR* strAcctName )
{
	m_mapAccount.SetAt( strAccount, strAcctName );
	m_cbAccount.AddString( m_pMainDlg->AccountFormat(strAccount) );
}

BOOL CStockAccountDlg::CheckAPI()
{
	if ( NULL == m_pMainDlg )
		return FALSE;

	return m_pMainDlg->CheckAPI();
}

CString CStockAccountDlg::Commify( TCHAR* pData )
{
	if ( NULL == m_pMainDlg )
		return _T("");

	return m_pMainDlg->Commify( pData );
}

CString CStockAccountDlg::Commify( long nData )
{
	if ( NULL == m_pMainDlg )
		return _T("");

	return m_pMainDlg->Commify( nData );
}

CString CStockAccountDlg::Commify( double dData )
{
	if ( NULL == m_pMainDlg )
		return _T("");

	return m_pMainDlg->Commify( dData );
}

void CStockAccountDlg::Process204006()
{
	TCHAR data[1024] = {0,};
	double dData = 0;
	
	g_iYuantaAPI.YOA_GetTRFieldDouble( _T("204006"), _T("OutBlock1"), _T("yesu_amt1"), &dData );
	m_ctrlInfo1.SetItemText( 0, 2, Commify(dData) );

	g_iYuantaAPI.YOA_GetTRFieldDouble( _T("204006"), _T("OutBlock1"), _T("maedosu_amt1"), &dData );
	m_ctrlInfo1.SetItemText( 0, 3, Commify(dData) );

	g_iYuantaAPI.YOA_GetTRFieldDouble( _T("204006"), _T("OutBlock1"), _T("yeonche_amt1"), &dData );
	m_ctrlInfo1.SetItemText( 0, 4, Commify(dData) );

	g_iYuantaAPI.YOA_GetTRFieldDouble( _T("204006"), _T("OutBlock1"), _T("yesu_amt2"), &dData );
	m_ctrlInfo1.SetItemText( 1, 2, Commify(dData) );

	g_iYuantaAPI.YOA_GetTRFieldDouble( _T("204006"), _T("OutBlock1"), _T("maedosu_amt2"), &dData );
	m_ctrlInfo1.SetItemText( 1, 3, Commify(dData) );

	g_iYuantaAPI.YOA_GetTRFieldDouble( _T("204006"), _T("OutBlock1"), _T("yeonche_amt2"), &dData );
	m_ctrlInfo1.SetItemText( 1, 4, Commify(dData) );

	memset( data, 0x00, sizeof(data) );
	g_iYuantaAPI.YOA_GetTRFieldString( _T("204006"), _T("OutBlock5"), _T("d1_date"), data, sizeof(data) );
	m_ctrlInfo1.SetItemText( 0, 1, data );

	memset( data, 0x00, sizeof(data) );
	g_iYuantaAPI.YOA_GetTRFieldString( _T("204006"), _T("OutBlock5"), _T("d1_date"), data, sizeof(data) );
	m_ctrlInfo1.SetItemText( 1, 1, data );

	g_iYuantaAPI.YOA_GetTRFieldDouble( _T("204006"), _T("OutBlock2"), _T("yesu_amt1"), &dData );
	m_ctrlInfo3.SetItemText( 0, 2, Commify(dData) );

	g_iYuantaAPI.YOA_GetTRFieldDouble( _T("204006"), _T("OutBlock2"), _T("we_margin_hyun_amt"), &dData );
	m_ctrlInfo3.SetItemText( 1, 2, Commify(dData) );

	g_iYuantaAPI.YOA_GetTRFieldDouble( _T("204006"), _T("OutBlock2"), _T("we_margin_dae_amt"), &dData );
	m_ctrlInfo3.SetItemText( 2, 2, Commify(dData) );

	g_iYuantaAPI.YOA_GetTRFieldDouble( _T("204006"), _T("OutBlock2"), _T("hyun_misu_amt"), &dData );
	m_ctrlInfo3.SetItemText( 3, 2, Commify(dData) );

	g_iYuantaAPI.YOA_GetTRFieldDouble( _T("204006"), _T("OutBlock2"), _T("dan_jumun_amt"), &dData );
	m_ctrlInfo3.SetItemText( 4, 2, Commify(dData) );

	g_iYuantaAPI.YOA_GetTRFieldDouble( _T("204006"), _T("OutBlock2"), _T("daeyounggum_amt"), &dData );
	m_ctrlInfo3.SetItemText( 5, 2, Commify(dData) );

	g_iYuantaAPI.YOA_GetTRFieldDouble( _T("204006"), _T("OutBlock2"), _T("jumun_poss_hyun_amt"), &dData );
	m_ctrlInfo3.SetItemText( 6, 2, Commify(dData) );

	g_iYuantaAPI.YOA_GetTRFieldDouble( _T("204006"), _T("OutBlock2"), _T("chul_poss_amt"), &dData );
	m_ctrlInfo3.SetItemText( 7, 2, Commify(dData) );

	g_iYuantaAPI.YOA_GetTRFieldDouble( _T("204006"), _T("OutBlock4"), _T("supyo_ip_amt"), &dData );
	m_ctrlInfo3.SetItemText( 8, 2, Commify(dData) );

	g_iYuantaAPI.YOA_GetTRFieldDouble( _T("204006"), _T("OutBlock4"), _T("gita_supyo_amt"), &dData );
	m_ctrlInfo3.SetItemText( 9, 2, Commify(dData) );

	g_iYuantaAPI.YOA_GetTRFieldDouble( _T("204006"), _T("OutBlock3"), _T("sin_settle_bo_amt"), &dData );
	m_ctrlInfo4.SetItemText( 0, 2, Commify(dData) );

	g_iYuantaAPI.YOA_GetTRFieldDouble( _T("204006"), _T("OutBlock3"), _T("sin_bo_hyun_amt"), &dData );
	m_ctrlInfo4.SetItemText( 1, 2, Commify(dData) );

	g_iYuantaAPI.YOA_GetTRFieldDouble( _T("204006"), _T("OutBlock3"), _T("sin_bo_dae_amt"), &dData );
	m_ctrlInfo4.SetItemText( 2, 2, Commify(dData) );

	g_iYuantaAPI.YOA_GetTRFieldDouble( _T("204006"), _T("OutBlock3"), _T("sin_dam_hyun_amt"), &dData );
	m_ctrlInfo4.SetItemText( 3, 2, Commify(dData) );

	g_iYuantaAPI.YOA_GetTRFieldDouble( _T("204006"), _T("OutBlock3"), _T("sin_dam_dae_amt"), &dData );
	m_ctrlInfo4.SetItemText( 4, 2, Commify(dData) );

	g_iYuantaAPI.YOA_GetTRFieldDouble( _T("204006"), _T("OutBlock3"), _T("cho_dam_hyun_amt"), &dData );
	m_ctrlInfo4.SetItemText( 5, 2, Commify(dData) );

	g_iYuantaAPI.YOA_GetTRFieldDouble( _T("204006"), _T("OutBlock3"), _T("cho_dam_dae_amt"), &dData );
	m_ctrlInfo4.SetItemText( 6, 2, Commify(dData) );

	g_iYuantaAPI.YOA_GetTRFieldDouble( _T("204006"), _T("OutBlock3"), _T("kwon_dae_amt"), &dData );
	m_ctrlInfo4.SetItemText( 7, 2, Commify(dData) );

	g_iYuantaAPI.YOA_GetTRFieldDouble( _T("204006"), _T("OutBlock3"), _T("yung_gum_amt"), &dData );
	m_ctrlInfo4.SetItemText( 8, 2, Commify(dData) );

	g_iYuantaAPI.YOA_GetTRFieldDouble( _T("204006"), _T("OutBlock4"), _T("daeju_amt"), &dData );
	m_ctrlInfo4.SetItemText( 9, 2, Commify(dData) );
}

void CStockAccountDlg::Process211010()
{
	double dData = 0;

	g_iYuantaAPI.YOA_GetTRFieldDouble( _T("211010"), _T("OutBlock1"), _T("elw_dptamt"), &dData );
	m_ctrlInfo2.SetItemText( 0, 2, Commify(dData) );

	g_iYuantaAPI.YOA_GetTRFieldDouble( _T("211010"), _T("OutBlock1"), _T("elw_bas_dpt_amt"), &dData );
	m_ctrlInfo2.SetItemText( 0, 4, Commify(dData) );

}

// CStockAccountDlg �޽��� ó�����Դϴ�.

BOOL CStockAccountDlg::PreTranslateMessage(MSG* pMsg)
{
	if ( WM_KEYDOWN == pMsg->message )
	{
		if ( VK_RETURN == pMsg->wParam || VK_ESCAPE == pMsg->wParam )
		{
			return TRUE;
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}

BOOL CStockAccountDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	InitControl();

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

LRESULT CStockAccountDlg::OnReceiveError(WPARAM wParam, LPARAM lParam)
{
	LRESULT ret = 0;

	int nReqID = wParam;

	CString strMsg;
	CString strDSO;

	if ( nReqID == m_nReqID_204006 )
	{
		strDSO = _T("[204006]�����꿹����Ȳ");
	}
	else if ( nReqID == m_nReqID_211010 )
	{
		strDSO = _T("[211010]ELW�Ÿű⺻��Ź����ȸ");
	}

	switch ( lParam )
	{
	case ERROR_TIMEOUT_DATA:
		{
			strMsg.Format( _T("Timeout %s ��û�� ������ �����ϴ�."), strDSO);
		}
		break;
	case ERROR_REQUEST_FAIL:
		{
			strMsg.Format( _T("%s ��û�� �����Ͽ����ϴ�."), strDSO);
			m_pMainDlg->LogMessage( strMsg, 1 );

			TCHAR msg[2048] = {0,};
			g_iYuantaAPI.YOA_GetErrorMessage( nReqID, msg, sizeof(msg) );
			strMsg.Format( _T("%s"), msg);
			strMsg.TrimRight();
			m_pMainDlg->LogMessage( strMsg, 1, FALSE );
		}
		break;
	}

	return ret;
}

LRESULT CStockAccountDlg::OnReceiveData(WPARAM wParam, LPARAM lParam)
{
	LRESULT ret = 0;

	if ( wParam == m_nReqID_204006 )
	{
		CString strMsg;
		strMsg.Format( _T("[ReqID:%d] [204006]�����꿹����Ȳ ������ �����Ͽ����ϴ�."), m_nReqID_204006 );
		m_pMainDlg->LogMessage( strMsg );

		Process204006();
	}
	else if ( wParam == m_nReqID_211010 )
	{
		CString strMsg;
		strMsg.Format( _T("[ReqID:%d] [211010]��ü�᳻�� ������ �����Ͽ����ϴ�."), m_nReqID_211010 );
		m_pMainDlg->LogMessage( strMsg );

		Process211010();
	}

	return ret;
}

LRESULT CStockAccountDlg::OnReceiveRealData(WPARAM wParam, LPARAM lParam)
{
	LRESULT ret = 0;

	CString strAutoID( (LPCTSTR)(LPCSTR)wParam );

	return ret;
}

void CStockAccountDlg::OnCbnSelchangeComboAccount()
{
	CString strName;
	CString strAccount;
	m_cbAccount.GetLBText( m_cbAccount.GetCurSel(), strAccount );

	strAccount.Remove('-');

	if ( m_mapAccount.Lookup( strAccount, strName ) )
	{
		GetDlgItem( IDC_STATIC_ACCOUNTNAME )->SetWindowTextW( strName );
	}
}

void CStockAccountDlg::OnBnClickedButtonSearch()
{
	if ( TRUE == CheckAPI() )
	{
		UpdateData();

		CString strAccount;
		m_cbAccount.GetLBText( m_cbAccount.GetCurSel(), strAccount );
		strAccount.Remove('-');

		g_iYuantaAPI.YOA_SetTRFieldString( _T("204006"), _T("InBlock1"), _T("kyejwa"), strAccount );
		g_iYuantaAPI.YOA_SetTRFieldString( _T("204006"), _T("InBlock1"), _T("passwd"), m_strAcctPassword );

		m_nReqID_204006 = g_iYuantaAPI.YOA_Request( GetSafeHwnd(), _T("204006") );

		if ( ERROR_MAX_CODE < m_nReqID_204006 )
		{
			CString strMsg;
			strMsg.Format( _T("[ReqID:%d] [204006]�����꿹����Ȳ ��ȸ�� ��û�Ͽ����ϴ�."), m_nReqID_204006 );

			m_pMainDlg->LogMessage( strMsg );
		}
		else
		{
			TCHAR msg[1024] = {0,};

			int nErrorCode = g_iYuantaAPI.YOA_GetLastError();
			g_iYuantaAPI.YOA_GetErrorMessage( nErrorCode, msg, sizeof(msg) );

			CString strErrorMsg;
			strErrorMsg.Format( _T("[%d] %s"), nErrorCode, msg );

			m_pMainDlg->LogMessage( _T("[204006]�����꿹����Ȳ ��ȸ�� ������ �߻��Ͽ����ϴ�."), 1 );
			m_pMainDlg->LogMessage( strErrorMsg, 1, FALSE );

			return;
		}

		g_iYuantaAPI.YOA_SetTRFieldString( _T("211010"), _T("InBlock1"), _T("acnt_aid"), strAccount );
		g_iYuantaAPI.YOA_SetTRFieldString( _T("211010"), _T("InBlock1"), _T("passwd"), m_strAcctPassword );

		m_nReqID_211010 = g_iYuantaAPI.YOA_Request( GetSafeHwnd(), _T("211010") );

		if ( ERROR_MAX_CODE < m_nReqID_211010 )
		{
			CString strMsg;
			strMsg.Format( _T("[ReqID:%d] [211010]ELW�Ÿű⺻��Ź�� ��ȸ�� ��û�Ͽ����ϴ�."), m_nReqID_211010 );

			m_pMainDlg->LogMessage( strMsg );
		}
		else
		{
			TCHAR msg[1024] = {0,};

			int nErrorCode = g_iYuantaAPI.YOA_GetLastError();
			g_iYuantaAPI.YOA_GetErrorMessage( nErrorCode, msg, sizeof(msg) );

			CString strErrorMsg;
			strErrorMsg.Format( _T("[%d] %s"), nErrorCode, msg );

			m_pMainDlg->LogMessage( _T("[211010]ELW�Ÿű⺻��Ź�� ��ȸ�� ������ �߻��Ͽ����ϴ�."), 1 );
			m_pMainDlg->LogMessage( strErrorMsg, 1, FALSE );
		}
	}
}

void CStockAccountDlg::OnNMCustomdrawListInfo1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLVCUSTOMDRAW pNMCD = reinterpret_cast<LPNMLVCUSTOMDRAW>(pNMHDR);

	*pResult = CDRF_DODEFAULT;

	switch(pNMCD->nmcd.dwDrawStage)
	{
	case CDDS_PREPAINT:
		*pResult = CDRF_NOTIFYITEMDRAW;
		break;
	case CDDS_ITEMPREPAINT:
		*pResult = CDRF_NOTIFYSUBITEMDRAW;
		break;
	case ( CDDS_ITEMPREPAINT | CDDS_SUBITEM ):
		{
			int nRow = pNMCD->nmcd.dwItemSpec;
			int nCol = pNMCD->iSubItem;

			if ( 1 == nCol )
				pNMCD->clrTextBk = RGB(225, 225, 225);
			else
				pNMCD->clrTextBk = RGB(255, 255, 255);
		}
		break;
	}
}

void CStockAccountDlg::OnNMCustomdrawListInfo2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLVCUSTOMDRAW pNMCD = reinterpret_cast<LPNMLVCUSTOMDRAW>(pNMHDR);

	*pResult = CDRF_DODEFAULT;

	switch(pNMCD->nmcd.dwDrawStage)
	{
	case CDDS_PREPAINT:
		*pResult = CDRF_NOTIFYITEMDRAW;
		break;
	case CDDS_ITEMPREPAINT:
		*pResult = CDRF_NOTIFYSUBITEMDRAW;
		break;
	case ( CDDS_ITEMPREPAINT | CDDS_SUBITEM ):
		{
			int nRow = pNMCD->nmcd.dwItemSpec;
			int nCol = pNMCD->iSubItem;

			if ( 1 == nCol || 3 == nCol )
				pNMCD->clrTextBk = RGB(225, 225, 225);
			else
				pNMCD->clrTextBk = RGB(255, 255, 255);
		}
		break;
	}
}

void CStockAccountDlg::OnNMCustomdrawListInfo3_4(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLVCUSTOMDRAW pNMCD = reinterpret_cast<LPNMLVCUSTOMDRAW>(pNMHDR);

	*pResult = CDRF_DODEFAULT;

	switch(pNMCD->nmcd.dwDrawStage)
	{
	case CDDS_PREPAINT:
		*pResult = CDRF_NOTIFYITEMDRAW;
		break;
	case CDDS_ITEMPREPAINT:
		*pResult = CDRF_NOTIFYSUBITEMDRAW;
		break;
	case ( CDDS_ITEMPREPAINT | CDDS_SUBITEM ):
		{
			int nRow = pNMCD->nmcd.dwItemSpec;
			int nCol = pNMCD->iSubItem;

			if ( 1 == nCol )
				pNMCD->clrTextBk = RGB(225, 225, 225);
			else
				pNMCD->clrTextBk = RGB(255, 255, 255);
		}
		break;
	}
}

