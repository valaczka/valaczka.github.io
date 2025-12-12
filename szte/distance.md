# Edit Distance

> A feladat forrása: https://cses.fi/problemset/task/1639

---

### Feladat

Két sztring közti különbség mértéke: hány minimális művelet kell, hogy az egyiket átalakítsd a másikká.

A lehetséges műveletek:
- Beszúrás
- Törlés
- Csere


### Dinamikus programozás

Létrehozunk egy **dp** táblát, ahol a **dp[i][j]** érték mindig azt mondja megy, hogy mennyi művelet
kell a két sztring adott hosszúságú prefixeinek egyezővé alakításához.

Létrehozzuk a **dp** táblát a sztringek méretei alapján:

```cpp
int n = (int)a.size();
int m = (int)b.size();

vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
```

Ha *i* vagy *j* üres, akkor törölni vagy beszúrni kell karaktereket:

```cpp
for (int i = 0; i <= n; ++i)
    dp[i][0] = i;       // i törlés

for (int j = 0; j <= m; ++j)
    dp[0][j] = j;       // j beszúrás
```


Felépítjük a táblát *1-n*, illetve *1-m* esetekre. Mindegyiknél 3 lehetőséget vizsgálunk:

- ha karaktert kellene törölni az *a*-ból, akkor `dp[i-1][j] + 1`, mert *i-1* karakter átalakítása (*j* karakterre) + 1 törlés
- ha karaktert kellene beszúrni az *a*-ba, akkor `dp[i][j-1] + 1`, mert 1 beszúrás + *j-1* karakter átalakítása (*i* karakterre)
- ha karaktert kellene cserélni, akkor 1 vagy 0 művelet, attól függően, hogy az aktuális karakterek egyeznek-e: `int cost = (a[i-1] == b[j-1]) ? 0 : 1;`

A három közül a minimálisat választjuk:

```cpp
dp[i][j] = min({
    dp[i - 1][j] + 1,         // törlés a-ból
    dp[i][j - 1] + 1,         // beszúrás a-ba
    dp[i - 1][j - 1] + cost   // csere (vagy egyezés)
});
```

``
