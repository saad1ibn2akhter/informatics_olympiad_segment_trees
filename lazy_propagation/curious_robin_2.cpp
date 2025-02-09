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

int a[1000001], *seg;

void build(int node, int left, int right)
{
    if (left == right)
    {
        seg[node] = a[left];
        return;
    }
    int mid = (left + right) / 2;
    build(2 * node + 1, left, mid);
    build(2 * node + 2, mid + 1, right);
    seg[node] = seg[2 * node + 1] + seg[2 * node + 2];
}

void give_money(int node, int left, int right, int index)
{
    if (index < left || right < index)
    {
        return;
    }

    if (left == right)
    {
        cout << seg[node] << endl;
        seg[node] = 0;
        return;
    }

    int mid = (left + right) / 2;
    give_money(2 * node + 1, left, mid, index);
    give_money(2 * node + 2, mid + 1, right, index);
    seg[node] = seg[2 * node + 1] + seg[2 * node + 2];
}

int query(int node, int left, int right, int l, int r)
{
    if (left > r || right < l)
    {
        return 0;
    }
    if (l <= left && right <= r)
    {
        return seg[node];
    }

    int mid = (left + right) / 2;
    int left_sum = query(2 * node + 1, left, mid, l, r);
    int right_sum = query(2 * node + 2, mid + 1, right, l, r);
    return left_sum + right_sum;
}

void update(int node, int left, int right, int index, int money)
{
    if (index < left || right < index)
    {
        return;
    }
    if (left == right)
    {
        seg[node] = money;
        return;
    }
    int mid = (left + right) / 2;
    update(2 * node + 1, left, mid, index, money);
    update(2 * node + 2, mid + 1, right, index, money);
    seg[node] = seg[2 * node + 1] + seg[2 * node + 2];
}

void solve()
{
    int n, q;
    cin >> n >> q;

    // Dynamically allocate memory for the segment tree
    seg = new int[4 * n];  // Allocate enough space for the segment tree

    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    build(0, 0, n - 1);

    while (q--)
    {
        int type;
        cin >> type;
        if (type == 1)
        {
            int index;
            cin >> index;
            // index--;  // Convert to 0-based index
            cout << query(0, 0, n - 1, index, index) << endl;
            give_money(0, 0, n - 1, index);
        }
        else if (type == 2)
        {
            int index, money;
            cin >> index >> money;
            // index--;  // Convert to 0-based index
            update(0, 0, n - 1, index, money);
        }
        else
        {
            int l, r;
            cin >> l >> r;
            // l--; r--;  // Convert to 0-based indices
            cout << query(0, 0, n - 1, l, r) << endl;
        }
    }

    delete[] seg;  // Free allocated memory after use
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
