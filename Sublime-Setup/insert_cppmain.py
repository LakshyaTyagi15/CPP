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

#ifdef LOCAL
#include <debug.h>
#else
#define dbg(x...)
#endif

using namespace std;

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
#ifdef LOCAL
    	cerr << "Testcase No. - " << i << "\\n";
#endif
    	solve();	
    }}

    return 0;
}}
""".format(stamp=stamp)

        self.view.run_command("insert_snippet", {"contents": tpl})
