using SoobiStock;
using SoobiStock.DataInfo;
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
                sstrader.getCodebyName("삼성전자");

                Thread.Sleep(1000);

                sstrader.UninitTrades();
            }
        }
    }
}
