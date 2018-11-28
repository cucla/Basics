        public static long makeChange(int[] coins, int money)
        {
            return makeChange(coins, money, 0, new Dictionary<string, long>());
        }

        public static long makeChange(int[] coins, int money, int index, Dictionary<string, long> memo)
        {
            if (money == 0) { return 1; }
            if (index >= coins.Count()) { return 0; }

            string key = money + "_" + index;
            if (memo.ContainsKey(key))
            {
                return memo[key];
            }

            int moneyWithCoin = 0;
            long ways = 0;
            while(moneyWithCoin <= money)
            {
                int remaining = money - moneyWithCoin;
                ways += makeChange(coins, remaining, index + 1, memo);
                moneyWithCoin += coins[index];
            }
            memo[key] = ways;
            return ways;
        }
        
