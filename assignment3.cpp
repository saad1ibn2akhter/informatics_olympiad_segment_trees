// Introduction to algorithm
// Author : Saad Ibn Akhter
// Date : 08/02/2025

#include <bits/stdc++.h>
using namespace std;
#define ll long long

vector<vector<int>> vis(10000, vector<int>(10000));

bool valid(int i, int j, int n, int m, vector<vector<char>> &vec)
{
    if (i >= 0 && i < n && j >= 0 && j < m && vis[i][j] == 0)
    {
        return true;
    }
    return false;
}

void dfs(int i, int j, int n, int m, vector<vector<char>> &vec)
{
    vis[i][j] = 1;

    int di[4] = {0, 0, 1, -1};
    int dj[4] = {1, -1, 0, 0};

    for (int x = 0; x < 4; x++)
    {
        int row = i + di[x];
        int col = j + dj[x];

        if (valid(row, col, n, m, vec) && !vis[row][col] && vec[row][col] != '#')
        {
            dfs(row, col, n, m, vec);
        }
    }
}

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<vector<char>> vec(n, vector<char>(m));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> vec[i][j];
        }
    }

    fill(vis.begin(), vis.begin() + n, vector<int>(m, 0));

    int srow, scol, erow, ecol;

    vector<int> counts;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (vec[i][j] == 'A')
            {
                srow = i;
                scol = j;
            }
            if (vec[i][j] == 'B')
            {
                erow = i;
                ecol = j;
            }
        }
    }

    // for (int i = srow; i < n; i++)
    // {
    //     for (int j = scol; j < m; j++)
    //     {
    //         if (vec[i][j] != '#' && vis[i][j] == 0)
    //         {
    //             dfs(i, j, n, m, vec);
    //         }
    //     }
    // }

    dfs(srow, scol, n, m, vec);

    if (vis[erow][ecol] == 1)
    {
        cout << "YES" << endl;
    }
    else
    {
        cout << "NO" << endl;
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
