#include <iostream>
#include <vector>
using namespace std;

bool canJump(vector<int>& nums) {
    int n = nums.size();
    vector<bool> dp(n, false); 
    dp[0] = true; 

    for (int i = 0; i < n; ++i) {
        if (!dp[i]) {
            break; 
        }
        for (int j = 1; j <= nums[i] && i + j < n; ++j) {
            dp[i + j] = true;
        }
    }

    return dp[n - 1]; 
}

int main() {
    vector<int> nums = {2, 3, 1, 1, 4};
    cout << (canJump(nums) ? "true" : "false") << endl;
    return 0;
}
