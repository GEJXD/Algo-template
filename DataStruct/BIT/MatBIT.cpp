template<class T, class Merge = std::plus<T>> struct MatBIT {
    const Merge merge;
    std::vector<BIT<T, Merge>> t;

    MatBIT(int n, int m)
        : t(n + 1, BIT<T>(m))
        , merge(Merge()) {}

    void modify(int x, int y, const T& v) {
        for (int i = x + 1; i < t.size(); i += i & -i) {
            t[i].modify(y, v);
        }
    }

    T posQuery(int x, int y) {
        T res = T();
        for (int i = x + 1; i; i -= i & -i) {
            res = merge(res, t[i].posQuery(y));
        }
        return res;
    }

    // [u, d), [l, r)
    T rangeQuery(int u, int l, int d, int r) {
        u -= 1, l -= 1, d -= 1, r -= 1;
        T res1 = posQuery(d, r) + posQuery(u, l);
        T res2 = posQuery(d, l) + posQuery(u, r);
        return res1 - res2;
    }
};