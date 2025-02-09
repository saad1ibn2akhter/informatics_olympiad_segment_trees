// Introduction to algorithm
// Author : Saad Ibn Akhter
// Date : 08/02/2025

#include <bits/stdc++.h>
using namespace std;
#define ll long long

vector<vector<int>> vis(10000, vector<int>(10000));

bool valid(int i, int j, int n, int m, vector<vector<char>> &vec)
{
    if (i >= 0 && i < n && j >= 0 && j < m && vis[i][j] == 0 && vec[i][j] == '.')
    {
        return true;
    }
    return false;
}

void dfs(int i, int j, int n, int m, vector<vector<char>> &vec, int &count)
{
    vis[i][j] = 1;
    count++;

    int di[4] = {0, 0, 1, -1};
    int dj[4] = {1, -1, 0, 0};

    for (int x = 0; x < 4; x++)
    {
        int row = i + di[x];
        int col = j + dj[x];

        if (valid(row, col, n, m, vec) && !vis[row][col])
        {
            dfs(row, col, n, m, vec, count);
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

    vector<int> counts;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (!vis[i][j] && vec[i][j] == '.')
            {
                int count = 0;
                dfs(i, j, n, m, vec, count);
                counts.push_back(count);
                // cout << count << " ";
            }
        }
    }

    // cout << count << endl;
    sort(counts.begin(), counts.end());
    int sum = 0;
    for (int i = 0; i < counts.size(); i++)
    {
        sum += counts[i];
    }
    if (sum == 0)
    {
        cout << 0 << endl;
        return;
    }
    for (int i = 0; i < counts.size(); i++)
    {
        cout << counts[i] << " ";
    }
    cout << endl;
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
