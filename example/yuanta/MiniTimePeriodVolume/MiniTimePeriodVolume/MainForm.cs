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

namespace MiniTimePeriodVolume
{
    public partial class MainForm : Form, IYuantaAPIEvents
    {
        IYuantaAPI iYuantaAPI;
        private int reqID;
        private bool nextFlag;
        private bool autoFlag;
        
        public MainForm()
        {
            InitializeComponent();

            // 유안타 오픈 API 기본 설정 ///////////////////////////////
            IConnectionPoint icp;
            IConnectionPointContainer icpc;
            int dwCookie = 0;

            iYuantaAPI = new YuantaAPI();
            icpc = (IConnectionPointContainer)iYuantaAPI;
            Guid IID_QueryEvents = typeof(IYuantaAPIEvents).GUID;
            icpc.FindConnectionPoint(ref IID_QueryEvents, out icp);
            icp.Advise(this, out dwCookie);
            ////////////////////////////////////////////////////////////

            cbDayType.SelectedIndex = 0;
            cbInterval.SelectedIndex = 0;
            cbType.SelectedIndex = 0;

            reqID = -1;
            nextFlag = false;
            autoFlag = false;

            ImageList imgList = new ImageList();
            imgList.ImageSize = new Size(1, 22);
            lvData.SmallImageList = imgList;
        }

        private void MainForm_Shown(object sender, EventArgs e)
        {
            LoginDlgShow();
        }

        private void MainForm_FormClosed(object sender, FormClosedEventArgs e)
        {
            if (null != iYuantaAPI)
                iYuantaAPI.YOA_UnInitial();
        }

        #region IYuantaAPIEvents 멤버

        void IYuantaAPIEvents.ReceiveSystemMessage(int nID, string strMsg)
        {
            lblLog.Text = strMsg;

            if (CommDef.NOTIFY_SYSTEM_NEED_TO_RESTART == nID)
                iYuantaAPI.YOA_ReStart();

            throw new NotImplementedException();
        }

        void IYuantaAPIEvents.Login(int nResult, string strMsg)
        {
            if (CommDef.RESPONSE_LOGIN_SUCCESS == nResult)
            {
                lblLog.Text = "로그인이 완료되었습니다.";

                tbCode.Enabled = true;
                lblName.Enabled = true;
                btnRequest.Enabled = true;
                cbDayType.Enabled = true;
                cbInterval.Enabled = true;
                tbVolume.Enabled = true;
                cbType.Enabled = true;

                tbCode.Focus();
            }
            else
            {
                lblLog.Text = "로그인이 실패하였습니다.";

                MessageBox.Show(strMsg, "로그인 실패", MessageBoxButtons.OK);
                LoginDlgShow();
            }

            throw new NotImplementedException();
        }

        void IYuantaAPIEvents.ReceiveError(int nReqID, int nErrCode, string strErrMsg)
        {
            if (nErrCode == CommDef.ERROR_TIMEOUT_DATA)
            {
                lblLog.Text = "타임아웃 : [301020] 요청의 응답이 없습니다.";
            }
            else if (nErrCode == CommDef.ERROR_REQUEST_FAIL)
            {
                lblLog.Text = "오류 : " + iYuantaAPI.YOA_GetErrorMessage(nReqID);
            }

            throw new NotImplementedException();
        }

        void IYuantaAPIEvents.ReceiveData(int nReqID, string strDSOID)
        {
            if (reqID == nReqID)
            {
                lblLog.Text = "[301020]시간대별체결량_MAX 응답을 수신하였습니다.";
                ProcessDSO301020();
            }

            throw new NotImplementedException();
        }

        void IYuantaAPIEvents.ReceiveRealData(int nReqID, string strAutoID)
        {
            if ("11" == strAutoID)
            {
                ProcessAUTO11();
            }

            throw new NotImplementedException();
        }

        #endregion

        private void LoginDlgShow()
        {
            LoginDlg dlg = new LoginDlg();

            if (DialogResult.OK == dlg.ShowDialog())
            {
                string strURL = "simul.tradar.api.com";

                if (1 == dlg.cbServer.SelectedIndex)
                    strURL = "real.tradar.api.com";
                else if (2 == dlg.cbServer.SelectedIndex)
                    strURL = "simul.tradarglobal.api.com";
                else if (3 == dlg.cbServer.SelectedIndex)
                    strURL = "simul.tradarglobal.api.com";

                if (CommDef.RESULT_SUCCESS == iYuantaAPI.YOA_Initial(strURL, ""))
                {
                    int nResult = iYuantaAPI.YOA_Login(dlg.tbUserID.Text, dlg.tbUserPW.Text, dlg.tbCertPW.Text);

                    if (CommDef.RESULT_SUCCESS == nResult)
                    {
                        lblLog.Text = "로그인 요청하였습니다.";
                    }
                    else
                    {
                        lblLog.Text = "로그인 요청 실패하였습니다.";
                        MessageBox.Show(iYuantaAPI.YOA_GetErrorMessage(nResult), "로그인 요청 실패", MessageBoxButtons.OK);

                        if (CommDef.ERROR_ID_SHORT == nResult || CommDef.ERROR_ID_PASSWORD_SHORT == nResult || CommDef.ERROR_CERT_PASSWORD_SHORT == nResult)
                        {
                            LoginDlgShow();
                        }
                        else
                        {
                            Close();
                        }
                    }
                }
                else
                {
                    MessageBox.Show("유안타 Open API 초기화 실패하였습니다..\n프로그램을 종료합니다.", "알림", MessageBoxButtons.OK);
                    Close();
                }
            }
            else
            {
                Close();
            }

            dlg.Dispose();
        }

        private void Auto()
        {
            autoFlag = !autoFlag;

            if (true == autoFlag)
            {
                btnAuto.Text = "중지";

                iYuantaAPI.YOA_SetTRFieldString("11", "InBlock1", "jongcode", tbCode.Text, 0);
                iYuantaAPI.YOA_RegistAuto("11");
            }
            else
            {
                btnAuto.Text = "실시간";
                iYuantaAPI.YOA_UnRegistAllAuto();
            }
        }

        private void ProcessDSO301020()
        {
            int next = iYuantaAPI.YOA_GetTRFieldByte("301020", "OutBlock1", "next", 0);
            if (1 == next)
                btnNext.Enabled = true;
            else
                btnNext.Enabled = false;

            ListViewItem item = null;
            int nData = 0;
            int nColor = 0;
            string strData = "";

            iYuantaAPI.YOA_SetTRInfo("301020", "OutBlock2");
            int dataCount = iYuantaAPI.YOA_GetRowCount("301020", "OutBlock2");

            for (int i = 0; i < dataCount; i++)
            {
                item = new ListViewItem();
                item.UseItemStyleForSubItems = false;

                strData = iYuantaAPI.YOA_GetFieldString("time", i);
                item.SubItems.Add(strData);

                nData = iYuantaAPI.YOA_GetFieldLong("curjuka", i);
                strData = string.Format("{0:#,###0}", nData);
                item.SubItems.Add(strData);

                nData = iYuantaAPI.YOA_GetFieldLong("debi", i);
                if (0 < nData)
                {
                    item.SubItems.Add("▲");
                }
                else if (0 > nData)
                {
                    item.SubItems.Add("▼");
                    nData = -nData;
                }
                strData = string.Format("{0:#,###0}", nData);
                item.SubItems.Add(strData);

                nColor = iYuantaAPI.YOA_GetFieldAttr("debi", i);
                if (2 == nColor)
                {
                    item.SubItems[3].ForeColor = Color.Red;
                    item.SubItems[4].ForeColor = Color.Red;
                }
                else if (5 == nColor)
                {
                    item.SubItems[3].ForeColor = Color.Blue;
                    item.SubItems[4].ForeColor = Color.Blue;
                }
                else
                {
                    item.SubItems[3].ForeColor = Color.Black;
                    item.SubItems[4].ForeColor = Color.Black;
                }

                nData = iYuantaAPI.YOA_GetFieldLong("nowvol", i);
                strData = string.Format("{0:#,###0}", nData);
                item.SubItems.Add(strData);

                nColor = iYuantaAPI.YOA_GetFieldAttr("nowvol", i);
                if (83 == nColor)
                {
                    item.SubItems[5].ForeColor = Color.Red;
                }
                else if (66 == nColor)
                {
                    item.SubItems[5].ForeColor = Color.Blue;
                }
                else
                {
                    item.SubItems[5].ForeColor = Color.Black;
                }

                lvData.Items.Add(item);
            }

            btnAuto.Enabled = true;
        }

        private void ProcessAUTO11()
        {
            iYuantaAPI.YOA_SetTRInfo("11", "OutBlock1");
        }

        private void btnRequest_Click(object sender, EventArgs e)
        {
            string strName = iYuantaAPI.YOA_GetCodeInfo(CommDef.MARKET_TYPE_INTERNAL, CommDef.CODE_INFO_NAME, tbCode.Text);

            if (tbCode.Text.Length < 6 || strName.Length < 1)
            {
                MessageBox.Show("종목코드를 확인해주시기 바랍니다.", "알림", MessageBoxButtons.OK);
            }
            else
            {
                if (-1 != reqID)
                    iYuantaAPI.YOA_ReleaseData(reqID);

                iYuantaAPI.YOA_UnRegistAllAuto();
                nextFlag = false;
                lvData.Items.Clear();
   
                lblName.Text = strName;

                string strJang = iYuantaAPI.YOA_GetCodeInfo(CommDef.MARKET_TYPE_INTERNAL, CommDef.CODE_INFO_JANG_GUBUN, tbCode.Text);
                iYuantaAPI.YOA_SetTRInfo("301020", "Inblock1");
                iYuantaAPI.YOA_SetFieldString("jongcode", tbCode.Text, 0);
                iYuantaAPI.YOA_SetFieldString("janggubun", strJang, 0);
                iYuantaAPI.YOA_SetFieldLong("mingubun", cbInterval.SelectedIndex, 0);
                iYuantaAPI.YOA_SetFieldString("contime", "", 0);
                iYuantaAPI.YOA_SetFieldString("nowvolume", tbVolume.Text, 0);
                iYuantaAPI.YOA_SetFieldLong("nowvoltype", cbType.SelectedIndex, 0);
                iYuantaAPI.YOA_SetFieldLong("daygubun", cbDayType.SelectedIndex, 0);
                iYuantaAPI.YOA_SetFieldString("sortgubun", "0", 0);

                reqID = iYuantaAPI.YOA_Request("301020", false, -1);

                if (CommDef.ERROR_MAX_CODE < reqID)
                {
                    lblLog.Text = "[301020]시간대별체결량_MAX 조회를 요청하였습니다.";
                }
                else               // 조회 요청 실패 시, 오류 처리
                {
                    lblLog.Text = iYuantaAPI.YOA_GetErrorMessage(reqID);     // 조회 요청 실패에 대한 메시지를 얻을 수 있습니다.
                }
            }
        }

        private void btnNext_Click(object sender, EventArgs e)
        {
            reqID = iYuantaAPI.YOA_Request("301020", false, reqID);
        }

        private void btnAuto_Click(object sender, EventArgs e)
        {
            Auto();
        }
    }
}
