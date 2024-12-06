// 动态规划正确性论证
// 状态定义：
// 令 𝑦(𝑖,𝑗)表示从起点 (0,0)到位置 (𝑖,𝑗)的最小匹配距离。
// 状态转移方程：
// 根据约束条件，当前位置的最小距离可以从三个方向更新：
// 水平：从 (i,j−1) 水平过来，增加的代价是 d(i,j)。
// 垂直：从 (i−1,j) 垂直过来，增加的代价是 d(i,j)。
// 对角线：从 (i−1,j−1) 斜着过来，增加的代价是 2⋅d(i,j)。
// 所以状态转移公式为：
// y(i−1,j−1)+2⋅d(i,j),对角线过来
// y(i−1,j)+d(i,j),垂直过来
// y(i,j−1)+d(i,j),水平过来
// 初始状态：y(0,0)=0：
// 起点的距离为y(i,0) 和 y(0,j)
// 边界条件，根据从起点逐步延伸的代价计算。
// 最优子结构性质：
// 当前的最小距离依赖于前一步的最小距离。
// 每一步的选择（水平、垂直、对角线）可以独立决策且最优。
// 动态规划的核心思想可以应用于本问题。

#include <iostream>
#include <vector>
#include <climits>
#include <iomanip>
#include <algorithm>  
using namespace std;


#define M 5 
#define N 6 

int d[M][N] = {
    {5, 1, 6, 1, 5, 8},
    {2, 4, 3, 2, 4, 1},
    {4, 8, 2, 6, 2, 2},
    {6, 3, 4, 4, 5, 5},
    {2, 5, 6, 1, 4, 3}
};

void DTW() {
    vector<vector<int>> dp(M + 1, vector<int>(N + 1, INT_MAX));
    vector<vector<pair<int, int>>> path(M + 1, vector<pair<int, int>>(N + 1));

    dp[0][0] = 0;

    for (int i = 1; i <= M; ++i) {
        for (int j = 1; j <= N; ++j) {
            int horizontal = dp[i][j - 1] + d[i - 1][j - 1];   // 水平
            int vertical = dp[i - 1][j] + d[i - 1][j - 1];     // 垂直
            int diagonal = dp[i - 1][j - 1] + 2 * d[i - 1][j - 1];  // 对角线

            int min_cost = min({horizontal, vertical, diagonal});
            dp[i][j] = min_cost;

            // 记录
            if (min_cost == horizontal) {
                path[i][j] = {i, j - 1};
            } else if (min_cost == vertical) {
                path[i][j] = {i - 1, j};
            } else {
                path[i][j] = {i - 1, j - 1};
            }
        }
    }

    // 最短距离
    int shortest_distance = dp[M][N];
    cout << "min: " << shortest_distance << endl;

    // 追溯最短路径
    vector<pair<int, int>> shortest_path;
    int i = M, j = N;

    while (i > 0 || j > 0) {
        shortest_path.push_back({i, j});
        auto prev = path[i][j];
        i = prev.first;
        j = prev.second;
    }
    shortest_path.push_back({0, 0});

    cout << "min:" << endl;
    for (auto it = shortest_path.rbegin(); it != shortest_path.rend(); ++it) {
        cout << "(" << it->first << ", " << it->second << ")";
        if (next(it) != shortest_path.rend()) cout << " -> ";
    }
    cout << endl;
}

int main() {
    DTW();
    return 0;
}

