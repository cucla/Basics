/* I. Maximum profit earned for 1 transaction
If you were only permitted to complete at most one transaction (i.e., buy one and sell one share of the stock), 
design an algorithm to find the maximum profit.
Note that you cannot sell a stock before you buy one.
 */

int maxProfit(vector<int>& prices) {
	int maxprofit = 0;
	int minPrice = INT_MAX;

	for(int i = 0; i < prices.size(); i++){
	    minPrice = min(minPrice, prices[i]);
	    maxprofit = max(maxprofit, prices[i] - minPrice);
	}
	return maxprofit;
}

/* II. Maximum profit earned for any number of transactions
Design an algorithm to find the maximum profit. You may complete as many transactions as you like 
(i.e., buy one and sell one share of the stock multiple times).
Note: You may not engage in multiple transactions at the same time (i.e., you must sell 
the stock before you buy again). */
    
int maxProfit(vector<int> & prices) {
	int maxprofit = 0;
	for (int i = 1; i < prices.size(); i++) {
	    if (prices[i] > prices[i - 1])
		maxprofit += prices[i] - prices[i - 1];
	}
	return maxprofit;
}
    
/* III. Maximum profit earned for at most K transactions
Note: You may not engage in multiple transactions at the same time (i.e., you must sell 
the stock before you buy again). */

