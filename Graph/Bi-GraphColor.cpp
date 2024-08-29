struct BiGraphColor {
    std::vector<int> col;
    bool isBiGraph;

    BiGraphColor(const std::vector<std::vector<int>>& e)
        : col(e.size(), -1)
        , isBiGraph(true) {

        int n = e.size();
        std::function<void(int)> dfs = [&](int x) {
            if (!isBiGraph) return;
            for (int y : e[x]) {
                if (col[y] == -1) {
                    col[y] = col[x] ^ 1;
                    dfs(y);
                } else if (col[y] == col[x]) {
                    isBiGraph = false;
                    return;
                }
            }
        };

        for (int i = 0; i < n; i++) {
            if (col[i] == -1) {
                col[i] = 0;
                dfs(i);
            }
            if (!isBiGraph) return;
        }
    }
};