template<class T, class G> struct ExCrt : public ExGcd<T> {
    std::vector<std::pair<T, T>> q;
    void insert(T a, T mod) { q.push_back({a, mod}); }

    // 方程组 x ≡ a (模 mod) 返回最小正解
    // 无解返回 -1
    T get() {
        T res = 0, M = 1;
        for (auto [a, mod] : q) {
            T r = (a - res) % mod;
            r += (r < 0 ? mod : 0);

            T x, y;
            T g = (*this)(M, mod, x, y);
            if (r % g) {
                q.clear();
                return -1;
            }

            x = (G(x) * r / g % (mod / g));
            x += (x < 0 ? mod / g : 0);

            T Last = M;
            M = M / g * mod;
            res = (G(x) * Last % M + res) % M;
        }
        q.clear();
        return res;
    }
};

ExCrt<i64, __int128> crt;
