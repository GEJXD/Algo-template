template<class T, class G> class Dijkstra
{
    const std::vector<std::vector<std::pair<int, T>>>& e;
    std::vector<std::vector<G>> dis;

    auto get(int s) {
        std::vector<G> dis(e.size(), std::numeric_limits<G>::max() / 2);

        using pii = std::pair<G, int>;
        std::priority_queue<pii, std::vector<pii>, std::greater<>> q;

        dis[s] = G();
        q.push({dis[s], s});

        while (!q.empty()) {
            auto [D, x] = q.top();
            q.pop();

            if (D > dis[x]) continue;

            for (auto&& [y, w] : e[x]) {
                if (dis[y] > dis[x] + w) {
                    dis[y] = dis[x] + w;
                    q.push({dis[y], y});
                }
            }
        }
        return dis;
    }

public:
    Dijkstra(const std::vector<std::vector<std::pair<int, T>>>& g)
        : e(g)
        , dis(g.size()) {}

    G operator()(int x, int y) {
        if (dis[x].empty()) dis[x] = get(x);
        return dis[x][y];
    }
};