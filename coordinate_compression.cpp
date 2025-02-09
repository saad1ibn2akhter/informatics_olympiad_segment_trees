#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define endl "\n"
#define pb push_back
#define ppb pop_back
#define pf push_front
#define ppf pop_front
#define all(x) (x).begin(), (x).end()
#define fr(a, b) for (ll i = a; i < b; i++)
#define uniq(v) (v).erase(unique((v).begin(), (v).end()))

void setIO(string name = "")
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    if (name.size())
    {
        freopen((name + ".in").c_str(), "r", stdin);
        freopen((name + ".out").c_str(), "w", stdout);
    }
}

void solve()
{
    vector<int> values = {100, 500, 2000, 100, 300};
    vector<int> ordered_values = values;
    sort(ordered_values.begin(), ordered_values.end());
    ordered_values.erase(unique(ordered_values.begin(), ordered_values.end()), ordered_values.end());

    unordered_map<int, int> compressed_map;

    for (int i = 0; i < ordered_values.size(); i++)
    {
        compressed_map[ordered_values[i]] = i;
    }
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
}