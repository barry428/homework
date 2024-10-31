#include <vector>
#include <iostream>
using namespace std;


void test_8_print_matrix(vector<vector<int> >& matrix, int n) {
    cout << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

void test_8_print_path(vector<int> &path){
    cout << "path: ";
    for (int i : path) {
        cout << i << " ";
    }
    cout << endl;
}

void test_8_backtrack(const std::vector<std::vector<int>>& matrix, int i, int j, int& sum, std::vector<int>& path, std::vector<int>& maxPath, int& maxPathSum) {
    // 如果到达底部行，则记录路径和并返回
    if (i == matrix.size() - 1) {
        // 判断当前路径和是否超过已知最大路径和
        if (sum > maxPathSum) {
            maxPathSum = sum;
            maxPath = path;
        }
        return;
    }

    // 遍历当前状态的所有可能选择（向下和右下）
    std::vector<std::pair<int, int>> directions = {{1, 0}, {1, 1}};
    for (const auto& [di, dj]: directions) {
        int next_i = i + di;
        int next_j = j + dj;

        // 判断约束条件：检查是否越界
        if (next_i < matrix.size() && next_j <= next_i) {
            // 做出选择
            path.push_back(matrix[next_i][next_j]);
            sum += matrix[next_i][next_j];

            // 递归探索：移动到下一个节点
            test_8_backtrack(matrix, next_i, next_j, sum, path, maxPath, maxPathSum);

            // 撤销选择
            path.pop_back();
            sum -= matrix[next_i][next_j];
        }
    }
}

int maximumPathSum(const std::vector<std::vector<int>>& matrix) {
    // dp[i][j] 是处在i,j位置是的最大路径和
    auto dp = matrix;

    // 从倒数第二行开始向上计算每个节点的最大路径和
    for (int i = matrix.size() - 2; i >= 0; --i) {
        for (int j = 0; j <= i; ++j) {
            dp[i][j] += std::max(dp[i + 1][j], dp[i + 1][j + 1]);
        }
    }

    // dp[0][0] 是从顶到底的最大路径和
    return dp[0][0];
}


int test_8() {

    int n;
    cin >> n;
    vector<vector<int> > matrix(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= i; ++j) {
            cin >> matrix[i][j];
        }
    }

    test_8_print_matrix(matrix, n);

    vector<int> path, maxPath;
    int sum = 0, maxSum = 0;

    // 从 -1 -1 开始，因为从0开始，没有上一步，所以-1 -1
    test_8_backtrack(matrix, -1, -1, sum, path, maxPath, maxSum);

    cout << "sum: " << maxSum << endl;
    test_8_print_path(maxPath);

    sum = maximumPathSum(matrix);
    cout << "sum: " << sum << endl;


    return 0;
}


/*

5
7
3 8
8 1 0
2 7 4 4
4 5 2 6 5

回溯法模板
void backtrack(状态) {
    if (满足结束条件) {
        记录解;
        return;
    }

    for (选择 in 当前状态的所有可能选择) {
        if (选择满足约束条件) {
            做出选择;
            backtrack(新的状态); // 递归探索下一步
            撤销选择;            // 回溯，尝试其他选择
        }
    }
}


动态规划模板：
dp[0][0] = ...; // 初始化
for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
        dp[i][j] = 状态转移方程;
    }
}
return dp[n][m];

*/