struct Manacher {
    const int n;
    std::vector<int> r, f;

    Manacher(const std::string& t)
        : n(t.size())
        , r(2 * t.size() + 3)
        , f(2 * t.size() + 3) {
        std::string s = "[-";
        for (int i = 0; i < n; i++) {
            s += t[i];
            s += '-';
        }
        s.push_back(']');

        int mid = 1, far = 1;
        for (int i = 1; i < s.size(); i++) {
            r[i] = std::min(r[2 * mid - i], far - i);
            while (s[i + r[i]] == s[i - r[i]]) r[i] += 1;
            if (far < i + r[i]) mid = i, far = i + r[i];
            f[i + r[i] - 1] = std::max(f[i + r[i] - 1], r[i]);
        }
        for (int i = f.size() - 2; i; i--) f[i] = std::max(f[i], f[i + 1] - 1);
    }

    // 返回以i为中心的最长回文字符串长度，center为以+0.5为中心
    // aaa (0, 1) = 2
    int getPalinLenFromCenter(int i, int center) const {
        assert(!center and 0 <= i and i < n or center and 0 <= i and i < n - 1);

        return r[2 * (i + 1) + center] - 1;
    }

    // 返回以i结尾的最长回文字符串长度
    int getPalinLenFromTail(int i) const {
        assert(0 <= i and i < n);
        return f[2 * (i + 1)];
    }
};