template<int Z, char Base> struct AcAutomaton {
    std::vector<std::array<int, Z>> son;
    std::vector<std::vector<int>> ID;
    std::vector<int> link;
    int SIZE = 0, tot = 0;

    AcAutomaton(const std::vector<std::string>& s) {
        for (auto t : s) SIZE += t.size();
        son.resize(SIZE + 1);
        ID.resize(SIZE + 1);
        link.resize(SIZE + 1);

        for (int i = 0; i < s.size(); i++) insert(i, s[i]);
        build();
    }

    void insert(int id, const std::string& s) {
        int p = 0;
        for (char c : s) {
            c -= Base;
            if (!son[p][c]) son[p][c] = ++tot;
            p = son[p][c];
        }
        ID[p].push_back(id);
    }

    void build() {
        std::queue<int> q;
        for (int& y : son[0])
            if (y) {
                q.push(y);
            }
        while (!q.empty()) {
            int x = q.front();
            q.pop();

            for (int c = 0; int& y : son[x]) {
                if (y) {
                    link[y] = son[link[x]][c];
                    q.push(y);
                } else
                    y = son[link[x]][c];
                c++;
            }
        }
    }
};