// StockOrderDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "YOADLLClient.h"
#include "StockOrderDlg.h"
#include "afxdialogex.h"
#include "../../include/MessageDef.h"
#include "YOADLLClientDlg.h"

#define ORDER_TYPE_MESU 0
#define ORDER_TYPE_MEDO 1

// CStockOrderDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CStockOrderDlg, CDialog)

CStockOrderDlg::CStockOrderDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStockOrderDlg::IDD, pParent)
	, m_strJongCode(_T(""))
	, m_nOrderPrice(0)
	, m_nOrderQuantity(0)
	, m_strAcctPassword(_T(""))
{
	m_pMainDlg = NULL;
	m_nOrderType = ORDER_TYPE_MESU;

	m_nReqID_300001		= -1;
	m_nReqID_mesu		= -1;
	m_nReqID_medo		= -1;
	m_nReqID_210006		= -1;
	m_nReqID_201007		= -1;

	m_nCurJukaColor		= 0;
	m_nStartJukaColor	= 0;
	m_nHighJukaColor	= 0;
	m_nLowJukaColor		= 0;
	m_nMedoHokaColor	= 0;
	m_nMesuHokaColor	= 0;
}

CStockOrderDlg::~CStockOrderDlg()
{
}

void CStockOrderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_JONG_INFO, m_ctrlJongInfo);
	DDX_Control(pDX, IDC_LIST_MICHEGYUL_HEADER, m_ctrlMiChegyulHeader);
	DDX_Control(pDX, IDC_LIST_MICHEGYUL, m_ctrlMiChegyul);
	DDX_Control(pDX, IDC_LIST_CHEGYUL_HEADER, m_ctrlChegyulHeader);
	DDX_Control(pDX, IDC_LIST_CHEGYUL, m_ctrlChegyul);
	DDX_Control(pDX, IDC_COMBO_ACCOUNT, m_cbAccount);
	DDX_Control(pDX, IDC_BUTTON_MESU, m_btnMesu);
	DDX_Text(pDX, IDC_EDIT_JONGCODE, m_strJongCode);
	DDX_Control(pDX, IDC_COMBO_ORDER_TYPE, m_cbOrderType);
	DDX_Text(pDX, IDC_EDIT_ORDER_PRICE, m_nOrderPrice);
	DDX_Text(pDX, IDC_EDIT_ORDER_QUANTITY, m_nOrderQuantity);
	DDX_Text(pDX, IDC_EDIT_ACCOUNT_PWD, m_strAcctPassword);
	DDX_Control(pDX, IDC_TAB_MEDOSU, m_tabMedosu);
	DDX_Control(pDX, IDC_SPIN_QTY, m_spinQty);
	DDX_Control(pDX, IDC_DATETIMEPICKER, m_ctrlDatePicker);
}


BEGIN_MESSAGE_MAP(CStockOrderDlg, CDialog)
	ON_MESSAGE(WMU_RECEIVE_ERROR, OnReceiveError)
	ON_MESSAGE(WMU_RECEIVE_DATA, OnReceiveData)
	ON_MESSAGE(WMU_RECEIVE_REAL_DATA, OnReceiveRealData)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST_JONG_INFO, &CStockOrderDlg::OnNMCustomdrawListJongInfo)
	ON_CBN_SELCHANGE(IDC_COMBO_ACCOUNT, &CStockOrderDlg::OnCbnSelchangeComboAccount)
	ON_CBN_SELCHANGE(IDC_COMBO_ORDER_TYPE, &CStockOrderDlg::OnCbnSelchangeComboOrderType)
	ON_EN_CHANGE(IDC_EDIT_ORDER_PRICE, &CStockOrderDlg::OnEnChangeEditOrderPrice)
	ON_EN_CHANGE(IDC_EDIT_ORDER_QUANTITY, &CStockOrderDlg::OnEnChangeEditOrderQuantity)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, &CStockOrderDlg::OnBnClickedButtonSearch)	
	ON_BN_CLICKED(IDC_BUTTON_SEARCH_MICHEGYUL, &CStockOrderDlg::OnBnClickedButtonSearchMiChegyul)
	ON_BN_CLICKED(IDC_BUTTON_MESU, &CStockOrderDlg::OnBnClickedButtonOrder)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST_MICHEGYUL, &CStockOrderDlg::OnNMCustomdrawListMiChegyul)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST_CHEGYUL, &CStockOrderDlg::OnNMCustomdrawListChegyul)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_MEDOSU, &CStockOrderDlg::OnTcnSelchangeTabMedosu)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH_CHEGYUL, &CStockOrderDlg::OnBnClickedButtonSearchChegyul)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_PRICE, &CStockOrderDlg::OnDeltaposSpinPrice)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_JONG_INFO, &CStockOrderDlg::OnLvnItemchangedListJongInfo)
END_MESSAGE_MAP()

void CStockOrderDlg::InitControl()
{
	m_tabMedosu.InsertItem(0, _T("매수"));
	m_tabMedosu.InsertItem(1, _T("매도"));

	m_cbAccount.AddString( _T("계좌번호") );
	m_cbAccount.SetCurSel( 0 );

	TCHAR* header[] = {	_T("현 재 가"), 
						_T("전일대비"), 
						_T("등 락 률"), 
						_T("거 래 량"), 
						_T("시      가"), 
						_T("고      가"), 
						_T("저      가"), 
						_T("매도호가"), 
						_T("매수호가"), 
						_T("상 한 가"), 
						_T("하 한 가"), 
						NULL };

	m_ctrlJongInfo.SetExtendedStyle( m_ctrlJongInfo.GetExtendedStyle() | LVS_EX_GRIDLINES );
	m_ctrlJongInfo.SetExtendedStyle( m_ctrlJongInfo.GetExtendedStyle() | LVS_EX_FULLROWSELECT );
	m_ctrlJongInfo.InsertColumn(0, _T(""), LVCFMT_CENTER, 0);
	m_ctrlJongInfo.InsertColumn(1, _T(""), LVCFMT_CENTER, 70);
	m_ctrlJongInfo.InsertColumn(2, _T(""), LVCFMT_RIGHT, 108);

	for ( int i = 0; i < 11; i++ )
	{
		m_ctrlJongInfo.InsertItem( i, _T("") );
		m_ctrlJongInfo.SetItemText( i, 1, header[i] );
	}

	m_btnMesu.SetFaceColor( RGB(186, 67, 68) );
	m_btnMesu.SetTextColor( RGB(255, 255, 255) );

	TCHAR* orderType[] = {	_T("01.보통"), 
							_T("05.시장가"), 
							_T("06.조건부지정가"), 
							_T("12.최유리지정가"), 
							_T("13.최우선지정가"), 
							_T("71.시간외종가"), 
							_T("81.시간외단일가"), 
							_T("I1.보통(IOC)"), 
							_T("I2.시장가(IOC)"), 
							_T("I3.최유리(IOC)"), 
							_T("F1.보통(FOC)"), 
							_T("F2.시장가(FOC)"), 
							_T("F3.최유리(FOC)"), 
							NULL };
	
	for ( int i = 0; i < 12; i++ )
	{
		m_cbOrderType.AddString( orderType[i] );
	}
	m_cbOrderType.SetCurSel(0);

	m_spinQty.SetBuddy( GetDlgItem( IDC_EDIT_ORDER_QUANTITY ) );
	m_spinQty.SetRange32( 0, 999999 );

	m_ctrlMiChegyulHeader.InsertColumn(0, _T(""), LVCFMT_CENTER, 0);
	m_ctrlMiChegyulHeader.InsertColumn(1, _T("주문번호"), LVCFMT_CENTER, 66);
	m_ctrlMiChegyulHeader.InsertColumn(2, _T("종목명"), LVCFMT_CENTER,	113);
	m_ctrlMiChegyulHeader.InsertColumn(3, _T("매매구분"), LVCFMT_CENTER,	60);
	m_ctrlMiChegyulHeader.InsertColumn(4, _T("주문가격"), LVCFMT_CENTER,	80);
	m_ctrlMiChegyulHeader.InsertColumn(5, _T("주문수량"), LVCFMT_CENTER,	75);
	m_ctrlMiChegyulHeader.InsertColumn(6, _T("미체결잔량"), LVCFMT_CENTER,	75);
	m_ctrlMiChegyulHeader.InsertColumn(7, _T("신용구분"), LVCFMT_CENTER,	60);

	m_ctrlMiChegyul.SetExtendedStyle( m_ctrlMiChegyul.GetExtendedStyle() | LVS_EX_GRIDLINES );
	m_ctrlMiChegyul.SetExtendedStyle( m_ctrlMiChegyul.GetExtendedStyle() | LVS_EX_FULLROWSELECT );
	m_ctrlMiChegyul.InsertColumn(0, _T(""), LVCFMT_CENTER, 0);
	m_ctrlMiChegyul.InsertColumn(1, _T("주문번호"), LVCFMT_RIGHT, 65);
	m_ctrlMiChegyul.InsertColumn(2, _T("구분"), LVCFMT_CENTER,	20);
	m_ctrlMiChegyul.InsertColumn(3, _T("종목명"), LVCFMT_LEFT,	93);
	m_ctrlMiChegyul.InsertColumn(4, _T("매매구분"), LVCFMT_CENTER,	60);
	m_ctrlMiChegyul.InsertColumn(5, _T("주문가격"), LVCFMT_RIGHT,	80);
	m_ctrlMiChegyul.InsertColumn(6, _T("주문수량"), LVCFMT_RIGHT,	75);
	m_ctrlMiChegyul.InsertColumn(7, _T("미체결잔량"), LVCFMT_RIGHT,	75);
	m_ctrlMiChegyul.InsertColumn(8, _T("신용구분"), LVCFMT_CENTER,	60);

	m_ctrlChegyulHeader.InsertColumn(0, _T(""), LVCFMT_CENTER, 0);
	m_ctrlChegyulHeader.InsertColumn(1, _T("종목명"), LVCFMT_CENTER,	119);
	m_ctrlChegyulHeader.InsertColumn(2, _T("매매구분"), LVCFMT_CENTER,	70);
	m_ctrlChegyulHeader.InsertColumn(3, _T("수량"), LVCFMT_CENTER,	100);
	m_ctrlChegyulHeader.InsertColumn(4, _T("단가"), LVCFMT_CENTER,	100);
	m_ctrlChegyulHeader.InsertColumn(5, _T("약정금액"), LVCFMT_CENTER, 140);

	m_ctrlChegyul.SetExtendedStyle( m_ctrlMiChegyul.GetExtendedStyle() | LVS_EX_GRIDLINES );
	m_ctrlChegyul.SetExtendedStyle( m_ctrlMiChegyul.GetExtendedStyle() | LVS_EX_FULLROWSELECT );
	m_ctrlChegyul.InsertColumn(0, _T(""), LVCFMT_CENTER, 0);
	m_ctrlChegyul.InsertColumn(1, _T("구분"), LVCFMT_CENTER,	20);
	m_ctrlChegyul.InsertColumn(2, _T("종목명"), LVCFMT_LEFT,	98);
	m_ctrlChegyul.InsertColumn(3, _T("매매구분"), LVCFMT_RIGHT,	70);
	m_ctrlChegyul.InsertColumn(4, _T("수량"), LVCFMT_RIGHT,	100);
	m_ctrlChegyul.InsertColumn(5, _T("단가"), LVCFMT_RIGHT,	100);
	m_ctrlChegyul.InsertColumn(6, _T("약정금액"), LVCFMT_RIGHT, 140);
}

void CStockOrderDlg::InitAccount()
{
	m_mapAccount.RemoveAll();
	m_cbAccount.ResetContent();
	
	m_cbAccount.AddString( _T("계좌번호") );
	m_cbAccount.SetCurSel( 0 );
}

void CStockOrderDlg::AddAccount( TCHAR* strAccount, TCHAR* strAcctName )
{
	m_mapAccount.SetAt( strAccount, strAcctName );
	m_cbAccount.AddString( m_pMainDlg->AccountFormat(strAccount) );
}

BOOL CStockOrderDlg::CheckAPI()
{
	if ( NULL == m_pMainDlg )
		return FALSE;

	return m_pMainDlg->CheckAPI();
}

CString CStockOrderDlg::Commify( TCHAR* pData )
{
	if ( NULL == m_pMainDlg )
		return _T("");

	return m_pMainDlg->Commify( pData );
}

CString CStockOrderDlg::Commify( long nData )
{
	if ( NULL == m_pMainDlg )
		return _T("");

	return m_pMainDlg->Commify( nData );
}

CString CStockOrderDlg::Commify( double dData )
{
	if ( NULL == m_pMainDlg )
		return _T("");

	return m_pMainDlg->Commify( dData );
}

void CStockOrderDlg::CalcTotPrice( long nOrderPrice, long nOrderQuantity )
{
	CString strTotPrice;
	strTotPrice.Format( _T("%s 원"), Commify(nOrderPrice * nOrderQuantity) );
	
	GetDlgItem( IDC_STATIC_TOTAL_PRICE )->SetWindowTextW( strTotPrice );
}

void CStockOrderDlg::Process300001()
{
	byte byteAttr = 0;
	long nData = 0;
	double dData = 0.0;
	TCHAR data[1024] = {0,};

	memset( data, 0x00, sizeof(data) );
	g_iYuantaAPI.YOA_GetTRFieldString( _T("300001"), _T("OutBlock1"), _T("jongname"), data, sizeof(data) );
	GetDlgItem( IDC_STATIC_JONGNAME )->SetWindowText( data );

	g_iYuantaAPI.YOA_GetTRFieldAttr( _T("300001"), _T("OutBlock1"), _T("curjuka"), &byteAttr );
	if ( 2 == byteAttr )
		m_nCurJukaColor = 1;
	else if ( 5 == byteAttr )
		m_nCurJukaColor = -1;
	else
		m_nCurJukaColor = 0;
	g_iYuantaAPI.YOA_GetTRFieldLong( _T("300001"), _T("OutBlock1"), _T("curjuka"), &nData );
	m_ctrlJongInfo.SetItemText( 0, 2, Commify(nData) );
	m_nOrderPrice = nData;
	UpdateData(FALSE);

	g_iYuantaAPI.YOA_GetTRFieldLong( _T("300001"), _T("OutBlock1"), _T("debi"), &nData );
	CString strDebi;
	if ( 0 < nData )
	{
		strDebi.Format(_T("▲  %s"), Commify(nData));
	}
    else if ( 0 > nData )
	{
		nData = -nData;
		strDebi.Format(_T("▼  %s"), Commify(nData));
	}
	else
	{
		strDebi.Format(_T("%d"), nData);
	}
	m_ctrlJongInfo.SetItemText( 1, 2, strDebi );

	g_iYuantaAPI.YOA_GetTRFieldDouble( _T("300001"), _T("OutBlock1"), _T("debirate"), &dData );
	m_ctrlJongInfo.SetItemText( 2, 2, Commify(dData) );

	memset( data, 0x00, sizeof(data) );
	g_iYuantaAPI.YOA_GetTRFieldString( _T("300001"), _T("OutBlock1"), _T("volume"), data, sizeof(data) );
	m_ctrlJongInfo.SetItemText( 3, 2, Commify(data) );

	g_iYuantaAPI.YOA_GetTRFieldAttr( _T("300001"), _T("OutBlock1"), _T("startjuka"), &byteAttr );
	if ( 2 == byteAttr )
		m_nStartJukaColor = 1;
	else if ( 5 == byteAttr )
		m_nStartJukaColor = -1;
	else
		m_nStartJukaColor = 0;
	g_iYuantaAPI.YOA_GetTRFieldLong( _T("300001"), _T("OutBlock1"), _T("startjuka"), &nData );
	m_ctrlJongInfo.SetItemText( 4, 2, Commify(nData) );

	g_iYuantaAPI.YOA_GetTRFieldAttr( _T("300001"), _T("OutBlock1"), _T("highjuka"), &byteAttr );
	if ( 2 == byteAttr )
		m_nHighJukaColor = 1;
	else if ( 5 == byteAttr )
		m_nHighJukaColor = -1;
	else
		m_nHighJukaColor = 0;
	g_iYuantaAPI.YOA_GetTRFieldLong( _T("300001"), _T("OutBlock1"), _T("highjuka"), &nData );
	m_ctrlJongInfo.SetItemText( 5, 2, Commify(nData) );

	g_iYuantaAPI.YOA_GetTRFieldAttr( _T("300001"), _T("OutBlock1"), _T("lowjuka"), &byteAttr );
	if ( 2 == byteAttr )
		m_nLowJukaColor = 1;
	else if ( 5 == byteAttr )
		m_nLowJukaColor = -1;
	else
		m_nLowJukaColor = 0;
	g_iYuantaAPI.YOA_GetTRFieldLong( _T("300001"), _T("OutBlock1"), _T("lowjuka"), &nData );
	m_ctrlJongInfo.SetItemText( 6, 2, Commify(nData) );

	g_iYuantaAPI.YOA_GetTRFieldAttr( _T("300001"), _T("OutBlock1"), _T("medohoka"), &byteAttr );
	if ( 2 == byteAttr )
		m_nMedoHokaColor = 1;
	else if ( 5 == byteAttr )
		m_nMedoHokaColor = -1;
	else
		m_nMedoHokaColor = 0;
	g_iYuantaAPI.YOA_GetTRFieldLong( _T("300001"), _T("OutBlock1"), _T("medohoka"), &nData );
	m_ctrlJongInfo.SetItemText( 7, 2, Commify(nData) );

	g_iYuantaAPI.YOA_GetTRFieldAttr( _T("300001"), _T("OutBlock1"), _T("mesuhoka"), &byteAttr );
	if ( 2 == byteAttr )
		m_nMesuHokaColor = 1;
	else if ( 5 == byteAttr )
		m_nMesuHokaColor = -1;
	else
		m_nMesuHokaColor = 0;
	g_iYuantaAPI.YOA_GetTRFieldLong( _T("300001"), _T("OutBlock1"), _T("mesuhoka"), &nData );
	m_ctrlJongInfo.SetItemText( 8, 2, Commify(nData) );
		
	g_iYuantaAPI.YOA_GetTRFieldLong( _T("300001"), _T("OutBlock1"), _T("upjuka"), &nData );
	m_ctrlJongInfo.SetItemText( 9, 2, Commify(nData) );
		
	g_iYuantaAPI.YOA_GetTRFieldLong( _T("300001"), _T("OutBlock1"), _T("downjuka"), &nData );
	m_ctrlJongInfo.SetItemText( 10, 2, Commify(nData) );

	UnregistAuto();
	RegistAuto( _T("11"), m_strJongCode );

	RegistAuto( _T("70"), _T("0000") );
	RegistAuto( _T("74"), _T("0000") );
}

void CStockOrderDlg::Process210006()
{
	byte byteAttr = 0;
	long nData = 0;
	double dData = 0.0;
	TCHAR data[1024] = {0,};
	CString strData;
	CString strTemp;
	CString strJongCode;
	CString strJongName;
	CString strJongType;

	int nDataCount = 0;
	if ( g_iYuantaAPI.YOA_GetTRFieldLong( _T("210006"), _T("OutBlock1"), _T("list_cnt"), &nData ) )
	{
		nDataCount = nData;
	}
	
	for ( int i = 0; i < nDataCount; i++ )
	{
		m_ctrlMiChegyul.InsertItem( 0, _T("") );

		memset( data, 0x00, sizeof(data) );
		g_iYuantaAPI.YOA_GetTRFieldString( _T("210006"), _T("OutBlock2"), _T("order_no"), data, sizeof(data), i );
		m_ctrlMiChegyul.SetItemText( 0, 1, data );

		memset( data, 0x00, sizeof(data) );
		g_iYuantaAPI.YOA_GetTRFieldString( _T("210006"), _T("OutBlock2"), _T("jong_code"), data, sizeof(data), i );
		strData.Format( _T("%s"), data );
		strData.TrimRight();
		AfxExtractSubString( strJongCode, strData, 0, '/' );
		AfxExtractSubString( strJongName, strData, 1, '/' );
		AfxExtractSubString( strJongType, strData, 2, '/' );
		strJongType.TrimRight();
		if ( !strJongType.Compare( _T("K") ) )
			m_arrJongTypeColor1.Add( 1 );
		else
			m_arrJongTypeColor1.Add( -1 );
		strJongName.TrimRight();
		m_ctrlMiChegyul.SetItemText( 0, 2, strJongType );
		m_ctrlMiChegyul.SetItemText( 0, 3, strJongName );

		memset( data, 0x00, sizeof(data) );
		g_iYuantaAPI.YOA_GetTRFieldString( _T("210006"), _T("OutBlock2"), _T("order_gubun"), data, sizeof(data), i );
		strData.Format( _T("%s"), data );
		AfxExtractSubString( strTemp, strData, 0, '}' );
		if ( -1 != strTemp.Find( _T("FF0000") ) )
			m_ctrlMiChegyul.SetItemData( 0, 1 );
		else
			m_ctrlMiChegyul.SetItemData( 0, -1 );
		AfxExtractSubString( strTemp, strData, 2, '}' );
		m_ctrlMiChegyul.SetItemText( 0, 4, strTemp );

		g_iYuantaAPI.YOA_GetTRFieldLong( _T("210006"), _T("OutBlock2"), _T("order_price"), &nData, i );
		m_ctrlMiChegyul.SetItemText( 0, 5, Commify(nData) );

		g_iYuantaAPI.YOA_GetTRFieldLong( _T("210006"), _T("OutBlock2"), _T("order_cnt"), &nData, i );
		m_ctrlMiChegyul.SetItemText( 0, 6, Commify(nData) );

		g_iYuantaAPI.YOA_GetTRFieldLong( _T("210006"), _T("OutBlock2"), _T("nn_contract_cnt"), &nData, i );
		m_ctrlMiChegyul.SetItemText( 0, 7, Commify(nData) );

		g_iYuantaAPI.YOA_GetTRFieldString( _T("210006"), _T("OutBlock2"), _T("credit_gubun"), data, sizeof(data), i );
		strData.Format( _T("%s"), data );
		AfxExtractSubString( strTemp, strData, 0, 'F' );
		m_ctrlMiChegyul.SetItemText( 0, 8, strTemp );
	}

	GetDlgItem( IDC_STATIC_SEARCH_COUNT )->SetWindowTextW( Commify((long)nDataCount) );
}

void CStockOrderDlg::Process201007()
{
	byte byteAttr = 0;
	long nData = 0;
	double dData = 0.0;
	TCHAR data[1024] = {0,};
	CString strData;
	CString strTemp;
	CString strJongCode;
	CString strJongName;
	CString strJongType;

	int nDataCount = g_iYuantaAPI.YOA_GetRowCount( _T("201007"), _T("OutBlock2") );

	for ( int i = 0; i < nDataCount; i++ )
	{
		m_ctrlChegyul.InsertItem( i, _T("") );

		memset( data, 0x00, sizeof(data) );
		g_iYuantaAPI.YOA_GetTRFieldString( _T("201007"), _T("OutBlock2"), _T("stk_name"), data, sizeof(data), i );
		strData.Format( _T("%s"), data );
		strData.TrimRight();
		AfxExtractSubString( strJongCode, strData, 0, '/' );
		AfxExtractSubString( strJongName, strData, 1, '/' );
		AfxExtractSubString( strJongType, strData, 2, '/' );
		strJongType.TrimRight();
		if ( !strJongType.Compare( _T("K") ) )
			m_arrJongTypeColor2.Add( 1 );
		else
			m_arrJongTypeColor2.Add( -1 );
		strJongName.TrimRight();
		m_ctrlChegyul.SetItemText( i, 1, strJongType );
		m_ctrlChegyul.SetItemText( i, 2, strJongName );

		memset( data, 0x00, sizeof(data) );
		g_iYuantaAPI.YOA_GetTRFieldString( _T("201007"), _T("OutBlock2"), _T("trde_tp_gubun"), data, sizeof(data), i );
		strData.Format( _T("%s"), data );
		AfxExtractSubString( strTemp, strData, 0, '}' );
		if ( -1 != strTemp.Find( _T("FF0000") ) )
			m_ctrlChegyul.SetItemData( 0, 1 );
		else
			m_ctrlChegyul.SetItemData( 0, -1 );
		AfxExtractSubString( strTemp, strData, 2, '}' );
		m_ctrlChegyul.SetItemText( i, 3, strTemp );

		memset( data, 0x00, sizeof(data) );
		g_iYuantaAPI.YOA_GetTRFieldString( _T("201007"), _T("OutBlock2"), _T("cntr_qty_cnt"), data, sizeof(data), i );
		m_ctrlChegyul.SetItemText( i, 4, Commify(data) );

		memset( data, 0x00, sizeof(data) );
		g_iYuantaAPI.YOA_GetTRFieldString( _T("201007"), _T("OutBlock2"), _T("cntr_uv_price"), data, sizeof(data), i );
		m_ctrlChegyul.SetItemText( i, 5, Commify(data) );

		g_iYuantaAPI.YOA_GetTRFieldLong( _T("201007"), _T("OutBlock2"), _T("contract_amt"), &nData, i );
		m_ctrlChegyul.SetItemText( i, 6, Commify(nData) );
	}

	GetDlgItem( IDC_STATIC_SEARCH_COUNT2 )->SetWindowTextW( Commify((long)nDataCount) );
}

void CStockOrderDlg::RegistAuto( CString strAutoID, CString strCode )
{
	g_iYuantaAPI.YOA_SetTRFieldString( strAutoID, _T("InBlock1"), _T("jongcode"), strCode );
	g_iYuantaAPI.YOA_RegistAuto( GetSafeHwnd(), strAutoID );
}

void CStockOrderDlg::UnregistAuto()
{
	g_iYuantaAPI.YOA_UnregistAutoWithWindow( GetSafeHwnd() );
}

void CStockOrderDlg::ProcessAuto11()
{
	byte byteAttr = 0;
	long nData = 0;
	double dData = 0.0;
	TCHAR data[1024] = {0,};

	long nCurJuka	= 0;
	long nDebi		= 0;

	g_iYuantaAPI.YOA_GetTRFieldAttr( _T("11"), _T("OutBlock1"), _T("curjuka"), &byteAttr );
	if ( 2 == byteAttr )
		m_nCurJukaColor = 1;
	else if ( 5 == byteAttr )
		m_nCurJukaColor = -1;
	else
		m_nCurJukaColor = 0;
	g_iYuantaAPI.YOA_GetTRFieldLong( _T("11"), _T("OutBlock1"), _T("curjuka"), &nCurJuka );
	m_ctrlJongInfo.SetItemText( 0, 2, Commify(nCurJuka) );

	g_iYuantaAPI.YOA_GetTRFieldLong( _T("11"), _T("OutBlock1"), _T("debi"), &nDebi );
	CString strDebi;
	if ( 0 < nDebi )
	{
		strDebi.Format(_T("▲  %s"), Commify(nDebi));
	}
	else if ( 0 > nDebi )
	{
		nDebi = -nDebi;
		strDebi.Format(_T("▼  %s"), Commify(nDebi));
	}
	else
	{
		strDebi.Format(_T("%d"), nData);
	}
	m_ctrlJongInfo.SetItemText( 1, 2, strDebi );

	g_iYuantaAPI.YOA_GetTRFieldDouble( _T("11"), _T("OutBlock1"), _T("debirate"), &dData );
	m_ctrlJongInfo.SetItemText( 2, 2, Commify(dData) );

	memset( data, 0x00, sizeof(data) );
	g_iYuantaAPI.YOA_GetTRFieldString( _T("11"), _T("OutBlock1"), _T("volume"), data, sizeof(data) );
	m_ctrlJongInfo.SetItemText( 3, 2, Commify(data) );

	g_iYuantaAPI.YOA_GetTRFieldAttr( _T("11"), _T("OutBlock1"), _T("startjuka"), &byteAttr );
	if ( 2 == byteAttr )
		m_nStartJukaColor = 1;
	else if ( 5 == byteAttr )
		m_nStartJukaColor = -1;
	else
		m_nStartJukaColor = 0;
	g_iYuantaAPI.YOA_GetTRFieldLong( _T("11"), _T("OutBlock1"), _T("startjuka"), &nData );
	m_ctrlJongInfo.SetItemText( 4, 2, Commify(nData) );

	g_iYuantaAPI.YOA_GetTRFieldAttr( _T("11"), _T("OutBlock1"), _T("highjuka"), &byteAttr );
	if ( 2 == byteAttr )
		m_nHighJukaColor = 1;
	else if ( 5 == byteAttr )
		m_nHighJukaColor = -1;
	else
		m_nHighJukaColor = 0;
	g_iYuantaAPI.YOA_GetTRFieldLong( _T("11"), _T("OutBlock1"), _T("highjuka"), &nData );
	m_ctrlJongInfo.SetItemText( 5, 2, Commify(nData) );

	g_iYuantaAPI.YOA_GetTRFieldAttr( _T("11"), _T("OutBlock1"), _T("lowjuka"), &byteAttr );
	if ( 2 == byteAttr )
		m_nLowJukaColor = 1;
	else if ( 5 == byteAttr )
		m_nLowJukaColor = -1;
	else
		m_nLowJukaColor = 0;
	g_iYuantaAPI.YOA_GetTRFieldLong( _T("11"), _T("OutBlock1"), _T("lowjuka"), &nData );
	m_ctrlJongInfo.SetItemText( 6, 2, Commify(nData) );

	g_iYuantaAPI.YOA_GetTRFieldAttr( _T("11"), _T("OutBlock1"), _T("medohoka"), &byteAttr );
	if ( 2 == byteAttr )
		m_nMedoHokaColor = 1;
	else if ( 5 == byteAttr )
		m_nMedoHokaColor = -1;
	else
		m_nMedoHokaColor = 0;
	g_iYuantaAPI.YOA_GetTRFieldLong( _T("11"), _T("OutBlock1"), _T("medohoka"), &nData );
	m_ctrlJongInfo.SetItemText( 7, 2, Commify(nData) );

	g_iYuantaAPI.YOA_GetTRFieldAttr( _T("11"), _T("OutBlock1"), _T("mesuhoka"), &byteAttr );
	if ( 2 == byteAttr )
		m_nMesuHokaColor = 1;
	else if ( 5 == byteAttr )
		m_nMesuHokaColor = -1;
	else
		m_nMesuHokaColor = 0;
	g_iYuantaAPI.YOA_GetTRFieldLong( _T("11"), _T("OutBlock1"), _T("mesuhoka"), &nData );
	m_ctrlJongInfo.SetItemText( 8, 2, Commify(nData) );

	g_iYuantaAPI.YOA_GetTRFieldLong( _T("11"), _T("OutBlock1"), _T("upjuka"), &nData );
	m_ctrlJongInfo.SetItemText( 9, 2, Commify(nData) );

	g_iYuantaAPI.YOA_GetTRFieldLong( _T("11"), _T("OutBlock1"), _T("downjuka"), &nData );
	m_ctrlJongInfo.SetItemText( 10, 2, Commify(nData) );

}


void CStockOrderDlg::ProcessAuto70()
{
	long ordno = 0 ;
	byte gubun48 = 0;

	g_iYuantaAPI.YOA_GetTRFieldLong( _T("70"), _T("OutBlock1"), _T("ordno"), &ordno );

	g_iYuantaAPI.YOA_GetTRFieldByte( _T("70"), _T("OutBlock1"), _T("gubun48"), &gubun48 );

	CString strOrder = _T("");

	switch( gubun48)
	{
	case '4': strOrder = _T("매수");				break;
	case '5': strOrder = _T("매수(차입체결)");	break;
	case '8': strOrder = _T("매도");				break;
	case '9': strOrder = _T("매도(대여체결)");	break;
	default : strOrder = _T("비체결통보");
		return;
	}

	CString  strMsg;
	strMsg.Format(_T("[주문번호 : %d] %s 체결통보가 수신되었습니다."), ordno, strOrder );
	m_pMainDlg->LogMessage( strMsg );
}

void CStockOrderDlg::ProcessAuto74()
{
	TCHAR data[1024] = {0, };
	
	memset( data, 0x00, sizeof(data) );
	g_iYuantaAPI.YOA_GetTRFieldString( _T("74"), _T("OutBlock1"), _T("custseq"), data, sizeof(data) );

	CString strAccount;
	m_cbAccount.GetLBText( m_cbAccount.GetCurSel(), strAccount );

	strAccount.Remove('-');

	if( strAccount == data )
	{
		CString strMsg;
		strMsg.Format(_T("[계좌번호:%s] 실시간계좌를 수신하였습니다."), data);

		m_pMainDlg->LogMessage( strMsg );


		OnBnClickedButtonSearchMiChegyul();
		OnBnClickedButtonSearchChegyul();
	}

}


// CStockOrderDlg 메시지 처리기입니다.

BOOL CStockOrderDlg::PreTranslateMessage(MSG* pMsg)
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

BOOL CStockOrderDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	InitControl();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

LRESULT CStockOrderDlg::OnReceiveError(WPARAM wParam, LPARAM lParam)
{
	LRESULT ret = 0;

	int nReqID = wParam;

	CString strMsg;
	CString strTrName;

	if ( nReqID == m_nReqID_300001 )
	{
		strTrName = _T("[300001]주식현재가");
	}
	else if ( nReqID == m_nReqID_mesu )
	{
		strTrName = _T("[100001]현금매수");
	}
	else if ( nReqID == m_nReqID_medo )
	{
		strTrName = _T("[100002]현금매도");
	}
	else if ( nReqID == m_nReqID_210006 )
	{
		strTrName = _T("[210006]미체결내역 조회");
	}
	else if ( nReqID == m_nReqID_210006 )
	{
		strTrName = _T("[201001]체결기준거래내역 조회");
	}

	switch ( lParam )
	{
	case ERROR_TIMEOUT_DATA:
		{
			strMsg.Format( _T("Timeout %s 요청의 응답이 없습니다."), strTrName);
			m_pMainDlg->LogMessage( strMsg, 1 );
		}
		break;
	case ERROR_REQUEST_FAIL:
		{
			strMsg.Format( _T("%s 요청이 실패하였습니다."), strTrName);
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

LRESULT CStockOrderDlg::OnReceiveData(WPARAM wParam, LPARAM lParam)
{
	LRESULT ret = 0;

	CString strTrName = _T("");

	if ( wParam == m_nReqID_300001 )
	{
		strTrName = _T("[300001]주식현재가");
		
		Process300001();
	}
	else if ( wParam == m_nReqID_210006 )
	{
		strTrName = _T("[210006]미체결내역");
		
		Process210006();
	}
	else if ( wParam == m_nReqID_201007 )
	{
		strTrName = _T("[201007]체결기준거래내역");
		
		Process201007();
	}
	else if ( wParam == m_nReqID_mesu )
	{
		int a = 0;
	}
	else if ( wParam == m_nReqID_medo )
	{
		int a = 0;
	}

	if ( 0 < strTrName.GetLength() )
	{
		CString strMsg;
		strMsg.Format( _T("[ReqID:%d] %s 응답을 수신하였습니다."), wParam, strTrName );
		m_pMainDlg->LogMessage( strMsg );
	}

	return ret;
}

LRESULT CStockOrderDlg::OnReceiveRealData(WPARAM wParam, LPARAM lParam)
{
	LRESULT ret = 0;

	LPRECV_DATA pRecvData = (LPRECV_DATA)lParam;
	CString strAutoID( pRecvData->szTrCode );

	if ( 0 == strAutoID.Compare( _T("11") ) )
		ProcessAuto11();
	else if ( 0 == strAutoID.Compare( _T("70") ) )
		ProcessAuto70();
	else if ( 0 == strAutoID.Compare( _T("74") ) )
		ProcessAuto74();

	return ret;
}

void CStockOrderDlg::OnNMCustomdrawListJongInfo(NMHDR *pNMHDR, LRESULT *pResult)
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

			pNMCD->clrTextBk = ( 1 == nCol ? RGB(248, 248, 248) : RGB(255, 255, 255) );

			if ( (0 == nRow || 1 == nRow || 2 == nRow) && 2 == nCol )
			{
				if ( 1 == m_nCurJukaColor )
					pNMCD->clrText = RGB( 255, 0, 0 );
				else if ( -1 == m_nCurJukaColor )
					pNMCD->clrText = RGB( 0, 0, 255 );
				else
					pNMCD->clrText = RGB( 0, 0, 0 );
			}
			else if ( 4 == nRow && 2 == nCol )
			{
				if ( 1 == m_nStartJukaColor )
					pNMCD->clrText = RGB( 255, 0, 0 );
				else if ( -1 == m_nStartJukaColor )
					pNMCD->clrText = RGB( 0, 0, 255 );
				else
					pNMCD->clrText = RGB( 0, 0, 0 );
			}
			else if ( 5 == nRow && 2 == nCol )
			{
				if ( 1 == m_nHighJukaColor )
					pNMCD->clrText = RGB( 255, 0, 0 );
				else if ( -1 == m_nHighJukaColor )
					pNMCD->clrText = RGB( 0, 0, 255 );
				else
					pNMCD->clrText = RGB( 0, 0, 0 );
			}
			else if ( 6 == nRow && 2 == nCol )
			{
				if ( 1 == m_nLowJukaColor )
					pNMCD->clrText = RGB( 255, 0, 0 );
				else if ( -1 == m_nLowJukaColor )
					pNMCD->clrText = RGB( 0, 0, 255 );
				else
					pNMCD->clrText = RGB( 0, 0, 0 );
			}
			else if ( 7 == nRow && 2 == nCol )
			{
				if ( 1 == m_nMedoHokaColor )
					pNMCD->clrText = RGB( 255, 0, 0 );
				else if ( -1 == m_nHighJukaColor )
					pNMCD->clrText = RGB( 0, 0, 255 );
				else
					pNMCD->clrText = RGB( 0, 0, 0 );
			}
			else if ( 8 == nRow && 2 == nCol )
			{
				if ( 1 == m_nMesuHokaColor )
					pNMCD->clrText = RGB( 255, 0, 0 );
				else if ( -1 == m_nHighJukaColor )
					pNMCD->clrText = RGB( 0, 0, 255 );
				else
					pNMCD->clrText = RGB( 0, 0, 0 );
			}
			else if ( 9 == nRow && 2 == nCol )
			{
				pNMCD->clrText = RGB( 255, 0, 0 );
			}
			else if ( 10 == nRow && 2 == nCol )
			{
				pNMCD->clrText = RGB( 0, 0, 255 );
			}
			else
			{
				pNMCD->clrText = RGB( 0, 0, 0 );
			}
		}
		break;
	}
}

void CStockOrderDlg::OnCbnSelchangeComboAccount()
{
	CString strName;
	CString strAccount;
	m_cbAccount.GetLBText( m_cbAccount.GetCurSel(), strAccount );

	strAccount.Remove('-');

	if ( m_mapAccount.Lookup( strAccount, strName ) )
	{
		GetDlgItem( IDC_STATIC_ACCOUNTNAME )->SetWindowTextW( strName );
	}
	else
	{
		GetDlgItem( IDC_STATIC_ACCOUNTNAME )->SetWindowTextW( _T("") );
	}

	GetDlgItem( IDC_EDIT_ACCOUNT_PWD )->SetWindowTextW( _T("") );
}

void CStockOrderDlg::OnCbnSelchangeComboOrderType()
{
	int nIndex = m_cbOrderType.GetCurSel();

	if (
		 1 == nIndex ||	// 05.시장가
		 3 == nIndex ||	// 12.최유리지정가
		 4 == nIndex ||	// 13.최우선지정가
		 5 == nIndex ||	// 71.시간외종가
		 8 == nIndex ||	// I2.시장가(IOC)
		11 == nIndex 	// F2.시장가(FOC)
		)
	{
		GetDlgItem( IDC_EDIT_ORDER_PRICE )->EnableWindow( FALSE );
	}
	else
	{
		GetDlgItem( IDC_EDIT_ORDER_PRICE )->EnableWindow( TRUE );
	}
}

void CStockOrderDlg::OnEnChangeEditOrderPrice()
{
	UpdateData();

	CalcTotPrice( m_nOrderPrice, m_nOrderQuantity );
}

void CStockOrderDlg::OnEnChangeEditOrderQuantity()
{
	UpdateData();
	
	CalcTotPrice( m_nOrderPrice, m_nOrderQuantity );
}

void CStockOrderDlg::OnBnClickedButtonSearch()
{
	if ( TRUE == CheckAPI() )
	{
		UpdateData();

		TCHAR szJang[101] = {0, };

		m_strJongCode.TrimRight();
		if ( 6 == m_strJongCode.GetLength() )
		{
			g_iYuantaAPI.YOA_GetCodeInfo( MARKET_TYPE_INTERNAL, CODE_INFO_JANG_GUBUN, m_strJongCode, szJang, sizeof(szJang) );
			g_iYuantaAPI.YOA_SetTRFieldString( _T("300001"), _T("InBlock1"), _T("jang"), szJang );
			g_iYuantaAPI.YOA_SetTRFieldString( _T("300001"), _T("InBlock1"), _T("jongcode"), m_strJongCode );
			g_iYuantaAPI.YOA_SetTRFieldString( _T("300001"), _T("InBlock1"), _T("outflag"), _T("N") );
			g_iYuantaAPI.YOA_SetTRFieldString( _T("300001"), _T("InBlock1"), _T("tsflag"), _T("0") );

			m_nReqID_300001 = g_iYuantaAPI.YOA_Request( GetSafeHwnd(), _T("300001") );

			if ( ERROR_MAX_CODE < m_nReqID_300001 )
			{
				CString strMsg;
				strMsg.Format( _T("[ReqID:%d] [300001]주식현재가 조회를 요청하였습니다."), m_nReqID_300001 );

				m_pMainDlg->LogMessage( strMsg );
			}
			else
			{
				TCHAR msg[1024] = {0,};

				int nErrorCode = g_iYuantaAPI.YOA_GetLastError();
				g_iYuantaAPI.YOA_GetErrorMessage( nErrorCode, msg, sizeof(msg) );

				CString strErrorMsg;
				strErrorMsg.Format( _T("[%d] %s"), nErrorCode, msg );

				m_pMainDlg->LogMessage( _T("[300001]주식현재가 조회중 오류가 발생하였습니다."), 1 );
				m_pMainDlg->LogMessage( strErrorMsg, 1, FALSE );
			}
		}
	}
}

void CStockOrderDlg::OnBnClickedButtonSearchMiChegyul()
{
	if ( TRUE == CheckAPI() )
	{
		UpdateData();

		m_ctrlMiChegyul.DeleteAllItems();
		m_arrJongTypeColor1.RemoveAll();

		CString strAccount;
		m_cbAccount.GetLBText( m_cbAccount.GetCurSel(), strAccount );
		strAccount.Remove('-');
		
		g_iYuantaAPI.YOA_SetTRFieldString( _T("210006"), _T("InBlock1"), _T("acnt_aid"), strAccount );
		g_iYuantaAPI.YOA_SetTRFieldString( _T("210006"), _T("InBlock1"), _T("passwd"), m_strAcctPassword );
		g_iYuantaAPI.YOA_SetTRFieldString( _T("210006"), _T("InBlock1"), _T("order_gubun"), _T("1") );

		m_nReqID_210006 = g_iYuantaAPI.YOA_Request( GetSafeHwnd(), _T("210006") );

		if ( ERROR_MAX_CODE < m_nReqID_210006 )
		{
			CString strMsg;
			strMsg.Format( _T("[ReqID:%d] [210006]미체결내역 조회를 요청하였습니다."), m_nReqID_210006 );

			m_pMainDlg->LogMessage( strMsg );
		}
		else
		{
			TCHAR msg[1024] = {0,};

			int nErrorCode = g_iYuantaAPI.YOA_GetLastError();
			g_iYuantaAPI.YOA_GetErrorMessage( nErrorCode, msg, sizeof(msg) );

			CString strErrorMsg;
			strErrorMsg.Format( _T("[%d] %s"), nErrorCode, msg );

			m_pMainDlg->LogMessage( _T("[210006]미체결내역 조회중 오류가 발생하였습니다."), 1 );
			m_pMainDlg->LogMessage( strErrorMsg, 1, FALSE );
		}
	}
}

void CStockOrderDlg::OnBnClickedButtonSearchChegyul()
{
	if ( TRUE == CheckAPI() )
	{
		UpdateData();

		m_ctrlChegyul.DeleteAllItems();
		m_arrJongTypeColor2.RemoveAll();

		CString strAccount;
		m_cbAccount.GetLBText( m_cbAccount.GetCurSel(), strAccount );
		strAccount.Remove('-');

		CTime date;
		m_ctrlDatePicker.GetTime( date );
		CString strDate;
		strDate.Format( _T("%d%02d%02d"), date.GetYear(), date.GetMonth(), date.GetDay() );

		g_iYuantaAPI.YOA_SetTRFieldString( _T("201007"), _T("InBlock1"), _T("acnt_aid"), strAccount );
		g_iYuantaAPI.YOA_SetTRFieldString( _T("201007"), _T("InBlock1"), _T("date"), strDate );
		g_iYuantaAPI.YOA_SetTRFieldString( _T("201007"), _T("InBlock1"), _T("qry_tp"), _T("3") );
		//g_iYuantaAPI.YOA_SetTRFieldString( _T("201007"), _T("InBlock1"), _T("jong_code"), _T("      "));//m_strJongCode );
		g_iYuantaAPI.YOA_SetTRFieldString( _T("201007"), _T("InBlock1"), _T("jong_code"), m_strJongCode);//m_strJongCode );

		
		m_nReqID_201007 = g_iYuantaAPI.YOA_Request( GetSafeHwnd(), _T("201007") );

		if ( ERROR_MAX_CODE < m_nReqID_201007 )
		{
			CString strMsg;
			strMsg.Format( _T("[ReqID:%d] [201007]체결기준거래내역 조회를 요청하였습니다."), m_nReqID_201007 );

			m_pMainDlg->LogMessage( strMsg );
		}
		else
		{
			TCHAR msg[1024] = {0,};

			int nErrorCode = g_iYuantaAPI.YOA_GetLastError();
			g_iYuantaAPI.YOA_GetErrorMessage( nErrorCode, msg, sizeof(msg) );

			CString strErrorMsg;
			strErrorMsg.Format( _T("[%d] %s"), nErrorCode, msg );

			m_pMainDlg->LogMessage( _T("[201007]미체결내역 조회중 오류가 발생하였습니다."), 1 );
			m_pMainDlg->LogMessage( strErrorMsg, 1, FALSE );
		}		
	}
}

void CStockOrderDlg::OnBnClickedButtonOrder()
{
	if ( TRUE == CheckAPI() )
	{
		UpdateData();

		int nIndex = m_cbAccount.GetCurSel();
		if ( 1 > nIndex )
		{
			AfxMessageBox( _T("계좌번호를 선택해주세요."), MB_OK );
			return;
		}

		if ( 0 == m_strAcctPassword.GetLength() )
		{
			AfxMessageBox( _T("계좌비밀번호를 입력해주세요."), MB_OK );
			GetDlgItem( IDC_EDIT_ACCOUNT_PWD )->SetFocus();
			return;
		}

		if ( 0 == m_strJongCode.GetLength() )
		{
			AfxMessageBox( _T("종목코드를 입력해주세요."), MB_OK );
			GetDlgItem( IDC_EDIT_JONGCODE )->SetFocus();
			return;
		}

		if ( 0 == m_nOrderPrice )
		{
			int nIndex = m_cbOrderType.GetCurSel();

			if (
				 1 == nIndex ||	// 05.시장가
				 3 == nIndex ||	// 12.최유리지정가
				 4 == nIndex ||	// 13.최우선지정가
				 5 == nIndex ||	// 71.시간외종가
				 8 == nIndex ||	// I2.시장가(IOC)
				11 == nIndex 	// F2.시장가(FOC)
				)
			{
				
			}
			else
			{
				AfxMessageBox( _T("가격을 입력해주세요."), MB_OK );
				GetDlgItem( IDC_EDIT_ORDER_PRICE )->SetFocus();
				return;
			}
		}

		if ( 0 == m_nOrderQuantity )
		{
			AfxMessageBox( _T("수량을 입력해주세요."), MB_OK );
			GetDlgItem( IDC_EDIT_ORDER_QUANTITY )->SetFocus();
			return;
		}

		CString strDSOID;
		if ( ORDER_TYPE_MESU == m_nOrderType )
			strDSOID = _T("100001");
		else if ( ORDER_TYPE_MEDO == m_nOrderType )
			strDSOID = _T("100002");

		CString strAccount;
		m_cbAccount.GetLBText( m_cbAccount.GetCurSel(), strAccount );
		strAccount.Remove('-');

		CString strMemeGubun;
		m_cbOrderType.GetLBText( m_cbOrderType.GetCurSel(), strMemeGubun );
		int nPos = strMemeGubun.Find('.');
		strMemeGubun = strMemeGubun.Mid(0, nPos);

		CString strJumunCond( _T("00") );
		if ( 1 < strMemeGubun.GetLength() )
		{
			if ( 'I' == strMemeGubun[0] )
				strJumunCond = _T("01");
			else if ( 'F' == strMemeGubun[0] )
				strJumunCond = _T("02");
		}

		g_iYuantaAPI.YOA_SetTRFieldString( strDSOID, _T("InBlock1"), _T("acnt_aid"),			strAccount);
		g_iYuantaAPI.YOA_SetTRFieldString( strDSOID, _T("InBlock1"), _T("gds_acnt_tp"),		_T("A01010001") );
		g_iYuantaAPI.YOA_SetTRFieldString( strDSOID, _T("InBlock1"), _T("passwd"),			m_strAcctPassword );
		g_iYuantaAPI.YOA_SetTRFieldString( strDSOID, _T("InBlock1"), _T("meme_gubun"),		strMemeGubun );
		g_iYuantaAPI.YOA_SetTRFieldString( strDSOID, _T("InBlock1"), _T("jong_code"),			m_strJongCode );
		g_iYuantaAPI.YOA_SetTRFieldString( strDSOID, _T("InBlock1"), _T("jang_gubun"),		_T("0") );
		g_iYuantaAPI.YOA_SetTRFieldLong(   strDSOID, _T("InBlock1"), _T("order_cnt"),			m_nOrderQuantity );
		g_iYuantaAPI.YOA_SetTRFieldLong(   strDSOID, _T("InBlock1"), _T("order_price"),		m_nOrderPrice );
		g_iYuantaAPI.YOA_SetTRFieldString( strDSOID, _T("InBlock1"), _T("jumun_condition"),	strJumunCond );
		
		int nReqID = g_iYuantaAPI.YOA_Request( GetSafeHwnd(), strDSOID );

		if ( ORDER_TYPE_MESU == m_nOrderType )
		{
			m_nReqID_mesu = nReqID;
		}
		else if ( ORDER_TYPE_MEDO == m_nOrderType )
		{
			m_nReqID_medo = nReqID;
		}

		if ( ERROR_MAX_CODE < nReqID )
		{
			CString strMsg;
			if ( ORDER_TYPE_MESU == m_nOrderType )
			{
				strMsg.Format( _T("[ReqID:%d] [%s]현금매수 주문을 요청 하였습니다."), nReqID, strDSOID );
			}
			else if ( ORDER_TYPE_MEDO == m_nOrderType )
			{
				strMsg.Format( _T("[ReqID:%d] [%s]현금매도 주문을 요청 하였습니다."), nReqID, strDSOID );
			}

			m_pMainDlg->LogMessage( strMsg );
		}
		else
		{
			TCHAR msg[1024] = {0,};

			int nErrorCode = g_iYuantaAPI.YOA_GetLastError();
			g_iYuantaAPI.YOA_GetErrorMessage( nErrorCode, msg, sizeof(msg) );

			CString strErrorMsg;
			strErrorMsg.Format( _T("[%d] %s"), nErrorCode, msg );

			CString strMsg;
			if ( ORDER_TYPE_MESU == m_nOrderType )
			{
				strMsg.Format( _T("[%s]현금매수 주문 요청중 오류가 발생하였습니다."), strDSOID );
			}
			else if ( ORDER_TYPE_MEDO == m_nOrderType )
			{
				strMsg.Format( _T("[%s]현금매도 주문 요청중 오류가 발생하였습니다."), strDSOID );
			}

			m_pMainDlg->LogMessage( strMsg, 1 );
			m_pMainDlg->LogMessage( strErrorMsg, 1, FALSE );
		}
	}
}

void CStockOrderDlg::OnNMCustomdrawListMiChegyul(NMHDR *pNMHDR, LRESULT *pResult)
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

			if ( 2 == nCol )
			{
				int nColor = m_arrJongTypeColor1[nRow];

				if ( 1 == nColor )
					pNMCD->clrText = RGB( 255, 0, 0 );
				else if ( -1 == nColor )
					pNMCD->clrText = RGB( 0, 0, 255 );
				else
					pNMCD->clrText = RGB( 0, 0, 0 );
			}
			else if ( 4 == nCol )
			{
				int nColor = m_ctrlMiChegyul.GetItemData( nRow );

				if ( 1 == nColor )
					pNMCD->clrText = RGB( 255, 0, 0 );
				else if ( -1 == nColor )
					pNMCD->clrText = RGB( 0, 0, 255 );
				else
					pNMCD->clrText = RGB( 0, 0, 0 );
			}
			else
				pNMCD->clrText = RGB( 0, 0, 0 );

			if ( 6 == nCol )
				pNMCD->clrTextBk = RGB(255, 255, 193);
			else
				pNMCD->clrTextBk = RGB(255, 255, 255);
		}
		break;
	}
}

void CStockOrderDlg::OnNMCustomdrawListChegyul(NMHDR *pNMHDR, LRESULT *pResult)
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
			{
				int nColor = m_arrJongTypeColor2[nRow];

				if ( 1 == nColor )
					pNMCD->clrText = RGB( 255, 0, 0 );
				else if ( -1 == nColor )
					pNMCD->clrText = RGB( 0, 0, 255 );
				else
					pNMCD->clrText = RGB( 0, 0, 0 );
			}
			else if ( 3 == nCol )
			{
				int nColor = m_ctrlChegyul.GetItemData( nRow );

				if ( 1 == nColor )
					pNMCD->clrText = RGB( 255, 0, 0 );
				else if ( -1 == nColor )
					pNMCD->clrText = RGB( 0, 0, 255 );
				else
					pNMCD->clrText = RGB( 0, 0, 0 );
			}
			else
				pNMCD->clrText = RGB( 0, 0, 0 );
		}
		break;
	}
}

void CStockOrderDlg::OnTcnSelchangeTabMedosu(NMHDR *pNMHDR, LRESULT *pResult)
{
	int nCurSel = m_tabMedosu.GetCurSel();

	if ( ORDER_TYPE_MESU == nCurSel )
	{
		m_btnMesu.SetWindowTextW( _T("현금매수") );
		m_btnMesu.SetFaceColor( RGB(186, 67, 68) );
	}
	else if ( ORDER_TYPE_MEDO == nCurSel )
	{
		m_btnMesu.SetWindowTextW( _T("현금매도") );
		m_btnMesu.SetFaceColor( RGB(104, 151, 221) );
	}

	*pResult = 0;
}


void CStockOrderDlg::OnDeltaposSpinPrice(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	
	UpdateData();
	int nPrice = m_nOrderPrice;



	*pResult = 0;
}


void CStockOrderDlg::OnLvnItemchangedListJongInfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	
	int nRow = pNMLV->iItem;

	if ( 1 != nRow && 2 != nRow && 3 != nRow )
	{
		CString strData = m_ctrlJongInfo.GetItemText(nRow, 2);
		strData.Remove( ',' );
		strData.TrimRight();

		if ( 0 < strData.GetLength() )
			GetDlgItem( IDC_EDIT_ORDER_PRICE )->SetWindowTextW( strData );
	}

	*pResult = 0;
}
