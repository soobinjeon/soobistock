using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SoobiStock.Yuanta
{
    interface ITraders
    {
        void Traderinit();
        void TraderUnInit();
        void TraderLogin();
        bool isLoggined();
    }
}
