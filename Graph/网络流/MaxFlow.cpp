template<class T> struct Flow {
    const int n;

    std::vector<std::pair<int, T>> e;
    std::vector<std::vector<int>> g;
    std::vector<int> cur, dep;

    Flow(int n)
        : n(n)
        , g(n) {}

    bool bfs(int s, int t) {
        dep.assign(n, -1);
        std::queue<int> q;
        dep[s] = 0;

        q.push(s);
        while (!q.empty()) {
            const int u = q.front();
            q.pop();

            for (int i : g[u]) {
                auto [v, c] = e[i];

                if (c > 0 and dep[v] == -1) {
                    dep[v] = dep[u] + 1;
                    if (v == t) return true;
                    q.push(v);
                }
            }
        }

        return false;
    }

    T dfs(int u, int t, T f) {
        if (u == t) {
            return f;
        }
        T res = f;
        for (int& i = cur[u]; i < g[u].size(); i++) {
            const int j = g[u][i];
            auto [v, c] = e[j];

            if (c > 0 and dep[v] == dep[u] + 1) {
                T out = dfs(v, t, std::min(res, c));
                e[j].second -= out;
                e[j ^ 1].second += out;

                res -= out;
                if (res == 0) {
                    return f;
                }
            }
        }
        return f - res;
    }

    void add(int u, int v, T c) {
        g[u].push_back(e.size());
        e.emplace_back(v, c);
        g[v].push_back(e.size());
        e.emplace_back(u, 0);
    }

    T work(int s, int t) {
        T ans = 0;
        while (bfs(s, t)) {
            cur.assign(n, 0);
            ans += dfs(s, t, std::numeric_limits<T>::max());
        }
        return ans;
    }
};