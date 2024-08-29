template <class T>
struct ExGcd {
    T operator()(const T &a, const T &b, T &x, T &y) {
        if (b == 0)
            return (x = 1, y = 0, a);
        T g = (*this)(b, a % b, y, x);
        y -= a / b * x;
        return g;
    }
};
ExGcd<int> exgcd;
