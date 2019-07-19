﻿using SoobiStock.DataInfo;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SoobiStock
{
    public abstract class ATraders
    {
        protected LogMessage logs;
        protected TraderList traderCate;
        public ATraders(TraderList tr)
        {
            this.traderCate = tr;
            logs = new LogMessage(tr);
        }

        public abstract void Traderinit();
        public abstract void TraderUnInit();
        public abstract void TraderLogin();
        public abstract bool isLoggined();
        public abstract int getAccountCount();
        public abstract List<Account> getAccountInfo();
        public abstract int getCodeCount();
        public abstract Code getCodeInfobyCodeID(string cid);
        public abstract Code getCodeInfobyIndex(int idx);

        public Dictionary<string, Code> getAllCodes()
        {
            Dictionary<string, Code> allcodes = new Dictionary<string, Code>();

            int ccnt = getCodeCount();
            for(int i = 0; i < ccnt; i++)
            {
                Code ncode = getCodeInfobyIndex(i);
                Code tcode;
                if(false == allcodes.TryGetValue(ncode.Name, out tcode))
                {
                    allcodes.Add(ncode.CodeID, ncode);
                }
                else
                {
                    logs.LOG_MESSAGE(LogMessage.TRADER_MESSAGE, "Code is already allocated - " + ncode.Name);
                }
            }

            return allcodes;
        }
    }
}
