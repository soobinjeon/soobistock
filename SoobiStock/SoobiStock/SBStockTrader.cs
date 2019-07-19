using SoobiStock.DataInfo;
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
        Dictionary<TraderList, ATraders> traders = new Dictionary<TraderList, ATraders>();
        ATraders MainTrader;
        Dictionary<string, Code> Allcodes;

        LogMessage logs = new LogMessage(TraderList.MAIN);
        public SBStockTrader()
        {
            DefineTrader();
        }
        private void DefineTrader()
        {
            traders.Add(TraderList.YUANTA, new SYuanta());
        }
        public bool InitTrades()
        {
            //init traders
            foreach(ATraders it in traders.Values)
            {
                it.Traderinit();
                it.TraderLogin();
                //check login status
                if (it.isLoggined())
                {
                    if(MainTrader == null)
                        MainTrader = it;
                }
                else
                {
                }
            }

            if(MainTrader != null)
            {
                //Get Allcode from Main Trader
                Allcodes = MainTrader.getAllCodes();
                logs.LOG_MESSAGE(LogMessage.SBSTOCK_SYSTEM_MESSAGE, "Traders Init Completed");
                return true;
            }
            else
            {
                logs.LOG_MESSAGE(LogMessage.SBSTOCK_SYSTEM_MESSAGE, "Traders Init Failed");
                return false;
            }
        }

        public void UninitTrades()
        {
            foreach (ATraders it in traders.Values)
            {
                it.TraderUnInit();
            }
        }

        public List<TraderList> getTraderList()
        {
            return traders.Keys.ToList();
        }

        public ATraders getTraderbyTraderID(TraderList tl)
        {
            ATraders retrader = null;
            if(true == traders.TryGetValue(tl, out retrader))
            {
                return retrader;
            }
            else
            {
                return null;
            }
        }

        public ATraders getMainTrader()
        {
            return MainTrader;
        }

        public Dictionary<TraderList, List<Account>> getAccountLists()
        {
            Dictionary<TraderList, List<Account>> alists = new Dictionary<TraderList, List<Account>>();

            foreach(TraderList it in traders.Keys)
            {
                ATraders targetT;
                if(true == traders.TryGetValue(it, out targetT))
                {
                    alists.Add(it, targetT.getAccountInfo());
                }
            }

            return alists;
        }

        public List<Account> getAccountListByTrader(TraderList tl)
        {
            ATraders targetT;
            List<Account> ret = null;
            if (true == traders.TryGetValue(tl, out targetT))
            {
                ret = targetT.getAccountInfo();
            }

            return ret;
        }
        public int getCodeCount()
        {
            return MainTrader.getCodeCount();
        }

        public Code getCodebyName(string name)
        {
            List<Code> klist = Allcodes.Values.ToList();
            List<Code> searchedList = klist.FindAll(x => x.Name.Contains(name));

            if (searchedList.Count != 0)
                return searchedList[0];
            else
                return null;
        }

        public List<Code> getAllCodebyName(string name)
        {
            List<Code> klist = Allcodes.Values.ToList();
            List<Code> searchedList = klist.FindAll(x => x.Name.Contains(name));

            return searchedList;
        }
    }
}
