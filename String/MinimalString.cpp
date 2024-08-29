std::vector<int> minimalString(std::vector<int>& a) {
    int n = a.size();
    int i = 0, j = 1, k = 0;
    while (k < n and i < n and j < n) {
        if (a[(i + k) % n] == a[(j + k) % n])
            k++;
        else {
            (a[(i + k) % n] > a[(j + k) % n] ? i : j) += k + 1;
            i += (i == j);
            k = 0;
        }
    }
    k = std::min(i, j);
    std::vector<int> ans(n);
    for (int i = 0; i < n; i++) ans[i] = a[(i + k) % n];
    return ans;
}
// 直接返回字典序最小循环同构串
// 4321的循环同构串有 3214 2134 1432，最小为1432