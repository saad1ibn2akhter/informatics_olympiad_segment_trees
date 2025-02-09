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

int a[1000000], seg[4000000], lazy[4000000];

void build(int node, int left, int right)
{
    if (left == right)
    {
        seg[node] = a[left];
        return;
    }

    int mid = (left + right) / 2;

    int leftChild = node * 2 + 1;
    int rightChild = node * 2 + 2;

    build(leftChild, left, mid);
    build(rightChild, mid + 1, right);

    seg[node] = seg[leftChild] + seg[rightChild];
}

void push(int node, int left, int right)
{
    if (lazy[node] != 0)
    {
        seg[node] = lazy[node] * (right - left + 1);
        if (left != right)
        {
            lazy[node * 2 + 1] += lazy[node];
            lazy[node * 2 + 2] += lazy[node];
        }

        lazy[node] = 0;
    }
}

int query(int node, int left, int right, int l, int r)
{
    push(node, left, right);

    if (l > right || r < left)
        return 0; // No overlap
    if (l <= left && right <= r)
        return seg[node]; // Complete overlap
    int mid = (left + right) / 2;
    int leftChild = node * 2 + 1;
    int rightChild = node * 2 + 2;
    int p1 = query(leftChild, left, mid, l, r);
    int p2 = query(rightChild, mid + 1, right, l, r);
    return p1 + p2;
}

void update(int node, int left, int right, int l, int r, int val)
{
    push(node, left, right);
    if (l > right || r < left)
        return;
    if (l <= left && right <= r)
    {
        lazy[node] += val;
        push(node, left, right);
        return;
    }
    int mid = (left + right) / 2;
    update(node * 2 + 1, left, mid, l, r, val);
    update(node * 2 + 2, mid + 1, right, l, r, val);
    seg[node] = seg[node * 2 + 1] + seg[node * 2 + 2];
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
        int type;
        cin >> type;

        if (type == 1)
        {
            int l, r, value;
            cin >> l >> r >> value;
            update(0, 0, n - 1, l, r, value);
        }
        else
        {
            int l, r;
            cin >> l >> r;
            cout << query(0, 0, n - 1, l, r) << endl;
        }
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
