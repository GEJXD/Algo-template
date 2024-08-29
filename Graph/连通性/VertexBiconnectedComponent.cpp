class VertexBC
{
    const std::vector<std::vector<int>>& e;
    int cur = 0;

    void dfs(int x, int root) {
        dfn[x] = low[x] = cur++;

        int sonNum = 0;
        for (int y : e[x]) {
            if (dfn[y] == -1) {
                sonNum += 1;
                dfs(y, root);
                low[x] = std::min(low[x], low[y]);

                if (low[y] >= dfn[x] and x != root) {
                    cutDeg[x] += 1;
                }
            } else {
                low[x] = std::min(low[x], dfn[y]);
            }
        }

        if (x == root) {
            cutDeg[x] = sonNum - 1;
        }
    }

public:
    // original graph
    std::vector<int> dfn, low, cutDeg;
    int componentNum = 0;

    VertexBC(const std::vector<std::vector<int>>& e)
        : e(e)
        , dfn(e.size(), -1)
        , low(e.size())
        , cutDeg(e.size()) {
        int n = e.size();

        for (int i = 0; i < n; i++) {
            if (dfn[i] == -1) {
                componentNum += 1;
                dfs(i, i);
            }
        }
    }
};