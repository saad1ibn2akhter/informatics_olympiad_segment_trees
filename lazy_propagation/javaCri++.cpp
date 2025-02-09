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

const int N = 1e5 + 9;
int amounts[N];
int tree[N * 4];

void buildSegmentTree(int node, int start, int end)
{
    if (start == end)
    {
        tree[node] = amounts[start];
        return;
    }
    int mid = (start + end) / 2;
    int leftChild = 2 * node;
    int rightChild = 2 * node + 1;
    buildSegmentTree(leftChild, start, mid);
    buildSegmentTree(rightChild, mid + 1, end);
    tree[node] = tree[leftChild] + tree[rightChild];
}

void updateSackToZero(int node, int start, int end, int index)
{
    if (index < start || end < index)
        return;
    if (start == end)
    {
        tree[node] = 0;
        return;
    }
    int mid = (start + end) / 2;
    int leftChild = 2 * node;
    int rightChild = 2 * node + 1;
    updateSackToZero(leftChild, start, mid, index);
    updateSackToZero(rightChild, mid + 1, end, index);
    tree[node] = tree[leftChild] + tree[rightChild];
}

void addMoneyToSack(int node, int start, int end, int index, int value)
{
    if (index < start || end < index)
        return;
    if (start == end)
    {
        tree[node] += value;
        return;
    }
    int mid = (start + end) / 2;
    int leftChild = 2 * node;
    int rightChild = 2 * node + 1;
    addMoneyToSack(leftChild, start, mid, index, value);
    addMoneyToSack(rightChild, mid + 1, end, index, value);
    tree[node] = tree[leftChild] + tree[rightChild];
}

int queryTotalMoney(int node, int start, int end, int left, int right)
{
    if (end < left || right < start)
        return 0;
    if (start >= left && end <= right)
    {
        return tree[node];
    }
    int mid = (start + end) / 2;
    int leftChild = 2 * node;
    int rightChild = 2 * node + 1;
    return queryTotalMoney(leftChild, start, mid, left, right) + queryTotalMoney(rightChild, mid + 1, end, left, right);
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int testCases, caseNumber = 0;
    cin >> testCases;
    while (testCases--)
    {
        int sacks, queries;
        cin >> sacks >> queries;
        for (int i = 1; i <= sacks; i++)
        {
            cin >> amounts[i];
        }
        buildSegmentTree(1, 1, sacks);
        cout << "Case " << ++caseNumber << ":\n";
        while (queries--)
        {
            int queryType;
            cin >> queryType;
            if (queryType == 1)
            {
                int sackIndex;
                cin >> sackIndex;
                sackIndex++;
                cout << queryTotalMoney(1, 1, sacks, sackIndex, sackIndex) << '\n';
                updateSackToZero(1, 1, sacks, sackIndex);
            }
            else if (queryType == 2)
            {
                int sackIndex, moneyToAdd;
                cin >> sackIndex >> moneyToAdd;
                sackIndex++;
                addMoneyToSack(1, 1, sacks, sackIndex, moneyToAdd);
            }
            else
            {
                int leftIndex, rightIndex;
                cin >> leftIndex >> rightIndex;
                leftIndex++;
                rightIndex++;
                int totalMoney = queryTotalMoney(1, 1, sacks, leftIndex, rightIndex);
                cout << totalMoney << '\n';
            }
        }
    }
    return 0;
}
