#include <iostream>
#include <vector>
#include <set>
#include <string>
using namespace std;

int LCSLength(const string &X, const string &Y, vector<vector<int>> &dp) {
    int m = X.size();
    int n = Y.size();
    
    dp.resize(m + 1, vector<int>(n + 1, 0));

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (X[i - 1] == Y[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    return dp[m][n];
}

void printAllLCS(int i, int j, const string &X, const string &Y, const vector<vector<int>> &dp, string currentLCS, set<string> &allLCS) {
    if (i == 0 || j == 0) {
        allLCS.insert(currentLCS);  
        return;
    }

    if (X[i - 1] == Y[j - 1]) {
        currentLCS = X[i - 1] + currentLCS;  
        printAllLCS(i - 1, j - 1, X, Y, dp, currentLCS, allLCS);
    }
    else {
        if (dp[i - 1][j] == dp[i][j]) {
            printAllLCS(i - 1, j, X, Y, dp, currentLCS, allLCS);
        }
        if (dp[i][j - 1] == dp[i][j]) {
            printAllLCS(i, j - 1, X, Y, dp, currentLCS, allLCS);
        }
    }
}

int main() {
    string X = "ABCBDAB";
    string Y = "BDCAB";

    vector<vector<int>> dp;
    int lcsLength = LCSLength(X, Y, dp);

    cout << "longest length is: " << lcsLength << endl;

    set<string> allLCS;

    string currentLCS = "";
    printAllLCS(X.size(), Y.size(), X, Y, dp, currentLCS, allLCS);

    cout << "all is:" << endl;
    for (const auto &lcs : allLCS) {
        cout << lcs << endl;
    }

    return 0;
}
