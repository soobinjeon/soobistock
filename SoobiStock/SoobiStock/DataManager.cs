using SoobiStock.DataAnalysis;
using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SoobiStock
{
    public class DataManager
    {
        LogMessage logs = new LogMessage(TraderList.MAIN);
        ConcurrentDictionary<string, StockData> stockDatas;
        public DataManager()
        {
            stockDatas = new ConcurrentDictionary<string, StockData>();
        }
    }
}
