using SoobiStock;
using SoobiStock.DataInfo;
using SoobiStock.login;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace SBStockMachine
{
    class Program
    {
        static void Main(string[] args)
        {
            SBStockTrader sstrader = new SBStockTrader();
            if(true == sstrader.InitTrades())
            {
                List<Account> alist = sstrader.getAccountListByTrader(TraderList.YUANTA);
                foreach(Account acc in alist)
                {
                    Console.WriteLine("Account : {0}, {1}, {2}, {3}",acc.accountID, acc.accountName, acc.accountNickName, acc.accountType);
                }
                Console.WriteLine("");
                Console.WriteLine("List of Codes");
                Code c = sstrader.getCodebyName("삼성전자");
                Console.WriteLine(c.CodeID + ", " + c.Name + ", " + c.Market_Type);

                int i = 0;
                foreach(Code cd in sstrader.getAllCodes().Values)
                {
                    if (i > 20)
                        break;

                    sstrader.AddRealTimeStock(cd.CodeID);
                    i++;
                }
                /*sstrader.AddRealTimeStock(c.CodeID);
                sstrader.AddRealTimeStock("034220");
                sstrader.AddRealTimeStock("225570");*/
                string var = Console.ReadLine();
                sstrader.CloseAll();
                sstrader.UninitTrades();
            }
        }
        
    }
}
