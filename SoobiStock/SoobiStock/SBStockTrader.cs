using SoobiStock.Yuanta;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SoobiStock
{
    public class SBStockTrader
    {
        Dictionary<string, ITraders> traders = new Dictionary<string, ITraders>();

        public SBStockTrader()
        {
            DefineTrader();
        }
        private void DefineTrader()
        {
            traders.Add("Yuanta", new SYuanta());
        }
        public void InitTrades()
        {
            //init traders
            foreach(ITraders it in traders.Values)
            {
                it.Traderinit();
                it.TraderLogin();
                //check login status
                if (it.isLoggined())
                {
                    Console.WriteLine("Login Suc");
                }
                else
                {
                    Console.WriteLine("Login Fail");
                }
            }
        }

        public void UninitTrades()
        {
            foreach (ITraders it in traders.Values)
            {
                it.TraderUnInit();
            }
        }
    }
}
