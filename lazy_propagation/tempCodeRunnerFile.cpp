e <bits/stdc++.h>
// using namespace std;
// #define ll long long
// #define endl "\n"

// int a[1000000], seg[4000000];

// void build(int node, int left, int right)
// {
//     if (left == right)
//     {
//         seg[node] = a[left];
//         return;
//     }
//     int mid = (left + right) / 2;
//     int leftChild = node * 2 + 1;
//     int rightChild = node * 2 + 2;
//     build(leftChild, left, mid);
//     build(rightChild, mid + 1, right);
//     seg[node] = seg[leftChild] + seg[rightChild];
// }

// int query(int node, int left, int right, int l, int r)
// {
//     if (l > right || r < left)
//         return 0; // No overlap
//     if (l <= left && right <= r)
//         return seg[node]; // Complete overlap
//     int mid = (left + right) / 2;
//     int leftChild = node * 2 + 1;
//     int rightChild = node * 2 + 2;
//     int p1 = query(leftChild, left, mid, l, r);
//     int p2 = query(rightChild, mid + 1, right, l, r);
//     return p1 + p2;
// }

// void solve()
// {
//     int n;
//     cin >> n;
//     for (int i = 0; i < n; i++)
//         cin >> a[i];
//     build(0, 0, n - 1);
//     int q;
//     cin >> q;
//     while (q--)
//     {
//         int l, r;
//         cin >> l >> r;
//         cout << query(0, 0, n - 1, l, r) << endl;
//     }
// }

// int main()
// {
//     int t;
//     cin >> t;
//     while (t--)
//         solve();
// }
