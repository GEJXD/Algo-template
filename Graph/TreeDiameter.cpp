template<class T> class TreeDiameter
{
    static constexpr std::pair<int, int> edge(int x) { return {x, 1}; }
    template<class G> static constexpr int edge(const std::pair<int, G>& pr) { return pr; }

    const std::vector<T>& e;
    std::vector<i64> dis;

    void dfs(int x, int fa) {
        for (auto p : e[x]) {
            auto [y, w] = edge(p);
            if (y != fa) {
                dis[y] = dis[x] + w;
                dfs(y, x);
            }
        }
    }

public:
    int v1 = 0, v2 = 0;
    i64 diameter = 0;

    TreeDiameter(const std::vector<T>& e)
        : e(e)
        , dis(e.size()) {
        dfs(0, -1);
        v1 = std::max_element(begin(dis), end(dis)) - begin(dis);
        dis[v1] = 0;
        dfs(v1, -1);
        v2 = std::max_element(begin(dis), end(dis)) - begin(dis);
        diameter = dis[v2];
    }
};