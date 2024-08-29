template<class T, class Cmp = std::less<T>> struct RMQ {
    const Cmp cmp = Cmp();
    std::vector<std::vector<T>> ST;

    RMQ(const std::vector<T>& a) {
        int n = a.size(), logn = std::__lg(n);
        ST.assign(n, std::vector<T>(logn + 1));
        for (int i = 0; i < n; i++) ST[i][0] = a[i];
        for (int j = 0; j < logn; j++) {
            for (int i = 0; i + (1 << (j + 1)) - 1 < n; i++) {
                ST[i][j + 1] = std::min(ST[i][j], ST[i + (1 << j)][j], cmp);
            }
        }
    }

    // [l, r)
    T operator()(int l, int r) {
        int log = std::__lg(r - l);
        return std::min(ST[l][log], ST[r - (1 << log)][log], cmp);
    }
};