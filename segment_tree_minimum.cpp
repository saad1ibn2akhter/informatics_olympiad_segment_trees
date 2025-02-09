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

int a[1000009], segment_tree[4000050];

void build(int node, int left, int right)
{
    if (left == right)
    {
        segment_tree[node] = a[left];
        return ;
    }
    int mid = (left + right) / 2;
    int left_child = 2 * node + 1;
    int right_child = 2 * node + 2;

    build(left_child, left, mid);
    build(right_child, mid + 1, right);

    segment_tree[node] = min(segment_tree[left_child], segment_tree[right_child]);
}

int query(int node, int left, int right, int target_left, int target_right)
{
    if (left >= target_left and right <= target_right)
    {
        return segment_tree[node];
    }
    if (left > target_right or right < target_left)
    {
        return INT_MAX;
    }

    int mid = (left + right) / 2;
    int leftSeg = query(2 * node + 1, left, mid, target_left, target_right);
    int rightSeg = query(2 * node + 2, mid + 1, right, target_left, target_right);

    return min(leftSeg, rightSeg);
}

void update(int node, int left, int right, int index, int value)
{
    if (left == right)
    {
        segment_tree[node] = value;
        return;
    }
    if (left > index || right < index)
    {
        return;
    }
    int mid = (left + right) / 2;
    int left_child = 2 * node + 1;
    int right_child = 2 * node + 2;
    update(left_child, left, mid, index, value);
    update(right_child, mid + 1, right, index, value);
    segment_tree[node] = min(segment_tree[left_child], segment_tree[right_child]);
}

void solve()
{
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    build(0, 0, n - 1);

    while (q--)
    {
        int opr;
        cin >> opr;
        if (opr == 1)
        {
            int in, val;
            cin >> in >> val;
            update(0, 0, n - 1, in, val);
        }
        else if (opr == 2)
        {
            int l, r;
            cin >> l >> r;
            cout << query(0, 0, n - 1, l-1, r-1) << endl;
        }
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