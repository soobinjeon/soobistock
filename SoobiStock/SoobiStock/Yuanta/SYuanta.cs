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
    public class SYuanta : IYuantaAPIEvents, ITraders
    {
        IYuantaAPI yapi;
        string id = "";
        string pwd = "";
        string sign = "";
        bool isLogined = false;

        public SYuanta()
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

        public void Traderinit()
        {
            int result = yapi.YOA_Initial(ServerList.Interal_Simulation, "");
            if (1000 == result)
            {
                Console.WriteLine("Server init completed");
            }
            else
            {
                Console.WriteLine("Server init failed - ErroCode : " + result);
            }
        }

        public void TraderUnInit()
        {
            if(1000 == yapi.YOA_UnInitial())
            {
                Console.WriteLine("Server Unitialized Completed");
            }
            else
            {
                Console.WriteLine("Server Unitialized Fail");
            }
        }

        public void TraderLogin()
        {
            int nResult = yapi.YOA_Login(id, pwd, sign);

            if(1000 == nResult)
            {
                Console.WriteLine("Login Success - " + nResult);
                isLogined = true;
                Thread.Sleep(3000);
            }
            else
            {
                Console.WriteLine("Login Fail");

                if(104 == nResult)
                {
                    Console.WriteLine("Connection Fail (Time Out)");
                }
                else
                {
                    Console.WriteLine("Login FailCode - "+nResult);
                }
            }
        }

        public void Login(int nResult, string bstrMsg)
        {
            if(nResult != 1000)
            {
                Console.WriteLine("Response from Login - " + nResult);
                Console.WriteLine(bstrMsg);
                isLogined = false;
            }
        }

        public void ReceiveError(int nReqID, int nErrCode, string bstrErrMsg)
        {
            throw new NotImplementedException();
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
            throw new NotImplementedException();
        }

        public bool isLoggined()
        {
            return this.isLogined;
        }
    }
}
