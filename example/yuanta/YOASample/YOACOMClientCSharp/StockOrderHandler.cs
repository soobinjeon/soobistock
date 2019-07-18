using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using YuantaCOMLib;

namespace YOACOMClientCSharp
{
    class StockOrderHandler
    {
        public static int ORDER_TYPE_MESU = 0;
        public static int ORDER_TYPE_MEDO = 1;

        public MainForm m_mainForm;
        public IYuantaAPI m_iYuantaAPI;
        public Dictionary<int, string> m_mapRequestTR;
        public Dictionary<int, string> m_mapAutoTR;
        public Dictionary<string, string> m_mapAcctInfos;
        private int m_nPrevLastPrice;
        private int m_nOrderMesuMedo;
        private int m_nReqID_mesu;
        private int m_nReqID_medo;
        private string m_strJongCode;

        public StockOrderHandler()
        {
            m_mainForm      = null;
            m_iYuantaAPI    = null;

            m_mapRequestTR  = new Dictionary<int, string>();
            m_mapAutoTR     = new Dictionary<int, string>();
            m_mapAcctInfos  = new Dictionary<string, string>();

            m_nPrevLastPrice = 0;
            m_nOrderMesuMedo = ORDER_TYPE_MESU;
            m_nReqID_mesu    = 0;
            m_nReqID_medo    = 0;
            m_strJongCode    = "";
        }

        public void InitControl()
        {
            ImageList imgList1 = new ImageList();
            imgList1.ImageSize = new Size(1, 23);
            m_mainForm.lvOrdJongInfoHeader.SmallImageList = imgList1;
            m_mainForm.lvOrdJongInfo.SmallImageList = imgList1;

            ImageList imgList2 = new ImageList();
            imgList2.ImageSize = new Size(1, 18);
            m_mainForm.lvOrdMiChegyul.SmallImageList = imgList2;

            m_mainForm.cbOrdType.SelectedIndex = 0;
        }

        public void AddAccount(string strAccount, string strAcctName)
        {
            m_mainForm.cbOrdAccount.Items.Add(strAccount);   
        }

        public void ClearAccount()
        {
            m_mainForm.cbOrdAccount.Items.Clear();
        }

        public void cbOrdAccount_SelectedIndexChanged()
        {
            string strAccount = m_mainForm.cbOrdAccount.SelectedItem.ToString();
            strAccount = strAccount.Replace("-", "");

            string strName = m_iYuantaAPI.YOA_GetAccountInfo(CommDef.ACCOUNT_INFO_NAME, strAccount);
            if (0 < strName.Length)
                m_mainForm.lblOrdAcctName.Text = strName;
        }

        public void nudOrdPrice_ValueChanged()
        {
            int nPrice = Convert.ToInt32(m_mainForm.nudOrdPrice.Value);
            int nQty = Convert.ToInt32(m_mainForm.nudOrdQty.Value);

            m_mainForm.lblOrdTotPrice.Text = m_mainForm.Commify(nPrice * nQty);
        }

        public void nudOrdQty_VisibleChanged()
        {
            int nPrice = Convert.ToInt32(m_mainForm.nudOrdPrice.Value);
            int nQty = Convert.ToInt32(m_mainForm.nudOrdQty.Value);

            m_mainForm.lblOrdTotPrice.Text = m_mainForm.Commify(nPrice * nQty);
        }

        public void SetOrderMedoMesu(int nType)
        {
            m_nOrderMesuMedo = nType;

            if (ORDER_TYPE_MESU == m_nOrderMesuMedo)
            {
                m_mainForm.btnOrder.Text = "현금매수";
                m_mainForm.btnOrder.BackColor = Color.FromArgb(186, 67, 68);
            }
            else if (ORDER_TYPE_MEDO == m_nOrderMesuMedo)
            {
                m_mainForm.btnOrder.Text = "현금매도";
                m_mainForm.btnOrder.BackColor = Color.FromArgb(104, 151, 221);
            }
        }

        public void Search()
        {
            UnRegistAuto();

            m_strJongCode = m_mainForm.txtJongCode.Text;
            m_strJongCode.Trim();

            m_iYuantaAPI.YOA_SetTRFieldString("300001", "InBlock1", "jang", "1", 0);
            m_iYuantaAPI.YOA_SetTRFieldString("300001", "InBlock1", "jongcode", m_strJongCode, 0);
            m_iYuantaAPI.YOA_SetTRFieldString("300001", "InBlock1", "outflag", "N", 0);
            m_iYuantaAPI.YOA_SetTRFieldString("300001", "InBlock1", "tsflag", "0", 0);
            int nReqID = m_iYuantaAPI.YOA_Request("300001", true, -1);

            if (CommDef.ERROR_MAX_CODE < nReqID)
            {
                m_mapRequestTR[nReqID] = "300001";
                string strMsg = "[ReqID:" + nReqID + "] [300001]주식현재가 조회를 요청하였습니다.";

                m_mainForm.LogMessage(strMsg);
            }
            else
            {
                string strMsg = "[300001]주식현재가 조회 요청중 오류가 발생하였습니다.";
                m_mainForm.LogMessage(strMsg, CommDef.YOALOG_ERROR);

                strMsg = "[" + nReqID + "]" + m_iYuantaAPI.YOA_GetErrorMessage(nReqID);
                m_mainForm.LogMessage(strMsg, CommDef.YOALOG_ERROR, false);
            }
        }

        public void RegistAuto()
        {
            UnRegistAuto();

            m_iYuantaAPI.YOA_SetTRFieldString("11", "InBlock1", "jongcode", m_strJongCode, 0);
            int nReqID = m_iYuantaAPI.YOA_RegistAuto("11");

            if (CommDef.ERROR_MAX_CODE < nReqID)
            {
                m_mapAutoTR[nReqID] = "11";

                m_mainForm.btnBTAutoUnRegist.Enabled = true;

                m_mainForm.LogMessage("[11]주식 실시간체결 Auto가 등록 되었습니다.");
            }
            else
            {
                m_mainForm.LogMessage("[11]주식 실시간체결 Auto 등록이 실패하였습니다.", CommDef.YOALOG_ERROR);

                string strMsg = m_iYuantaAPI.YOA_GetErrorMessage(nReqID);     // 실시간 등록 실패에 대한 메시지를 얻을 수 있습니다.
                m_mainForm.LogMessage(strMsg, CommDef.YOALOG_ERROR, false);
            }
        }

        public void UnRegistAuto()
        {
            foreach (KeyValuePair<int, string> autoTR in m_mapAutoTR)
            {
                int nResult = m_iYuantaAPI.YOA_UnRegistAutoWithReqID(autoTR.Key);

                if (CommDef.RESULT_SUCCESS == nResult)
                {
                    if (autoTR.Value.Equals("11"))
                        m_mainForm.LogMessage("[11]주식 실시간체결 Auto가 해지 되었습니다.");
                }
                else
                {
                    if (autoTR.Value.Equals("11"))
                        m_mainForm.LogMessage("[11]주식 실시간체결 Auto 해지가 실패하였습니다.");

                    string strMsg = m_iYuantaAPI.YOA_GetErrorMessage(nResult);     // 실시간 해지 실패에 대한 메시지를 얻을 수 있습니다.
                    m_mainForm.LogMessage(strMsg, CommDef.YOALOG_ERROR, false);
                }
            }

            m_mapAutoTR.Clear();
        }

        public void Order()
        {
            string strAcctPwd = m_mainForm.txtOrdAcctPwd.Text;
            strAcctPwd.Trim();
            if (0 == strAcctPwd.Length)
            {
                MessageBox.Show("계좌비밀번호를 입력해주세요.");
                m_mainForm.txtOrdAcctPwd.Focus();
                return;
            }

            string strJongCode = m_mainForm.txtOrdJongCode.Text;
            strJongCode.Trim();
            if (0 == strJongCode.Length)
            {
                MessageBox.Show("종목코드를 입력해주세요.");
                m_mainForm.txtOrdAcctPwd.Focus();
                return;
            }

            int nOrderType = m_mainForm.cbOrdType.SelectedIndex;

            int nPrice = Convert.ToInt32(m_mainForm.nudOrdPrice.Value);
            if (0 == nPrice)
            {
                if (
                     1 == nOrderType ||	// 05.시장가
                     3 == nOrderType ||	// 12.최유리지정가
                     4 == nOrderType ||	// 13.최우선지정가
                     5 == nOrderType ||	// 71.시간외종가
                     8 == nOrderType ||	// I2.시장가(IOC)
                    11 == nOrderType 	// F2.시장가(FOC)
                    )
                {

                }
                else
                {
                    MessageBox.Show("가격을 입력해주세요.");
                    m_mainForm.nudOrdPrice.Focus();
                    return;
                }
            }

            int nQty = Convert.ToInt32(m_mainForm.nudOrdQty.Value);
            if (0 == nQty)
            {
                MessageBox.Show("수량을 입력해주세요.");
                m_mainForm.nudOrdQty.Focus();
                return;
            }

            string strDSOID = "";
            if (ORDER_TYPE_MESU == m_nOrderMesuMedo)
                strDSOID = "100001";
            else if (ORDER_TYPE_MEDO == m_nOrderMesuMedo)
                strDSOID = "100002";

            string strAccount = m_mainForm.cbOrdAccount.SelectedItem.ToString();
            strAccount = strAccount.Replace("-", "");

            string strMemeGubun = m_mainForm.cbOrdType.SelectedItem.ToString();
            int nPos = strMemeGubun.IndexOf('.');
		    strMemeGubun = strMemeGubun.Remove(nPos);

		    string strJumunCond = "00";
		    if ( 1 < strMemeGubun.Length )
		    {
			    if ( 'I' == strMemeGubun[0] )
				    strJumunCond = "01";
			    else if ( 'F' == strMemeGubun[0] )
				    strJumunCond = "02";
		    }

            m_iYuantaAPI.YOA_SetTRInfo(strDSOID, "InBlock1");
            m_iYuantaAPI.YOA_SetFieldString("acnt_aid",         strAccount, 0);
            m_iYuantaAPI.YOA_SetFieldString("gds_acnt_tp",      "A01010001", 0);
            m_iYuantaAPI.YOA_SetFieldString("passwd",           strAcctPwd, 0);
            m_iYuantaAPI.YOA_SetFieldString("meme_gubun",       strMemeGubun, 0);
            m_iYuantaAPI.YOA_SetFieldString("jong_code",        strJongCode, 0);
            m_iYuantaAPI.YOA_SetFieldString("jang_gubun",       "0", 0);
            m_iYuantaAPI.YOA_SetFieldLong("order_cnt",          nQty, 0);
            m_iYuantaAPI.YOA_SetFieldLong("order_price",        nPrice, 0);
            m_iYuantaAPI.YOA_SetFieldString("jumun_condition",  strJumunCond, 0);

            int nReqID = m_iYuantaAPI.YOA_Request(strDSOID, true, -1);

            if (ORDER_TYPE_MESU == m_nOrderMesuMedo)
            {
                m_nReqID_mesu = nReqID;
            }
            else if (ORDER_TYPE_MEDO == m_nOrderMesuMedo)
            {
                m_nReqID_medo = nReqID;
            }

            if ( CommDef.ERROR_MAX_CODE < nReqID )
		    {
			    string strMsg = "";
			    if ( ORDER_TYPE_MESU == m_nOrderMesuMedo )
			    {
                    m_mapRequestTR[nReqID] = "100001";
				    strMsg = "[ReqID:" + nReqID + "] [100001]현금매수 주문을 요청 하였습니다.";
			    }
			    else if ( ORDER_TYPE_MEDO == m_nOrderMesuMedo )
			    {
                    m_mapRequestTR[nReqID] = "100002";
                    strMsg = "[ReqID:" + nReqID + "] [100002]현금매도 주문을 요청 하였습니다.";
			    }

			    m_mainForm.LogMessage(strMsg);
		    }
		    else
		    {
                if (ORDER_TYPE_MESU == m_nOrderMesuMedo)
			    {
                    m_mainForm.LogMessage("[100001]현금매수 주문 요청중 오류가 발생하였습니다.", CommDef.YOALOG_ERROR);
			    }
                else if (ORDER_TYPE_MEDO == m_nOrderMesuMedo)
			    {
                    m_mainForm.LogMessage("[100002]현금매도 주문 요청중 오류가 발생하였습니다.", CommDef.YOALOG_ERROR);
			    }
                
                int nErrorCode = m_iYuantaAPI.YOA_GetLastError();
                m_mainForm.LogMessage("[" + nErrorCode + " ]" + m_iYuantaAPI.YOA_GetErrorMessage(nErrorCode), CommDef.YOALOG_ERROR, false);
		    }
        }
        
        public void SearchMiChegyul()
        {
            m_mainForm.lvOrdMiChegyul.Items.Clear();

            string strAcctPwd = m_mainForm.txtOrdAcctPwd.Text;
            strAcctPwd.Trim();
            if (0 == strAcctPwd.Length)
            {
                MessageBox.Show("계좌비밀번호를 입력해주세요.");
                m_mainForm.txtOrdAcctPwd.Focus();
                return;
            }

            string strAccount = m_mainForm.cbOrdAccount.SelectedItem.ToString();
            strAccount = strAccount.Replace("-", "");

            m_iYuantaAPI.YOA_SetTRFieldString("210006", "InBlock1", "acnt_aid",     strAccount, 0);
            m_iYuantaAPI.YOA_SetTRFieldString("210006", "InBlock1", "passwd",       strAcctPwd, 0);
            m_iYuantaAPI.YOA_SetTRFieldString("210006", "InBlock1", "order_gubun",  "1", 0);

            int nReqID = m_iYuantaAPI.YOA_Request("210006", true, -1);

		    if ( CommDef.ERROR_MAX_CODE < nReqID )
		    {
                m_mapRequestTR[nReqID] = "210006";
			    m_mainForm.LogMessage("[ReqID:" + nReqID + " [210006]미체결내역 조회를 요청하였습니다.");
		    }
		    else
		    {
                m_mainForm.LogMessage("[210006]미체결내역 조회중 오류가 발생하였습니다.", CommDef.YOALOG_ERROR);

                int nErrorCode = m_iYuantaAPI.YOA_GetLastError();
                m_mainForm.LogMessage("[" + nErrorCode + " ]" + m_iYuantaAPI.YOA_GetErrorMessage(nErrorCode), CommDef.YOALOG_ERROR, false);
		    }
        }

        public void SearchChegyul()
        {
            m_mainForm.lvOrdChegyul.Items.Clear();

            string strAcctPwd = m_mainForm.txtOrdAcctPwd.Text;
            strAcctPwd.Trim();
            if (0 == strAcctPwd.Length)
            {
                MessageBox.Show("계좌비밀번호를 입력해주세요.");
                m_mainForm.txtOrdAcctPwd.Focus();
                return;
            }

            string strAccount = m_mainForm.cbOrdAccount.SelectedItem.ToString();
            strAccount = strAccount.Replace("-", "");

            string strDate = m_mainForm.dateTimePicker.ToString();
            strDate = strDate.Replace("-", "");

            m_iYuantaAPI.YOA_SetTRFieldString("201007", "InBlock1", "acnt_aid", strAccount, 0);
            m_iYuantaAPI.YOA_SetTRFieldString("201007", "InBlock1", "date", strDate, 0);
            m_iYuantaAPI.YOA_SetTRFieldString("201007", "InBlock1", "qry_tp", "3", 0);

            int nReqID = m_iYuantaAPI.YOA_Request("201007", true, -1);

            if (CommDef.ERROR_MAX_CODE < nReqID)
            {
                m_mapRequestTR[nReqID] = "201007";
                m_mainForm.LogMessage("[ReqID:" + nReqID + " [201007]체결기준거래내역 조회를 요청하였습니다.");
            }
            else
            {
                m_mainForm.LogMessage("[201007]미체결내역 조회중 오류가 발생하였습니다.", CommDef.YOALOG_ERROR);

                int nErrorCode = m_iYuantaAPI.YOA_GetLastError();
                m_mainForm.LogMessage("[" + nErrorCode + " ]" + m_iYuantaAPI.YOA_GetErrorMessage(nErrorCode), CommDef.YOALOG_ERROR, false);
            }
        }

        private void Process300001_Auto11(bool bAuto)
        {
            if (bAuto)
                m_iYuantaAPI.YOA_SetTRInfo("11", "OutBlock1");
            else
                m_iYuantaAPI.YOA_SetTRInfo("300001", "OutBlock1");

            if (!bAuto)
                m_mainForm.lblOrdJongName.Text = m_iYuantaAPI.YOA_GetFieldString("jongname", 0);

            int nColor = m_iYuantaAPI.YOA_GetFieldAttr("curjuka", 0);
            m_mainForm.lvOrdJongInfo.Items[0].SubItems[1].Text = m_mainForm.Commify(m_iYuantaAPI.YOA_GetFieldLong("curjuka", 0));

            if (2 == nColor)
            {
                m_mainForm.lvOrdJongInfo.Items[0].ForeColor = Color.Red;
                m_mainForm.lvOrdJongInfo.Items[1].ForeColor = Color.Red;
                m_mainForm.lvOrdJongInfo.Items[2].ForeColor = Color.Red;
            }
            else if (5 == nColor)
            {
                m_mainForm.lvOrdJongInfo.Items[0].ForeColor = Color.Blue;
                m_mainForm.lvOrdJongInfo.Items[1].ForeColor = Color.Blue;
                m_mainForm.lvOrdJongInfo.Items[2].ForeColor = Color.Blue;
            }
            else
            {
                m_mainForm.lvOrdJongInfo.Items[0].ForeColor = Color.Black;
                m_mainForm.lvOrdJongInfo.Items[1].ForeColor = Color.Black;
                m_mainForm.lvOrdJongInfo.Items[2].ForeColor = Color.Black;
            }

            int nDebi = m_iYuantaAPI.YOA_GetFieldLong("debi", 0);
            string strValue;
            if (0 < nDebi)
            {
                strValue = "▲  " + m_mainForm.Commify(nDebi);
            }
            else if (0 > nDebi)
            {
                nDebi = -nDebi;
                strValue = "▼  " + m_mainForm.Commify(nDebi);
            }
            else
            {
                strValue = m_mainForm.Commify(Convert.ToString(nDebi));
            }
            m_mainForm.lvOrdJongInfo.Items[1].SubItems[1].Text = strValue;
            
            strValue = string.Format("{0:0.00}", m_iYuantaAPI.YOA_GetFieldDouble("debirate", 0));
            m_mainForm.lvOrdJongInfo.Items[2].SubItems[1].Text = strValue;
            
            strValue = m_mainForm.Commify(m_iYuantaAPI.YOA_GetFieldString("volume", 0));
            m_mainForm.lvOrdJongInfo.Items[3].SubItems[1].Text = strValue;
            
            nColor = m_iYuantaAPI.YOA_GetFieldAttr("startjuka", 0);
            strValue = m_mainForm.Commify(m_iYuantaAPI.YOA_GetFieldString("startjuka", 0));
            m_mainForm.lvOrdJongInfo.Items[4].SubItems[1].Text = strValue;
            

            if (2 == nColor)
            {
                m_mainForm.lvOrdJongInfo.Items[4].ForeColor = Color.Red;
            }
            else if (5 == nColor)
            {
                m_mainForm.lvOrdJongInfo.Items[4].ForeColor = Color.Blue;
            }
            else
            {
                m_mainForm.lvOrdJongInfo.Items[4].ForeColor = Color.Black;
            }

            nColor = m_iYuantaAPI.YOA_GetFieldAttr("highjuka", 0);
            strValue = m_mainForm.Commify(m_iYuantaAPI.YOA_GetFieldString("highjuka", 0));
            m_mainForm.lvOrdJongInfo.Items[5].SubItems[1].Text = strValue;
            
            if (2 == nColor)
            {
                m_mainForm.lvOrdJongInfo.Items[5].ForeColor = Color.Red;
            }
            else if (5 == nColor)
            {
                m_mainForm.lvOrdJongInfo.Items[5].ForeColor = Color.Blue;
            }
            else
            {
                m_mainForm.lvOrdJongInfo.Items[5].ForeColor = Color.Black;
            }

            nColor = m_iYuantaAPI.YOA_GetFieldAttr("lowjuka", 0);
            strValue = m_mainForm.Commify(m_iYuantaAPI.YOA_GetFieldString("lowjuka", 0));
            m_mainForm.lvOrdJongInfo.Items[6].SubItems[1].Text = strValue;
            
            if (2 == nColor)
            {
                m_mainForm.lvOrdJongInfo.Items[6].ForeColor = Color.Red;
            }
            else if (5 == nColor)
            {
                m_mainForm.lvOrdJongInfo.Items[6].ForeColor = Color.Blue;
            }
            else
            {
                m_mainForm.lvOrdJongInfo.Items[6].ForeColor = Color.Black;
            }

            if (!bAuto)
            {
                m_nPrevLastPrice = m_iYuantaAPI.YOA_GetFieldLong("prevlastjuka", 0);
                m_mainForm.lvOrdJongInfo.Items[7].SubItems[1].Text = m_mainForm.Commify(m_iYuantaAPI.YOA_GetFieldString("prevlastjuka", 0));

                RegistAuto();
            }
        }

        private void Process210006() 
        {
            string strData = "";
            int nData = 0;

            m_iYuantaAPI.YOA_SetTRInfo("210006", "OutBlock1");

            string[] strSeparator1 = new string[] { "/" };
            string[] strSeparator2 = new string[] { "}" };
            string[] strSeparator3 = new string[] { "F" };
            string[] strResult = null;

            string strJongCode = "";
            string strJongName = "";
            string strJongType = "";
            Color clrJongType = new Color();

            ListViewItem item = null;

            int nDataCount = m_iYuantaAPI.YOA_GetFieldLong("list_cnt", 0);
            for (int i = 0; i < nDataCount; i++)
            {
                strResult   = null;

                strJongCode = "";
                strJongName = "";
                strJongType = "";

                item = new ListViewItem();
                item.UseItemStyleForSubItems = false;
                item.SubItems.Add(m_iYuantaAPI.YOA_GetFieldString("order_no", i));

                strData = m_iYuantaAPI.YOA_GetFieldString("jong_code", i);
                strData.TrimEnd();

                strResult = strData.Split(strSeparator1,  StringSplitOptions.None);

                if (0 < strResult.Length)
                    strJongCode = strResult[0];

                if (1 < strResult.Length)
                    strJongName = strResult[1];

                if (2 < strResult.Length)
                {
                    strJongType = strResult[2];
                    strJongType.TrimEnd();

                    if (strJongType.Equals("K"))
                        clrJongType = Color.Red;
                    else
                        clrJongType = Color.Blue;
                }
                
                item.SubItems.Add(strJongType);
                item.SubItems[1].ForeColor = clrJongType;

                item.SubItems.Add(strJongName);

                strData = m_iYuantaAPI.YOA_GetFieldString("order_gubun", i);
                strData.TrimEnd();

                strResult = strData.Split(strSeparator2, StringSplitOptions.None);

                if (2 < strResult.Length)
                {
                    item.SubItems.Add(strResult[2]);

                    strData = strResult[0];
                    if (-1 != strData.IndexOf("FF0000"))
                        item.SubItems[3].ForeColor = Color.Red;
                    else
                        item.SubItems[3].ForeColor = Color.Blue;
                }
                else
                {
                    item.SubItems.Add("");
                }

                nData = m_iYuantaAPI.YOA_GetFieldLong("order_price", i);
                item.SubItems.Add(m_mainForm.Commify(nData));

                nData = m_iYuantaAPI.YOA_GetFieldLong("order_cnt", i);
                item.SubItems.Add(m_mainForm.Commify(nData));

                nData = m_iYuantaAPI.YOA_GetFieldLong("nn_contract_cnt", i);
                item.SubItems.Add(m_mainForm.Commify(nData));

                strData = m_iYuantaAPI.YOA_GetFieldString("credit_gubun", i);

                strResult = strData.Split(strSeparator3, StringSplitOptions.None);
                if (0 < strResult.Length)
                    item.SubItems.Add(strResult[0]);
                else
                    item.SubItems.Add("");

                m_mainForm.lvOrdMiChegyul.Items.Insert(0, item);
            }

            m_mainForm.lblOrdCnt1.Text = Convert.ToString(nDataCount);
        }

        private void Process201007()
        {
            string strData = "";
            int nData = 0;

            m_iYuantaAPI.YOA_SetTRInfo("210007", "OutBlock2");

            string[] strSeparator1 = new string[] { "/" };
            string[] strSeparator2 = new string[] { "}" };
            string[] strResult = null;

            string strJongCode = "";
            string strJongName = "";
            string strJongType = "";
            Color clrJongType = new Color();

            ListViewItem item = null;


            int nDataCount = m_iYuantaAPI.YOA_GetRowCount("201007", "OutBlock2");
            for (int i = 0; i < nDataCount; i++)
            {
                strResult = null;

                strJongCode = "";
                strJongName = "";
                strJongType = "";

                item = new ListViewItem();
                item.UseItemStyleForSubItems = false;

                strData = m_iYuantaAPI.YOA_GetFieldString("stk_name", i);
                strData.TrimEnd();

                strResult = strData.Split(strSeparator1, StringSplitOptions.None);

                if (0 < strResult.Length)
                    strJongCode = strResult[0];

                if (1 < strResult.Length)
                    strJongName = strResult[1];

                if (2 < strResult.Length)
                {
                    strJongType = strResult[2];
                    strJongType.TrimEnd();

                    if (strJongType.Equals("K"))
                        clrJongType = Color.Red;
                    else
                        clrJongType = Color.Blue;
                }

                item.SubItems.Add(strJongType);
                item.SubItems[0].ForeColor = clrJongType;

                item.SubItems.Add(strJongName);

                strData = m_iYuantaAPI.YOA_GetFieldString("trde_tp_gubun", i);
                strData.TrimEnd();

                strResult = strData.Split(strSeparator2, StringSplitOptions.None);

                if (2 < strResult.Length)
                {
                    item.SubItems.Add(strResult[2]);

                    strData = strResult[0];
                    if (-1 != strData.IndexOf("FF0000"))
                        item.SubItems[2].ForeColor = Color.Red;
                    else
                        item.SubItems[2].ForeColor = Color.Blue;
                }
                else
                {
                    item.SubItems.Add("");
                }

                nData = m_iYuantaAPI.YOA_GetFieldLong("cntr_qty_cnt", i);
                item.SubItems.Add(m_mainForm.Commify(nData));

                nData = m_iYuantaAPI.YOA_GetFieldLong("cntr_uv_price", i);
                item.SubItems.Add(m_mainForm.Commify(nData));

                nData = m_iYuantaAPI.YOA_GetFieldLong("contract_amt", i);
                item.SubItems.Add(m_mainForm.Commify(nData));

                m_mainForm.lvOrdChegyul.Items.Insert(0, item);
            }

            m_mainForm.lblOrdCnt1.Text = Convert.ToString(nDataCount);
        }

        public void ReceiveError(int nReqID, int nErrCode, string strErrMsg)
        {
            string strTRID = m_mapRequestTR[nReqID];
            string strName = "";
            if (strTRID.Equals("300001"))
            {
                strName = "[300001]주식현재가";
            }
            else if (strTRID.Equals("100001"))
            {
                strName = "[100001]주식매수주문";
            }
            else if (strTRID.Equals("100002"))
            {
                strName = "[100002]주식매도주문";
            }

            if (nErrCode == CommDef.ERROR_TIMEOUT_DATA)
            {
                m_mainForm.lbLog.Items.Add("Timeout " + strName + "요청의 응답이 없습니다.");
            }
            else if (nErrCode == CommDef.ERROR_REQUEST_FAIL)
            {
                m_mainForm.lbLog.Items.Add(strName + m_iYuantaAPI.YOA_GetErrorMessage(nErrCode));
            }
        }

        public void ReceiveData(int nReqID)
        {
            string strTRID = m_mapRequestTR[nReqID];
            string strName = "";

            if (strTRID.Equals("300001"))
            {
                strName = "[300001]주식현재가";
                Process300001_Auto11(false);
            }
            else if (strTRID.Equals("210006"))
            {
                strName = "[210006]미체결내역";

                Process210006();
            }
            else if (strTRID.Equals("201007"))
            {
                strName = "[201007]체결기준거래내역";

                Process201007();
            }
            else if (strTRID.Equals("100001"))
            {
            }
            else if (strTRID.Equals("100002"))
            {
            }

            string strMsg = "[ReqID:" + nReqID + "] " + strName + " 응답을 수신하였습니다.";
            m_mainForm.LogMessage(strMsg);
        }

        public void ReceiveRealData(int nReqID, string strAutoID)
        {
            if (m_mapAutoTR.ContainsKey(nReqID))
            {
                if (strAutoID.Equals("11"))
                {
                    Process300001_Auto11(true);
                }
            }
        }
    }
}
