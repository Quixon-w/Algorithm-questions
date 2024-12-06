#include <iostream>
#include <vector>
using namespace std;

int maxProfit(vector<int>& prices) {
    int n = prices.size();
    if (n < 2) return 0;

    // dp[i][0] 表示第 i 天结束时未持有股票的最大利润
    // dp[i][1] 表示第 i 天结束时持有股票的最大利润
    vector<vector<int>> dp(n, vector<int>(2, 0));
    
    dp[0][0] = 0;            // 第一天未持有股票，利润为 0
    dp[0][1] = -prices[0];   

    for (int i = 1; i < n; ++i) {
        dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] + prices[i]);
        dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] - prices[i]); 
    }

    return dp[n - 1][0]; 
}

int main() {
    vector<int> prices = {7, 1, 5, 3, 6, 4};
    cout << maxProfit(prices) << endl; 
    return 0;
}
