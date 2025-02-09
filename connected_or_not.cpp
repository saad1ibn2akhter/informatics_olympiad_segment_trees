// Introduction to algorithm
// Author : Saad Ibn Akhter
// Date : 08/02/2025

#include <bits/stdc++.h>
using namespace std;
#define ll long long

bool vis[10005];
vector<int> adj[10005];

void dfs(int node, int target_node, bool &found)
{
    vis[node] = true;
    if (node == target_node)
    {
        found = true;
    }
    for (auto u : adj[node])
    {
        if (!vis[u] && !found)
        {
            dfs(u, target_node, found);
        }
    }
}

void solve()
{
    int n, e;
    cin >> n >> e;

    for (int i = 0; i < e; i++)
    {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
    }

    int q;
    cin >> q;

    while (q--)
    {
        int a, b;
        cin >> a >> b;

        memset(vis, false, sizeof(vis));

        bool found = false;
        dfs(a, b, found);

        if (found)
        {
            cout << "YES" << endl;
        }
        else
        {
            cout << "NO" << endl;
        }
    }
}

int main()
{
    int t = 1;
    while (t--)
    {
        solve();
    }
}
