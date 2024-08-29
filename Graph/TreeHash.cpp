using u64 = unsigned long long;

template<class T> struct Rand {
    std::mt19937 myrand;
    Rand(const i64 seed = time(0))
        : myrand(seed) {}
    T operator()(T l, T r) { return std::uniform_int_distribution<T>(l, r)(myrand); }
};
Rand<u64> rd;

u64 f(u64 x) {
    const static u64 r1 = rd(1 << 20, 1 << 24);
    const static u64 r2 = rd(1 << 25, 1 << 30);
    const static u64 mask = (1ll << 31) - 1;

    auto h = [&](u64 y) { return (u64)y * y * y * r1 + r2; };
    return h(x & mask) + h(x >> 31);
}
