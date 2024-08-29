template<class T> class PresidentTree
{

    using NodeIndex = int;

    struct Node {
        int val;
        NodeIndex l, r;

        Node(int val = 0)
            : val{val}
            , l{0}
            , r{0} {}
    };

    std::vector<Node> t;   // memory pool

    const T Start, Last;
    std::vector<NodeIndex> root;

    constexpr NodeIndex newNode(int val = 0) {
        t.emplace_back(val);
        return (int)t.size() - 1;
    }

    constexpr void up(NodeIndex i) { t[i].val = t[t[i].l].val + t[t[i].r].val; }

    constexpr void modify(NodeIndex& p, T l, T r, T x) {
        if (p == 0) {
            p = newNode();
        }
        if (r - l == 1) {
            t[p].val++;
            return;
        }

        T mid = (0LL + l + r) / 2;

        if (x < mid)
            modify(t[p].l, l, mid, x);
        else
            modify(t[p].r, mid, r, x);
        up(p);
    }
    constexpr NodeIndex merge(NodeIndex x, NodeIndex y, T l, T r) {
        if (!x or !y) return (x ? x : y);

        // 每次把 x 修改
        if (r - l == 1) {
            t[x].val += t[y].val;
            return x;
        }

        T mid = (0LL + l + r) / 2;
        t[x].l = merge(t[x].l, t[y].l, l, mid);
        t[x].r = merge(t[x].r, t[y].r, mid, r);
        return up(x), x;
    }

    constexpr int getRange(NodeIndex x, NodeIndex y, T l, T r, T tl, T tr) {
        if (tl <= l and r <= tr) {
            return t[y].val - t[x].val;
        }
        T mid = (0LL + l + r) / 2;
        return (tl < mid ? getRange(t[x].l, t[y].l, l, mid, tl, tr) : 0) +
               (mid < tr ? getRange(t[x].r, t[y].r, mid, r, tl, tr) : 0);
    }

    constexpr T getKth(NodeIndex x, NodeIndex y, T l, T r, int k) {
        if (r - l == 1) return l;
        T mid = (0LL + l + r) / 2;
        int L = t[t[y].l].val - t[t[x].l].val;

        return (L >= k ? getKth(t[x].l, t[y].l, l, mid, k) : getKth(t[x].r, t[y].r, mid, r, k - L));
    }

public:
    constexpr PresidentTree(const std::vector<T>& a, T min, T max)
        : root(a.size() + 1)
        , Start(min)
        , Last(max + 1)
        , t(1) {

        t.reserve(a.size() * std::__lg(a.size() * 2));

        root[0] = newNode();
        for (int i = 1; i <= a.size(); i++) {
            if (t.capacity() <= t.size() + 64) {
                t.reserve(std::max(2 * t.capacity(), t.capacity() + 64));
            }
            modify(root[i], Start, Last, a[i - 1]);
            root[i] = merge(root[i], root[i - 1], Start, Last);
        }
    }
    // [l, r), [tl, tr)
    constexpr int getRange(int l, int r, T tl, T tr) {
        return getRange(root[l], root[r], Start, Last, tl, tr);
    }
    // [l, r)
    constexpr T getKth(int l, int r, int k) { return getKth(root[l], root[r], Start, Last, k); }
};