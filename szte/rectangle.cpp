#include <string>
#include <iostream>
#include <vector>

using namespace std;

struct Event {
    long long x;
    int y1, y2;
    int type;

    bool operator<(const Event& other) const {
        return x < other.x;
    }
};

struct SegTree {
    const int n;
    vector<int> cnt;
    vector<long long> len;
    const vector<long long>& ys;

    SegTree(int n, const vector<long long>& ys)
      : n(n), cnt(4*n,0), len(4*n,0), ys(ys)
      { }

    void update(int node, int l, int r, int ql, int qr, int val) {
        if (qr <= l || r <= ql) return;

        if (ql <= l && r <= qr) {
            cnt[node] += val;
        } else {
            int mid = (l + r) / 2;
            update(node*2, l, mid, ql, qr, val);
            update(node*2+1, mid, r, ql, qr, val);
        }

        if (cnt[node] > 0) {
            len[node] = ys[r] - ys[l];
        } else {
            if (l + 1 == r) len[node] = 0;
            else len[node] = len[node*2] + len[node*2+1];
        }
    }

    void update(int l, int r, int val) {
        if (l < r) update(1, 0, n, l, r, val);
    }

    long long covered() const { return len[1]; }
};


int main() {
    int n;
    cin >> n;

    struct Rect {
      long long x1,y1,x2,y2;
    };

    vector<Rect> rects(n);
    vector<long long> ys;

    for (int i = 0; i < n; ++i) {
        cin >> rects[i].x1 >> rects[i].y1 >> rects[i].x2 >> rects[i].y2;
        ys.push_back(rects[i].y1);
        ys.push_back(rects[i].y2);
    }

    sort(ys.begin(), ys.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());

    auto yidx = [&](long long y){
        return int(lower_bound(ys.begin(), ys.end(), y) - ys.begin());
    };

    vector<Event> evs;

    for (auto &r : rects) {
        evs.push_back({r.x1, yidx(r.y1), yidx(r.y2), +1});
        evs.push_back({r.x2, yidx(r.y1), yidx(r.y2), -1});
    }

    sort(evs.begin(), evs.end());

    SegTree st((int)ys.size()-1, ys);

    long long area = 0;
    long long prevX = evs[0].x;

    for (size_t i = 0; i < evs.size(); ) {
        long long x = evs[i].x;
        long long dx = x - prevX;

        area += st.covered() * dx;
        prevX = x;

        while (i < evs.size() && evs[i].x == x) {
            st.update(evs[i].y1, evs[i].y2, evs[i].type);
            ++i;
        }
    }

    cout << area << "\n";
    
    return 0;
}
