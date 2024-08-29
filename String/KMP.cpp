auto kmp(const std::string& s) {
    int n = s.size();
    std::vector<int> link(n);
    for (int i = 1, j = 0; i < n; i++) {
        while (j and s[i] != s[j]) j = link[j - 1];
        j += (s[i] == s[j]);
        link[i] = j;
    }
    return link;
}

void find(const std::string& s, const std::string& p, const std::vector<int>& link) {
    for (int i = 0, j = 0; i < (int)s.size(); ++i) {
        while (j && s[i] != p[j]) j = link[j - 1];
        j += (s[i] == p[j]);
        if (j == (int)p.size()) {
            std::cout << i - j + 2 << '\n';
            j = link[j - 1];
        }
    }
}