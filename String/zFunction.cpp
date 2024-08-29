auto zFunction(const std::string& s) {
    int n = s.size();
    std::vector<int> z(n);
    for (int i = 1, l = 0, r = 0; i < n; i++) {
        if (i < r) z[i] = std::min(z[i - l], r - i);
        while (i + z[i] < n and s[i + z[i]] == s[z[i]]) z[i]++;
        if (i + z[i] > r) l = i, r = i + z[i];
    }
    return z;
    // S : aabcaabcaaaab
    // Z : 0100610022310
}