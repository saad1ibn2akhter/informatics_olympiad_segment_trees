// Introduction to algorithm
// Author : Saad Ibn Akhter
// Date : 08/02/2025
#include <bits/stdc++.h>
using namespace std;

int main()
{
    int nodes, edges;
    cin >> nodes >> edges;

    set<pair<int, int>> edgeSet;

    for (int i = 0; i < edges; ++i)
    {
        int u, v;
        cin >> u >> v;
        edgeSet.insert({u, v});
    }

    int q;
    cin >> q;

    while (q--)
    {
        int u, v;
        cin >> u >> v;

        if (u == v || edgeSet.count({u, v}))
        {
            cout << "YES" << endl;
        }
        else
        {
            cout << "NO" << endl;
        }
    }

    return 0;
}