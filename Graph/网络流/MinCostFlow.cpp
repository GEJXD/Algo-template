template<class T = i64> struct MCFGraph {
    struct Edge {
        int y, c, f;
    };
    const int n;
    std::vector<Edge> e;
    std::vector<std::vector<int>> g;
    std::vector<T> h, dis;
    std::vector<int> pre;

    bool dijkstra(int s, int t) {
        dis.assign(n, std::numeric_limits<T>::max());
        pre.assign(n, -1);
        using pii = std::pair<T, int>;
        std::priority_queue<pii, std::vector<pii>, std::greater<>> q;
        dis[s] = 0;
        q.emplace(0, s);

        while (!q.empty()) {
            auto [D, x] = q.top();
            q.pop();

            if (dis[x] < D) continue;
            for (int i : g[x]) {
                const auto& [y, c, f] = e[i];
                if (c > 0 and dis[y] > D + h[x] - h[y] + f) {
                    dis[y] = D + h[x] - h[y] + f;
                    pre[y] = i;
                    q.emplace(dis[y], y);
                }
            }
        }
        return dis[t] != std::numeric_limits<T>::max();
    }
    MCFGraph(int n)
        : n(n)
        , g(n) {}
    void add(int x, int y, int c, int f) {
        if (f < 0) {   // ** 删除 <=> 最大流
            g[x].push_back(e.size());
            e.emplace_back(y, 0, f);
            g[y].push_back(e.size());
            e.emplace_back(x, c, -f);
        } else   // **
            g[x].push_back(e.size()), e.emplace_back(y, c, f), g[y].push_back(e.size()),
                e.emplace_back(x, 0, -f);
    }
    std::pair<int, T> work(int s, int t) {
        int flow = 0;
        T cost = 0;
        h.assign(n, 0);
        while (dijkstra(s, t)) {
            for (int i = 0; i < n; ++i) h[i] += dis[i];
            int aug = std::numeric_limits<int>::max();
            for (int i = t; i != s; i = e[pre[i] ^ 1].y) aug = std::min(aug, e[pre[i]].c);
            for (int i = t; i != s; i = e[pre[i] ^ 1].y) {
                e[pre[i]].c -= aug;
                e[pre[i] ^ 1].c += aug;
            }
            flow += aug;
            cost += T(aug) * h[t];
        }
        return std::pair(flow, cost);
    }
};