struct DSU {
    std::vector<int> f;
    std::vector<int> size;

    DSU(int n)
        : f(n)
        , size(n) {
        std::iota(f.begin(), f.end(), 0);
        std::fill(size.begin(), size.end(), 1);
    }

    int find(int x) {
        while (x != f[x]) x = f[x] = f[f[x]];
        return x;
    }

    void Union(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return;

        if (size[x] < size[y]) std::swap(x, y);

        size[x] += size[y];
        f[y] = x;
    }
};