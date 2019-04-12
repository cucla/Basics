/* I. Maximum profit earned for any number of transactions
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
    
/* II. Maximum profit earned for at most K transactions
Note: You may not engage in multiple transactions at the same time (i.e., you must sell 
the stock before you buy again). */

int maxProfit(vector<int> & prices, int k) {
	std::priority_queue<int, std::vector<int>, std::greater<int>> maxHeap;
	int maxprofit = 0;
	for (int i = 1; i < prices.size(); i++) {
		if (prices[i] > prices[i - 1])
			maxprofit += prices[i] - prices[i - 1];
		if ((prices[i] < prices[i - 1]) && maxprofit != 0) {
			maxHeap.push(maxprofit);
			maxprofit = 0;
		}
	}
	maxHeap.push(maxprofit); maxprofit = 0;
	for (int i = 0; i < k; i++) {
		if (!maxHeap.empty())
			maxprofit += maxHeap.top(); maxHeap.pop();
	}
	return maxprofit;
}
