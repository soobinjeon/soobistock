using SoobiStock.DataInfo;
using SoobiStock.login;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices.ComTypes;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using YuantaCOMLib;
namespace SoobiStock.Yuanta
{
    public class SYuanta : ATraders, IYuantaAPIEvents
    {
        IYuantaAPI yapi;
        
        //for Login
        bool isLogined = false;
        const int sysInit = -10000;
        int SystemReceivedID = sysInit;
        int LoginReceivedID = sysInit;
        Dictionary<int, string> ReqManager;

        public SYuanta(LoginIO lio)
            : base(TraderList.YUANTA, lio)
        {
            IConnectionPoint icp;
            IConnectionPointContainer icpc;
            int dwCookie = 0;
            yapi = new YuantaAPI();
            icpc = (IConnectionPointContainer)yapi;
            Guid IID_QueryEvents = typeof(IYuantaAPIEvents).GUID;
            icpc.FindConnectionPoint(ref IID_QueryEvents, out icp);
            icp.Advise(this, out dwCookie);

            ReqManager = new Dictionary<int, string>();
        }

        public void Login(int nResult, string bstrMsg)
        {
            LoginReceivedID = nResult;
            if (CommDef.RESPONSE_LOGIN_SUCCESS == nResult)
            {
                logs.LOG_MESSAGE(LogMessage.SYSTEM_MESSAGE, "Login Success", nResult);
            }
            else
            {
                logs.LOG_MESSAGE(LogMessage.SYSTEM_MESSAGE, "Login Fail", nResult);
            }

            //throw new NotImplementedException();
        }

        public void ReceiveError(int nReqID, int nErrCode, string bstrErrMsg)
        {
            if (nErrCode == CommDef.ERROR_TIMEOUT_DATA)
            {
                logs.LOG_MESSAGE(LogMessage.SYSTEM_MESSAGE, "TimeOut - [301020]No Response", nErrCode);
            }
            else if (nErrCode == CommDef.ERROR_REQUEST_FAIL)
            {
                string errmsg = yapi.YOA_GetErrorMessage(nReqID);
                logs.LOG_MESSAGE(LogMessage.SYSTEM_MESSAGE, errmsg, nErrCode);
            }

            //throw new NotImplementedException();
        }

        public void ReceiveData(int nReqID, string bstrDSOID)
        {
            throw new NotImplementedException();
        }

        public void ReceiveRealData(int nReqID, string bstrAutoID)
        {
            string jcode;
            //logs.LOG_MESSAGE(LogMessage.TRADER_MESSAGE, "Get realtime messages", nReqID);
            if(ReqManager.TryGetValue(nReqID, out jcode))
            {
                getAutoStock(nReqID);
            }
        }

        public void ReceiveSystemMessage(int nID, string bstrMsg)
        {
            SystemReceivedID = nID;
            logs.LOG_MESSAGE(LogMessage.SYSTEM_MESSAGE, bstrMsg, SystemReceivedID);

            if (CommDef.NOTIFY_SYSTEM_NEED_TO_RESTART == nID)
                yapi.YOA_ReStart();

            //throw new NotImplementedException();
        }

        public override void Traderinit()
        {
            int result = yapi.YOA_Initial(ServerList.Interal_Simulation, "");
            if (1000 == result)
            {
                logs.LOG_MESSAGE(LogMessage.TRADER_MESSAGE, "Server init completed");
            }
            else
            {
                logs.LOG_MESSAGE(LogMessage.TRADER_MESSAGE, "Server init failed", result);
            }
        }

        public override void TraderUnInit()
        {
            try
            {
                if(1000 == yapi.YOA_UnInitial())
                {
                    logs.LOG_MESSAGE(LogMessage.TRADER_MESSAGE, "Server Unitialized Completed");
                }
                else
                {
                    logs.LOG_MESSAGE(LogMessage.TRADER_MESSAGE, "Server Unitialized Fail");
                }
            }catch(Exception e)
            {

            }
        }

        public override void TraderLogin()
        {
            int nResult = yapi.YOA_Login(linfo.userid, linfo.passwd, linfo.cert);
            bool SysReceivedLogin = false;
            bool LoginRecevied = false;
            bool LoginSuccess = false;
            if(CommDef.RESULT_SUCCESS == nResult)
            {
                logs.LOG_MESSAGE(LogMessage.TRADER_MESSAGE, "Login Started", nResult);
                
            }
            else
            {
                string failres = yapi.YOA_GetErrorMessage(nResult);
                logs.LOG_MESSAGE(LogMessage.SYSTEM_MESSAGE, failres, nResult);
            }

            if (SystemReceivedID != sysInit)
                SystemReceivedID = sysInit;

            if (LoginReceivedID != sysInit)
                LoginReceivedID = sysInit;

            while (true)
            {
                if (SystemReceivedID == CommDef.NOTIFY_SYSTEM_LOGIN_FILE_DWN_END)
                {
                    SysReceivedLogin = true;
                }

                if(LoginReceivedID == CommDef.RESPONSE_LOGIN_SUCCESS)
                {
                    LoginRecevied = true;
                }

                if (SysReceivedLogin && LoginRecevied)
                {
                    LoginSuccess = true;
                    break;
                }
                Thread.Sleep(500);
            }

            if (LoginSuccess)
            {
                isLogined = true;
                logs.LOG_MESSAGE(LogMessage.TRADER_MESSAGE, "Login Completed", nResult);
            }
        }

        public override bool isLoggined()
        {
            return this.isLogined;
        }

        public override int getCodeCount()
        {
            if (!isLogined)
                return -1;

            int result = yapi.YOA_GetCodeCount(CommDef.MARKET_TYPE_INTERNAL_STOCK);
            return result;
        }

        public override int getAccountCount()
        {
            if (!isLogined)
                return -1;

            int cnt = yapi.YOA_GetAccountCount();
            return cnt;
        }

        public override List<Account> getAccountInfo()
        {
            if (!isLogined)
                return null;

            List<Account> accounts = new List<Account>();
            int nCount = getAccountCount();
            for(int i = 0; i < nCount; i++)
            {
                string accid = yapi.YOA_GetAccount(i);
                string accname = yapi.YOA_GetAccountInfo(CommDef.ACCOUNT_INFO_NAME, accid);
                string accnick = yapi.YOA_GetAccountInfo(CommDef.ACCOUNT_INFO_NICKNAME, accid);
                string acctype = yapi.YOA_GetAccountInfo(CommDef.ACCOUNT_INFO_TYPE, accid);
                accounts.Add(new Account(accid, accname, accnick, acctype));
            }
            return accounts;
        }

        public override Code getCodeInfobyCodeID(string cid)
        {
            if (!isLogined)
                return null;

            string stdcode = yapi.YOA_GetCodeInfo(CommDef.MARKET_TYPE_INTERNAL_STOCK, CommDef.CODE_INFO_STANDARD_CODE, cid);
            string name = yapi.YOA_GetCodeInfo(CommDef.MARKET_TYPE_INTERNAL_STOCK, CommDef.CODE_INFO_NAME, cid);
            name = RecheckCodeName(cid, name);
            string ename = yapi.YOA_GetCodeInfo(CommDef.MARKET_TYPE_INTERNAL_STOCK, CommDef.CODE_INFO_ENG_NAME, cid);
            string mtype = yapi.YOA_GetCodeInfo(CommDef.MARKET_TYPE_INTERNAL_STOCK, CommDef.CODE_INFO_JANG_GUBUN, cid);

            return new Code(cid, stdcode, name, ename, mtype);
        }

        public override Code getCodeInfobyIndex(int idx)
        {
            if (!isLogined)
                return null;

            string cid = yapi.YOA_GetCodeInfoByIndex(CommDef.MARKET_TYPE_INTERNAL_STOCK, CommDef.CODE_INFO_CODE, idx);
            string stdcode = yapi.YOA_GetCodeInfoByIndex(CommDef.MARKET_TYPE_INTERNAL_STOCK, CommDef.CODE_INFO_STANDARD_CODE, idx);
            string name = yapi.YOA_GetCodeInfoByIndex(CommDef.MARKET_TYPE_INTERNAL_STOCK, CommDef.CODE_INFO_NAME, idx);
            name = RecheckCodeName(cid, name);
            string ename = yapi.YOA_GetCodeInfoByIndex(CommDef.MARKET_TYPE_INTERNAL_STOCK, CommDef.CODE_INFO_ENG_NAME, idx);
            string mtype = yapi.YOA_GetCodeInfoByIndex(CommDef.MARKET_TYPE_INTERNAL_STOCK, CommDef.CODE_INFO_JANG_GUBUN, idx);

            return new Code(cid, stdcode, name, ename, mtype);
        }

        public override void RequestAuto(string cid)
        {
            yapi.YOA_SetTRFieldString("12", "InBlock1", "jongcode", cid, 0);
            int nReqID = yapi.YOA_RegistAuto("12");

            if(CommDef.ERROR_MAX_CODE < nReqID)
            {
                ReqManager.Add(nReqID, "12");
                logs.LOG_MESSAGE(LogMessage.TRADER_MESSAGE, "[12] Realtime submitted - " + cid);
            }
            else
            {
                logs.LOG_MESSAGE(LogMessage.TRADER_MESSAGE, yapi.YOA_GetErrorMessage(nReqID));
            }
        }

        private void getAutoStock(int reqid)
        {
            StockPrice sp = new StockPrice();
            yapi.YOA_SetTRInfo("12", "OutBlock1");          // TR정보(TR명, Block명)를 설정합니다.
            string code = yapi.YOA_GetFieldString("jongcode", 0);       // 종목코드 값을 가져옵합니다.
            long medo = yapi.YOA_GetFieldLong("medohoka", 0);       // 매도호가 값을 가져옵합니다.
            long mesu = yapi.YOA_GetFieldLong("mesuhoka", 0);       // 매수호가 값을 가져옵합니다.
            long vol = yapi.YOA_GetFieldLong("volume", 0);     // 누적거래량_주단위 값을 가져옵합니다.
            /*yapi.YOA_GetFieldString("sisegubun", 0);      // 시세급변 값을 가져옵합니다.
            yapi.YOA_GetFieldString("updowngubun", 0);        // 상하한가근접구분 값을 가져옵합니다.
            sp.CurrentPrice = yapi.YOA_GetFieldLong("curjuka", 0);        // 현재가 값을 가져옵합니다.
            sp.StartPrice = yapi.YOA_GetFieldLong("startjuka", 0);      // 시가 값을 가져옵합니다.
            sp.HighPrice = yapi.YOA_GetFieldLong("highjuka", 0);       // 고가 값을 가져옵합니다.
            sp.LowPrice = yapi.YOA_GetFieldLong("lowjuka", 0);        // 저가 값을 가져옵합니다.
            yapi.YOA_GetFieldString("filler1", 0);        // 4bytes맞추기위해 값을 가져옵합니다.
            yapi.YOA_GetFieldString("money", 0);      // 누적거래대금_천단위 값을 가져옵합니다.
            yapi.YOA_GetFieldString("debirate", 0);       // 등락률 값을 가져옵합니다.
            yapi.YOA_GetFieldString("time", 0);       // 시간_HH:SS 값을 가져옵합니다.
            yapi.YOA_GetFieldString("hightime", 0);       // 고가시간 값을 가져옵합니다.
            yapi.YOA_GetFieldString("lowtime", 0);        // 저가시간 값을 가져옵합니다.
            yapi.YOA_GetFieldString("debi", 0);       // 전일대비 값을 가져옵합니다.
            yapi.YOA_GetFieldString("nowvol", 0);     // 직전체결량 값을 가져옵합니다.
            yapi.YOA_GetFieldString("sisesec", 0);        // 시세급변_초 값을 가져옵합니다.
            yapi.YOA_GetFieldString("siserate", 0);       // 시세급변_등락률 값을 가져옵합니다.
            yapi.YOA_GetFieldString("nowmoney", 0);       // 직전거래대금 값을 가져옵합니다.
            yapi.YOA_GetFieldString("chejuka", 0);        // 체결가 값을 가져옵합니다.
            yapi.YOA_GetFieldString("chedebi", 0);        // 체결가전일대비 값을 가져옵합니다.
            yapi.YOA_GetFieldString("jang", 0);       // 장구분 값을 가져옵합니다.
            yapi.YOA_GetFieldString("updownflag", 0);     // 상한가근접_구분값 값을 가져옵합니다.
            yapi.YOA_GetFieldString("filler2", 0);        // 4bytes맞추기위해 값을 가져옵합니다.
            yapi.YOA_GetFieldString("time2", 0);      // 시간2 값을 가져옵합니다.
            yapi.YOA_GetFieldString("chegyulrate", 0);        // 체결강도 값을 가져옵합니다.
            yapi.YOA_GetFieldString("mesusumvolume", 0);      // 매수체결합 값을 가져옵합니다.
            yapi.YOA_GetFieldString("medosumvolume", 0);      // 매도체결합 값을 가져옵합니다.
            yapi.YOA_GetFieldString("upjuka", 0);     // 상한가 값을 가져옵합니다.
            yapi.YOA_GetFieldString("downjuka", 0);       // 하한가 값을 가져옵합니다.
            yapi.YOA_GetFieldString("filler3", 0);        // 4bytes맞추기위해 값을 가져옵합니다.
            yapi.YOA_GetFieldString("befminvol", 0);      // 전일동시간거래량 값을 가져옵합니다.
            yapi.YOA_GetFieldString("befmindebi", 0);     // 전일동시간대비 값을 가져옵합니다.
            yapi.YOA_GetFieldString("startdebirate", 0);      // 시가등략율 값을 가져옵합니다.
            yapi.YOA_GetFieldString("highdebirate", 0);       // 고가등략율 값을 가져옵합니다.
            yapi.YOA_GetFieldString("lowdebirate", 0);		// 저가등략율 값을 가져옵합니다.
            */
            //string str = "Code: " + code + ", CurPrice: " + sp.CurrentPrice + ", StPrice :" + sp.StartPrice + ", HP : " + sp.HighPrice + ", LP : " + sp.LowPrice;

            string str = "Code: " + code + ", Medo: " + medo + ", Mesu: " + mesu + ", Vol: " + vol;
            logs.LOG_MESSAGE(LogMessage.TRADER_MESSAGE, str);
        }

        private string RecheckCodeName(string cid, string name)
        {
            if(cid.Equals("520020"))
            {
                return name + "(H)";
            }
            else
            {
                return name;
            }
        }

        public override void close()
        {
            yapi.YOA_UnRegistAllAuto();
        }
    }
}
