class SCC
{
    const std::vector<std::vector<int>>& e;
    std::vector<int> q;   // stack
    int r = 0, cur = 0;

    void dfs(int x) {
        dfn[x] = low[x] = cur++;
        q[++r] = x;

        for (int y : e[x]) {
            if (dfn[y] == -1) {
                dfs(y);
                low[x] = std::min(low[x], low[y]);
            } else if (bel[y] == -1) {
                low[x] = std::min(low[x], dfn[y]);
            }
        }

        if (dfn[x] == low[x]) {
            int y;
            do {
                y = q[r--];
                bel[y] = cntBlock;
            } while (y != x);
            cntBlock += 1;
        }
    }

public:
    // original graph
    std::vector<int> dfn, low, bel;

    // shrinking graph
    std::vector<std::vector<int>> g;
    int cntBlock = 0;

    SCC(const std::vector<std::vector<int>>& e)
        : e(e)
        , dfn(e.size(), -1)
        , low(e.size())
        , bel(e.size(), -1) {
        int n = e.size();
        q.assign(n + 1, 0);

        for (int i = 0; i < n; i++) {
            if (dfn[i] == -1) {
                dfs(i);
            }
        }

        g.resize(cntBlock);
        for (int x = 0; x < n; x++) {
            for (int y : e[x]) {
                if (bel[x] == bel[y]) continue;
                g[bel[x]].push_back(bel[y]);
            }
        }

        // for (int x = 0; x < cntBlock; x++) {
        //     std::sort(begin(g[x]), end(g[x]));
        //     g[x].erase(std::unique(begin(g[x]), end(g[x])), end(g[x]));
        // }
    }
};
