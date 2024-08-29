template<class T> struct RangeBIT {
    BIT<T, std::plus<T>> d, s;

    RangeBIT(int n)
        : d(n)
        , s(n) {}

    // O(n) build RangeBIT
    RangeBIT(std::vector<T> a)
        : d(diff(a))
        , s(multIndex(diff(a))) {}

    static std::vector<T> diff(std::vector<T> a) {
        std::adjacent_difference(begin(a), end(a), begin(a));
        return a;
    }

    static std::vector<T> multIndex(std::vector<T> a) {
        for (int i = 0; i < a.size(); i++) {
            a[i] *= i;
        }
        return a;
    }

    // [l, r)
    void rangeModify(int l, int r, const T& x) {
        d.modify(l, x), d.modify(r, -x);
        s.modify(l, l * x), s.modify(r, -r * x);
    }

    // [l, r)
    T rangeQuery(int l, int r) {
        T res1 = r * d.posQuery(r - 1) - s.posQuery(r - 1);
        T res2 = l * d.posQuery(l - 1) - s.posQuery(l - 1);
        return res1 - res2;
    }
};