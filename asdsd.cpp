// Introduction to Algorithms
// Author : Saad Ibn Akhter
// Date : 08/02/2025

#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;

    vector<int> adj[n];

    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int q;
    cin >> q;

    while (q--)
    {
        int node;
        cin >> node;

        if (adj[node].empty())
        {
            cout << -1 << endl;
        }
        else
        {

            sort(adj[node].rbegin(), adj[node].rend());

            for (int i : adj[node])
            {
                cout << i << " ";
            }
            cout << endl;
        }
    }

    return 0;
}
