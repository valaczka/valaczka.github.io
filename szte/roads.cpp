using namespace std;

const int MAXN = 100000;

vector<int> adj[MAXN];
bool visited[MAXN];

void find(int u) {
    visited[u] = true;
    for (int v : adj[u]) {
        if (!visited[v])
            find(v);
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<int> reps;

    for (int i = 1; i <= n; ++i) {
        if (!visited[i]) {
            reps.push_back(i);
            find(i);
        }
    }

    int k = (int)reps.size() - 1;
    
    cout << k << "\n";

    for (int i = 0; i + 1 < (int)reps.size(); ++i)
        cout << reps[i] << " " << reps[i + 1] << "\n";


    return 0;
}
