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

vector<ll> a, seg;

void build(int node, int low, int high)
{
    if (low == high)
    {
        seg[node] = a[low];
        return;
    }
    int mid = (low + high) / 2;
    int left = node * 2 + 1;
    int right = node * 2 + 2;
    build(left, low, mid);
    build(right, mid + 1, high);
    seg[node] = seg[left] + seg[right];
}

ll query(int node, int low, int high, int l, int r)
{
    if (low >= l and high <= r)
    {
        return seg[node];
    }
    if (low > r or high < l)
    {
        return 0;
    }
    int mid = (low + high) / 2;
    int left = (node * 2) + 1;
    int right = (node * 2) + 2;
    ll leftSum = query(left, low, mid, l, r);
    ll rightSum = query(right, mid + 1, high, l, r);

    return leftSum + rightSum;
}

void solve()
{
    int n, q;
    cin >> n >> q;
    a.resize(n);
    seg.resize(4 * n); 

    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    build(0, 0, n - 1);

    while (q--)
    {
        int l, r;
        cin >> l >> r;
        cout << query(0, 0, n - 1, l - 1, r - 1) << endl;
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
