template<class T, class Tag> struct LazySegT {
    int n;
    std::vector<T> info;
    std::vector<Tag> tag;

    LazySegT(int n, T v = T())
        : LazySegT(std::vector(n, v)) {}

    template<class G>
    LazySegT(const std::vector<G>& a)
        : n(a.size()) {
        info.assign(4 << std::__lg(n), T());
        tag.assign(4 << std::__lg(n), Tag());
        std::function<void(int, int, int)> build = [&](int i, int l, int r) {
            if (r - l == 1) {
                info[i] = a[l];
                return;
            }
            int mid = l + r >> 1;
            build(i << 1, l, mid);
            build(i << 1 | 1, mid, r);
            up(i);
        };
        build(1, 0, n);
    }

    void up(int i) { info[i] = info[i << 1] + info[i << 1 | 1]; }
    void apply(int i, const Tag& v) {
        info[i].apply(v);
        tag[i].apply(v);
    }
    void down(int i) {
        apply(i << 1, tag[i]);
        apply(i << 1 | 1, tag[i]);
        tag[i] = Tag();
    }

    // 单点修改
    void modify(int i, const T& v) { modify(1, 0, n, i, v); }
    void modify(int i, int l, int r, int x, const T& v) {
        if (r - l == 1) {
            info[i] = v;
            return;
        }
        int mid = l + r >> 1;
        down(i);
        if (x < mid) {
            modify(i << 1, l, mid, x, v);
        } else {
            modify(i << 1 | 1, mid, r, x, v);
        }
        up(i);
    }

    // 区间查询 [l, r)
    T rangeQuery(int l, int r) { return rangeQuery(1, 0, n, l, r); }
    T rangeQuery(int i, int l, int r, int tl, int tr) {

        if (tl <= l and r <= tr) return info[i];

        down(i);
        int mid = l + r >> 1;

        return (tl < mid ? rangeQuery(i << 1, l, mid, tl, tr) : T()) +
               (mid < tr ? rangeQuery(i << 1 | 1, mid, r, tl, tr) : T());
    }

    // 区间修改 [l, r)
    void rangeModify(int l, int r, const Tag& v) { return rangeModify(1, 0, n, l, r, v); }
    void rangeModify(int i, int l, int r, int tl, int tr, const Tag& v) {

        if (tl <= l and r <= tr) {
            apply(i, v);
            return;
        }
        down(i);
        int mid = l + r >> 1;

        if (tl < mid) rangeModify(i << 1, l, mid, tl, tr, v);
        if (mid < tr) rangeModify(i << 1 | 1, mid, r, tl, tr, v);
        up(i);
    }

    // 区间左边第一个满足条件的下标
    template<class F> int findFirst(int l, int r, F pred) { return findFirst(1, 0, n, l, r, pred); }
    template<class F> int findFirst(int i, int l, int r, int tl, int tr, F pred) {
        if (l >= tr || r <= tl || !pred(info[i])) {
            return -1;
        }
        if (r - l == 1) {
            return l;
        }
        int mid = l + r >> 1;
        down(i);
        int res = findFirst(i << 1, l, mid, tl, tr, pred);
        if (res == -1) {
            res = findFirst(i << 1 | 1, mid, r, tl, tr, pred);
        }
        return res;
    }

    // 区间右边第一个满足条件的下标
    template<class F> int findLast(int l, int r, F pred) { return findLast(1, 0, n, l, r, pred); }
    template<class F> int findLast(int i, int l, int r, int tl, int tr, F pred) {
        if (l >= tr || r <= tl || !pred(info[i])) {
            return -1;
        }
        if (r - l == 1) {
            return l;
        }
        int mid = l + r >> 1;
        down(i);
        int res = findLast(i << 1 | 1, mid, r, tl, tr, pred);
        if (res == -1) {
            res = findLast(i << 1, l, mid, tl, tr, pred);
        }
        return res;
    }
};

struct Tag {
    int add;

    Tag(const int& add = 0)
        : add(add) {}

    void apply(const Tag& tag) {
        if (tag.add) {}
    }
};

struct Node {
    i64 val;
    int len;

    Node(const i64& val = 0, const int& len = 1)
        : val(val)
        , len(len) {}

    void apply(const Tag& tag) {
        if (tag.add) {
            val += 1ll * tag.add * len;
        }
    }

    Node operator+(const Node& a) { return Node(val + a.val, len + a.len); }
};