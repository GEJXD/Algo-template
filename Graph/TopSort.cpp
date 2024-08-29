class TopSort
{
    static constexpr int endPoint(int x) { return x; }
    template<class G> static constexpr int endPoint(const std::pair<int, G>& pr) {
        return pr.first;
    }

public:
    template<class T> std::vector<int> operator()(const std::vector<T>& e) const {
        int n = e.size();
        std::vector<int> ind(n);
        for (int x = 0; x < n; x++) {
            for (auto p : e[x]) {
                ind[endPoint(p)] += 1;
            }
        }

        std::vector<int> q;
        for (int x = 0; x < n; x++) {
            if (ind[x] == 0) {
                q.push_back(x);
            }
        }

        std::vector<int> res;
        while (!q.empty()) {
            int x = q.back();
            res.push_back(x);
            q.pop_back();

            for (auto p : e[x]) {
                int y = endPoint(p);
                ind[y] -= 1;
                if (ind[y] == 0) {
                    q.push_back(y);
                }
            }
        }

        return res;
    }
};
const TopSort topSort;