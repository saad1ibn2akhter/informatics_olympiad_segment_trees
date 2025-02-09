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

int a[1000005], seg[4 * 1000005];

void build(int index, int low, int high)
{
    if (low == high)
    {
        seg[index] = a[low];
        return;
    }

    int mid = (low + high) / 2;
    int a = 2 * index + 1;
    int b = 2 * index + 2;

    build(a, low, mid);
    build(b, mid + 1, high);

    seg[index] = (seg[a] + seg[b]);
}

int query(int index, int low, int high, int l, int r)
{
    if (low >= l && high <= r)
    {
        // completely inside the range
        return seg[index];
    }
    if (low > r || high < l)
    {
        return 0;
        // doesnt not lie in the range
    }

    // overlap
    int mid = (high + low) / 2;
    int left = query(2 * index + 1, low, mid, l, r);
    int right = query(2 * index + 2, mid + 1, high, l, r);

    return left + right;
}

void solve()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    build(0, 0, n - 1);

    int q;
    cin >> q;
    while (q--)
    {
        int l, r;
        cin >> l >> r;
        cout << query(0, 0, n - 1, l, r) << endl;
    }
}

int main()
{
    int t = 1;
    // cin >> t;
    while (t--)
    {
        solve();
    }
}