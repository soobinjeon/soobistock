using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.Runtime.InteropServices.ComTypes;
using YuantaCOMLib;

namespace YOACOMClientCSharp
{
    public partial class MainForm : Form, IYuantaAPIEvents
    {
        IYuantaAPI m_iYuantaAPI;
        
        BasicTestHandler    m_basicTestHandler;
        StockSiseHandler    m_stockSiseHandler;
        StockOrderHandler   m_stockOrderHandler;
        StockAccountHandler m_stockAccountHandler;

        [System.Runtime.InteropServices.DllImport("kernel32")]
        private static extern int GetPrivateProfileString(
            string section, string key, string def,
            StringBuilder retVal, int size, string filePath);

        public MainForm()
        {
            InitializeComponent();

            // 유안타 오픈 API 기본 설정 ///////////////////////////////
            IConnectionPoint icp;
            IConnectionPointContainer icpc;
            int dwCookie = 0;

            m_iYuantaAPI = new YuantaAPI();
            icpc = (IConnectionPointContainer)m_iYuantaAPI;
            Guid IID_QueryEvents = typeof(IYuantaAPIEvents).GUID;
            icpc.FindConnectionPoint(ref IID_QueryEvents, out icp);
            icp.Advise(this, out dwCookie);
            ////////////////////////////////////////////////////////////

            m_basicTestHandler = new BasicTestHandler();
            m_basicTestHandler.m_mainForm = this;
            m_basicTestHandler.m_iYuantaAPI = m_iYuantaAPI;

            m_stockSiseHandler = new StockSiseHandler();
            m_stockSiseHandler.m_mainForm   = this;
            m_stockSiseHandler.m_iYuantaAPI = m_iYuantaAPI;
            m_stockSiseHandler.InitControl();

            ImageList imgList = new ImageList();
            imgList.ImageSize = new Size(1, 18);
            lvAcctList.SmallImageList = imgList;

            m_stockOrderHandler = new StockOrderHandler();
            m_stockOrderHandler.m_mainForm = this;
            m_stockOrderHandler.m_iYuantaAPI = m_iYuantaAPI;
            m_stockOrderHandler.InitControl();

            m_stockAccountHandler = new StockAccountHandler();
            m_stockAccountHandler.m_mainForm = this;
            m_stockAccountHandler.m_iYuantaAPI = m_iYuantaAPI;
            m_stockAccountHandler.InitControl();

            //Initial();
        }

        private void MainForm_FormClosed(object sender, FormClosedEventArgs e)
        {
            if (null != m_iYuantaAPI)
                m_iYuantaAPI.YOA_UnInitial();
        }

        #region IYuantaAPIEvents 멤버

        void IYuantaAPIEvents.ReceiveSystemMessage(int nID, string strMsg)
        {
            //MessageBox.Show("[MsgID : " + nID + "] " + strMsg);
            LogMessage(strMsg);
            
            if (CommDef.NOTIFY_SYSTEM_NEED_TO_RESTART == nID)
            {
                m_iYuantaAPI.YOA_ReStart();
            }
            
            throw new NotImplementedException();
        }

        void IYuantaAPIEvents.Login(int nResult, string strMsg)
        {
            if (CommDef.RESPONSE_LOGIN_SUCCESS == nResult)
            {
                btnLogout.Enabled = true;
                btnGetAccount.Enabled = true;

                LogMessage("로그인이 완료되었습니다.");
            }
            else
            {
                btnLogin.Enabled = true;
                btnLogout.Enabled = false;
                btnGetAccount.Enabled = false;

                LogMessage("로그인이 실패하였습니다.", CommDef.YOALOG_ERROR);

                if (CommDef.ERROR_TIMEOUT_DATA == nResult)
                {
                    LogMessage("서버로부터 로그인 응답이 없습니다. 다시 시도하여 주십시오.", CommDef.YOALOG_ERROR, false);
                }
                else
                {
                    LogMessage(m_iYuantaAPI.YOA_GetErrorMessage(nResult), CommDef.YOALOG_ERROR, false);
                }
            }

            throw new NotImplementedException();
        }

        void IYuantaAPIEvents.ReceiveError(int nReqID, int nErrCode, string strErrMsg)
        {
            if (m_basicTestHandler.m_mapRequestTR.ContainsKey(nReqID))
            {
                m_basicTestHandler.ReceiveError(nReqID, nErrCode, strErrMsg);
            }
            else if (m_stockSiseHandler.m_mapRequestTR.ContainsKey(nReqID))
            {
                m_stockSiseHandler.ReceiveError(nReqID, nErrCode, strErrMsg);
            }
            else if (m_stockOrderHandler.m_mapRequestTR.ContainsKey(nReqID))
            {
                m_stockOrderHandler.ReceiveError(nReqID, nErrCode, strErrMsg);
            }

            throw new NotImplementedException();
        }

        void IYuantaAPIEvents.ReceiveData(int nReqID, string strDSOID)
        {
            if (m_basicTestHandler.m_mapRequestTR.ContainsKey(nReqID))
            {
                m_basicTestHandler.ReceiveData(nReqID);
            }
            else if (m_stockSiseHandler.m_mapRequestTR.ContainsKey(nReqID))
            {
                m_stockSiseHandler.ReceiveData(nReqID);
            }
            else if (m_stockOrderHandler.m_mapRequestTR.ContainsKey(nReqID))
            {
                m_stockOrderHandler.ReceiveData(nReqID);
            }

            throw new NotImplementedException();
        }

        void IYuantaAPIEvents.ReceiveRealData(int nReqID, string strAutoID)
        {
            if (m_basicTestHandler.m_mapAutoTR.ContainsKey(nReqID))
            {
                m_basicTestHandler.ReceiveRealData(nReqID, strAutoID);
            }
            else if (m_stockSiseHandler.m_mapAutoTR.ContainsKey(nReqID))
            {
                m_stockSiseHandler.ReceiveRealData(nReqID, strAutoID);
            }
            else if (m_stockOrderHandler.m_mapAutoTR.ContainsKey(nReqID))
            {
                m_stockOrderHandler.ReceiveRealData(nReqID, strAutoID);
            }
            
            throw new NotImplementedException();
        }

        #endregion

        private void LoadUserInfo()
        {
            string strPath = System.Windows.Forms.Application.ExecutablePath;
            strPath = System.IO.Path.GetDirectoryName(strPath);
            strPath = strPath + "\\testlogin.ini";

            StringBuilder strTemp = new StringBuilder(255);
            GetPrivateProfileString("TEST_INFO", "ID", string.Empty, strTemp, 255, strPath);
            txtUserID.Text = strTemp.ToString();

            GetPrivateProfileString("TEST_INFO", "PWD", string.Empty, strTemp, 255, strPath);
            txtUserPW.Text = strTemp.ToString();

            GetPrivateProfileString("TEST_INFO", "CERT_PWD", string.Empty, strTemp, 255, strPath);
            txtCertPW.Text = strTemp.ToString();

            if (0 < txtUserID.Text.Length && 0 < txtUserPW.Text.Length && 0 < txtCertPW.Text.Length)
                Login();
        }

        public void LogMessage(string strMsg, int nType = 0, bool bTimeStamp = true)
        {
            string strLog = "";

            if (true == bTimeStamp)
            {
                DateTime dt = DateTime.Now;

                if (0 == nType)
                {
                    strLog = "[LOG:" + dt.ToString("yyyy-MM-dd hh:mm:ss") + "] " + strMsg;
                }
                else if (1 == nType)
                {
                    strLog = "[ERR:" + dt.ToString("yyyy-MM-dd hh:mm:ss") + "] " + strMsg;
                }
            }
            else
            {
                strLog = "[ERR_MSG] " + strMsg;
            }

            lbMainLog.Items.Add(strLog);
        }

        public string Commify(int nData)
        {
            string strResult = "";
            strResult = string.Format("{0:#,###0}", nData);

            return strResult;
        }

        public string Commify(double dData)
        {
            string strResult = "";
            strResult = string.Format("{0:#,###.##0}", dData);

            return strResult;
        }

        public string Commify(string strData)
        {
            int nData = Convert.ToInt32(strData);
            return Commify(nData);
        }

        private void Initial()
        {
            btnInitial.Enabled = false;

            //string strURL = "simul.tradarglobal.api.com";
            //string strURL = "real.tradarglobal.api.com";
            //string strURL = "real.tradar.api.com";
            string strURL = "simul.tradar.api.com";
            if (CommDef.RESULT_SUCCESS == m_iYuantaAPI.YOA_Initial(strURL, ""))
            {
                if (strURL == "simul.tradar.api.com" || strURL == "simul.tradarglobal.api.com")
                    MessageBox.Show("모의투자로 접속합니다.\n모의투자의 계좌비밀번호는 0000입니다.", "알림", MessageBoxButtons.OK);

                btnLogin.Enabled = true;
                txtUserID.Focus();

                LogMessage("유안타 Open API가 초기화되었습니다.");
            }
            else
            {
                btnInitial.Enabled = true;

                LogMessage("유안타 Open API가 초기화에 실패하였습니다.", CommDef.YOALOG_ERROR);
            }
        }

        private void Login()
        {
            int nResult = m_iYuantaAPI.YOA_Login(txtUserID.Text, txtUserPW.Text, txtCertPW.Text);

            if (CommDef.RESULT_SUCCESS == nResult)
            {
                btnLogin.Enabled = false;

                LogMessage("로그인 요청이 되었습니다.");
            }
            else
            {
                btnLogin.Enabled = true;

                LogMessage("로그인 요청이 실패하였습니다.", CommDef.YOALOG_ERROR);
                LogMessage(m_iYuantaAPI.YOA_GetErrorMessage(nResult), CommDef.YOALOG_ERROR, false);
            }
        }

        private void InitAccount()
        {
            lvAcctList.BeginUpdate();

            lvAcctList.Items.Clear();
            m_stockOrderHandler.ClearAccount();
            m_stockAccountHandler.ClearAccount();

            ListViewItem item = null;
            string strAccount = "";
            string strAcctName = "";

            int nCount = m_iYuantaAPI.YOA_GetAccountCount();
            for (int i = 0; i < nCount; i++)
            {
                item = new ListViewItem(Convert.ToString(i + 1));

                strAccount = m_iYuantaAPI.YOA_GetAccount(i);
                if (1 == strAccount.Length % 2)
                {
                    strAccount = strAccount.Insert(5, "-");
                    strAccount = strAccount.Insert(3, "-");
                }
                else
                {
                    strAccount = strAccount.Insert(8, "-");
                    strAccount = strAccount.Insert(4, "-");
                }

                strAcctName = m_iYuantaAPI.YOA_GetAccountInfo(CommDef.ACCOUNT_INFO_NAME, strAccount);

                item.SubItems.Add(strAccount);
                item.SubItems.Add(strAcctName);

                lvAcctList.Items.Add(item);

                m_stockOrderHandler.AddAccount(strAccount, strAcctName);
                m_stockAccountHandler.AddAccount(strAccount, strAcctName);
            }

            if (0 < nCount)
            {
                cbOrdAccount.SelectedIndex = 0;
                cbAcctAccount.SelectedIndex = 0;
            }

            lvAcctList.EndUpdate();
        }
        
        private void btnInitial_Click(object sender, EventArgs e)
        {
            Initial();
        }

        private void btnLogin_Click(object sender, EventArgs e)
        {
            Login();
        }

        private void btnLogout_Click(object sender, EventArgs e)
        {
            
        }

        private void btnGetAccount_Click(object sender, EventArgs e)
        {
            InitAccount();
        }

        private void btnBTSearch_Click(object sender, EventArgs e)
        {
            m_basicTestHandler.Search();
        }

        private void btnBTAutoRegist_Click(object sender, EventArgs e)
        {
            m_basicTestHandler.RegistAuto();
        }

        private void btnBTAutoUnRegist_Click(object sender, EventArgs e)
        {
            m_basicTestHandler.UnRegistAuto();
        } 

        private void btnSearch_Click(object sender, EventArgs e)
        {
            m_stockSiseHandler.Search();
        }

        private void btnNextSearch_Click(object sender, EventArgs e)
        {
            m_stockSiseHandler.NextSearch();
        }

        private void btnOrdSearch_Click(object sender, EventArgs e)
        {
            m_stockOrderHandler.Search();
        }

        private void tabPanel_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (2 == tabPanel.SelectedIndex || 3 == tabPanel.SelectedIndex)
            {
                if (0 == lvAcctList.Items.Count)
                {
                    if (DialogResult.OK == MessageBox.Show("계좌정보가 없습니다.\n계좌가져오기를 하시겠습니까?", "알림", MessageBoxButtons.OKCancel))
                    {
                        InitAccount();
                    }
                }
            }
        }

        private void cbOrdAccount_SelectedIndexChanged(object sender, EventArgs e)
        {
            m_stockOrderHandler.cbOrdAccount_SelectedIndexChanged();
        }

        private void nudOrdPrice_ValueChanged(object sender, EventArgs e)
        {
            m_stockOrderHandler.nudOrdPrice_ValueChanged();
        }

        private void nudOrdQty_ValueChanged(object sender, EventArgs e)
        {
            m_stockOrderHandler.nudOrdPrice_ValueChanged();
        }

        private void tabMesuMedo_SelectedIndexChanged(object sender, EventArgs e)
        {
            m_stockOrderHandler.SetOrderMedoMesu(tabMesuMedo.SelectedIndex);
        }

        private void btnOrder_Click(object sender, EventArgs e)
        {
            m_stockOrderHandler.Order();
        }

        private void btnOrdSearchMiChegyul_Click(object sender, EventArgs e)
        {
            m_stockOrderHandler.SearchMiChegyul();
        }

        private void btnOrdSearchChegyul_Click(object sender, EventArgs e)
        {
            m_stockOrderHandler.SearchChegyul();
        }

        private void cbAcctAccount_SelectedIndexChanged(object sender, EventArgs e)
        {
            m_stockAccountHandler.cbAcctAccount_SelectedIndexChanged();
        }

        private void btnAcctSearch_Click(object sender, EventArgs e)
        {
            m_stockAccountHandler.Search();
        }
    
    }
}
