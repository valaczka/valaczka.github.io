# Movie Festival II

> A feladat forrása: https://cses.fi/problemset/task/1632

---

### Számítás

A feladatot mohó algoritmussal oldjuk meg. A **movies** tömbbe tároljuk a filmek kezdő és befejezési idejét, és ezt a befejezési idejük szerint sorbarendezzük.

```
vector<pair<int,int>> movies(n);

for (int i = 0; i < n; ++i) {
    int a, b; cin >> a >> b;
    movies[i] = {b, a};              // Azért a végét vesszük előre, hogy egyszerűbben rendezhessük aszerint
}

sort(movies.begin(), movies.end());
```


Az **ans** változóban adjuk vissza a kért nézőszámot.

Az **ends** multisetben tároljuk, hogy mikor ér véget a nézők által nézett film (mikor lesz újra szabad).

```
multiset<int> ends;                  // A nézők utolsó választott filmjének befejezései
```


Minden filmnél keresünk egy olyan tagot, aki a film kezdésekor szabad. Az ends multisetben mindig rendezva vannak a nézők aktuális foglaltsági idejei, így *upper_bound*-dal gyorsan megtaláljuk a megfelelőt.


```
auto it = ends.upper_bound(start);
```

Ha nincs ilyen, de még nincs kihasználva mind a **k** tag, akkor nyitunk egy új nézőt.
Minden sikeres hozzárendelés növeli a számlálót.

```
if (it == ends.begin()) {    
    if ((int) ends.size() < k) {
        ends.insert(end);
        ++ans;
    }

    // Ha nincs több lehetőségünk, akkor kihagyjuk.
}
```

Ha van ilyen, akkor lecseréljük a befejezési idejét az aktuális film végére, és növeljük a számlálót.

```
else {    
    --it;
    ends.erase(it);
    ends.insert(end);
    ++ans;
}
```
