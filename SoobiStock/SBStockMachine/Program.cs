using SoobiStock;
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
            sstrader.InitTrades();
            sstrader.UninitTrades();
        }
    }
}
