struct Sieve {
    std::vector<int> P, v;

    Sieve(int n)
        : v(n) {
        for (int i = 2; i < n; i++) {
            if (v[i] == 0) {
                P.push_back(i);
                v[i] = i;
            }
            for (int j = 0; j < P.size() and i * P[j] < n; j++) {
                v[i * P[j]] = P[j];
                if (P[j] == v[i]) break;
            }
        }
    }

    // 求所有约数
    auto getDiv(int x) const {
        std::vector<int> _div(1, 1);
        while (x > 1) {
            int D = v[x];
            int l = 0, r = _div.size();
            while (x % D == 0) {
                for (int k = l; k < r; k++) _div.push_back(_div[k] * D);
                x /= D, l = r, r = _div.size();
            }
        }
        return _div;
    }
};
