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

#define MAXN 100005
ll arr[MAXN], seg[4 * MAXN];

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

void build(int node, int start, int end)
{
    if (start == end)
    {
        seg[node] = arr[start];
    }
    else
    {
        int mid = (start + end) / 2;
        build(2 * node + 1, start, mid);
        build(2 * node + 2, mid + 1, end);
        seg[node] = seg[2 * node + 1] + seg[2 * node + 2];
    }
}

ll query(int node, int start, int end, int l, int r)
{
    if (r < start || end < l)
    {
        return 0;
    }
    if (l <= start && end <= r)
    {
        return seg[node];
    }
    int mid = (start + end) / 2;
    ll left_query = query(2 * node + 1, start, mid, l, r);
    ll right_query = query(2 * node + 2, mid + 1, end, l, r);
    return left_query + right_query;
}

void update(int node, int start, int end, int idx, ll val)
{
    if (start == end)
    {
        seg[node] = val;
    }
    else
    {
        int mid = (start + end) / 2;
        if (start <= idx && idx <= mid)
        {
            update(2 * node + 1, start, mid, idx, val);
        }
        else
        {
            update(2 * node + 2, mid + 1, end, idx, val);
        }
        seg[node] = seg[2 * node + 1] + seg[2 * node + 2];
    }
}

void solve()
{
    int n, q;
    cin >> n >> q;

    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    build(0, 0, n - 1);

    int case_num = 1;
    while (q--)
    {
        int ty;
        cin >> ty;

        if (ty == 1)
        {
            int i;
            cin >> i;
            cout << query(0, 0, n - 1, i - 1, i - 1) << endl;
            update(0, 0, n - 1, i - 1, 0);
        }
        else if (ty == 2)
        {
            int i, v;
            cin >> i >> v;
            update(0, 0, n - 1, i - 1, arr[i - 1] + v);
            arr[i - 1] += v;
        }
        else
        {
            int l, r;
            cin >> l >> r;
            cout << query(0, 0, n - 1, l - 1, r - 1) << endl;
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin >> T;

    for (int t = 1; t <= T; t++)
    {
        cout << "Case " << t << ":\n";
        solve();
    }

    return 0;
}
