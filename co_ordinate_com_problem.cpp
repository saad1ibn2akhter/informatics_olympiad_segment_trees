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
vector<int> coords;
unordered_map<int, int> compressed;

int segTree[4 * 600005];

void build(int node, int left, int right)
{
    segTree[node] = 0;
    if (left == right)
    {
        return;
    }
    int mid = (left + right) / 2;
    int leftChild = 2 * node, rightChild = 2 * node + 1;
    build(leftChild, left, mid);
    build(rightChild, mid + 1, right);
}

void update(int node, int left, int right, int uleft, int uright, int val)
{
    if (uleft > right || uright < left)
        return; // No overlap
    if (uleft <= left && right <= uright)
    {
        // Full overlap
        segTree[node] += val;
        return;
    }

    int mid = (left + right) / 2;
    update(2 * node, left, mid, uleft, uright, val);
    update(2 * node + 1, mid + 1, right, uleft, uright, val);
}
int query(int node, int left, int right, int idx)
{
    if (left == right)
    {
        return segTree[node];
    }
    int mid = (left + right) / 2;

    if (idx <= mid)
    {
        return segTree[node] + query(2 * node, left, mid, idx);
    }
    else
    {
        return segTree[node] + query(2 * node + 1, mid + 1, right, idx);
    }
}

void solve()
{
    int n, q;
    cin >> n >> q;
    vector<int> points(q);
    vector<pair<int, int>> segments(n);
    for (int i = 0; i < n; i++)
    {
        cin >> segments[i].first;
        cin >> segments[i].second;
        coords.pb(segments[i].first);
        coords.pb(segments[i].second);
    }

    for (int i = 0; i < q; i++)
    {
        cin >> points[i];
        coords.pb(points[i]);
    }
    sort(all(coords));
    coords.erase(unique(all(coords)), coords.end());

    for (int i = 0; i < coords.size(); i++)
    {
        compressed[coords[i]] = i + 1;
    }
    int maxIdx = coords.size();

    build(1, 1, maxIdx);

    for (auto &seg : segments)
    {
        int start = compressed[seg.first];
        int end = compressed[seg.second];

        update(1, 1, maxIdx, start, end, 1);
    }

    for (int p : points)
    {
        int idx = compressed[p];
        cout << query(1, 1, maxIdx, idx) << endl;
    }
}

int main()
{
    int t;
    cin >> t;
    int tc = 0;
    while (t--)
    {
        cout << "Case " << ++tc << ":" << endl;
        solve();
    }
}