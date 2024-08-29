template<class T> struct Rand {
    std::mt19937 myrand;
    Rand(const i64 seed = time(0))
        : myrand(seed) {}
    T operator()(T l, T r) { return std::uniform_int_distribution<T>(l, r)(myrand); }
};
Rand<int> rd;

// std::mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());
