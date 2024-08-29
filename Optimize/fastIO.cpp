char buf[1 << 22], *p1 = buf, *p2 = buf;
// p1 means start-pointer, p2 means end-pointer

char gc() {
    if (p1 == p2) p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin);
    return *(p1++);
}

template<typename T> T read() {
    T sum = 0, fl = 1;   // 将 sum,fl 和 ch 以输入的类型定义
    int ch = gc();
    for (; !isdigit(ch); ch = gc())
        if (ch == '-') fl = -1;
    for (; isdigit(ch); ch = gc()) sum = sum * 10 + ch - '0';
    return sum * fl;
}

template<typename T> void write(T x) {
    if (x < 0) x = -x, putchar('-');   // 负数输出
    static T sta[35];
    T top = 0;
    do {
        sta[top++] = x % 10, x /= 10;
    } while (x);
    while (top) putchar(sta[--top] + '0');
}