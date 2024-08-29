template<class T> struct RangeMatBIT {
    MatBIT<T> p, px, py, pxy;

    RangeMatBIT(int n, int m)
        : p(n, m)
        , px(n, m)
        , py(n, m)
        , pxy(n, m) {}

    // [u, d), [l, r)
    void rangeModify(int u, int l, int d, int r, const T& v) {
        modify(u, l, v);
        modify(d, r, v);
        modify(u, r, -v);
        modify(d, l, -v);
    }

    // [u, d), [l, r)
    T rangeQuery(int u, int l, int d, int r) {
        u -= 1, l -= 1, d -= 1, r -= 1;
        return query(u, l) + query(d, r) - query(d, l) - query(u, r);
    }

private:
    void modify(int x, int y, const T& v) {
        p.modify(x, y, v);
        px.modify(x, y, v * x);
        py.modify(x, y, v * y);
        pxy.modify(x, y, v * x * y);
    }

    T query(int x, int y) {
        T res = T();
        res += p.posQuery(x, y) * (x + 1) * (y + 1);
        res -= px.posQuery(x, y) * (y + 1);
        res -= py.posQuery(x, y) * (x + 1);
        res += pxy.posQuery(x, y);
        return res;
    }
};