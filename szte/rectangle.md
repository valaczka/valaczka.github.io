
# Area of Rectangles

> A feladat forrása: https://cses.fi/problemset/task/1741

---

### SegTree

A feladatot egy olyan algoritmussal oldjuk meg, amely a koordinátarendszer x tengelyén végighaladva
lépésenként kiszámolja a téglalapok uniójának teljes területét a lefedettség változása szerint.

Az akutális lefedettség tárolásához egy olyan bináris fát építünk, amely
az y tengelyt szegmensenkre osztja és tárolja a téglalapok által ténylegesen lefedett hosszt az y tengelyen.

Ez az algoritmus O(n * log n) időben számítja ki az uniók teljes terüeltét.

A nagy y-koordináták helyett csak a ténylegesen előfordulókat tároljuk, és azok indexeivel (**ys** vektor) dolgozunk.

```
struct SegTree {
    const int n;                  // A szegmensek száma
    vector<int> cnt;              // A lefedett téglalapok száma csomópontonként
    vector<long long> len;        // A ténylegesen lefedett hossz az y tengelyen csomópontonként
    const vector<long long>& ys;  // Az tényleges y-koordináták
}
```

A fa gyökerében (1) mindig az aktuálisan lefedett teljesn hossz található.
A csúcsokat tömbökben reprezentáljuk, indexszel hivatkozunk rá:
- egy csúcs bal gyerekének indexe = csúcs indexe * 2
- egy csúcs jobb gyerekének indexe = csúcs indexe * 2 +1

Hogy biztosan beleférjen a fa a tömbökbe, 4*n méretűekre foglaljuk le őket.

```
SegTree(int n, const vector<long long>& ys)
  : n(n), cnt(4*n,0), len(4*n,0), ys(ys)
  { }
```

### Rect

A téglalapok koordináit a Rect struktúrába gyűjtjük.

```
struct Rect {
  long long x1,y1,x2,y2;
};
```

Az y-koordinátákat sorba rendezzük, és eltávolítjuk az ismétlődéseket.

```
sort(ys.begin(), ys.end());
ys.erase(unique(ys.begin(), ys.end()), ys.end());
```


### Event

Az x tengelyen való végighaladáshoz _eseményeket_ hozunk létre.

```
struct Event {
    long long x;
    int y1, y2;
    int type;         // Az esemény típusa: +1 = belépünk, -1 = kilépünk
}
```

A téglalapokat függőleges élek mentén dolgozzuk fel.
Minden téglalapból két eseményt képezünk:
  - `(x1, +1, [y1, y2))` – amikor belépünk a téglalapba.
  - `(x2, -1, [y1, y2))` – amikor kilépünk a téglalapból.

```
vector<Event> evs;

for (auto &r : rects) {
    evs.push_back({r.x1, yidx(r.y1), yidx(r.y2), +1});
    evs.push_back({r.x2, yidx(r.y1), yidx(r.y2), -1});
}
```


Az eseményeket az x értékük alapján sorbarendezzük (ld. `bool operator<(const Event& other) const`);

```
sort(evs.begin(), evs.end());
```


### Számítás

A lefedett területet az *area* változóban számoljuk.
Végigmegyünk az eseményeken, minden lépés után a `st.covered()` megmutatja az aktuális lefedett y-hosszt,  
amit az x-különbséggel (*dx*) megszorozva kapjuk meg az új területdarabot.


```
long long area = 0;
long long prevX = evs[0].x;

for (size_t i = 0; i < evs.size(); ) {
    long long x = evs[i].x;
    long long dx = x - prevX;

    area += st.covered() * dx;
    prevX = x;  
```

Az azonos x értékeket együtt dolgozzuk fel.

```
    while (i < evs.size() && evs[i].x == x) {
        st.update(evs[i].y1, evs[i].y2, evs[i].type);
        ++i;
    }
}
```

A `SegTree::update()` minden lépésnél újraszámolja a fa érintett csúcsait.

```
void update(int node, int l, int r, int ql, int qr, int val) {
    if (qr <= l || r <= ql) return;     // Ha nincs átfedés akkor nem is folytatjuk

    // Az átfedéő téglapok kiszámítása (val értéke alapján +1/-1)

    if (ql <= l && r <= qr) {           // Ha teljesen átfedi
        cnt[node] += val;
    } else {                            // Ha csak részlegesen fed át, akkor rekurzívan meghívjuk a két gyereke
        int mid = (l + r) / 2;
        update(node*2, l, mid, ql, qr, val);
        update(node*2+1, mid, r, ql, qr, val);
    }

    // A valós y hossz számítása

    if (cnt[node] > 0) {                // Ha esik a csúcsra lefedett téglalap
        len[node] = ys[r] - ys[l];
    } else {
        if (l + 1 == r) len[node] = 0;
        else len[node] = len[node*2] + len[node*2+1];         // A két gyerek hosszát adjuk össze
    }
}
```
