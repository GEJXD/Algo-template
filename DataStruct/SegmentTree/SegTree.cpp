template<class T, class Merge = std::plus<T>> struct SegT {
    const Merge merge;
    const int n;
    std::vector<T> t;

    SegT(int n)
        : n(n)
        , t(4 << std::__lg(n))
        , merge(Merge()) {}

    SegT(const std::vector<T>& a)
        : SegT(a.size()) {
        std::function<void(int, int, int)> build = [&](int i, int l, int r) {
            if (r - l == 1) {
                t[i] = a[l];
                return;
            }
            int mid = l + r >> 1;
            build(i << 1, l, mid);
            build(i << 1 | 1, mid, r);
            up(i);
        };
        build(1, 0, n);
    }

    void up(int i) { t[i] = merge(t[i << 1], t[i << 1 | 1]); }

    // 默认单点赋值
    void modify(int x, const T& v) { modify(1, 0, n, x, v); }

    void modify(int i, int l, int r, int x, const T& v) {
        if (r - l == 1) {
            t[i] = v;
            return;
        }
        int mid = l + r >> 1;
        if (x < mid)
            modify(i << 1, l, mid, x, v);
        else
            modify(i << 1 | 1, mid, r, x, v);
        up(i);
    }

    // [l, r)
    T rangeQuery(int l, int r) { return rangeQuery(1, 0, n, l, r); }

    T rangeQuery(int i, int l, int r, int tl, int tr) {
        if (tl <= l and r <= tr) {
            return t[i];
        }
        int mid = l + r >> 1;
        return merge((tl < mid ? rangeQuery(i << 1, l, mid, tl, tr) : T()),
                     (mid < tr ? rangeQuery(i << 1 | 1, mid, r, tl, tr) : T()));
    }
};