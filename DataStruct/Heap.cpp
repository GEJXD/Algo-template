template<class T, class Cmp = std::less<T>> struct Heap {
    std::priority_queue<T, std::vector<T>, Cmp> qPush, qErase;   // Heap=qPush-qErase

    void push(T x) { qPush.push(x); }

    void erase(T x) { qErase.push(x); }

    T top() {
        while (!qErase.empty() && qPush.top() == qErase.top()) qPush.pop(), qErase.pop();
        return qPush.top();
    }

    void pop() {
        while (!qErase.empty() && qPush.top() == qErase.top()) qPush.pop(), qErase.pop();
        qPush.pop();
    }

    int size() { return qPush.size() - qErase.size(); }
};