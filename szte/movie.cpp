#include <string>
#include <iostream>
#include <vector>
#include <set>

using namespace std;

int main() {
    int n, k;

    if (!(cin >> n >> k)) return 0;

    vector<pair<int,int>> movies(n);

    for (int i = 0; i < n; ++i) {
        int a, b; cin >> a >> b;
        movies[i] = {b, a};
    }

    sort(movies.begin(), movies.end());

    multiset<int> ends;
    long long ans = 0;

    for (auto [end, start] : movies) {
        auto it = ends.upper_bound(start);

        if (it == ends.begin()) {
            if ((int) ends.size() < k) {
                ends.insert(end);
                ++ans;
            }
        } else {
            --it;
            ends.erase(it);
            ends.insert(end);
            ++ans;
        }
    }

    cout << ans << "\n";
    
    return 0;
}
