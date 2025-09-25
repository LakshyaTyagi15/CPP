import sublime, sublime_plugin
from datetime import datetime, timezone, timedelta

class InsertCppmainCommand(sublime_plugin.TextCommand):
    def run(self, edit):
        # Asia/Kolkata (UTC+05:30)
        ist_now = datetime.now(timezone(timedelta(hours=5, minutes=30)))
        stamp = ist_now.strftime("%Y-%m-%d %H:%M:%S")

        tpl = """/*
	Author: Lakshya Tyagi
	Created on: {stamp} IST
*/

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#ifdef LOCAL
#include <debug.h>
#else
#define dbg(x...)
#endif

using namespace std;
using namespace __gnu_pbds;

template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

using ll = long long;
const ll mod = 1e9 + 7;
const ll modd = 998244353;

void solve()
{{
    
}}

int main()
{{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t = 1;
    cin >> t;
    
    for (int i = 1; i <= t; i++) {{
    	cerr << "Testcase No. - " << i << "\\n";
    	solve();	
    }}

    return 0;
}}
""".format(stamp=stamp)

        self.view.run_command("insert_snippet", {"contents": tpl})
