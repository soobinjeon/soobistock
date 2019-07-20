using SoobiStock.DataInfo;
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
        string id = "";
        string pwd = "";
        string sign = "";

        //for Login
        bool isLogined = false;
        const int sysInit = -10000;
        int SystemReceivedID = sysInit;
        int LoginReceivedID = sysInit;

        public SYuanta()
            : base(TraderList.YUANTA)
        {
            IConnectionPoint icp;
            IConnectionPointContainer icpc;
            int dwCookie = 0;
            yapi = new YuantaAPI();
            icpc = (IConnectionPointContainer)yapi;
            Guid IID_QueryEvents = typeof(IYuantaAPIEvents).GUID;
            icpc.FindConnectionPoint(ref IID_QueryEvents, out icp);
            icp.Advise(this, out dwCookie);
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
            throw new NotImplementedException();
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
            int nResult = yapi.YOA_Login(id, pwd, sign);
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
    }
}
