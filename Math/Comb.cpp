template<class T, T P> class Comb
{
    static constexpr int multip(const int& a, const int& b) { return 1ll * a * b % P; }
    static constexpr i64 multip(const i64& a, const i64& b) {
        i64 res = a * b - i64(1.L * a * b / P) * P;
        res %= P;
        res += (res < 0 ? P : 0);
        return res;
    }

    int n;
    std::vector<T> _jc, _ijc, _inv;

public:
    constexpr Comb()
        : n{0}
        , _jc{1}
        , _ijc{1}
        , _inv{0} {}
    Comb(int n)
        : Comb() {
        init(n);
    }

    static constexpr T powp(T a, i64 mi) {
        T ans = 1;
        for (; mi; mi >>= 1, a = multip(a, a))
            if (mi & 1) ans = multip(ans, a);
        return ans;
    }

    void init(int m) {
        m = std::min(m, P - 1);
        if (m <= n) return;

        _jc.resize(m + 1);
        _ijc.resize(m + 1);
        _inv.resize(m + 1);

        for (int i = n + 1; i <= m; i++) {
            _jc[i] = multip(i, _jc[i - 1]);
        }
        _ijc.back() = powp(_jc.back(), P - 2);
        for (int i = m; i > n; i--) {
            _ijc[i - 1] = multip(i, _ijc[i]);
            _inv[i] = multip(_ijc[i], _jc[i - 1]);
        }

        n = m;
    }

    T jc(int x) {
        if (x > n) init(x << 1);
        return _jc[x];
    }
    T ijc(int x) {
        if (x > n) init(x << 1);
        return _ijc[x];
    }
    T inv(int x) {
        if (x > n) init(x << 1);
        return _inv[x];
    }

    T A(int a, int b) {
        if (a < b or b < 0) return 0;
        return multip(jc(a), ijc(a - b));
    }
    T C(int a, int b) {
        if (a < b or b < 0) return 0;
        return multip(A(a, b), ijc(b));
    }
};
constexpr int P = 998244353;
Comb<int, P> comb;

// 取模加法
int add(int a, int b) {
    a += b;

    if (a >= P) {
        a -= P;
    }

    if (a < 0) {
        a += P;
    }

    return a;
}
