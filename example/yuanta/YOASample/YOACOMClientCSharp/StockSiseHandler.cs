using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using YuantaCOMLib;

namespace YOACOMClientCSharp
{
    class StockSiseHandler
    {
        public MainForm m_mainForm;
        public IYuantaAPI m_iYuantaAPI;
        public Dictionary<int, string> m_mapRequestTR;
        public Dictionary<int, string> m_mapAutoTR;
        private int m_nPrevLastPrice;
        private int m_nReqID_301004;
        private string m_strJongCode;

        public StockSiseHandler()
        {
            m_mainForm      = null;
            m_iYuantaAPI    = null;

            m_mapRequestTR = new Dictionary<int, string>();
            m_mapAutoTR = new Dictionary<int, string>();

            m_nPrevLastPrice    = 0;
            m_nReqID_301004     = 0;
        }

        public void InitControl()
        {
            ImageList imgList1 = new ImageList();
            imgList1.ImageSize = new Size(1, 28);
            m_mainForm.lvJongInfoHeader.SmallImageList  = imgList1;
            m_mainForm.lvJongInfo.SmallImageList        = imgList1;
            m_mainForm.lvHogaFooter.SmallImageList      = imgList1;
            
            ImageList imgList2 = new ImageList();
            imgList2.ImageSize = new Size(1, 18);
            m_mainForm.lvMedoHoga.SmallImageList        = imgList2;
            m_mainForm.lvMesuHoga.SmallImageList        = imgList2;
            m_mainForm.lvConTick.SmallImageList         = imgList2;
            m_mainForm.lvDaily.SmallImageList           = imgList2;

            m_mainForm.lvMedoHoga.Items[1].UseItemStyleForSubItems = false;
        }

        public void Search()
        {
            if (0 != m_nReqID_301004)
                m_iYuantaAPI.YOA_ReleaseData(m_nReqID_301004);

            m_mainForm.lvConTick.Items.Clear();
            m_mainForm.lvDaily.Items.Clear();
            ListViewItem item = new ListViewItem();
            item.UseItemStyleForSubItems = false;
            item.SubItems.Add("현    재");
            item.SubItems.Add("");
            item.SubItems.Add("");
            item.SubItems.Add("");
            item.SubItems.Add("");
            item.SubItems.Add("");
            item.SubItems.Add("");
            item.SubItems.Add("");
            item.SubItems.Add("");
            m_mainForm.lvDaily.Items.Add(item);
            m_nReqID_301004 = 0;

            UnRegistAuto();

            m_strJongCode = m_mainForm.txtJongCode.Text;
            m_strJongCode.Trim();

            m_iYuantaAPI.YOA_SetTRFieldString("300001", "InBlock1", "jang",     "1", 0);
            m_iYuantaAPI.YOA_SetTRFieldString("300001", "InBlock1", "jongcode", m_strJongCode, 0);
            m_iYuantaAPI.YOA_SetTRFieldString("300001", "InBlock1", "outflag",  "N", 0);
            m_iYuantaAPI.YOA_SetTRFieldString("300001", "InBlock1", "tsflag",   "0", 0);
            int nResult = m_iYuantaAPI.YOA_Request("300001", true, -1);

            if ( CommDef.ERROR_MAX_CODE < nResult )
            {
                m_mapRequestTR[nResult] = "300001";
                string strMsg = "[ReqID:"+ nResult +"] [300001]주식현재가 조회를 요청하였습니다.";

				m_mainForm.LogMessage( strMsg );
            }
            else
            {
                string strMsg = "[300001]주식현재가 조회 요청중 오류가 발생하였습니다.";
                m_mainForm.LogMessage(strMsg, CommDef.YOALOG_ERROR);

                strMsg = "[" + nResult + "]" + m_iYuantaAPI.YOA_GetErrorMessage( nResult );
                m_mainForm.LogMessage(strMsg, CommDef.YOALOG_ERROR, false);
            }

            string strJang = m_iYuantaAPI.YOA_GetCodeInfo(CommDef.MARKET_TYPE_INTERNAL, CommDef.CODE_INFO_JANG_GUBUN, m_mainForm.txtJongCode.Text);
            m_iYuantaAPI.YOA_SetTRInfo("300002", "InBlock1");
            m_iYuantaAPI.YOA_SetFieldString("jang", strJang, 0);
            m_iYuantaAPI.YOA_SetFieldString("jongcode", m_strJongCode, 0);
            m_iYuantaAPI.YOA_SetFieldString("outflag", "N", 0);
            nResult = m_iYuantaAPI.YOA_Request("300002", true, -1);

            if (CommDef.ERROR_MAX_CODE < nResult)
            {
                m_mapRequestTR[nResult] = "300002";
                string strMsg = "[ReqID:" + nResult + "] [300002]주식현재가_호가체결 조회를 요청하였습니다.";

                m_mainForm.LogMessage(strMsg);
            }
            else
            {
                string strMsg = "[300002]주식현재가_호가체결 조회 요청중 오류가 발생하였습니다.";
                m_mainForm.LogMessage(strMsg, CommDef.YOALOG_ERROR);

                strMsg = "[" + nResult + "]" + m_iYuantaAPI.YOA_GetErrorMessage(nResult);
                m_mainForm.LogMessage(strMsg, CommDef.YOALOG_ERROR, false);
            }

            DateTime dt = DateTime.Now;
            string strDate = dt.ToString("yyyyMMdd");

            m_iYuantaAPI.YOA_SetTRInfo("301004", "InBlock1");
            m_iYuantaAPI.YOA_SetFieldString("jongcode", m_strJongCode, 0);
            m_iYuantaAPI.YOA_SetFieldString("janggubun", strJang, 0);
            m_iYuantaAPI.YOA_SetFieldString("searchdate", strDate, 0);
            m_iYuantaAPI.YOA_SetFieldString("daygubun", "1", 0);
            m_iYuantaAPI.YOA_SetFieldString("querygubun", "0", 0);
            m_iYuantaAPI.YOA_SetFieldString("bpquery", "0", 0);
            nResult = m_iYuantaAPI.YOA_Request("301004", false, -1);

            if (CommDef.ERROR_MAX_CODE < nResult)
            {
                m_nReqID_301004 = nResult;
                m_mapRequestTR[nResult] = "301004";
                string strMsg = "[ReqID:" + nResult + "] [301004]수정일자별주가 조회를 요청하였습니다.";

                m_mainForm.LogMessage(strMsg);
            }
            else
            {
                string strMsg = "[301004]수정일자별주가 조회 요청중 오류가 발생하였습니다.";
                m_mainForm.LogMessage(strMsg, CommDef.YOALOG_ERROR);

                strMsg = "[" + nResult + "]" + m_iYuantaAPI.YOA_GetErrorMessage(nResult);
                m_mainForm.LogMessage(strMsg, CommDef.YOALOG_ERROR, false);
            }
        }

        public void NextSearch()
        {
            m_iYuantaAPI.YOA_Request("301004", false, m_nReqID_301004);
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

            m_iYuantaAPI.YOA_SetTRFieldString("12", "InBlock1", "jongcode", m_strJongCode, 0);
            nReqID = m_iYuantaAPI.YOA_RegistAuto("12");

            if (CommDef.ERROR_MAX_CODE < nReqID)
            {
                m_mapAutoTR[nReqID] = "12";

                m_mainForm.btnBTAutoUnRegist.Enabled = true;

                m_mainForm.LogMessage("[12]주식 실시간호가 Auto가 등록 되었습니다.");
            }
            else
            {
                m_mainForm.LogMessage("[12]주식 실시간호가 Auto 등록이 실패하였습니다.", CommDef.YOALOG_ERROR);

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
                    else if (autoTR.Value.Equals("12"))
                        m_mainForm.LogMessage("[12]주식 실시간호가 AUto가 해지 되었습니다.");
                }
                else
                {
                    if (autoTR.Value.Equals("11"))
                        m_mainForm.LogMessage("[11]주식 실시간체결 Auto 해지가 실패하였습니다.", CommDef.YOALOG_ERROR);
                    else if (autoTR.Value.Equals("12"))
                        m_mainForm.LogMessage("[12]주식 실시간호가 AUto 해지가 실패하였습니다.", CommDef.YOALOG_ERROR);

                    string strMsg = m_iYuantaAPI.YOA_GetErrorMessage(nResult);     // 실시간 해지 실패에 대한 메시지를 얻을 수 있습니다.
                    m_mainForm.LogMessage(strMsg, CommDef.YOALOG_ERROR, false);
                }
            }

            m_mapAutoTR.Clear();
        }

        private void Process300001_Auto11(bool bAuto)
        {
            if (bAuto)
                m_iYuantaAPI.YOA_SetTRInfo("11", "OutBlock1");
            else
                m_iYuantaAPI.YOA_SetTRInfo("300001", "OutBlock1");

            if (!bAuto)
                m_mainForm.lblJongName.Text = m_iYuantaAPI.YOA_GetFieldString("jongname", 0);

            int nColor = m_iYuantaAPI.YOA_GetFieldAttr("curjuka", 0);
            m_mainForm.lvJongInfo.Items[0].SubItems[1].Text = m_mainForm.Commify(m_iYuantaAPI.YOA_GetFieldLong("curjuka", 0));
            m_mainForm.lvDaily.Items[0].SubItems[2].Text = m_mainForm.Commify(m_iYuantaAPI.YOA_GetFieldLong("curjuka", 0));

            if (2 == nColor)
            {
                m_mainForm.lvJongInfo.Items[0].ForeColor = Color.Red;
                m_mainForm.lvJongInfo.Items[1].ForeColor = Color.Red;
                m_mainForm.lvJongInfo.Items[2].ForeColor = Color.Red;
                m_mainForm.lvDaily.Items[0].SubItems[2].ForeColor = Color.Red;
                m_mainForm.lvDaily.Items[0].SubItems[3].ForeColor = Color.Red;
                m_mainForm.lvDaily.Items[0].SubItems[4].ForeColor = Color.Red;
                m_mainForm.lvDaily.Items[0].SubItems[5].ForeColor = Color.Red;
            }
            else if (5 == nColor)
            {
                m_mainForm.lvJongInfo.Items[0].ForeColor = Color.Blue;
                m_mainForm.lvJongInfo.Items[1].ForeColor = Color.Blue;
                m_mainForm.lvJongInfo.Items[2].ForeColor = Color.Blue;
                m_mainForm.lvDaily.Items[0].SubItems[2].ForeColor = Color.Blue;
                m_mainForm.lvDaily.Items[0].SubItems[3].ForeColor = Color.Blue;
                m_mainForm.lvDaily.Items[0].SubItems[4].ForeColor = Color.Blue;
                m_mainForm.lvDaily.Items[0].SubItems[5].ForeColor = Color.Blue;
            }
            else
            {
                m_mainForm.lvJongInfo.Items[0].ForeColor = Color.Black;
                m_mainForm.lvJongInfo.Items[1].ForeColor = Color.Black;
                m_mainForm.lvJongInfo.Items[2].ForeColor = Color.Black;
                m_mainForm.lvDaily.Items[0].SubItems[2].ForeColor = Color.Black;
                m_mainForm.lvDaily.Items[0].SubItems[3].ForeColor = Color.Black;
                m_mainForm.lvDaily.Items[0].SubItems[4].ForeColor = Color.Black;
                m_mainForm.lvDaily.Items[0].SubItems[5].ForeColor = Color.Black;
            }

            int nDebi = m_iYuantaAPI.YOA_GetFieldLong("debi", 0);
            string strValue;
            if (0 < nDebi)
            {
                strValue = "▲  " + m_mainForm.Commify(nDebi);
                m_mainForm.lvDaily.Items[0].SubItems[3].Text = "▲";
            }
            else if (0 > nDebi)
            {
                nDebi = -nDebi;
                strValue = "▼  " + m_mainForm.Commify(nDebi);
                m_mainForm.lvDaily.Items[0].SubItems[3].Text = "▼";
            }
            else
            {
                strValue = m_mainForm.Commify(Convert.ToString(nDebi));
            }
            m_mainForm.lvJongInfo.Items[1].SubItems[1].Text = strValue;
            m_mainForm.lvDaily.Items[0].SubItems[4].Text = m_mainForm.Commify(nDebi);

            strValue = string.Format("{0:0.00}", m_iYuantaAPI.YOA_GetFieldDouble("debirate", 0));
            m_mainForm.lvJongInfo.Items[2].SubItems[1].Text = strValue;
            m_mainForm.lvDaily.Items[0].SubItems[5].Text = strValue;

            strValue = m_mainForm.Commify(m_iYuantaAPI.YOA_GetFieldString("volume", 0));
            m_mainForm.lvJongInfo.Items[3].SubItems[1].Text = strValue;
            m_mainForm.lvDaily.Items[0].SubItems[6].Text = strValue;

            nColor = m_iYuantaAPI.YOA_GetFieldAttr("startjuka", 0);
            strValue = m_mainForm.Commify(m_iYuantaAPI.YOA_GetFieldString("startjuka", 0));
            m_mainForm.lvJongInfo.Items[4].SubItems[1].Text = strValue;
            m_mainForm.lvDaily.Items[0].SubItems[7].Text = strValue;

            if (2 == nColor)
            {
                m_mainForm.lvJongInfo.Items[4].ForeColor = Color.Red;
                m_mainForm.lvDaily.Items[0].SubItems[7].ForeColor = Color.Red;
            }
            else if (5 == nColor)
            {
                m_mainForm.lvJongInfo.Items[4].ForeColor = Color.Blue;
                m_mainForm.lvDaily.Items[0].SubItems[7].ForeColor = Color.Blue;
            }
            else
            {
                m_mainForm.lvJongInfo.Items[4].ForeColor = Color.Black;
                m_mainForm.lvDaily.Items[0].SubItems[7].ForeColor = Color.Black;
            }

            nColor = m_iYuantaAPI.YOA_GetFieldAttr("highjuka", 0);
            strValue = m_mainForm.Commify(m_iYuantaAPI.YOA_GetFieldString("highjuka", 0));
            m_mainForm.lvJongInfo.Items[5].SubItems[1].Text = strValue;
            m_mainForm.lvDaily.Items[0].SubItems[8].Text = strValue;
            if (2 == nColor)
            {
                m_mainForm.lvJongInfo.Items[5].ForeColor = Color.Red;
                m_mainForm.lvDaily.Items[0].SubItems[8].ForeColor = Color.Red;
            }
            else if (5 == nColor)
            {
                m_mainForm.lvJongInfo.Items[5].ForeColor = Color.Blue;
                m_mainForm.lvDaily.Items[0].SubItems[8].ForeColor = Color.Blue;
            }
            else
            {
                m_mainForm.lvJongInfo.Items[5].ForeColor = Color.Black;
                m_mainForm.lvDaily.Items[0].SubItems[8].ForeColor = Color.Black;
            }

            nColor = m_iYuantaAPI.YOA_GetFieldAttr("lowjuka", 0);
            strValue = m_mainForm.Commify(m_iYuantaAPI.YOA_GetFieldString("lowjuka", 0));
            m_mainForm.lvJongInfo.Items[6].SubItems[1].Text = strValue;
            m_mainForm.lvDaily.Items[0].SubItems[9].Text = strValue;
            if (2 == nColor)
            {
                m_mainForm.lvJongInfo.Items[6].ForeColor = Color.Red;
                m_mainForm.lvDaily.Items[0].SubItems[9].ForeColor = Color.Red;
            }
            else if (5 == nColor)
            {
                m_mainForm.lvJongInfo.Items[6].ForeColor = Color.Blue;
                m_mainForm.lvDaily.Items[0].SubItems[9].ForeColor = Color.Blue;
            }
            else
            {
                m_mainForm.lvJongInfo.Items[6].ForeColor = Color.Black;
                m_mainForm.lvDaily.Items[0].SubItems[9].ForeColor = Color.Black;
            }

            if (bAuto)
            {
                int nRowCnt = m_mainForm.lvConTick.Items.Count;
                if (19 < nRowCnt)
                    m_mainForm.lvConTick.Items.RemoveAt(nRowCnt - 1);

                ListViewItem item = new ListViewItem();
                item.UseItemStyleForSubItems = false;
                item.SubItems.Add(m_iYuantaAPI.YOA_GetFieldString("time2", 0));
                item.SubItems.Add(m_mainForm.Commify(m_iYuantaAPI.YOA_GetFieldString("curjuka", 0)));

                item.SubItems.Add(m_mainForm.Commify(m_iYuantaAPI.YOA_GetFieldString("nowvol", 0)));
                char szColor = (char)m_iYuantaAPI.YOA_GetTRFieldAttr("11", "OutBlock1", "nowvol", 0);
                if ('S' == szColor)
                    item.SubItems[3].ForeColor = Color.Red;
                else if ('B' == szColor)
                    item.SubItems[3].ForeColor = Color.Blue;
                else
                    item.SubItems[3].ForeColor = Color.Black;

                m_mainForm.lvConTick.Items.Insert(0, item);
            }
            else
            {
                m_nPrevLastPrice = m_iYuantaAPI.YOA_GetFieldLong("prevlastjuka", 0);
                m_mainForm.lvJongInfo.Items[7].SubItems[1].Text = m_mainForm.Commify(m_nPrevLastPrice);
            }
        }

        private void Process300002_Auto12(bool bAuto)
        {
            int nValue      = 0;
            double dRate    = 0.0;

            int nDataCount = 0;

            if (bAuto)
            {
                m_iYuantaAPI.YOA_SetTRInfo("12", "OutBlock2");
                nDataCount = m_iYuantaAPI.YOA_GetRowCount("12", "OutBlock2");
            }
            else
            {
                m_iYuantaAPI.YOA_SetTRInfo("300002", "OutBlock1");
                nDataCount = m_iYuantaAPI.YOA_GetRowCount("300002", "OutBlock1");
            }   

            int nMedoTot        = 0;
            int nMesuTot        = 0;
            int nMedoDebiTot    = 0;
            int nMesuDebiTot    = 0;
            
            for (int i = 0; i < nDataCount; i++)
            {
                nValue = m_iYuantaAPI.YOA_GetFieldLong("medohoka", i);

                if (0 != nValue)
                {
                    if (bAuto)
                    {
                        nMedoDebiTot += m_iYuantaAPI.YOA_GetFieldLong("medodebi", i);
                        m_mainForm.lvMedoHoga.Items[9 - i].SubItems[1].Text = "0";
                    }
                    else
                    {
                        m_mainForm.lvMedoHoga.Items[9 - i].SubItems[1].Text = "0";
                    }

                    nMedoTot += m_iYuantaAPI.YOA_GetFieldLong("medovol", i);
                    m_mainForm.lvMedoHoga.Items[9 - i].SubItems[2].Text = m_iYuantaAPI.YOA_GetFieldString("medovol", i);

                    if (m_nPrevLastPrice < nValue)
                    {
                        m_mainForm.lvMedoHoga.Items[9 - i].SubItems[3].ForeColor = Color.Red;
                        m_mainForm.lvMedoHoga.Items[9 - i].SubItems[4].ForeColor = Color.Red;
                    }
                    else if (m_nPrevLastPrice > nValue)
                    {
                        m_mainForm.lvMedoHoga.Items[9 - i].SubItems[3].ForeColor = Color.Blue;
                        m_mainForm.lvMedoHoga.Items[9 - i].SubItems[4].ForeColor = Color.Blue;
                    }
                    else
                    {
                        m_mainForm.lvMedoHoga.Items[9 - i].SubItems[3].ForeColor = Color.Black;
                        m_mainForm.lvMedoHoga.Items[9 - i].SubItems[4].ForeColor = Color.Black;
                    }
                    m_mainForm.lvMedoHoga.Items[9 - i].SubItems[3].Text = m_mainForm.Commify(Convert.ToString(nValue));
                    dRate = ((double)nValue / (double)m_nPrevLastPrice - 1) * 100;
                    m_mainForm.lvMedoHoga.Items[9 - i].SubItems[4].Text = string.Format("{0:0.00}", dRate);
                }
                else
                {
                    m_mainForm.lvMedoHoga.Items[9 - i].SubItems[1].Text = "";
                    m_mainForm.lvMedoHoga.Items[9 - i].SubItems[2].Text = "";
                    m_mainForm.lvMedoHoga.Items[9 - i].SubItems[3].Text = "";
                    m_mainForm.lvMedoHoga.Items[9 - i].SubItems[4].Text = "";
                }

                nValue = m_iYuantaAPI.YOA_GetFieldLong("mesuhoka", i);

                if (0 != nValue)
                {
                    if (m_nPrevLastPrice < nValue)
                    {
                        m_mainForm.lvMesuHoga.Items[i].SubItems[3].ForeColor = Color.Red;
                        m_mainForm.lvMesuHoga.Items[i].SubItems[4].ForeColor = Color.Red;
                    }
                    else if (m_nPrevLastPrice > nValue)
                    {
                        m_mainForm.lvMesuHoga.Items[i].SubItems[3].ForeColor = Color.Blue;
                        m_mainForm.lvMesuHoga.Items[i].SubItems[4].ForeColor = Color.Blue;
                    }
                    else
                    {
                        m_mainForm.lvMesuHoga.Items[i].SubItems[3].ForeColor = Color.Black;
                        m_mainForm.lvMesuHoga.Items[i].SubItems[4].ForeColor = Color.Black;
                    }
                    m_mainForm.lvMesuHoga.Items[i].SubItems[3].Text = m_mainForm.Commify(Convert.ToString(nValue));
                    dRate = ((double)nValue / (double)m_nPrevLastPrice - 1) * 100;
                    m_mainForm.lvMesuHoga.Items[i].SubItems[4].Text = string.Format("{0:0.00}", dRate);

                    nMesuTot += m_iYuantaAPI.YOA_GetFieldLong("mesuvol", i);
                    m_mainForm.lvMesuHoga.Items[i].SubItems[5].Text = m_iYuantaAPI.YOA_GetFieldString("mesuvol", i);

                    if (bAuto)
                    {
                        nMesuDebiTot += m_iYuantaAPI.YOA_GetFieldLong("mesudebi", i);
                        m_mainForm.lvMedoHoga.Items[i].SubItems[6].Text = "0";
                    }
                    else
                    {
                        m_mainForm.lvMedoHoga.Items[i].SubItems[6].Text = "0";
                    }
                }
                else
                {
                    m_mainForm.lvMesuHoga.Items[i].SubItems[3].Text = "";
                    m_mainForm.lvMesuHoga.Items[i].SubItems[4].Text = "";
                    m_mainForm.lvMesuHoga.Items[i].SubItems[5].Text = "";
                    m_mainForm.lvMesuHoga.Items[i].SubItems[6].Text = "";
                }
            }

            int nTot = nMesuTot - nMedoTot;
            m_mainForm.lvHogaFooter.Items[0].SubItems[1].Text = m_mainForm.Commify(nMedoDebiTot);
            m_mainForm.lvHogaFooter.Items[0].SubItems[2].Text = m_mainForm.Commify(nMedoTot);
            m_mainForm.lvHogaFooter.Items[0].SubItems[3].Text = m_mainForm.Commify(nTot);
            m_mainForm.lvHogaFooter.Items[0].SubItems[4].Text = m_mainForm.Commify(nMesuTot);
            m_mainForm.lvHogaFooter.Items[0].SubItems[5].Text = m_mainForm.Commify(nMesuDebiTot);

            m_mainForm.lvHogaFooter.Items[0].SubItems[2].ForeColor = Color.Blue;
            m_mainForm.lvHogaFooter.Items[0].SubItems[4].ForeColor = Color.Red;

            if (0 < nTot)
            {
                m_mainForm.lvHogaFooter.Items[0].SubItems[3].ForeColor = Color.Red;
            }
            else if (0 < nTot)
            {
                m_mainForm.lvHogaFooter.Items[0].SubItems[3].ForeColor = Color.Blue;
            }
            else
            {
                m_mainForm.lvHogaFooter.Items[0].SubItems[3].ForeColor = Color.Black;
            }

            if (!bAuto)
            {
                ListViewItem item = null;
                char attr;

                m_mainForm.lvConTick.BeginUpdate();

                m_iYuantaAPI.YOA_SetTRInfo("300002", "OutBlock5");
                nDataCount = m_iYuantaAPI.YOA_GetRowCount("300002", "OutBlock5");
                for (int i = 0; i < nDataCount; i++)
                {
                    item = new ListViewItem();
                    item.UseItemStyleForSubItems = false;
                    item.SubItems.Add(m_iYuantaAPI.YOA_GetFieldString("time", i));
                    item.SubItems.Add(m_mainForm.Commify(m_iYuantaAPI.YOA_GetFieldString("curjuka", i)));

                    item.SubItems.Add(m_mainForm.Commify(m_iYuantaAPI.YOA_GetFieldString("nowvol", i)));
                    attr = (char)m_iYuantaAPI.YOA_GetTRFieldAttr("300002", "OutBlock5", "nowvol", i);
                    if ('S' == attr)
                        item.SubItems[3].ForeColor = Color.Red;
                    else if ('B' == attr)
                        item.SubItems[3].ForeColor = Color.Blue;
                    else
                        item.SubItems[3].ForeColor = Color.Black;

                    m_mainForm.lvConTick.Items.Add(item);
                }

                m_mainForm.lvConTick.EndUpdate();

                RegistAuto();
            }
        }

        private void Process301004()
        {
            int nNext = m_iYuantaAPI.YOA_GetTRFieldByte("301004", "OutBlock1", "next", 0);
            if (1 == nNext)
            {
                m_mainForm.btnNextSearch.Enabled = true;
            }
            else
            {
                m_mainForm.btnNextSearch.Enabled = false;
            }

            string strValue = "";
            int nDebi = 0;
            int nColor = 0;
            double dValue = 0.0;
            ListViewItem item = null;

            m_iYuantaAPI.YOA_SetTRInfo("301004", "OutBlock2");
            int nDataCount = m_iYuantaAPI.YOA_GetRowCount("301004", "OutBlock2");
            for (int i = 0; i < nDataCount; i++)
            {
                item = new ListViewItem();
                item.UseItemStyleForSubItems = false;

                strValue = m_iYuantaAPI.YOA_GetFieldString("date", i);
                strValue = strValue.TrimStart();
                item.SubItems.Add(strValue);
                item.SubItems.Add(m_mainForm.Commify(m_iYuantaAPI.YOA_GetFieldString("lastjuka", i)));

                nDebi = m_iYuantaAPI.YOA_GetFieldLong("debi", i);
                if (0 < nDebi)
                {
                    item.SubItems.Add("▲");
                }
                else if (0 > nDebi)
                {
                    item.SubItems.Add("▼");
                }
                item.SubItems.Add(m_mainForm.Commify(nDebi));
                
                dValue = m_iYuantaAPI.YOA_GetFieldDouble("debirate", i);
                if (0.0 < dValue)
                {
                    item.SubItems.Add("+" + string.Format("{0:0.00}", dValue));
                }
                else if (0.0 > dValue)
                {
                    item.SubItems.Add(string.Format("{0:0.00}", dValue));
                }

                nColor = m_iYuantaAPI.YOA_GetTRFieldAttr("301004", "OutBlock2", "debi", i);
                if (2 == nColor)
                {
                    item.SubItems[2].ForeColor = Color.Red;
                    item.SubItems[3].ForeColor = Color.Red;
                    item.SubItems[4].ForeColor = Color.Red;
                    item.SubItems[5].ForeColor = Color.Red;
                }
                else if (5 == nColor)
                {
                    item.SubItems[2].ForeColor = Color.Blue;
                    item.SubItems[3].ForeColor = Color.Blue;
                    item.SubItems[4].ForeColor = Color.Blue;
                    item.SubItems[5].ForeColor = Color.Blue;
                }
                else
                {
                    item.SubItems[2].ForeColor = Color.Black;
                    item.SubItems[3].ForeColor = Color.Black;
                    item.SubItems[4].ForeColor = Color.Black;
                    item.SubItems[5].ForeColor = Color.Black;
                }

                item.SubItems.Add(m_mainForm.Commify(m_iYuantaAPI.YOA_GetFieldLong("volume", i)));
                item.SubItems.Add(m_mainForm.Commify(m_iYuantaAPI.YOA_GetFieldString("startjuka", i)));
                item.SubItems.Add(m_mainForm.Commify(m_iYuantaAPI.YOA_GetFieldString("highjuka", i)));
                item.SubItems.Add(m_mainForm.Commify(m_iYuantaAPI.YOA_GetFieldString("lowjuka", i)));
                
                m_mainForm.lvDaily.Items.Add(item);
            }

        }

        private void ProcessAuto11()
        {
            
        }

        public void ReceiveError(int nReqID, int nErrCode, string strErrMsg)
        {
            string strTRID = m_mapRequestTR[nReqID];
            string strName = "";
            if (strTRID.Equals("300001"))
            {
                strName = "[300001]주식현재가";
            }
            else if (strTRID.Equals("300002"))
            {
                strName = "[300002]주식현재가_호가체결";
            }
            else if (strTRID.Equals("301004"))
            {
                strName = "[301004]수정일자별주가";
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
            else if (strTRID.Equals("300002"))
            {
                strName = "[300002]주식현재가_호가체결";
                Process300002_Auto12(false);
            }
            else if (strTRID.Equals("301004"))
            {
                strName = "[301004]수정일자별주가";
                Process301004();
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
                else if (strAutoID.Equals("12"))
                {
                    Process300002_Auto12(true);
                }
            }
        }
    }
}
