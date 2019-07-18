// TransactionDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "YOADLLClient.h"
#include "TransactionDlg.h"
#include "afxdialogex.h"
#include "../../include/MessageDef.h"
#include "YOADLLClientDlg.h"

// CTransactionDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CTransactionDlg, CDialog)

CTransactionDlg::CTransactionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTransactionDlg::IDD, pParent)
{
	m_strInBlockName = _T("InBlock1");
	m_strOutBlockName = _T("OutBlock1");
	m_strOutArrayBlockName = _T("OutBlock2");
	m_nInArrayIndex = 0;
	m_nOutArrayIndex = 0;

	m_pMainDlg = NULL;
	m_nReqID = -1;
}

CTransactionDlg::~CTransactionDlg()
{
}

void CTransactionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_IN_BLOCKNAME, m_strInBlockName);
	DDX_Text(pDX, IDC_EDIT_IN_FIELDNAME, m_strInFieldName);
	DDX_Text(pDX, IDC_EDIT_IN_FIELDVALUE, m_strInFieldValue);
	DDX_Text(pDX, IDC_EDIT_OUT_BLOCKNAME, m_strOutBlockName);
	DDX_Text(pDX, IDC_EDIT_OUT_FIELDNAME, m_strOutFieldName);
	DDX_Text(pDX, IDC_EDIT_OUT_ARRAY_BLOCKNAME, m_strOutArrayBlockName);
	DDX_Text(pDX, IDC_EDIT_OUT_ARRAY_FIELDNAME, m_strOutArrayFieldName);
	DDX_Text(pDX, IDC_EDIT_IN_DSONO, m_strDSO);
	DDX_Text(pDX, IDC_EDIT_IN_ARRAY_INDEX, m_nInArrayIndex);
	DDV_MinMaxInt(pDX, m_nInArrayIndex, 0, 1000);
	DDX_Text(pDX, IDC_EDIT_OUT_ARRAY_INDEX, m_nOutArrayIndex);
	DDV_MinMaxInt(pDX, m_nOutArrayIndex, 0, 1000);
	DDX_Control(pDX, IDC_LIST_INBLOCK, m_ctrlInBlocks);
	DDX_Control(pDX, IDC_LIST_OUTBLOCK, m_ctrlOutBlocks);
	DDX_Control(pDX, IDC_LIST_ARRAY_OUTBLOCK, m_ctrlOutArrayBlock);
}


BEGIN_MESSAGE_MAP(CTransactionDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_REQUEST, &CTransactionDlg::OnBnClickedButtonRequest)
	ON_BN_CLICKED(IDC_BUTTON_NEXT_REQUEST, &CTransactionDlg::OnBnClickedButtonNextRequest)
	ON_BN_CLICKED(IDC_BUTTON_DSO_INIT, &CTransactionDlg::OnBnClickedButtonDsoInit)
	ON_BN_CLICKED(IDC_BUTTON_IN_ADD, &CTransactionDlg::OnBnClickedButtonInAdd)
	ON_BN_CLICKED(IDC_BUTTON_IN_DEL, &CTransactionDlg::OnBnClickedButtonInDel)
	ON_BN_CLICKED(IDC_BUTTON_OUT_ADD, &CTransactionDlg::OnBnClickedButtonOutAdd)
	ON_BN_CLICKED(IDC_BUTTON_OUT_DEL, &CTransactionDlg::OnBnClickedButtonOutDel)
	ON_MESSAGE(WMU_RECEIVE_ERROR, OnReceiveError)
	ON_MESSAGE(WMU_RECEIVE_DATA, OnReceiveData)
	ON_BN_CLICKED(IDC_BUTTON_OUT_ARRAY_ADD, &CTransactionDlg::OnBnClickedButtonOutArrayAdd)
	ON_BN_CLICKED(IDC_BUTTON_OUT_ARRAY_DEL, &CTransactionDlg::OnBnClickedButtonOutArrayDel)
	ON_NOTIFY(HDN_ITEMCLICK, 0, &CTransactionDlg::OnHdnItemclickListArrayOutblock)
END_MESSAGE_MAP()


void CTransactionDlg::InitControl()
{
	m_ctrlInBlocks.SetExtendedStyle( m_ctrlInBlocks.GetExtendedStyle() | LVS_EX_GRIDLINES );
	m_ctrlInBlocks.SetExtendedStyle( m_ctrlInBlocks.GetExtendedStyle() | LVS_EX_FULLROWSELECT );

	m_ctrlInBlocks.InsertColumn(0, _T(""), LVCFMT_RIGHT, 0);
	m_ctrlInBlocks.InsertColumn(1, _T("블록명"), LVCFMT_CENTER,	85);
	m_ctrlInBlocks.InsertColumn(2, _T("필드명"), LVCFMT_CENTER,	100);
	m_ctrlInBlocks.InsertColumn(3, _T("필드값"), LVCFMT_CENTER,	100);
	m_ctrlInBlocks.InsertColumn(4, _T("인덱스"), LVCFMT_CENTER,	50);

	m_ctrlOutBlocks.SetExtendedStyle( m_ctrlOutBlocks.GetExtendedStyle() | LVS_EX_GRIDLINES );
	m_ctrlOutBlocks.SetExtendedStyle( m_ctrlOutBlocks.GetExtendedStyle() | LVS_EX_FULLROWSELECT );

	m_ctrlOutBlocks.InsertColumn(0, _T(""), LVCFMT_RIGHT, 0);
	m_ctrlOutBlocks.InsertColumn(1, _T("블록명"), LVCFMT_CENTER,	85);
	m_ctrlOutBlocks.InsertColumn(2, _T("필드명"), LVCFMT_CENTER,	100);
	m_ctrlOutBlocks.InsertColumn(3, _T("필드값"), LVCFMT_CENTER,	100);
	m_ctrlOutBlocks.InsertColumn(4, _T("인덱스"), LVCFMT_CENTER,	50);

	m_ctrlOutArrayBlock.SetExtendedStyle( m_ctrlOutArrayBlock.GetExtendedStyle() | LVS_EX_GRIDLINES );

	m_ctrlOutArrayBlock.InsertColumn(0, _T(""), LVCFMT_RIGHT, 0);
}

void CTransactionDlg::SetSample()
{
	/*
	m_strDSO = _T("301004");
	UpdateData(FALSE);

	CTime date = CTime::GetCurrentTime();
	
	CString strDate;
	strDate.Format( _T("%d%02d%02d"), date.GetYear(), date.GetMonth(), date.GetDay() );

	AddBlockItem( _T("InBlock1"), _T("jongcode"), _T("005930") );
	AddBlockItem( _T("InBlock1"), _T("janggubun"), _T("1") );
	AddBlockItem( _T("InBlock1"), _T("searchdate"), strDate );
	AddBlockItem( _T("InBlock1"), _T("daygubun"), _T("1") );
	AddBlockItem( _T("InBlock1"), _T("querygubun"), _T("0") );
	AddBlockItem( _T("InBlock1"), _T("bpquery"), _T("0") );

	AddBlockItem( _T("OutBlock1"), _T("faceprice"), _T(""), 0, FALSE );
	AddBlockItem( _T("OutBlock1"), _T("next"), _T(""), 0, FALSE );
	AddBlockItem( _T("NextBlock1"), _T("condate"), _T(""), 0, FALSE );
	*/
	/*
	m_strDSO = _T("160001");
	UpdateData(FALSE);

	AddBlockItem( _T("InBlock1"), _T("acnt_aid"), _T("50404129013") );
	AddBlockItem( _T("InBlock1"), _T("passwd"), _T("2010") );
	AddBlockItem( _T("InBlock1"), _T("jumun_gubun"), _T("2") );
	AddBlockItem( _T("InBlock1"), _T("meme_gubun"), _T("L") );
	AddBlockItem( _T("InBlock1"), _T("jong_code"), _T("101N3") );
	AddBlockItem( _T("InBlock1"), _T("order_cnt"), _T("1") );
	AddBlockItem( _T("InBlock1"), _T("order_price"), _T("329.20") );
	AddBlockItem( _T("InBlock1"), _T("jang_gubun"), _T("0") );
	AddBlockItem( _T("InBlock1"), _T("futu_ord_if"), _T("S") );
	*/
	
	m_strDSO = _T("402001");
	UpdateData(FALSE);

	AddBlockItem( _T("InBlock1"), _T("janggubun"), _T("5") );
	AddBlockItem( _T("InBlock1"), _T("jongcode"), _T("101N3000") );
	AddBlockItem( _T("InBlock1"), _T("linkgb"), _T("0") );
	AddBlockItem( _T("InBlock1"), _T("timeuint"), _T("001M") );
	AddBlockItem( _T("InBlock1"), _T("startdate"), _T("0") );
	AddBlockItem( _T("InBlock1"), _T("starttime"), _T("0") );
	AddBlockItem( _T("InBlock1"), _T("enddate"), _T("20171023") );
	AddBlockItem( _T("InBlock1"), _T("endtime"), _T("235959") );
	AddBlockItem( _T("InBlock1"), _T("readcount"), _T("20") );
	
}

BOOL CTransactionDlg::CheckAPI()
{
	if ( NULL == m_pMainDlg )
		return FALSE;

	return m_pMainDlg->CheckAPI();
}

void CTransactionDlg::AddBlockItem( CString strBlockName, CString strFieldName, CString strFieldValue, int nIndex /* = 0 */, BOOL bInBlock /* = TRUE */ )
{
	CListCtrl* pList = ( bInBlock ? &m_ctrlInBlocks : &m_ctrlOutBlocks );

	BOOL bFindBlock = FALSE;
	CString strTemp;
	CString strIndex;

	strIndex.Format( _T("%d"), nIndex );

	int nRowCnt = pList->GetItemCount();
	for ( int nRow = 0; nRow < nRowCnt; nRow++ )
	{
		strTemp = pList->GetItemText(nRow, 0);

		if ( strTemp == strBlockName )
		{
			bFindBlock = TRUE;
		}
		else
		{
			if ( TRUE == bFindBlock && 0 < strFieldName.GetLength() )
			{
				pList->InsertItem( nRow, _T("Field") );
				pList->SetItemText( nRow, 0, strBlockName );
				pList->SetItemText( nRow, 2, strFieldName );
				pList->SetItemText( nRow, 3, strFieldValue );
				pList->SetItemText( nRow, 4, strIndex );

				return;
			}
		}
	}

	int nRow = nRowCnt;

	if ( FALSE == bFindBlock && 0 < strFieldName.GetLength() )
	{
		pList->InsertItem( nRow, _T("Block") );
		pList->SetItemText( nRow, 0, strBlockName );
		pList->SetItemText( nRow, 1, strBlockName );

		nRow++;
		pList->InsertItem( nRow, _T("Field") );
		pList->SetItemText( nRow, 0, strBlockName );
		pList->SetItemText( nRow, 2, strFieldName );
		pList->SetItemText( nRow, 3, strFieldValue );
		pList->SetItemText( nRow, 4, strIndex );
	}
	else if ( TRUE == bFindBlock && 0 < strFieldName.GetLength() )
	{
		pList->InsertItem( nRow, _T("Field") );
		pList->SetItemText( nRow, 0, strBlockName );
		pList->SetItemText( nRow, 2, strFieldName );
		pList->SetItemText( nRow, 3, strFieldValue );
		pList->SetItemText( nRow, 4, strIndex );
	}
}

// CTransactionDlg 메시지 처리기입니다.

BOOL CTransactionDlg::PreTranslateMessage(MSG* pMsg)
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

BOOL CTransactionDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	InitControl();
	SetSample();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

LRESULT CTransactionDlg::OnReceiveError(WPARAM wParam, LPARAM lParam)
{

	LRESULT ret = 0;

	CString strMsg;
	int nReqID = wParam;

	switch ( lParam )
	{
	case ERROR_TIMEOUT_DATA:
		{
			m_pMainDlg->LogMessage( _T("Timeout 요청의 응답이 없습니다."), 1, FALSE );
		}
		break;
	case ERROR_REQUEST_FAIL:			// 서버에서 조회TR(DSO) 처리중 오류가 있는 경우 발생합니다.
		{
			TCHAR msg[2048] = {0,};
			g_iYuantaAPI.YOA_GetErrorMessage( nReqID, msg, sizeof(msg) );	// 처리 중 오류에 대한 메시지를 얻을 수 있습니다.
			m_pMainDlg->LogMessage( msg, 1, FALSE );
		}
		break;
	}

	return ret;

}

LRESULT CTransactionDlg::OnReceiveData(WPARAM wParam, LPARAM lParam)
{
	LRESULT ret = 0;

	int nReqID = wParam;

	CString strValue;
	if ( nReqID == m_nReqID )
	{
		m_pMainDlg->LogMessage( _T("[") + m_strDSO + _T("] DSO의 응답을 수신하였습니다.") );

		TCHAR data[1024] = {0,};
		
		CString strTemp;
		CString strBlock;
		CString strField;
		CString strValue;
		CString strIndex;
		int nIndex;

		int nRowCnt = m_ctrlOutBlocks.GetItemCount();
		for ( int nRow = 0; nRow < nRowCnt; nRow++ )
		{
			strTemp = m_ctrlOutBlocks.GetItemText(nRow, 1);

			if ( !strTemp.IsEmpty() )
			{
				strBlock = strTemp;
			}
			else
			{
				memset( data, 0x00, sizeof(data) );
				strField = m_ctrlOutBlocks.GetItemText(nRow, 2);
				nIndex = _ttoi( m_ctrlOutBlocks.GetItemText(nRow, 4) );

				g_iYuantaAPI.YOA_GetTRFieldString( m_strDSO, strBlock, strField, data, sizeof(data), nIndex );

				m_ctrlOutBlocks.SetItemText( nRow, 3, data );
			}
		}

		int nRowCount = g_iYuantaAPI.YOA_GetRowCount( m_strDSO, m_strOutArrayBlockName );

		CHeaderCtrl* pHeader = m_ctrlOutArrayBlock.GetHeaderCtrl();
		m_ctrlOutArrayBlock.DeleteAllItems();

		TCHAR lpBuffer[256];
		HDITEM hdi;
		hdi.mask = HDI_TEXT;
		hdi.pszText = lpBuffer;
		hdi.cchTextMax = sizeof(lpBuffer);

		int nColCount = pHeader->GetItemCount();

		if ( 1 < nColCount )
		{
			for ( int nRow = 0; nRow < nRowCount; nRow++ )
			{
				m_ctrlOutArrayBlock.InsertItem( nRow, _T("Value") );

				for ( int nCol = 0; nCol < nColCount; nCol++ )
				{
					memset( lpBuffer, 0x00, sizeof(lpBuffer) );
					pHeader->GetItem( nCol, &hdi );

					if ( 0 < _tcslen( lpBuffer ) )
					{
						memset( data, 0x00, sizeof(data) );

						g_iYuantaAPI.YOA_GetTRFieldString( m_strDSO, m_strOutArrayBlockName, lpBuffer, data, sizeof(data), nRow );

						m_ctrlOutArrayBlock.SetItemText( nRow, nCol, data );
					}
				}
			}
		}
	}

	return ret;
}

void CTransactionDlg::OnBnClickedButtonDsoInit()
{
	m_ctrlInBlocks.DeleteAllItems();
	m_ctrlOutBlocks.DeleteAllItems();

	m_strDSO			= _T("");
	m_strInBlockName	= _T("InBlock1");
	m_strInFieldName	= _T("");
	m_strInFieldValue	= _T("");
	m_strOutBlockName	= _T("OutBlock1");
	m_strOutFieldName	= _T("");

	m_nInArrayIndex		= 0;
	m_nOutArrayIndex	= 0;

	UpdateData(FALSE);
}

void CTransactionDlg::OnBnClickedButtonRequest()
{
	if ( TRUE == CheckAPI() )
	{
		if ( -1 != m_nReqID )
			g_iYuantaAPI.YOA_ReleaseData( m_nReqID );

		UpdateData();
		
		long result = -1;

		CString strTemp;
		CString strBlock;
		CString strField;
		CString strValue;
		CString strIndex;
		int nIndex;

		int nRowCnt = m_ctrlInBlocks.GetItemCount();
		for ( int nRow = 0; nRow < nRowCnt; nRow++ )
		{
			strTemp = m_ctrlInBlocks.GetItemText(nRow, 1);

			if ( !strTemp.IsEmpty() )
			{
				strBlock = strTemp;
			}
			else
			{
				strField = m_ctrlInBlocks.GetItemText(nRow, 2);
				strValue = m_ctrlInBlocks.GetItemText(nRow, 3);
				nIndex = _ttoi( m_ctrlInBlocks.GetItemText(nRow, 4) );

				result = g_iYuantaAPI.YOA_SetTRFieldString( m_strDSO, strBlock, strField, strValue, nIndex );

				if ( RESULT_SUCCESS != result )
				{
					TCHAR msg[1024] = {0,};

					//int nErrorCode = g_iYuantaAPI.YOA_GetLastError();
					g_iYuantaAPI.YOA_GetErrorMessage( result, msg, sizeof(msg) );

					CString strErrorMsg;
					strErrorMsg.Format( _T("[%d] %s"), result, msg );

					m_pMainDlg->LogMessage( _T("[") + strField + _T("] 필드 값 설정중 오류가 발생하였습니다."), 1 );
					m_pMainDlg->LogMessage( strErrorMsg );

					return;
				}
			}
		}
		
		int nReqID = -1;
		if ( 0 < nRowCnt )
		{
			nReqID = g_iYuantaAPI.YOA_Request( GetSafeHwnd(), m_strDSO, FALSE );

			if ( ERROR_MAX_CODE < nReqID )
			{
				m_pMainDlg->LogMessage( _T("[") + m_strDSO + _T("] DSO를 요청하였습니다.") );
				m_nReqID = nReqID;
			}
			else
			{
				TCHAR msg[1024] = {0,};

				//int nErrorCode = g_iYuantaAPI.YOA_GetLastError();
				g_iYuantaAPI.YOA_GetErrorMessage( nReqID, msg, sizeof(msg) );

				CString strErrorMsg;
				strErrorMsg.Format( _T("[%d] %s"), nReqID, msg );

				m_pMainDlg->LogMessage( _T("[") + m_strDSO + _T("] DSO 요청중 오류가 발생하였습니다."), 1 );
				m_pMainDlg->LogMessage( strErrorMsg );
			}
		}		
	}
}

void CTransactionDlg::OnBnClickedButtonNextRequest()
{
	if ( TRUE == CheckAPI() )
	{
		if ( ERROR_MAX_CODE < m_nReqID )
		{

			int nReqID = g_iYuantaAPI.YOA_Request( GetSafeHwnd(), m_strDSO, FALSE, m_nReqID );

			if ( ERROR_MAX_CODE < nReqID )
			{
				m_pMainDlg->LogMessage( _T("[") + m_strDSO + _T("] DSO 연속 조회를 요청하였습니다.") );
			}
			else
			{
				TCHAR msg[1024] = {0,};

				//int nErrorCode = g_iYuantaAPI.YOA_GetLastError();
				g_iYuantaAPI.YOA_GetErrorMessage( nReqID, msg, sizeof(msg) );

				CString strErrorMsg;
				strErrorMsg.Format( _T("[%d] %s"), nReqID, msg );

				m_pMainDlg->LogMessage( _T("[") + m_strDSO + _T("] DSO 연속 조회 요청중 오류가 발생하였습니다."), 1 );
				m_pMainDlg->LogMessage( strErrorMsg );
			}
		}
	}
}

void CTransactionDlg::OnBnClickedButtonInAdd()
{
	UpdateData();

	AddBlockItem( m_strInBlockName, m_strInFieldName, m_strInFieldValue, m_nInArrayIndex );
}

void CTransactionDlg::OnBnClickedButtonInDel()
{
	int nSelRow = m_ctrlInBlocks.GetSelectionMark();

	CString strTemp = m_ctrlInBlocks.GetItemText( nSelRow, 1 );

	if ( -1 == strTemp.Find(_T("InBlock"), 0) )
	{
		m_ctrlInBlocks.DeleteItem( nSelRow );
	}
	else
	{
		CString strBlockName = strTemp;

		int nRowCnt = m_ctrlInBlocks.GetItemCount();
		for ( int nRow = nRowCnt- 1; nRow >= 0; nRow-- )
		{
			strTemp = m_ctrlInBlocks.GetItemText(nRow, 0);

			if ( strBlockName == strTemp )
			{
				m_ctrlInBlocks.DeleteItem( nRow );
			}
		}
	}
}


void CTransactionDlg::OnBnClickedButtonOutAdd()
{
	UpdateData();

	AddBlockItem( m_strOutBlockName, m_strOutFieldName, _T(""), m_nOutArrayIndex, FALSE );
}


void CTransactionDlg::OnBnClickedButtonOutDel()
{
	int nSelRow = m_ctrlOutBlocks.GetSelectionMark();

	CString strTemp = m_ctrlOutBlocks.GetItemText( nSelRow, 1 );

	if ( -1 == strTemp.Find(_T("OutBlock"), 0) )
	{
		m_ctrlOutBlocks.DeleteItem( nSelRow );
	}
	else
	{
		CString strBlockName = strTemp;

		int nRowCnt = m_ctrlOutBlocks.GetItemCount();
		for ( int nRow = nRowCnt- 1; nRow >= 0; nRow-- )
		{
			strTemp = m_ctrlOutBlocks.GetItemText(nRow, 0);

			if ( strBlockName == strTemp )
			{
				m_ctrlOutBlocks.DeleteItem( nRow );
			}
		}
	}
}


void CTransactionDlg::OnBnClickedButtonOutArrayAdd()
{
	UpdateData();

	m_strOutArrayFieldName.TrimRight();

	if ( 0 < m_strOutArrayFieldName.GetLength() )
	{
		int nColCount = m_ctrlOutArrayBlock.GetHeaderCtrl()->GetItemCount();
		m_ctrlOutArrayBlock.InsertColumn(nColCount, m_strOutArrayFieldName, LVCFMT_CENTER, 85);
	}

}


void CTransactionDlg::OnBnClickedButtonOutArrayDel()
{
	UpdateData();

	m_strOutArrayFieldName.TrimRight();

	if ( 0 < m_strOutArrayFieldName.GetLength() )
	{
		CHeaderCtrl* pHeader = m_ctrlOutArrayBlock.GetHeaderCtrl();

		TCHAR lpBuffer[256];
		HDITEM hdi;
		hdi.mask = HDI_TEXT;
		hdi.pszText = lpBuffer;
		hdi.cchTextMax = sizeof(lpBuffer);

		int nColCount = pHeader->GetItemCount();
		for ( int i = 0; i < nColCount; i++ )
		{
			memset( lpBuffer, 0x00, sizeof(lpBuffer) );
			pHeader->GetItem( i, &hdi );

			if ( 0 == _tcsncmp( hdi.pszText, m_strOutArrayFieldName.GetBuffer(0), sizeof(lpBuffer) ) )
			{
				m_ctrlOutArrayBlock.DeleteColumn( i );

				if ( 2 == nColCount )
					m_ctrlOutArrayBlock.DeleteAllItems();

				break;
			}
		}
	}
}


void CTransactionDlg::OnHdnItemclickListArrayOutblock(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	
	int nCol = phdr->iItem;

	CHeaderCtrl* pHeader = m_ctrlOutArrayBlock.GetHeaderCtrl();

	TCHAR lpBuffer[256] = {0,};
	HDITEM hdi;
	hdi.mask = HDI_TEXT;
	hdi.pszText = lpBuffer;
	hdi.cchTextMax = sizeof(lpBuffer);

	pHeader->GetItem( nCol, &hdi );

	m_strOutArrayFieldName = lpBuffer;
	UpdateData(FALSE);

	*pResult = 0;
}

