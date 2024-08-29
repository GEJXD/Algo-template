// O(sqrt(n)) 区间加, O(1) 单点查
template<class T, class Merge = std::plus<T>> struct Block {
    const int n, B;
    const Merge merge;
    std::vector<T> a, b;

    Block(int n, const T& v = T())
        : Block(std::vector<T>(n, v)) {}

    Block(const std::vector<T>& _init)
        : n(_init.size())
        , B(sqrt(2 * _init.size()))
        , a(_init)
        , merge(Merge()) {
        b.assign(n / B + 1, T());
    }

    // [l, r)
    void add(int l, int r, const T& v) {
        for (; l / B == (l - 1) / B and l < r; l++) {
            a[l] = merge(a[l], v);
        }
        for (; r / B == (r - 1) / B and l < r; r--) {
            a[r - 1] = merge(a[r - 1], v);
        }
        for (int i = l / B; i < r / B; i++) {
            b[i] = merge(b[i], v);
        }
    }

    T get(int x) { return merge(a[x], b[x / B]); }
};