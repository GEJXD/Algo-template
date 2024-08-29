/*
维基百科 :
n < 4e9, Prime = [2, 7, 61]
n < 3e14, Prime = [2, 3, 5, 7, 11, 13, 17]
n < 3e18, Prime = [2, 3, 5, 7, 11, 13, 17, 19, 23]
n < 3e23, Prime = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37]
*/
template<class T> struct MillerRabin {
    const std::vector<int> Prime;
    MillerRabin()
        : Prime({2, 3, 5, 7, 11, 13, 17, 19, 23}) {}

    static constexpr int mulp(const int& a, const int& b, const int& P) { return 1ll * a * b % P; }
    static constexpr i64 mulp(const i64& a, const i64& b, const i64& P) {
        i64 res = a * b - i64(1.L * a * b / P) * P;
        res %= P;
        res += (res < 0 ? P : 0);
        return res;
    }

    static constexpr T powp(T a, T mi, const T& mod) {
        T ans = 1;
        for (; mi; mi >>= 1) {
            if (mi & 1) ans = mulp(ans, a, mod);
            a = mulp(a, a, mod);
        }
        return ans;
    }

    constexpr bool operator()(const T& v) {   // 判断v是不是质数
        if (v < 2 or v != 2 and v % 2 == 0) return false;
        T s = v - 1;
        while (!(s & 1)) s >>= 1;
        for (int x : Prime) {
            if (v == x) return true;
            T t = s, m = powp(x, s, v);
            while (t != v - 1 and m != 1 and m != v - 1) m = mulp(m, m, v), t <<= 1;
            if (m != v - 1 and !(t & 1)) return false;
        }
        return true;
    }
};
MillerRabin<i64> isp;
