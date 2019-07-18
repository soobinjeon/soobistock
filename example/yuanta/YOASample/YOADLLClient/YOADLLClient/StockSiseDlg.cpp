// CStockSiseDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "YOADLLClient.h"
#include "StockSiseDlg.h"
#include "afxdialogex.h"
#include "../../include/MessageDef.h"
#include "YOADLLClientDlg.h"

// CStockSiseDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CStockSiseDlg, CDialog)

CStockSiseDlg::CStockSiseDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStockSiseDlg::IDD, pParent)
	, m_strJongCode(_T(""))
{
	m_pMainDlg = NULL;

	m_nPrevLastPrice	= 0;
	m_nMedoDebiTot		= 0;
	m_nMesuDebiTot		= 0;
	m_nMedoTot			= 0;
	m_nMesuTot			= 0;

	m_nReqID_300001		= -1;
	m_nReqID_300002		= -1;
	m_nReqID_301004		= -1;
	m_bNext_301004		= FALSE;
}

CStockSiseDlg::~CStockSiseDlg()
{
}

void CStockSiseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_HOGA_HEADER, m_ctrlHogaHeader);
	DDX_Control(pDX, IDC_LIST_HOGA, m_ctrlHoga);
	DDX_Control(pDX, IDC_LIST_HOGA_FOOTER, m_ctrlHogaFooter);
	DDX_Control(pDX, IDC_LIST_CONTICK_HEADER, m_ctrlConTickHeader);
	DDX_Control(pDX, IDC_LIST_CONTICK, m_ctrlConTick);
	DDX_Control(pDX, IDC_LIST_DAILY_HEADER, m_ctrlDailyHeader);
	DDX_Control(pDX, IDC_LIST_DAILY, m_ctrlDaily);
	DDX_Text(pDX, IDC_EDIT_JONGCODE, m_strJongCode);
	DDX_Control(pDX, IDC_STATIC_JONGNAME, m_ctrlJongName);
}


BEGIN_MESSAGE_MAP(CStockSiseDlg, CDialog)
	ON_MESSAGE(WMU_RECEIVE_ERROR, OnReceiveError)
	ON_MESSAGE(WMU_RECEIVE_DATA, OnReceiveData)
	ON_MESSAGE(WMU_RECEIVE_REAL_DATA, OnReceiveRealData)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, &CStockSiseDlg::OnBnClickedButtonSearch)
	ON_BN_CLICKED(IDC_BUTTON_NEXT, &CStockSiseDlg::OnBnClickedButtonNext)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST_HOGA, &CStockSiseDlg::OnNMCustomdrawListHoga)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST_HOGA_FOOTER, &CStockSiseDlg::OnNMCustomdrawListHogaFooter)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST_CONTICK, &CStockSiseDlg::OnNMCustomdrawListConTick)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST_DAILY, &CStockSiseDlg::OnNMCustomdrawListDaily)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

void CStockSiseDlg::InitControl()
{
	m_ctrlHogaHeader.InsertColumn(0, _T(""), LVCFMT_RIGHT, 0);
	m_ctrlHogaHeader.InsertColumn(1, _T("대비"), LVCFMT_CENTER,	49);
	m_ctrlHogaHeader.InsertColumn(2, _T("매도잔량"), LVCFMT_CENTER,	63);
	m_ctrlHogaHeader.InsertColumn(3, _T(""), LVCFMT_CENTER,	126);
	m_ctrlHogaHeader.InsertColumn(4, _T("매수잔량"), LVCFMT_CENTER,	63);
	m_ctrlHogaHeader.InsertColumn(5, _T("대비"), LVCFMT_CENTER,	49);

	m_ctrlHoga.SetExtendedStyle( m_ctrlHoga.GetExtendedStyle() | LVS_EX_GRIDLINES );
	m_ctrlHoga.InsertColumn(0, _T(""), LVCFMT_RIGHT, 0);
	m_ctrlHoga.InsertColumn(1, _T("대비"), LVCFMT_RIGHT,	48);
	m_ctrlHoga.InsertColumn(2, _T("매도잔량"), LVCFMT_RIGHT,	63);
	m_ctrlHoga.InsertColumn(3, _T(""), LVCFMT_RIGHT,	76);
	m_ctrlHoga.InsertColumn(4, _T(""), LVCFMT_RIGHT,	50);
	m_ctrlHoga.InsertColumn(5, _T("매수잔량"), LVCFMT_RIGHT,	63);
	m_ctrlHoga.InsertColumn(6, _T("대비"), LVCFMT_RIGHT,	49);

	for ( int nRow = 0; nRow < 20; nRow++ )
	{
		m_ctrlHoga.InsertItem( nRow, _T("") );

		m_arrHogaColor.Add(0);
		m_arrMedosuDebiColor.Add(0);
	}

	m_ctrlHogaFooter.SetExtendedStyle( m_ctrlHogaFooter.GetExtendedStyle() | LVS_EX_GRIDLINES );
	m_ctrlHogaFooter.InsertColumn(0, _T(""), LVCFMT_RIGHT, 0);
	m_ctrlHogaFooter.InsertColumn(1, _T("매도총대비"), LVCFMT_RIGHT, 44);
	m_ctrlHogaFooter.InsertColumn(2, _T("매도총잔량"), LVCFMT_RIGHT,	65);
	m_ctrlHogaFooter.InsertColumn(3, _T("총순매수"), LVCFMT_CENTER,	130);
	m_ctrlHogaFooter.InsertColumn(4, _T("매수총잔량"), LVCFMT_RIGHT,	65);
	m_ctrlHogaFooter.InsertColumn(5, _T("매수총대비"), LVCFMT_RIGHT,	45);
	m_ctrlHogaFooter.InsertItem( 0, _T("") );

	m_ctrlConTickHeader.InsertColumn(0, _T(""), LVCFMT_RIGHT, 0);
	m_ctrlConTickHeader.InsertColumn(1, _T("시간"), LVCFMT_CENTER,	63);
	m_ctrlConTickHeader.InsertColumn(2, _T("현재가"), LVCFMT_CENTER,	75);
	m_ctrlConTickHeader.InsertColumn(3, _T("체결량"), LVCFMT_CENTER,	60);

	m_ctrlConTick.SetExtendedStyle( m_ctrlConTick.GetExtendedStyle() | LVS_EX_GRIDLINES );
	m_ctrlConTick.InsertColumn(0, _T(""), LVCFMT_RIGHT, 0);
	m_ctrlConTick.InsertColumn(1, _T("시간"), LVCFMT_CENTER,	62);
	m_ctrlConTick.InsertColumn(2, _T("현재가"), LVCFMT_RIGHT,	75);
	m_ctrlConTick.InsertColumn(3, _T("체결량"), LVCFMT_RIGHT,	60);

	m_ctrlDailyHeader.InsertColumn(0, _T(""), LVCFMT_CENTER, 0);
	m_ctrlDailyHeader.InsertColumn(1, _T("일자"), LVCFMT_CENTER, 66);
	m_ctrlDailyHeader.InsertColumn(2, _T("종가"), LVCFMT_CENTER,	73);
	m_ctrlDailyHeader.InsertColumn(3, _T("대비"), LVCFMT_CENTER,	81);
	m_ctrlDailyHeader.InsertColumn(4, _T("등락율"), LVCFMT_CENTER,	50);
	m_ctrlDailyHeader.InsertColumn(5, _T("거래량"), LVCFMT_CENTER,	73);
	m_ctrlDailyHeader.InsertColumn(6, _T("시가"), LVCFMT_CENTER,	73);
	m_ctrlDailyHeader.InsertColumn(7, _T("고가"), LVCFMT_CENTER,	73);
	m_ctrlDailyHeader.InsertColumn(8, _T("저가"), LVCFMT_CENTER,	73);

	m_ctrlDaily.SetExtendedStyle( m_ctrlDaily.GetExtendedStyle() | LVS_EX_GRIDLINES );
	m_ctrlDaily.InsertColumn(0, _T(""), LVCFMT_CENTER, 0);
	m_ctrlDaily.InsertColumn(1, _T("일자"), LVCFMT_CENTER, 65);
	m_ctrlDaily.InsertColumn(2, _T("종가"), LVCFMT_RIGHT,	73);
	m_ctrlDaily.InsertColumn(3, _T(""), LVCFMT_CENTER,	23);
	m_ctrlDaily.InsertColumn(4, _T("대비"), LVCFMT_RIGHT,	58);
	m_ctrlDaily.InsertColumn(5, _T("등락율"), LVCFMT_RIGHT,	50);
	m_ctrlDaily.InsertColumn(6, _T("거래량"), LVCFMT_RIGHT,	73);
	m_ctrlDaily.InsertColumn(7, _T("시가"), LVCFMT_RIGHT,	73);
	m_ctrlDaily.InsertColumn(8, _T("고가"), LVCFMT_RIGHT,	73);
	m_ctrlDaily.InsertColumn(9, _T("저가"), LVCFMT_RIGHT,	73);

	m_ctrlDaily.InsertItem( 0, _T("") );
	m_ctrlDaily.SetItemText( 0, 1, _T("현    재") );
}

BOOL CStockSiseDlg::CheckAPI()
{
	if ( NULL == m_pMainDlg )
		return FALSE;

	return m_pMainDlg->CheckAPI();
}

CString CStockSiseDlg::Commify( TCHAR* pData )
{
	if ( NULL == m_pMainDlg )
		return _T("");

	return m_pMainDlg->Commify( pData );
}

CString CStockSiseDlg::Commify( long nData )
{
	if ( NULL == m_pMainDlg )
		return _T("");

	return m_pMainDlg->Commify( nData );
}

CString CStockSiseDlg::Commify( double dData )
{
	if ( NULL == m_pMainDlg )
		return _T("");

	return m_pMainDlg->Commify( dData );
}

void CStockSiseDlg::Process300001()
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
	GetDlgItem( IDC_EDIT_CURJUKA )->SetWindowText( Commify(nData) );
	m_ctrlDaily.SetItemText( 0, 2, Commify(nData) );

	g_iYuantaAPI.YOA_GetTRFieldLong( _T("300001"), _T("OutBlock1"), _T("debi"), &nData );
	CString strDebi;
	if ( 0 < nData )
	{
		strDebi.Format(_T("▲  %s"), Commify(nData));
		m_ctrlDaily.SetItemText( 0, 3, _T("▲") );
	}
	else if ( 0 > nData )
	{
		nData = -nData;
		strDebi.Format(_T("▼  %s"), Commify(nData));
		m_ctrlDaily.SetItemText( 0, 3, _T("▼") );
	}
	else
	{
		strDebi.Format(_T("%d"), nData);
	}
	GetDlgItem( IDC_EDIT_DEBI )->SetWindowText( strDebi );

	m_ctrlDaily.SetItemText( 0, 4, Commify(nData) );

	g_iYuantaAPI.YOA_GetTRFieldDouble( _T("300001"), _T("OutBlock1"), _T("debirate"), &dData );
	GetDlgItem( IDC_EDIT_DEBIRATE )->SetWindowText( Commify(dData) );
	m_ctrlDaily.SetItemText( 0, 5, Commify(dData) );

	memset( data, 0x00, sizeof(data) );
	g_iYuantaAPI.YOA_GetTRFieldString( _T("300001"), _T("OutBlock1"), _T("volume"), data, sizeof(data) );
	GetDlgItem( IDC_EDIT_VOLUME )->SetWindowText( Commify(data) );
	m_ctrlDaily.SetItemText( 0, 6, Commify(data) );

	g_iYuantaAPI.YOA_GetTRFieldAttr( _T("300001"), _T("OutBlock1"), _T("startjuka"), &byteAttr );
	if ( 2 == byteAttr )
		m_nStartJukaColor = 1;
	else if ( 5 == byteAttr )
		m_nStartJukaColor = -1;
	else
		m_nStartJukaColor = 0;
	g_iYuantaAPI.YOA_GetTRFieldLong( _T("300001"), _T("OutBlock1"), _T("startjuka"), &nData );
	GetDlgItem( IDC_EDIT_STARTJUKA )->SetWindowText( Commify(nData) );
	m_ctrlDaily.SetItemText( 0, 7, Commify(nData) );

	g_iYuantaAPI.YOA_GetTRFieldAttr( _T("300001"), _T("OutBlock1"), _T("highjuka"), &byteAttr );
	if ( 2 == byteAttr )
		m_nHighJukaColor = 1;
	else if ( 5 == byteAttr )
		m_nHighJukaColor = -1;
	else
		m_nHighJukaColor = 0;
	g_iYuantaAPI.YOA_GetTRFieldLong( _T("300001"), _T("OutBlock1"), _T("highjuka"), &nData );
	GetDlgItem( IDC_EDIT_HIGHJUKA )->SetWindowText( Commify(nData) );
	m_ctrlDaily.SetItemText( 0, 8, Commify(nData) );

	g_iYuantaAPI.YOA_GetTRFieldAttr( _T("300001"), _T("OutBlock1"), _T("lowjuka"), &byteAttr );
	if ( 2 == byteAttr )
		m_nLowJukaColor = 1;
	else if ( 5 == byteAttr )
		m_nLowJukaColor = -1;
	else
		m_nLowJukaColor = 0;
	g_iYuantaAPI.YOA_GetTRFieldLong( _T("300001"), _T("OutBlock1"), _T("lowjuka"), &nData );
	GetDlgItem( IDC_EDIT_LOWJUKA )->SetWindowText( Commify(nData) );
	m_ctrlDaily.SetItemText( 0, 9, Commify(nData) );

	g_iYuantaAPI.YOA_GetTRFieldLong( _T("300001"), _T("OutBlock1"), _T("prevlastjuka"), &m_nPrevLastPrice, 0 );
	GetDlgItem( IDC_EDIT_PREVLASTJUKA )->SetWindowText( Commify(m_nPrevLastPrice) );
}

void CStockSiseDlg::Process300002()
{
	byte byteAttr = 0;
	long nData = 0;
	double dData = 0.0;
	long nHoga = 0;

	int nDataCount = g_iYuantaAPI.YOA_GetRowCount( _T("300002"), _T("OutBlock1") );
	for ( int i = 0; i < nDataCount; i++ )
	{
		g_iYuantaAPI.YOA_GetTRFieldAttr( _T("300002"), _T("OutBlock1"), _T("medohoka"), &byteAttr, i );
		if ( 2 == byteAttr )
			m_arrHogaColor.SetAt( 9 - i, 1 );
		else if ( 5 == byteAttr )
			m_arrHogaColor.SetAt( 9 - i, -1 );
		else
			m_arrHogaColor.SetAt( 9 - i, 0 );

		g_iYuantaAPI.YOA_GetTRFieldLong( _T("300002"), _T("OutBlock1"), _T("medohoka"), &nHoga, i );
		
		if ( 0 != nHoga )
		{
			m_ctrlHoga.SetItemText( 9 - i, 1, _T("0") );
			g_iYuantaAPI.YOA_GetTRFieldLong( _T("300002"), _T("OutBlock1"), _T("medovol"), &nData, i );
			m_ctrlHoga.SetItemText( 9 - i, 2, Commify(nData) );
			m_ctrlHoga.SetItemText( 9 - i, 3, Commify(nHoga) );
			dData = ((double)nHoga / (double)m_nPrevLastPrice - 1) * 100; 
			m_ctrlHoga.SetItemText( 9 - i, 4, Commify(dData) );
		}
		else
		{
			m_ctrlHoga.SetItemText( 9 - i, 1, _T("") );
			m_ctrlHoga.SetItemText( 9 - i, 2, _T("") );
			m_ctrlHoga.SetItemText( 9 - i, 3, _T("") );
			m_ctrlHoga.SetItemText( 9 - i, 4, _T("") );
		}

		g_iYuantaAPI.YOA_GetTRFieldAttr( _T("300002"), _T("OutBlock1"), _T("mesuhoka"), &byteAttr, i );
		if ( 2 == byteAttr )
			m_arrHogaColor.SetAt( 10 + i, 1 );
		else if ( 5 == byteAttr )
			m_arrHogaColor.SetAt( 10 + i, -1 );
		else
			m_arrHogaColor.SetAt( 10 + i, 0 );

		g_iYuantaAPI.YOA_GetTRFieldLong( _T("300002"), _T("OutBlock1"), _T("mesuhoka"), &nHoga, i );
		
		if ( 0 != nHoga )
		{
			m_ctrlHoga.SetItemText( 10 + i, 3, Commify(nHoga) );
			dData = ((double)nHoga / (double)m_nPrevLastPrice - 1) * 100; 
			m_ctrlHoga.SetItemText( 10 + i, 4, Commify(dData) );
			g_iYuantaAPI.YOA_GetTRFieldLong( _T("300002"), _T("OutBlock1"), _T("mesuvol"), &nData, i );
			m_ctrlHoga.SetItemText( 10 + i, 5, Commify(nData) );
			m_ctrlHoga.SetItemText( 10 + i, 6, _T("0") );
		}
		else
		{
			m_ctrlHoga.SetItemText( 10 + i, 3, _T("") );
			m_ctrlHoga.SetItemText( 10 + i, 4, _T("") );
			m_ctrlHoga.SetItemText( 10 + i, 5, _T("") );
			m_ctrlHoga.SetItemText( 10 + i, 6, _T("") );
		}
	}

	g_iYuantaAPI.YOA_GetTRFieldLong( _T("300002"), _T("OutBlock6"), _T("medotot"), &m_nMedoTot, 0 );
	g_iYuantaAPI.YOA_GetTRFieldLong( _T("300002"), _T("OutBlock6"), _T("mesutot"), &m_nMesuTot, 0 );
	m_ctrlHogaFooter.SetItemText( 0, 1, Commify(m_nMedoDebiTot) );
	m_ctrlHogaFooter.SetItemText( 0, 2, Commify(m_nMedoTot) );
	m_ctrlHogaFooter.SetItemText( 0, 3, Commify(m_nMesuTot-m_nMedoTot) );
	m_ctrlHogaFooter.SetItemText( 0, 4, Commify(m_nMesuTot) );
	m_ctrlHogaFooter.SetItemText( 0, 5, Commify(m_nMesuDebiTot) );

	byte byteData = 0;
	TCHAR data[1024] = {0,};

	nDataCount = g_iYuantaAPI.YOA_GetRowCount( _T("300002"), _T("OutBlock5") );
	for ( int i = 0; i < nDataCount; i++ )
	{
		m_ctrlConTick.InsertItem( i, _T("") );

		memset( data, 0x00, sizeof(data) );
		g_iYuantaAPI.YOA_GetTRFieldString( _T("300002"), _T("OutBlock5"), _T("time"), data, sizeof(data), i );
		m_ctrlConTick.SetItemText( i, 1, data );

		memset( data, 0x00, sizeof(data) );
		g_iYuantaAPI.YOA_GetTRFieldString( _T("300002"), _T("OutBlock5"), _T("curjuka"), data, sizeof(data), i );
		m_ctrlConTick.SetItemText( i, 2, Commify(data) );

		memset( data, 0x00, sizeof(data) );
		g_iYuantaAPI.YOA_GetTRFieldAttr( _T("300002"), _T("OutBlock5"), _T("nowvol"), &byteData, i );
		if ( 'S' == byteData )
			m_ctrlConTick.SetItemData( i, 1 );
		else if ( 'B' == byteData )
			m_ctrlConTick.SetItemData( i, -1 );
		else
			m_ctrlConTick.SetItemData( i, 0 );
		g_iYuantaAPI.YOA_GetTRFieldString( _T("300002"), _T("OutBlock5"), _T("nowvol"), data, sizeof(data), i );
		m_ctrlConTick.SetItemText( i, 3, Commify(data) );
	}

	memset( data, 0x00, sizeof(data) );
	g_iYuantaAPI.YOA_GetTRFieldString( _T("300002"), _T("OutBlock6"), _T("hokatime"), data, sizeof(data) );
	HDITEM hdi;
	hdi.mask = HDI_TEXT;
	hdi.pszText = data;
	hdi.cchTextMax = sizeof(data);
	m_ctrlHogaHeader.GetHeaderCtrl()->SetItem( 3, &hdi );

	UnregistAuto();
	RegistAuto( _T("11"), m_strJongCode );
	RegistAuto( _T("12"), m_strJongCode );
}

void CStockSiseDlg::Process301004()
{
	byte byteData = 0;
	long nData = 0;
	double dData = 0.0;
	TCHAR data[1024] = {0,};
	CString strData;

	g_iYuantaAPI.YOA_GetTRFieldByte( _T("301004"), _T("OutBlock1"), _T("next"), &byteData );
	if ( 1 == byteData )
	{
		GetDlgItem( IDC_BUTTON_NEXT )->EnableWindow( TRUE );
	}
	else
	{
		GetDlgItem( IDC_BUTTON_NEXT )->EnableWindow( FALSE );
	}

	int nIndex = 1;
	if ( TRUE == m_bNext_301004 )
	{
		nIndex = m_ctrlDaily.GetItemCount();
	}

	int nDataCount = g_iYuantaAPI.YOA_GetRowCount( _T("301004"), _T("OutBlock2") );
	for ( int i = 0; i < nDataCount; i++ )
	{
		m_ctrlDaily.InsertItem( nIndex, _T("") );

		memset( data, 0x00, sizeof(data) );
		g_iYuantaAPI.YOA_GetTRFieldString( _T("301004"), _T("OutBlock2"), _T("date"), data, sizeof(data), i );
		strData.Format( _T("%s"), data );
		strData.TrimLeft();
		m_ctrlDaily.SetItemText( nIndex, 1, strData );

		memset( data, 0x00, sizeof(data) );
		g_iYuantaAPI.YOA_GetTRFieldString( _T("301004"), _T("OutBlock2"), _T("lastjuka"), data, sizeof(data), i );
		m_ctrlDaily.SetItemText( nIndex, 2, Commify(data) );

		g_iYuantaAPI.YOA_GetTRFieldAttr( _T("301004"), _T("OutBlock2"), _T("debi"), &byteData, i );
		if ( 2 == byteData )
			m_ctrlDaily.SetItemData( nIndex, 1 );
		else if ( 5 == byteData )
			m_ctrlDaily.SetItemData( nIndex, -1 );
		else
			m_ctrlDaily.SetItemData( nIndex, 0 );
		g_iYuantaAPI.YOA_GetTRFieldLong(  _T("301004"), _T("OutBlock2"), _T("debi"), &nData, i );
		if ( 0 < nData )
		{
			m_ctrlDaily.SetItemText( nIndex, 3, _T("▲") );
		}
		else if ( 0 > nData )
		{
			nData = -nData;
			m_ctrlDaily.SetItemText( nIndex, 3, _T("▼") );
		}
		m_ctrlDaily.SetItemText( nIndex, 4, Commify(nData) );

		g_iYuantaAPI.YOA_GetTRFieldDouble(  _T("301004"), _T("OutBlock2"), _T("debirate"), &dData, i );
		if ( 0 < dData )
		{
			strData.Format( _T("+%s"), Commify(dData) );
		}
		else
		{
			strData.Format( _T("%s"), Commify(dData) );
		}
		m_ctrlDaily.SetItemText( nIndex, 5, strData );

		memset( data, 0x00, sizeof(data) );
		g_iYuantaAPI.YOA_GetTRFieldLong(  _T("301004"), _T("OutBlock2"), _T("volume"), &nData, i );
		m_ctrlDaily.SetItemText( nIndex, 6, Commify(nData) );

		memset( data, 0x00, sizeof(data) );
		g_iYuantaAPI.YOA_GetTRFieldLong(  _T("301004"), _T("OutBlock2"), _T("startjuka"), &nData, i );
		m_ctrlDaily.SetItemText( nIndex, 7, Commify(nData) );

		memset( data, 0x00, sizeof(data) );
		g_iYuantaAPI.YOA_GetTRFieldLong(  _T("301004"), _T("OutBlock2"), _T("highjuka"), &nData, i );
		m_ctrlDaily.SetItemText( nIndex, 8, Commify(nData) );

		memset( data, 0x00, sizeof(data) );
		g_iYuantaAPI.YOA_GetTRFieldLong(  _T("301004"), _T("OutBlock2"), _T("lowjuka"), &nData, i );
		m_ctrlDaily.SetItemText( nIndex, 9, Commify(nData) );

		nIndex++;
	}
}

void CStockSiseDlg::RegistAuto( CString strAutoID, CString strCode )
{
	if ( TRUE == CheckAPI() )
	{
		g_iYuantaAPI.YOA_SetTRFieldString( strAutoID, _T("InBlock1"), _T("jongcode"), strCode );
		g_iYuantaAPI.YOA_RegistAuto( GetSafeHwnd(), strAutoID );
	}
}

void CStockSiseDlg::UnregistAuto()
{
	if ( TRUE == CheckAPI() )
	{
		g_iYuantaAPI.YOA_UnregistAutoWithWindow( GetSafeHwnd() );
	}
}

void CStockSiseDlg::ProcessAuto11()
{
	byte byteAttr = 0;
	long nData = 0;
	double dData = 0.0;
	TCHAR data[1024] = {0,};
	CString strData;

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
	GetDlgItem( IDC_EDIT_CURJUKA )->SetWindowText( Commify(nCurJuka) );
	m_ctrlDaily.SetItemData( 0, m_nCurJukaColor );
	m_ctrlDaily.SetItemText( 0, 2, Commify(nCurJuka) );

	g_iYuantaAPI.YOA_GetTRFieldLong( _T("11"), _T("OutBlock1"), _T("debi"), &nDebi );
	if ( 0 < nDebi )
	{
		strData.Format(_T("▲  %s"), Commify(nDebi));
		
		m_ctrlDaily.SetItemText( 0, 3, _T("▲") );
	}
	else if ( 0 > nDebi )
	{
		nDebi = -nDebi;
		strData.Format(_T("▼  %s"), Commify(nDebi));

		m_ctrlDaily.SetItemText( 0, 3, _T("▼") );
	}
	else
	{
		strData.Format(_T("%d"), nData);
	}
	GetDlgItem( IDC_EDIT_DEBI )->SetWindowText( strData );
	m_ctrlDaily.SetItemText( 0, 4, Commify(nDebi) );

	g_iYuantaAPI.YOA_GetTRFieldDouble( _T("11"), _T("OutBlock1"), _T("debirate"), &dData );
	if ( 0 < dData )
	{
		strData.Format( _T("+%s"), Commify(dData) );
	}
	else
	{
		strData.Format( _T("%s"), Commify(dData) );
	}
	GetDlgItem( IDC_EDIT_DEBIRATE )->SetWindowText( strData );
	m_ctrlDaily.SetItemText( 0, 5, strData );

	memset( data, 0x00, sizeof(data) );
	g_iYuantaAPI.YOA_GetTRFieldString( _T("11"), _T("OutBlock1"), _T("volume"), data, sizeof(data) );
	GetDlgItem( IDC_EDIT_VOLUME )->SetWindowText( Commify(data) );
	m_ctrlDaily.SetItemText( 0, 6, Commify(data) );

	g_iYuantaAPI.YOA_GetTRFieldAttr( _T("11"), _T("OutBlock1"), _T("startjuka"), &byteAttr );
	if ( 2 == byteAttr )
		m_nStartJukaColor = 1;
	else if ( 5 == byteAttr )
		m_nStartJukaColor = -1;
	else
		m_nStartJukaColor = 0;
	g_iYuantaAPI.YOA_GetTRFieldLong( _T("11"), _T("OutBlock1"), _T("startjuka"), &nData );
	GetDlgItem( IDC_EDIT_STARTJUKA )->SetWindowText( Commify(nData) );
	m_ctrlDaily.SetItemText( 0, 7, Commify(nData) );

	g_iYuantaAPI.YOA_GetTRFieldAttr( _T("11"), _T("OutBlock1"), _T("highjuka"), &byteAttr );
	if ( 2 == byteAttr )
		m_nHighJukaColor = 1;
	else if ( 5 == byteAttr )
		m_nHighJukaColor = -1;
	else
		m_nHighJukaColor = 0;
	g_iYuantaAPI.YOA_GetTRFieldLong( _T("11"), _T("OutBlock1"), _T("highjuka"), &nData );
	GetDlgItem( IDC_EDIT_HIGHJUKA )->SetWindowText( Commify(nData) );
	m_ctrlDaily.SetItemText( 0, 8, Commify(nData) );

	g_iYuantaAPI.YOA_GetTRFieldAttr( _T("11"), _T("OutBlock1"), _T("lowjuka"), &byteAttr );
	if ( 2 == byteAttr )
		m_nLowJukaColor = 1;
	else if ( 5 == byteAttr )
		m_nLowJukaColor = -1;
	else
		m_nLowJukaColor = 0;
	g_iYuantaAPI.YOA_GetTRFieldLong( _T("11"), _T("OutBlock1"), _T("lowjuka"), &nData );
	GetDlgItem( IDC_EDIT_LOWJUKA )->SetWindowText( Commify(nData) );
	m_ctrlDaily.SetItemText( 0, 9, Commify(nData) );

	int nRowCnt = m_ctrlConTick.GetItemCount();
	if ( 19 < nRowCnt )
		m_ctrlConTick.DeleteItem( nRowCnt - 1 );
	m_ctrlConTick.InsertItem( 0, _T("") );

	memset( data, 0x00, sizeof(data) );
	g_iYuantaAPI.YOA_GetTRFieldString( _T("11"), _T("OutBlock1"), _T("time2"), data, sizeof(data) );
	m_ctrlConTick.SetItemText( 0, 1, data );

	memset( data, 0x00, sizeof(data) );
	g_iYuantaAPI.YOA_GetTRFieldString( _T("11"), _T("OutBlock1"), _T("curjuka"), data, sizeof(data) );
	m_ctrlConTick.SetItemText( 0, 2, Commify(data) );

	memset( data, 0x00, sizeof(data) );
	g_iYuantaAPI.YOA_GetTRFieldAttr( _T("11"), _T("OutBlock1"), _T("nowvol"), &byteAttr );
	if ( 'S' == byteAttr )
		m_ctrlConTick.SetItemData( 0, 1 );
	else if ( 'B' == byteAttr )
		m_ctrlConTick.SetItemData( 0, -1 );
	else
		m_ctrlConTick.SetItemData( 0, 0 );
	g_iYuantaAPI.YOA_GetTRFieldString( _T("11"), _T("OutBlock1"), _T("nowvol"), data, sizeof(data) );
	m_ctrlConTick.SetItemText( 0, 3, Commify(data) );
}

void CStockSiseDlg::ProcessAuto12()
{
	long nData = 0;
	double dData = 0.0;
	long nHoga = 0;
	byte byteAttr = 0;

	m_nMedoDebiTot	= 0;
	m_nMesuDebiTot	= 0;
	m_nMedoTot		= 0;
	m_nMesuTot		= 0;

	int nDataCount = g_iYuantaAPI.YOA_GetRowCount( _T("12"), _T("OutBlock2") );
	for ( int i = 0; i < nDataCount; i++ )
	{
	
		g_iYuantaAPI.YOA_GetTRFieldAttr( _T("12"), _T("OutBlock2"), _T("medohoka"), &byteAttr, i );
		if ( 2 == byteAttr )
			m_arrHogaColor.SetAt( 9 - i, 1 );
		else if ( 5 == byteAttr )
			m_arrHogaColor.SetAt( 9 - i, -1 );
		else
			m_arrHogaColor.SetAt( 9 - i, 0 );

		g_iYuantaAPI.YOA_GetTRFieldLong( _T("12"), _T("OutBlock2"), _T("medohoka"), &nHoga, i );
		
		if ( 0 != nHoga )
		{
			g_iYuantaAPI.YOA_GetTRFieldLong( _T("12"), _T("OutBlock2"), _T("medodebi"), &nData, i );
			if ( 0 < nData )
				m_arrMedosuDebiColor.SetAt( 9 - i, 1 );
			else if ( 0 > nData )
				m_arrMedosuDebiColor.SetAt( 9 - i, -1 );
			else
				m_arrMedosuDebiColor.SetAt( 9 - i, 0 );
			m_nMedoDebiTot += nData;
			m_ctrlHoga.SetItemText( 9 - i, 1, Commify(nData) );

			g_iYuantaAPI.YOA_GetTRFieldLong( _T("12"), _T("OutBlock2"), _T("medovol"), &nData, i );
			m_nMedoTot += nData;
			m_ctrlHoga.SetItemText( 9 - i, 2, Commify(nData) );
			m_ctrlHoga.SetItemText( 9 - i, 3, Commify(nHoga) );
			dData = ((double)nHoga / (double)m_nPrevLastPrice - 1) * 100; 
			m_ctrlHoga.SetItemText( 9 - i, 4, Commify(dData) );
		}
		else
		{
			m_ctrlHoga.SetItemText( 9 - i, 1, _T("") );
			m_ctrlHoga.SetItemText( 9 - i, 2, _T("") );
			m_ctrlHoga.SetItemText( 9 - i, 3, _T("") );
			m_ctrlHoga.SetItemText( 9 - i, 4, _T("") );
		}

		g_iYuantaAPI.YOA_GetTRFieldAttr( _T("12"), _T("OutBlock2"), _T("mesuhoka"), &byteAttr, i );
		if ( 2 == byteAttr )
			m_arrHogaColor.SetAt( 10 + i, 1 );
		else if ( 5 == byteAttr )
			m_arrHogaColor.SetAt( 10 + i, -1 );
		else
			m_arrHogaColor.SetAt( 10 + i, 0 );

		g_iYuantaAPI.YOA_GetTRFieldLong( _T("12"), _T("OutBlock2"), _T("mesuhoka"), &nHoga, i );
		
		if ( 0 != nHoga )
		{
			m_ctrlHoga.SetItemText( 10 + i, 3, Commify(nHoga) );
			dData = ((double)nHoga / (double)m_nPrevLastPrice - 1) * 100; 
			m_ctrlHoga.SetItemText( 10 + i, 4, Commify(dData) );
			g_iYuantaAPI.YOA_GetTRFieldLong( _T("12"), _T("OutBlock2"), _T("mesuvol"), &nData, i );
			m_nMesuTot += nData;
			m_ctrlHoga.SetItemText( 10 + i, 5, Commify(nData) );

			g_iYuantaAPI.YOA_GetTRFieldLong( _T("12"), _T("OutBlock2"), _T("mesudebi"), &nData, i );
			if ( 0 < nData )
				m_arrMedosuDebiColor.SetAt( 10 + i, 1 );
			else if ( 0 > nData )
				m_arrMedosuDebiColor.SetAt( 10 + i, -1 );
			else
				m_arrMedosuDebiColor.SetAt( 10 + i, 0 );
			m_nMesuDebiTot += nData;
			m_ctrlHoga.SetItemText( 10 + i, 6, Commify(nData) );
		}
		else
		{
			m_ctrlHoga.SetItemText( 10 + i, 3, _T("") );
			m_ctrlHoga.SetItemText( 10 + i, 4, _T("") );
			m_ctrlHoga.SetItemText( 10 + i, 5, _T("") );
			m_ctrlHoga.SetItemText( 10 + i, 6, _T("") );
		}
		
	}

	TCHAR data[10] = {0,};
	g_iYuantaAPI.YOA_GetTRFieldString( _T("12"), _T("OutBlock3"), _T("time"), data, sizeof(data) );
	HDITEM hdi;
	hdi.mask = HDI_TEXT;
	hdi.pszText = data;
	hdi.cchTextMax = sizeof(data);
	m_ctrlHogaHeader.GetHeaderCtrl()->SetItem( 3, &hdi );

	m_ctrlHogaFooter.SetItemText( 0, 1, Commify(m_nMedoDebiTot) );
	m_ctrlHogaFooter.SetItemText( 0, 2, Commify(m_nMedoTot) );
	m_ctrlHogaFooter.SetItemText( 0, 3, Commify(m_nMesuTot-m_nMedoTot) );
	m_ctrlHogaFooter.SetItemText( 0, 4, Commify(m_nMesuTot) );
	m_ctrlHogaFooter.SetItemText( 0, 5, Commify(m_nMesuDebiTot) );
	
}

// cStockSiseDlg 메시지 처리기입니다.


BOOL CStockSiseDlg::PreTranslateMessage(MSG* pMsg)
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

BOOL CStockSiseDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	InitControl();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

LRESULT CStockSiseDlg::OnReceiveError(WPARAM wParam, LPARAM lParam)
{

	LRESULT ret = 0;

	int nReqID = wParam;

	CString strMsg;
	CString strTrName;

	if ( nReqID == m_nReqID_300001 )
	{
		strTrName = _T("[300001]주식현재가");
	}
	else if ( nReqID == m_nReqID_300002 )
	{
		strTrName = _T("[300002]주식현재가_호가체결");
	}
	else if ( nReqID == m_nReqID_301004 )
	{
		strTrName = _T("[301004]수정일자별주가");
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

LRESULT CStockSiseDlg::OnReceiveData(WPARAM wParam, LPARAM lParam)
{
	LRESULT ret = 0;

	CString strTrName = _T("");

	if ( wParam == m_nReqID_300001 )
	{
		strTrName = _T("[300001]주식현재가");

		Process300001();
	}
	else if ( wParam == m_nReqID_300002 )
	{
		strTrName = _T("[300002]주식현재가_호가체결");

		Process300002();
	}
	else if ( wParam == m_nReqID_301004 )
	{
		strTrName = _T("[301004]수정일자별주가");

		Process301004();
	}

	if ( 0 < strTrName.GetLength() )
	{
		CString strMsg;
		strMsg.Format( _T("[ReqID:%d] %s 응답을 수신하였습니다."), wParam, strTrName );
		m_pMainDlg->LogMessage( strMsg );
	}

	return ret;
}

LRESULT CStockSiseDlg::OnReceiveRealData(WPARAM wParam, LPARAM lParam)
{
	LRESULT ret = 0;

	//CString strAutoID( (LPCTSTR)(LPCSTR)lParam );
	LPRECV_DATA pRecvData = (LPRECV_DATA)lParam;
	CString strAutoID( pRecvData->szTrCode );
	
	if ( 0 == strAutoID.Compare( _T("11") ) )
		ProcessAuto11();
	else if ( 0 == strAutoID.Compare( _T("12") ) )
		ProcessAuto12();
	
	return ret;
}

void CStockSiseDlg::OnBnClickedButtonSearch()
{
	if ( TRUE == CheckAPI() )
	{
		UpdateData();

		m_strJongCode.TrimRight();
		if ( 6 == m_strJongCode.GetLength() )
		{
			g_iYuantaAPI.YOA_ReleaseData( m_nReqID_301004 );

			m_ctrlConTick.DeleteAllItems();
			m_ctrlDaily.DeleteAllItems();
			m_ctrlDaily.InsertItem( 0, _T("") );
			m_ctrlDaily.SetItemText( 0, 1, _T("현    재") );

			m_nMedoDebiTot	= 0;
			m_nMesuDebiTot	= 0;
			m_nMedoTot		= 0;
			m_nMesuTot		= 0;
			m_bNext_301004	= FALSE;

			TCHAR szJang[64] = {0,};
			g_iYuantaAPI.YOA_GetCodeInfo( MARKET_TYPE_INTERNAL, CODE_INFO_JANG_GUBUN, m_strJongCode, szJang, sizeof(szJang) );
			
			int nJang = _wtoi( szJang );
			g_iYuantaAPI.YOA_SetTRFieldByte( _T("300001"), _T("InBlock1"), _T("jang"), (byte)nJang );
			//g_iYuantaAPI.YOA_SetTRFieldString( _T("300001"), _T("InBlock1"), _T("jang"), strJang );
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
				TCHAR msg[2048] = {0,};

				//int nErrorCode = g_iYuantaAPI.YOA_GetLastError();
				int nErrorCode = m_nReqID_300001;
				g_iYuantaAPI.YOA_GetErrorMessage( nErrorCode, msg, sizeof(msg) );

				CString strErrorMsg;
				strErrorMsg.Format( _T("[%d] %s"), nErrorCode, msg );

				m_pMainDlg->LogMessage( _T("[300001]주식현재가 조회 요청중 오류가 발생하였습니다."), 1 );
				m_pMainDlg->LogMessage( strErrorMsg, 1, FALSE );
			}

			/*
			g_iYuantaAPI.YOA_SetTRFieldByte( _T("300002"), _T("InBlock1"), _T("jang"), nJang );
			g_iYuantaAPI.YOA_SetTRFieldString( _T("300002"), _T("InBlock1"), _T("jongcode"), m_strJongCode );
			g_iYuantaAPI.YOA_SetTRFieldString( _T("300002"), _T("InBlock1"), _T("outflag"), _T("N") );
			*/

			g_iYuantaAPI.YOA_SetTRInfo( _T("300002"), _T("InBlock1") );
			g_iYuantaAPI.YOA_SetFieldString( _T("jang"), szJang );
			g_iYuantaAPI.YOA_SetFieldString( _T("jongcode"), m_strJongCode );
			g_iYuantaAPI.YOA_SetFieldString( _T("outflag"), _T("N") );
			m_nReqID_300002 = g_iYuantaAPI.YOA_Request( GetSafeHwnd(), _T("300002") );

			if ( ERROR_MAX_CODE < m_nReqID_300002 )
			{
				CString strMsg;
				strMsg.Format( _T("[ReqID:%d] [300002]주식현재가_호가체결 조회를 요청하였습니다."), m_nReqID_300002 );

				m_pMainDlg->LogMessage( strMsg );
			}
			else
			{
				TCHAR msg[1024] = {0,};

				//int nErrorCode = g_iYuantaAPI.YOA_GetLastError();
				int nErrorCode = m_nReqID_300002;
				g_iYuantaAPI.YOA_GetErrorMessage( nErrorCode, msg, sizeof(msg) );

				CString strErrorMsg;
				strErrorMsg.Format( _T("[%d] %s"), nErrorCode, msg );

				m_pMainDlg->LogMessage( _T("[300002]주식현재가_호가체결 조회 요청중 오류가 발생하였습니다."), 1 );
				m_pMainDlg->LogMessage( strErrorMsg, 1, FALSE );
			}

			CTime date = CTime::GetCurrentTime();
			CString strDate;
			strDate.Format( _T("%d%02d%02d"), date.GetYear(), date.GetMonth(), date.GetDay() );

			g_iYuantaAPI.YOA_SetTRFieldString( _T("301004"), _T("InBlock1"), _T("jongcode"), m_strJongCode );
			g_iYuantaAPI.YOA_SetTRFieldString( _T("301004"), _T("InBlock1"), _T("janggubun"), szJang );
			g_iYuantaAPI.YOA_SetTRFieldString( _T("301004"), _T("InBlock1"), _T("searchdate"), strDate );
			g_iYuantaAPI.YOA_SetTRFieldString( _T("301004"), _T("InBlock1"), _T("daygubun"), _T("1") );
			g_iYuantaAPI.YOA_SetTRFieldString( _T("301004"), _T("InBlock1"), _T("querygubun"), _T("0") );
			g_iYuantaAPI.YOA_SetTRFieldString( _T("301004"), _T("InBlock1"), _T("bpquery"), _T("0") );
			m_nReqID_301004 = g_iYuantaAPI.YOA_Request( GetSafeHwnd(), _T("301004"), FALSE );

			if ( ERROR_MAX_CODE < m_nReqID_301004 )
			{
				CString strMsg;
				strMsg.Format( _T("[ReqID:%d] [301004]수정일자별주가 조회를 요청하였습니다."), m_nReqID_301004 );

				m_pMainDlg->LogMessage( strMsg );
			}
			else
			{
				TCHAR msg[1024] = {0,};

				//int nErrorCode = g_iYuantaAPI.YOA_GetLastError();
				int nErrorCode = m_nReqID_301004;
				g_iYuantaAPI.YOA_GetErrorMessage( nErrorCode, msg, sizeof(msg) );

				CString strErrorMsg;
				strErrorMsg.Format( _T("[%d] %s"), nErrorCode, msg );

				m_pMainDlg->LogMessage( _T("[301004]수정일자별주가 조회 요청중 오류가 발생하였습니다."), 1 );
				m_pMainDlg->LogMessage( strErrorMsg, 1, FALSE );
			}
		
		}
	}
}

void CStockSiseDlg::OnBnClickedButtonNext()
{
	m_bNext_301004 = TRUE;
	g_iYuantaAPI.YOA_Request( GetSafeHwnd(), _T("301004"), FALSE, m_nReqID_301004 );
}

void CStockSiseDlg::OnNMCustomdrawListHoga(NMHDR *pNMHDR, LRESULT *pResult)
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

			if ( 1 == nCol && 10 > nRow )
			{
				int nColor = m_arrMedosuDebiColor[nRow];

				if ( 1 == nColor )
					pNMCD->clrText = RGB( 255, 0, 0 );
				else if ( -1 == nColor )
					pNMCD->clrText = RGB( 0, 0, 255 );
				else
					pNMCD->clrText = RGB( 0, 0, 0 );
			}
			else if ( 3 == nCol || 4 == nCol )
			{
				int nColor = m_arrHogaColor[nRow];

				if ( 1 == nColor )
					pNMCD->clrText = RGB( 255, 0, 0 );
				else if ( -1 == nColor )
					pNMCD->clrText = RGB( 0, 0, 255 );
				else
					pNMCD->clrText = RGB( 0, 0, 0 );
			}
			else if ( 6 == nCol && 9 < nRow )
			{
				int nColor = m_arrMedosuDebiColor[nRow];

				if ( 1 == nColor )
					pNMCD->clrText = RGB( 255, 0, 0 );
				else if ( -1 == nColor )
					pNMCD->clrText = RGB( 0, 0, 255 );
				else
					pNMCD->clrText = RGB( 0, 0, 0 );
			}

			else
				pNMCD->clrText = RGB( 0, 0, 0 );

			if ( 10 > nRow )
			{
				pNMCD->clrTextBk = RGB(235, 247, 255);
			}
			else
			{
				pNMCD->clrTextBk = RGB(255, 234, 234);
			}
		}
		break;
	}
}

void CStockSiseDlg::OnNMCustomdrawListHogaFooter(NMHDR *pNMHDR, LRESULT *pResult)
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
				if ( 0 < m_nMedoDebiTot )
					pNMCD->clrText = RGB( 255, 0, 0 );
				else if ( 0 > m_nMedoDebiTot )
					pNMCD->clrText = RGB( 0, 0, 255 );
				else
					pNMCD->clrText = RGB( 0, 0, 0 );
			}
			else if ( 2 == nCol )
			{
				pNMCD->clrText = RGB( 0, 0, 255 );
			}
			else if ( 3 == nCol )
			{
				if ( 0 < (m_nMesuTot - m_nMedoTot) )
					pNMCD->clrText = RGB( 255, 0, 0 );
				else if ( 0 > (m_nMesuTot - m_nMedoTot) )
					pNMCD->clrText = RGB( 0, 0, 255 );
				else
					pNMCD->clrText = RGB( 0, 0, 0 );
			}
			else if ( 4 == nCol )
			{
				pNMCD->clrText = RGB( 255, 0, 0 );
			}
			else if ( 5 == nCol )
			{
				if ( 0 < m_nMesuDebiTot )
					pNMCD->clrText = RGB( 255, 0, 0 );
				else if ( 0 > m_nMesuDebiTot )
					pNMCD->clrText = RGB( 0, 0, 255 );
				else
					pNMCD->clrText = RGB( 0, 0, 0 );
			}
			else
				pNMCD->clrText = RGB( 0, 0, 0 );

			pNMCD->clrTextBk = RGB(248, 248, 248);
		}
		break;
	}
}

void CStockSiseDlg::OnNMCustomdrawListConTick(NMHDR *pNMHDR, LRESULT *pResult)
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

			if ( 3 == nCol )
			{
				char attr = (char)m_ctrlConTick.GetItemData(nRow);

				if ( 1 == attr )
					pNMCD->clrText = RGB( 255, 0, 0 );
				else if ( -1 == attr )
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

void CStockSiseDlg::OnNMCustomdrawListDaily(NMHDR *pNMHDR, LRESULT *pResult)
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

			if ( 0 == nRow )
			{
				if ( 2 == nCol || 3 == nCol || 4 == nCol || 5 == nCol )
				{
					if ( 1 == m_nCurJukaColor )
						pNMCD->clrText = RGB(255, 0, 0);
					else if ( -1 == m_nCurJukaColor )
						pNMCD->clrText = RGB(0, 0, 255);
					else
						pNMCD->clrText = RGB(0, 0, 0);
				}
				else if ( 7 == nCol )
				{
					if ( 1 == m_nStartJukaColor )
						pNMCD->clrText = RGB(255, 0, 0);
					else if ( -1 == m_nStartJukaColor )
						pNMCD->clrText = RGB(0, 0, 255);
					else
						pNMCD->clrText = RGB(0, 0, 0);
				}
				else if ( 8 == nCol )
				{
					if ( 1 == m_nHighJukaColor )
						pNMCD->clrText = RGB(255, 0, 0);
					else if ( -1 == m_nHighJukaColor )
						pNMCD->clrText = RGB(0, 0, 255);
					else
						pNMCD->clrText = RGB(0, 0, 0);
				}
				else if ( 9 == nCol )
				{
					if ( 1 == m_nLowJukaColor )
						pNMCD->clrText = RGB(255, 0, 0);
					else if ( -1 == m_nLowJukaColor )
						pNMCD->clrText = RGB(0, 0, 255);
					else
						pNMCD->clrText = RGB(0, 0, 0);
				}
				else
				{
					pNMCD->clrText = RGB(0, 0, 0);
				}
			}
			else 
			{
				if ( 2 == nCol || 3 == nCol || 4 == nCol || 5 == nCol )
				{
					int nColor = m_ctrlDaily.GetItemData( nRow );

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
		}
		break;
	}
}

HBRUSH CStockSiseDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	int nID = pWnd->GetDlgCtrlID();
	switch(nID)
	{
	case IDC_EDIT_CURJUKA:
	case IDC_EDIT_DEBI:
	case IDC_EDIT_DEBIRATE:
		{
			if ( 1 == m_nCurJukaColor )
				pDC->SetTextColor( RGB(255, 0, 0) );
			else if ( -1 == m_nCurJukaColor )
				pDC->SetTextColor( RGB(0, 0, 255) );
			else
				pDC->SetTextColor( RGB(0, 0, 0) );
		}
		break;
	case IDC_EDIT_STARTJUKA:
		{
			if ( 1 == m_nStartJukaColor )
				pDC->SetTextColor( RGB(255, 0, 0) );
			else if ( -1 == m_nStartJukaColor )
				pDC->SetTextColor( RGB(0, 0, 255) );
			else
				pDC->SetTextColor( RGB(0, 0, 0) );
		}
		break;
	case IDC_EDIT_HIGHJUKA:
		{
			if ( 1 == m_nHighJukaColor )
				pDC->SetTextColor( RGB(255, 0, 0) );
			else if ( -1 == m_nHighJukaColor )
				pDC->SetTextColor( RGB(0, 0, 255) );
			else
				pDC->SetTextColor( RGB(0, 0, 0) );
		}
		break;
	case IDC_EDIT_LOWJUKA:
		{
			if ( 1 == m_nLowJukaColor )
				pDC->SetTextColor( RGB(255, 0, 0) );
			else if ( -1 == m_nLowJukaColor )
				pDC->SetTextColor( RGB(0, 0, 255) );
			else
				pDC->SetTextColor( RGB(0, 0, 0) );
		}
		break;
	}
	
	return hbr;
}

