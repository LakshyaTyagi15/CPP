#ifndef DEBUG
#define DEBUG

#include <bits/stdc++.h>
using namespace std;

// ----------------------- Traits -----------------------
namespace detail {

    // is_iterable: has begin/end
    template <typename T, typename = void>
    struct is_iterable : false_type {};

    template <typename T>
    struct is_iterable<T, void_t<decltype(begin(declval<T>())), decltype(end(declval<T>()))>> : true_type {};

    template <typename T>
    constexpr bool is_iterable_v = is_iterable<T>::value;

    // is_std_string: treat std::string and string_view specially
    template <typename T> struct is_std_string : false_type {};
    template <> struct is_std_string<string> : true_type {};
    template <> struct is_std_string<string_view> : true_type {};
    template <typename T> constexpr bool is_std_string_v = is_std_string<decay_t<T>>::value;

    // has_value_type
    template <typename T, typename = void>
    struct has_value_type : false_type {};
    template <typename T>
    struct has_value_type<T, void_t<typename T::value_type>> : true_type {};
    template <typename T> constexpr bool has_value_type_v = has_value_type<T>::value;

    // is_pair
    template <typename T> struct is_pair : false_type {};
    template <typename A, typename B> struct is_pair<pair<A,B>> : true_type {};
    template <typename T> constexpr bool is_pair_v = is_pair<decay_t<T>>::value;

    // is_tuple
    template <typename T> struct is_tuple : false_type {};
    template <typename... Ts> struct is_tuple<tuple<Ts...>> : true_type {};
    template <typename T> constexpr bool is_tuple_v = is_tuple<decay_t<T>>::value;

} // namespace detail

// ----------------------- Forward Declarations -----------------------
// Forward declare iterable printer
template <typename T>
enable_if_t<detail::is_iterable_v<T> && !detail::is_std_string_v<T> && !detail::is_pair_v<T>, void>
_print(const T &container);

// Forward declare pair printer
template <typename A, typename B>
void _print(const pair<A,B> &p);

// Forward declare tuple printer
template <typename... Args>
void _print(const tuple<Args...> &t);


// ----------------------- Declarations -----------------------
// We avoid an unconstrained template declaration; each overload is constrained.


// ----------------------- Simple / fundamental types -----------------------
inline void _print(const char &c) { cerr << '\'' << c << '\''; }
inline void _print(const char *s) { if (s) cerr << '"' << s << '"'; else cerr << "null"; }
inline void _print(const string &s) { cerr << '"' << s << '"'; }
inline void _print(const string_view &s) { cerr << '"' << s << '"'; }
inline void _print(const bool &b) { cerr << (b ? "true" : "false"); }

template <typename T, typename = enable_if_t<is_arithmetic<T>::value && !is_same<T,char>::value>>
void _print(const T &x) { cerr << x; }

template <typename T> void _print(const complex<T> &c) { cerr << c.real() << "+" << c.imag() << "i"; }
template <size_t N> void _print(const bitset<N> &b) { cerr << b; }

// optional
template <typename T> void _print(const optional<T> &opt) {
    if (opt.has_value()) { cerr << "Some("; _print(opt.value()); cerr << ")"; }
    else cerr << "None";
}

// ----------------------- pair & tuple -----------------------
template <typename A, typename B>
void _print(const pair<A,B> &p) {
    cerr << "{"; _print(p.first); cerr << ", "; _print(p.second); cerr << "}";
}

namespace tuple_impl {
    template <class Tuple, size_t... I>
    void print_tuple(const Tuple &t, index_sequence<I...>) {
        (( _print(get<I>(t)), cerr << (I + 1 < sizeof...(I) ? ", " : "") ), ...);
    }
}

template <typename... Args>
void _print(const tuple<Args...> &t) {
    cerr << "(";
    tuple_impl::print_tuple(t, index_sequence_for<Args...>{});
    cerr << ")";
}




// ---------- Helper for runtime-sized arrays (VLAs or new[] / pointer) ----------
// Use this when the array length is known only at runtime. Call like:
//    dbg_array(adj, n);
// where adj is either `vector<T>*` (pointer) or array decayed to pointer.
template <typename ContainerT>
void dbg_array(ContainerT* arr, size_t n) {
    // Convert the pointer-range into a vector<ContainerT>
    vector<ContainerT> tmp;
    tmp.reserve(n);
    for (size_t i = 0; i < n; ++i) tmp.push_back(arr[i]);
    debug_out(move(tmp)); // forward the newly-built vector for printing
}




// ----------------------- Generic iterable (single overload) -----------------------
// Handles vector<...>, set<...>, map<...>, array<...>, deque<...>, list<...>, etc.
// Excludes string/string_view and pair to avoid ambiguity.
template <typename T>
enable_if_t<detail::is_iterable_v<T> && !detail::is_std_string_v<T> && !detail::is_pair_v<T>, void>
_print(const T &container) {
    // If the container's value_type is itself iterable (and not a string), print multi-line for readability.
    if constexpr (detail::has_value_type_v<T> && detail::is_iterable_v<typename T::value_type> && !detail::is_std_string_v<typename T::value_type>) {
        cerr << "[\n";
        for (const auto &row : container) {
            cerr << " ";
            _print(row);
            cerr << "\n";
        }
        cerr << "]";
    } else {
        bool first = true;
        cerr << "[";
        for (const auto &x : container) {
            if (!first) cerr << " ";
            _print(x);
            first = false;
        }
        cerr << "]";
    }
}

// ----------------------- STL adapters without iterators -----------------------
template <typename T>
void _print(stack<T> s) {
    cerr << "[";
    bool first = true;
    while (!s.empty()) {
        if (!first) cerr << " ";
        _print(s.top());
        s.pop();
        first = false;
    }
    cerr << "]";
}

template <typename T>
void _print(queue<T> q) {
    cerr << "[";
    bool first = true;
    while (!q.empty()) {
        if (!first) cerr << " ";
        _print(q.front());
        q.pop();
        first = false;
    }
    cerr << "]";
}

template <typename T, typename Container, typename Compare>
void _print(priority_queue<T, Container, Compare> pq) {
    cerr << "[";
    bool first = true;
    while (!pq.empty()) {
        if (!first) cerr << " ";
        _print(pq.top());
        pq.pop();
        first = false;
    }
    cerr << "]";
}

// ----------------------- Fallback for user types that support operator<< -----------------------
// Only enabled when none of the above apply (not iterable, not arithmetic, not pair/tuple, not string)
template <typename T>
enable_if_t<!detail::is_iterable_v<T> && !is_arithmetic<T>::value && !detail::is_pair_v<T> && !detail::is_tuple_v<T> && !detail::is_std_string_v<T>,void>
_print(const T &x) {
    // Attempt operator<< as last resort. If the type doesn't support it, you'll get a compile error
    cerr << x;
}


// ---------- Manual overloads for C-style arrays of containers ----------
// Put these after the existing C-style array printer in your header.

// 1) Compile-time C-style array of std::vector<T>
// Handles: vector<T> adj[N];
template <typename T, size_t N>
void _print(vector<T> (&a)[N]) {
    cerr << "[\n";
    for (size_t i = 0; i < N; ++i) {
        cerr << " ";
        _print(a[i]);         // uses vector<T> printer for each element
        if (i + 1 < N) cerr << "\n";
    }
    cerr << "\n]";
}

// 2) Compile-time C-style array of std::set<T>
// Handles: set<T> adj[N];
template <typename T, size_t N>
void _print(set<T> (&a)[N]) {
    cerr << "[\n";
    for (size_t i = 0; i < N; ++i) {
        cerr << " ";
        _print(a[i]);         // uses generic iterable printer for each set
        if (i + 1 < N) cerr << "\n";
    }
    cerr << "\n]";
}

// 3) Compile-time C-style array of std::vector<std::vector<T>>
// (This is redundant because vector<T> overload covers it, but provided explicitly.)
template <typename T, size_t N>
void _print(vector<vector<T>> (&a)[N]) {
    cerr << "[\n";
    for (size_t i = 0; i < N; ++i) {
        cerr << " ";
        _print(a[i]);         // nested vector-of-vectors printing
        if (i + 1 < N) cerr << "\n";
    }
    cerr << "\n]";
}


// ----------------------- C-style array -----------------------
template <typename T, size_t N>
void _print(T (&a)[N]) {
    cerr << "[";
    for (size_t i = 0; i < N; ++i) {
        _print(a[i]);
        if (i + 1 < N) cerr << ", ";
    }
    cerr << "]";
}





// ----------------------- variadic debug -----------------------
void debug_out() { cerr << "\n"; }

template <typename T>
void debug_out(T &&a) {
    _print(forward<T>(a));
    cerr << "\n";
}

template <typename T, typename... Args>
void debug_out(T &&a, Args &&...args) {
    _print(forward<T>(a));
    cerr << ", ";
    debug_out(forward<Args>(args)...);
}

#define dbg(...) cerr << #__VA_ARGS__ << ":- "; debug_out(__VA_ARGS__)

#endif // DEBUG
