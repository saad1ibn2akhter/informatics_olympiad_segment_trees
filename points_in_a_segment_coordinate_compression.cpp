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

#define FASTIO                   \
    ios::sync_with_stdio(false); \
    cin.tie(0);
#define MAXN 150000 // Max compressed index size

vector<int> coords;               // Stores unique, sorted coordinates
unordered_map<int, int> compress; // Maps original values to compressed indices
int segmentTree[4 * MAXN];        // Segment tree for range updates

// **Step 1: Build Segment Tree**
void build(int node, int left, int right)
{
    segmentTree[node] = 0;
    if (left == right)
        return;
    int mid = (left + right) / 2;
    build(2 * node, left, mid);
    build(2 * node + 1, mid + 1, right);
}

// **Step 2: Update the segment tree in range [uleft, uright]**
void update(int node, int left, int right, int uleft, int uright, int value)
{
    if (uleft > right || uright < left)
        return; // No overlap
    if (uleft <= left && right <= uright)
    { // Full overlap
        segmentTree[node] += value;
        return;
    }
    int mid = (left + right) / 2;
    update(2 * node, left, mid, uleft, uright, value);
    update(2 * node + 1, mid + 1, right, uleft, uright, value);
}

// **Step 3: Query the segment tree to find segment count at `pos`**
int query(int node, int left, int right, int pos)
{
    if (pos < left || pos > right)
        return 0; // Out of range
    if (left == right)
        return segmentTree[node]; // Leaf node
    int mid = (left + right) / 2;
    return segmentTree[node] + query(2 * node, left, mid, pos) + query(2 * node + 1, mid + 1, right, pos);
}

int main()
{
    FASTIO;
    int T;
    cin >> T;

    for (int tc = 1; tc <= T; tc++)
    {
        int n, q;
        cin >> n >> q;

        vector<pair<int, int>> segments(n);
        vector<int> points(q);
        coords.clear();
        compress.clear();
        memset(segmentTree, 0, sizeof(segmentTree));

        // Read segments and collect coordinates
        for (int i = 0; i < n; i++)
        {
            cin >> segments[i].first >> segments[i].second;
            coords.push_back(segments[i].first);
            coords.push_back(segments[i].second);
        }

        // Read query points and collect coordinates
        for (int i = 0; i < q; i++)
        {
            cin >> points[i];
            coords.push_back(points[i]);
        }

        // **Step 1: Coordinate Compression**
        sort(coords.begin(), coords.end());
        coords.erase(unique(coords.begin(), coords.end()), coords.end());
        for (int i = 0; i < coords.size(); i++)
        {
            compress[coords[i]] = i + 1; // 1-based index for segment tree
        }
        int maxIdx = coords.size();

        // **Step 2: Build Segment Tree**
        build(1, 1, maxIdx);

        // **Step 3: Construct Difference Array Using Segment Tree**
        for (auto &seg : segments)
        {
            int start = compress[seg.first];
            int end = compress[seg.second];
            update(1, 1, maxIdx, start, end, 1); // Mark start+1, end+1
        }

        // **Step 4: Answer Queries**
        cout << "Case " << tc << ":\n";
        for (int p : points)
        {
            int idx = compress[p];
            cout << query(1, 1, maxIdx, idx) << "\n";
        }
    }

    return 0;
}
