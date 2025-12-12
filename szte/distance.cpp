#include <string>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    string a, b;

    if (!(cin >> a)) return 0;
    if (!(cin >> b)) return 0;

    int n = (int)a.size();
    int m = (int)b.size();

    vector<vector<int>> dp(n+1, vector<int>(m+1, 0));

    for (int i = 0; i <= n; ++i)
        dp[i][0] = i;

    for (int j = 0; j <= m; ++j)
        dp[0][j] = j;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            int cost = (a[i-1] == b[j-1]) ? 0 : 1;

            dp[i][j] = min({
                dp[i-1][j] + 1,
                dp[i][j-1] + 1,
                dp[i-1][j-1] + cost
            });
        }
    }

    cout << dp[n][m] << '\n';
    return 0;
}
