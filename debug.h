#ifndef DEBUG
#define DEBUG

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

// ================= PRINT FUNCTIONS =================

template<typename T>
void _print(const T& x) {
    cerr << x;
}

template<typename T1, typename T2>
void _print(const pair<T1, T2>& a) {
    cerr << "{" << a.first << ", " << a.second << "}";
}

template<typename T1, size_t N>
void _print(const array<T1, N>&a) {
    cerr << "[";
    for (auto& i : a) _print(i), cerr << " ";
    cerr << "]";
}

template<typename T>
void _print(const deque<T>& a) {
    cerr << "[";
    for (auto& i : a) _print(i), cerr << " ";
    cerr << "]";
}

template<typename T>
void _print(stack<T> s) { // pass by value to pop
    cerr << "[";
    while (!s.empty()) {
        _print(s.top()); cerr << " ";
        s.pop();
    }
    cerr << "]";
}

template<typename T>
void _print(queue<T> q) { // pass by value to pop
    cerr << "[";
    while (!q.empty()) {
        _print(q.front()); cerr << " ";
        q.pop();
    }
    cerr << "]";
}


template<class Tuple, size_t... I>
void _print_tuple_impl(const Tuple& t, index_sequence<I...>) {
    (( _print(get<I>(t)), cerr << (I + 1 < sizeof...(I) ? ", " : "") ), ...);
}

template<typename... Args>
void _print(const tuple<Args...>& t) {
    cerr << "(";
    _print_tuple_impl(t, index_sequence_for<Args...> {});
    cerr << ")";
}


template<typename T>
void _print(const vector<T>& a) {
    bool first = 1;
    cerr << "[";
    for (auto& i : a) {
        if (!first) {
            cerr << " ";
        }
        _print(i);
        first = 0;
    }
    cerr << "]";
}

template<typename T>
void _print(priority_queue<T> pq) { // max-heap
    cerr << "[";
    while (!pq.empty()) {
        _print(pq.top()); cerr << " ";
        pq.pop();
    }
    cerr << "]";
}

template<size_t N>
void _print(const bitset<N>& b) {
    cerr << b;
}


template<typename T>
void _print(priority_queue<T, vector<T>, greater<T>> pq) { // min-heap
    cerr << "[";
    while (!pq.empty()) {
        _print(pq.top()); cerr << " ";
        pq.pop();
    }
    cerr << "]";
}


template<typename T>
void _print(const vector<vector<T>>& a) {
    cerr << "[\n";
    for (auto& row : a) {
        cerr << "  ";
        _print(row);
        cerr << "\n";
    }
    cerr << "]";
}

template<typename T>
void _print(const set<T>& a) {
    cerr << "{";
    for (auto& i : a) _print(i), cerr << " ";
    cerr << "}";
}

template<typename T>
void _print(const multiset<T>& a) {
    cerr << "{ ";
    for (auto& i : a) _print(i), cerr << " ";
    cerr << "}";
}

template<typename T1, typename T2>
void _print(const map<T1, T2>& a) {
    cerr << "{";
    for (auto& [key, val] : a) {
        cerr << "["; _print(key); cerr << " : "; _print(val); cerr << "] ";
    }
    cerr << "}";
}

template<typename T>
void _print(const unordered_set<T>& a) {
    cerr << "{";
    for (auto& i : a) _print(i), cerr << " ";
    cerr << "}";
}

template<typename T1, typename T2>
void _print(const unordered_map<T1, T2>& a) {
    cerr << "{";
    for (auto& [key, val] : a) {
        cerr << "["; _print(key); cerr << " : "; _print(val); cerr << "], ";
    }
    cerr << "}";
}

template<typename T1, typename T2>
void _print(const vector<pair<T1, T2>>& a) {
    cerr << "[";
    for (auto& p : a) _print(p), cerr << " ";
    cerr << "]";
}


template<typename T, size_t N>
void _print(T (&a)[N]) {
    cerr << "[";
    for (size_t i = 0; i < N; i++) {
        _print(a[i]);   // prints element
        if (i + 1 < N) cerr << ", ";
    }
    cerr << "]";
}


// ================= VARIADIC DEBUG =================

void debug_out() {
    cerr << "\n";
}


template<typename T>
void debug_out(T&& a) {   // universal reference
    _print(std::forward<T>(a));
    cerr << "\n";
}


template<typename T, typename... Args>
void debug_out(T&& a, Args&&... args) {
    _print(std::forward<T>(a));
    cerr << "\n";
    debug_out(std::forward<Args>(args)...);
}


#define dbg(...) debug_out(__VA_ARGS__)

#endif // DEBUG
