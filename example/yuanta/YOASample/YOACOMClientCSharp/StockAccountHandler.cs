using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using YuantaCOMLib;

namespace YOACOMClientCSharp
{
    class StockAccountHandler
    {
        public MainForm m_mainForm;
        public IYuantaAPI m_iYuantaAPI;
        public Dictionary<int, string> m_mapRequestTR;
        public Dictionary<string, string> m_mapAutoTR;

        public StockAccountHandler()
        {
            m_mainForm      = null;
            m_iYuantaAPI    = null;

            m_mapRequestTR = new Dictionary<int, string>();
            m_mapAutoTR = new Dictionary<string, string>();
        }

        public void InitControl()
        {
            ImageList imgList1 = new ImageList();
            imgList1.ImageSize = new Size(1, 23);
            m_mainForm.lvAcctInfo1.SmallImageList = imgList1;
            m_mainForm.lvAcctInfo2.SmallImageList = imgList1;

            ImageList imgList2 = new ImageList();
            imgList2.ImageSize = new Size(1, 20);
            m_mainForm.lvAcctInfo3.SmallImageList = imgList2;
            m_mainForm.lvAcctInfo4.SmallImageList = imgList2;
        }

        public void AddAccount(string strAccount, string strAcctName)
        {
            m_mainForm.cbAcctAccount.Items.Add(strAccount);
        }

        public void ClearAccount()
        {
            m_mainForm.cbAcctAccount.Items.Clear();
        }

        public void cbAcctAccount_SelectedIndexChanged()
        {
            string strAccount = m_mainForm.cbAcctAccount.SelectedItem.ToString();
            strAccount = strAccount.Replace("-", "");

            string strName = m_iYuantaAPI.YOA_GetAccountInfo(CommDef.ACCOUNT_INFO_NAME, strAccount);
            if (0 < strName.Length)
                m_mainForm.lblAcctName.Text = strName;
        }

        public void Search()
        {
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

		    m_iYuantaAPI.YOA_SetTRFieldString("204006", "InBlock1", "kyejwa", strAccount, 0);
		    m_iYuantaAPI.YOA_SetTRFieldString("204006", "InBlock1", "passwd", strAcctPwd, 0);

		    int nReqID = m_iYuantaAPI.YOA_Request("204006", true, -1);

		    if ( CommDef.ERROR_MAX_CODE < nReqID )
		    {
			    m_mapRequestTR[nReqID] = "204006";
			    m_mainForm.LogMessage("[ReqID:"+ nReqID +"] [204006]가정산예수현황 조회를 요청하였습니다.");
		    }
		    else
		    {
                m_mainForm.LogMessage("[204006]가정산예수현황 조회중 오류가 발생하였습니다.", CommDef.YOALOG_ERROR);

                int nErrorCode = m_iYuantaAPI.YOA_GetLastError();
                m_mainForm.LogMessage("[" + nErrorCode + " ]" + m_iYuantaAPI.YOA_GetErrorMessage(nErrorCode), CommDef.YOALOG_ERROR, false);

			    return;
		    }

		    m_iYuantaAPI.YOA_SetTRFieldString("211010", "InBlock1", "acnt_aid", strAccount, 0);
		    m_iYuantaAPI.YOA_SetTRFieldString("211010", "InBlock1", "passwd", strAcctPwd, 0);

		    nReqID = m_iYuantaAPI.YOA_Request("211010", true, -1);

		    if (CommDef.ERROR_MAX_CODE < nReqID)
		    {
                m_mapRequestTR[nReqID] = "211010";
			    m_mainForm.LogMessage("[ReqID:"+ nReqID +"] [211010]ELW매매기본예탁금 조회를 요청하였습니다.");
		    }
		    else
		    {
                m_mainForm.LogMessage("[211010]ELW매매기본예탁금 조회중 오류가 발생하였습니다.", CommDef.YOALOG_ERROR);

                int nErrorCode = m_iYuantaAPI.YOA_GetLastError();
                m_mainForm.LogMessage("[" + nErrorCode + " ]" + m_iYuantaAPI.YOA_GetErrorMessage(nErrorCode), CommDef.YOALOG_ERROR, false);
		    }
        }

        private void Process204006()
        {
            m_iYuantaAPI.YOA_SetTRInfo("204006", "OutBlock1");
	        m_mainForm.lvAcctInfo1.Items[0].SubItems[1].Text = m_mainForm.Commify(m_iYuantaAPI.YOA_GetFieldDouble("yesu_amt1", 0));
            m_mainForm.lvAcctInfo1.Items[0].SubItems[2].Text = m_mainForm.Commify(m_iYuantaAPI.YOA_GetFieldDouble("maedosu_amt1", 0));
            m_mainForm.lvAcctInfo1.Items[0].SubItems[3].Text = m_mainForm.Commify(m_iYuantaAPI.YOA_GetFieldDouble("yeonche_amt1", 0));
            m_mainForm.lvAcctInfo1.Items[1].SubItems[1].Text = m_mainForm.Commify(m_iYuantaAPI.YOA_GetFieldDouble("yesu_amt2", 0));
            m_mainForm.lvAcctInfo1.Items[1].SubItems[2].Text = m_mainForm.Commify(m_iYuantaAPI.YOA_GetFieldDouble("maedosu_amt2", 0));
            m_mainForm.lvAcctInfo1.Items[1].SubItems[3].Text = m_mainForm.Commify(m_iYuantaAPI.YOA_GetFieldDouble("yeonche_amt2", 0));
            m_mainForm.lvAcctInfo1.Items[0].SubItems[0].Text = m_iYuantaAPI.YOA_GetFieldString("d1_date", 0);
            m_mainForm.lvAcctInfo1.Items[1].SubItems[0].Text = m_iYuantaAPI.YOA_GetFieldString("d1_date", 0);

            m_mainForm.lvAcctInfo3.Items[0].SubItems[1].Text = m_mainForm.Commify(m_iYuantaAPI.YOA_GetFieldDouble("yesu_amt1", 0));
            m_mainForm.lvAcctInfo3.Items[1].SubItems[1].Text = m_mainForm.Commify(m_iYuantaAPI.YOA_GetFieldDouble("we_margin_hyun_amt", 0));
            m_mainForm.lvAcctInfo3.Items[2].SubItems[1].Text = m_mainForm.Commify(m_iYuantaAPI.YOA_GetFieldDouble("we_margin_dae_amt", 0));
            m_mainForm.lvAcctInfo3.Items[3].SubItems[1].Text = m_mainForm.Commify(m_iYuantaAPI.YOA_GetFieldDouble("hyun_misu_amt", 0));
            m_mainForm.lvAcctInfo3.Items[4].SubItems[1].Text = m_mainForm.Commify(m_iYuantaAPI.YOA_GetFieldDouble("dan_jumun_amt", 0));
            m_mainForm.lvAcctInfo3.Items[5].SubItems[1].Text = m_mainForm.Commify(m_iYuantaAPI.YOA_GetFieldDouble("daeyounggum_amt", 0));
            m_mainForm.lvAcctInfo3.Items[6].SubItems[1].Text = m_mainForm.Commify(m_iYuantaAPI.YOA_GetFieldDouble("jumun_poss_hyun_amt", 0));
            m_mainForm.lvAcctInfo3.Items[7].SubItems[1].Text = m_mainForm.Commify(m_iYuantaAPI.YOA_GetFieldDouble("chul_poss_amt", 0));
            m_mainForm.lvAcctInfo3.Items[8].SubItems[1].Text = m_mainForm.Commify(m_iYuantaAPI.YOA_GetFieldDouble("supyo_ip_amt", 0));
            m_mainForm.lvAcctInfo3.Items[9].SubItems[1].Text = m_mainForm.Commify(m_iYuantaAPI.YOA_GetFieldDouble("gita_supyo_amt", 0));

            m_mainForm.lvAcctInfo4.Items[0].SubItems[1].Text = m_mainForm.Commify(m_iYuantaAPI.YOA_GetFieldDouble("sin_settle_bo_amt", 0));
            m_mainForm.lvAcctInfo4.Items[1].SubItems[1].Text = m_mainForm.Commify(m_iYuantaAPI.YOA_GetFieldDouble("sin_bo_hyun_amt", 0));
            m_mainForm.lvAcctInfo4.Items[2].SubItems[1].Text = m_mainForm.Commify(m_iYuantaAPI.YOA_GetFieldDouble("sin_bo_dae_amt", 0));
            m_mainForm.lvAcctInfo4.Items[3].SubItems[1].Text = m_mainForm.Commify(m_iYuantaAPI.YOA_GetFieldDouble("sin_dam_hyun_amt", 0));
            m_mainForm.lvAcctInfo4.Items[4].SubItems[1].Text = m_mainForm.Commify(m_iYuantaAPI.YOA_GetFieldDouble("sin_dam_dae_amt", 0));
            m_mainForm.lvAcctInfo4.Items[5].SubItems[1].Text = m_mainForm.Commify(m_iYuantaAPI.YOA_GetFieldDouble("cho_dam_hyun_amt", 0));
            m_mainForm.lvAcctInfo4.Items[6].SubItems[1].Text = m_mainForm.Commify(m_iYuantaAPI.YOA_GetFieldDouble("cho_dam_dae_amt", 0));
            m_mainForm.lvAcctInfo4.Items[7].SubItems[1].Text = m_mainForm.Commify(m_iYuantaAPI.YOA_GetFieldDouble("kwon_dae_amt", 0));
            m_mainForm.lvAcctInfo4.Items[8].SubItems[1].Text = m_mainForm.Commify(m_iYuantaAPI.YOA_GetFieldDouble("yung_gum_amt", 0));
            m_mainForm.lvAcctInfo4.Items[9].SubItems[1].Text = m_mainForm.Commify(m_iYuantaAPI.YOA_GetFieldDouble("daeju_amt", 0));
        }

        private void Process211010()
        {
	        m_mainForm.lvAcctInfo2.Items[0].SubItems[1].Text = m_mainForm.Commify(m_iYuantaAPI.YOA_GetTRFieldDouble("211010", "OutBlock1", "elw_dptamt", 0));
	        m_mainForm.lvAcctInfo2.Items[0].SubItems[3].Text = m_mainForm.Commify(m_iYuantaAPI.YOA_GetTRFieldDouble("211010", "OutBlock1", "elw_bas_dpt_amt", 0));
        }

        public void ReceiveError(int nReqID, int nErrCode, string strErrMsg)
        {

        }

        public void ReceiveData(int nReqID)
        {
            string strTRID = m_mapRequestTR[nReqID];
            string strTRName = "";

            if (strTRID.Equals("204006"))
            {
                strTRName = "[204006]가정산예수현황";
                Process204006();
            }
            else if (strTRID.Equals("211010"))
            {
                strTRName = "[211010]미체결내역";
                Process211010();
            }

            string strMsg = "[ReqID:" + nReqID + "] " + strTRName + " 응답을 수신하였습니다.";
            m_mainForm.LogMessage(strMsg);
        }

        public void ReceiveRealData(string strAutoID)
        {
        }
    }
}
