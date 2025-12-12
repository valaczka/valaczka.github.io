# Building Roads

> A feladat forrása: https://cses.fi/problemset/task/1666

---

### Gráf felépítése

* Városok: gráf csúcsai: `1..n`
* Utak: gráf élei
* `adj[i]` = i város szomszédlitsája (mely városokkal van útja)
* `visited[i]` = volt-e már `find` közben meglátogatva.


### find függvény

```cpp
void find(int u) {
    visited[u] = true;
    for (int v : adj[u]) {
        if (!visited[v])
            find(v);
    }
}
```

* Megjelöljük `u`-t látogatottnak
* Végigmegyünk az `u`-hoz kapcsolódó szomszédokon.
* Mindegyikre, amleyik még nem `visited`, rekurzívan meghívjuk a `find`-t.
* Így minden, ami `u`-ból elérhető, mind `visited` lesz.

### Szomszédok beolvasása és komponenesek keresése

Minden út két várost köt össze, így egymásnak szomszédai lesznek:

* `adj[a].push_back(b)`
* `adj[b].push_back(a)`

A *reps* minden komponensből egy reprezentáns csúcsot tárol.
Végigmegyünk az összes városon, és ha még nem látogatott, akkor létrehozunk egy új komponenest, az aktuális csúcsot megjelöljük a *reps*-ben mint a képviselőjét, és rekurzívan látogatottra állítjuk a komponenst.

```cpp
vector<int> reps;

for (int i = 1; i <= n; ++i) {
    if (!visited[i]) {
        reps.push_back(i);
        dfs(i);
    }
}
```

### Komponensek összekötése

Ahhoz, hogy midnen város bejárható legyen, elég a komponenseket összekötnünk, ehhez `reps.size()-1` útra van szükségünk.

A reprezentáns csúcsok között utat építünk, ezzel egy nagy összefüggő komponensünk lesz.

```cpp
for (int i = 0; i+1 < (int)reps.size(); ++i) {
    cout << reps[i] << " " << reps[i + 1] << "\n";
}
```
