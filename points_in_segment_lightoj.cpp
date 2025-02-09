#include <bits/stdc++.h>
using namespace std;

const int MAX_COORDINATE = 1e8; // Maximum value for coordinates
const int MAX_NODES = 200000;   // Adjust for coordinate compression

vector<int> compressedPoints;
map<int, int> compressMap;
int segmentTree[MAX_NODES * 4], lazy[MAX_NODES * 4];

void buildSegmentTree(int node, int leftBound, int rightBound)
{
    if (leftBound == rightBound)
    {
        segmentTree[node] = 0;
        lazy[node] = 0;
        return;
    }
    int middleIndex = (leftBound + rightBound) / 2;
    int leftChildIndex = 2 * node;
    int rightChildIndex = 2 * node + 1;

    buildSegmentTree(leftChildIndex, leftBound, middleIndex);
    buildSegmentTree(rightChildIndex, middleIndex + 1, rightBound);

    segmentTree[node] = 0;
    lazy[node] = 0;
}

// Lazy propagation for range updates
void updateSegmentTree(int node, int leftBound, int rightBound, int updateLeft, int updateRight, int value)
{
    if (lazy[node] != 0)
    {
        segmentTree[node] += lazy[node];
        if (leftBound != rightBound)
        {
            lazy[node * 2] += lazy[node];
            lazy[node * 2 + 1] += lazy[node];
        }
        lazy[node] = 0;
    }

    if (leftBound > updateRight || rightBound < updateLeft)
        return;

    if (leftBound >= updateLeft && rightBound <= updateRight)
    {
        segmentTree[node] += value;
        if (leftBound != rightBound)
        {
            lazy[node * 2] += value;
            lazy[node * 2 + 1] += value;
        }
        return;
    }

    int middleIndex = (leftBound + rightBound) / 2;
    updateSegmentTree(node * 2, leftBound, middleIndex, updateLeft, updateRight, value);
    updateSegmentTree(node * 2 + 1, middleIndex + 1, rightBound, updateLeft, updateRight, value);

    segmentTree[node] = max(segmentTree[node * 2], segmentTree[node * 2 + 1]);
}

// Query to find the count of segments containing a given point
int querySegmentTree(int node, int leftBound, int rightBound, int queryIndex)
{
    if (lazy[node] != 0)
    {
        segmentTree[node] += lazy[node];
        if (leftBound != rightBound)
        {
            lazy[node * 2] += lazy[node];
            lazy[node * 2 + 1] += lazy[node];
        }
        lazy[node] = 0;
    }

    if (leftBound == rightBound)
        return segmentTree[node];

    int middleIndex = (leftBound + rightBound) / 2;
    if (queryIndex <= middleIndex)
        return querySegmentTree(node * 2, leftBound, middleIndex, queryIndex);
    else
        return querySegmentTree(node * 2 + 1, middleIndex + 1, rightBound, queryIndex);
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int testCases;
    cin >> testCases;
    for (int testCase = 1; testCase <= testCases; testCase++)
    {
        int numberOfSegments, numberOfQueries;
        cin >> numberOfSegments >> numberOfQueries;

        vector<pair<int, int>> segments;
        vector<int> queryPoints;

        compressedPoints.clear();
        compressMap.clear();

        // Read input and prepare for coordinate compression
        for (int i = 0; i < numberOfSegments; i++)
        {
            int left, right;
            cin >> left >> right;
            segments.emplace_back(left, right);
            compressedPoints.push_back(left);
            compressedPoints.push_back(right);
        }

        for (int i = 0; i < numberOfQueries; i++)
        {
            int query;
            cin >> query;
            queryPoints.push_back(query);
            compressedPoints.push_back(query);
        }

        // Coordinate Compression
        sort(compressedPoints.begin(), compressedPoints.end());
        compressedPoints.erase(unique(compressedPoints.begin(), compressedPoints.end()), compressedPoints.end());

        for (int i = 0; i < compressedPoints.size(); i++)
        {
            compressMap[compressedPoints[i]] = i + 1;
        }

        int compressedSize = compressedPoints.size();
        buildSegmentTree(1, 1, compressedSize);

        // Mark segment start and end in the segment tree
        for (auto &[left, right] : segments)
        {
            int compressedLeft = compressMap[left];
            int compressedRight = compressMap[right];
            updateSegmentTree(1, 1, compressedSize, compressedLeft, compressedRight, 1);
        }

        cout << "Case " << testCase << ":\n";
        for (int point : queryPoints)
        {
            int compressedIndex = compressMap[point];
            cout << querySegmentTree(1, 1, compressedSize, compressedIndex) << '\n';
        }
    }
    return 0;
}
