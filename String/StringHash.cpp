// -std=c++20
template<int D, std::array<int, D> B, std::array<int, D> P> struct StringHash {
    std::vector<std::array<int, D>> h;

    template<class T>
    StringHash(const T& s)
        : h(s.size() + 1) {
        for (int i = 0; i < s.size(); i++) {
            for (int k = 0; k < D; k++) {
                h[i + 1][k] = (1ll * h[i][k] * B[k] + s[i] + 1) % P[k];
            }
        }
    }

    // [l, r)
    std::array<int, D> get(int l, int r) {
        static std::vector<std::array<int, D>> spow(1);
        if (r - l < 0) throw -1;

        if (spow.size() < r - l + 1) {
            if (spow[0][0] == 0) {
                spow[0].fill(1);
            }
            int n = spow.size();
            spow.resize(r - l + 1);
            for (int i = n; i < spow.size(); i++) {
                for (int k = 0; k < D; k++) {
                    spow[i][k] = 1ll * spow[i - 1][k] * B[k] % P[k];
                }
            }
        }

        std::array<int, D> res = {};
        for (int k = 0; k < D; k++) {
            res[k] = h[r][k] - 1ll * h[l][k] * spow[r - l][k] % P[k];
            res[k] += (res[k] < 0 ? P[k] : 0);
        }
        return res;
    }
};
using Hash = StringHash<2, {133, 331}, {int(1e9 + 21), int(1e9 + 33)}>;
