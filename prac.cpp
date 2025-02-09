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

int a[1005], st[4 * 1005];

void build(int node, int left, int right)
{
    if (left == right)
    {
        st[node] = a[left]; // leaf node
        return;
    }
    int mid = (left + right) / 2;
    int leftNode = 2 * node + 1;
    int rightNode = 2 * node + 2;

    build(leftNode, left, mid);
    build(rightNode, mid + 1, right);

    st[node] = st[leftNode] + st[rightNode]; // summing up the ans;
}

int query(int node, int left, int right, int t_left, int t_right)
{
    if (left > t_right || right < t_left)
    {
        // nowhere near the range
        return 0;
    }
    if (left >= t_left && right <= t_right)
    {
        return st[node];
    }

    int mid = (left + right) / 2;
    int leftNode = 2 * node + 1;
    int rightNode = 2 * node + 2;

    // query(leftNode , left , mid , t_left , t_right)
    // query(rightNode , mid + 1 , right , t_left , t_right)

    return query(leftNode, left, mid, t_left, t_right) + query(rightNode, mid + 1, right, t_left, t_right);
}

void update(int node, int left, int right, int index, int value)
{
    if (left > index || right < index)
    {
        return;
    }
    if (left == right)
    {
        st[node] = value;
    }

    int mid = (left + right) / 2;
    int leftNode = 2 * node + 1;
    int rightNode = 2 * node + 2;

    update(leftNode, left, mid, index, value);
    update(rightNode, mid + 1, right, index, value);

    st[node] = st[leftNode] + st[rightNode];
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
        int l, r;
        cin >> l >> r;
        cout << query(0, 0, n - 1, l - 1, r - 1) << endl;
        // update(0, 0, n - 1,4, 10000);
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