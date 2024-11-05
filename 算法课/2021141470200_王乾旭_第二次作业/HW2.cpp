#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
#include <functional> 

using namespace std;

set<string> lcs_all(const string &X, const string &Y) {
    int m = X.size(), n = Y.size();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (X[i - 1] == Y[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    set<string> result;

    function<void(int, int, string)> backtrack = [&](int i, int j, string current) {
        if (i == 0 || j == 0) {
            reverse(current.begin(), current.end());
            result.insert(current);
            return;
        }

        if (X[i - 1] == Y[j - 1]) {
            backtrack(i - 1, j - 1, current + X[i - 1]);
        } else {
            if (dp[i - 1][j] == dp[i][j]) {
                backtrack(i - 1, j, current);
            }
            if (dp[i][j - 1] == dp[i][j]) {
                backtrack(i, j - 1, current);
            }
        }
    };
    backtrack(m, n, "");

    return result;
}

int main() {
    string X, Y;
    cout << "Please enter the first string X: ";
    cin >> X;
    cout << "Please enter the second string Y: ";
    cin >> Y;   

    

    set<string> lcs_list = lcs_all(X, Y);

    cout << "All longest common subsequences:";
    for (const auto &lcs : lcs_list) {
        cout << lcs << " ";
    }
    cout << endl;
    return 0;
}
