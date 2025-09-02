#ifndef DEBUG
#define DEBUG

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

// ================== HELPER TRAITS ==================

template <typename T, typename = void>
struct is_iterable : false_type {};

template <typename T>
struct is_iterable<T, void_t<decltype(begin(declval<T>())), decltype(end(declval<T>()))>> : true_type {};

template <typename T>
constexpr bool is_iterable_v = is_iterable<T>::value;

// ================== PRINT FUNCTIONS ==================

template <typename T>
void _print(const T &x);

// base types
void _print(const string &s) { cerr << '"' << s << '"'; }
void _print(const char *s) { cerr << '"' << s << '"'; }
void _print(char c) { cerr << '\'' << c << '\''; }
void _print(bool b) { cerr << (b ? "true" : "false"); }

template <typename T>
void _print(const complex<T> &c) { cerr << c.real() << "+" << c.imag() << "i"; }

template <typename T>
void _print(const optional<T> &opt) {
    if (opt.has_value()) {
        cerr << "Some(";
        _print(opt.value());
        cerr << ")";
    } else {
        cerr << "None";
    }
}

// pair

template <typename T1, typename T2>
void _print(const pair<T1, T2> &a) {
    cerr << "{";
    _print(a.first);
    cerr << ", ";
    _print(a.second);
    cerr << "}";
}

// tuple

template <class Tuple, size_t... I>
void _print_tuple_impl(const Tuple &t, index_sequence<I...>) {
    (( _print(get<I>(t)), cerr << (I + 1 < sizeof...(I) ? ", " : "") ), ...);
}

template <typename... Args>
void _print(const tuple<Args...> &t) {
    cerr << "(";
    _print_tuple_impl(t, index_sequence_for<Args...>{});
    cerr << ")";
}

// bitset
template <size_t N>
void _print(const bitset<N> &b) { cerr << b; }

template <>
void _print(const vector<bool> &v) {
    cerr << "[";
    for (size_t i = 0; i < v.size(); i++) {
        cerr << (v[i] ? 1 : 0);
        if (i + 1 < v.size()) cerr << " ";
    }
    cerr << "]";
}



// ================== GENERIC CONTAINER ==================

template <typename T>
void _print(const T &a) {
    if constexpr (is_iterable_v<T> && !is_same_v<T, string>) {
        cerr << "[";
        bool first = true;
        for (auto &x : a) {
            if (!first) cerr << " ";
            _print(x);
            first = false;
        }
        cerr << "]";
    } else {
        cerr << a;
    }
}

// ================== RAW ARRAY ==================

template <typename T, size_t N>
void _print(const T (&a)[N]) {
    cerr << "[";
    for (size_t i = 0; i < N; i++) {
        _print(a[i]);
        if (i + 1 < N) cerr << ", ";
    }
    cerr << "]";
}

// ================= VARIADIC DEBUG =================

void debug_out() { cerr << "\n"; }

template <typename T>
void debug_out(T &&a) {
    _print(forward<T>(a));
    cerr << "\n";
}

template <typename T, typename... Args>
void debug_out(T &&a, Args &&...args) {
    _print(forward<T>(a));
    cerr << "\n";
    debug_out(forward<Args>(args)...);
}

#define dbg(...) debug_out(__VA_ARGS__)

#endif // DEBUG
