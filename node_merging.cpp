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
const int N = 1e5 + 9, INF = 1e9 + 9;
int inputArray[N];

struct SegmentTreeNode
{
    int minimumValue;
    int frequencyCount;
};

SegmentTreeNode segmentTree[N * 4];

// Function to merge two segment tree nodes and return the combined result
SegmentTreeNode mergeSegmentTreeNodes(SegmentTreeNode leftSegmentNode, SegmentTreeNode rightSegmentNode)
{
    SegmentTreeNode mergedSegmentNode; // merged seg node declared with custom data type
    mergedSegmentNode.minimumValue = min(leftSegmentNode.minimumValue, rightSegmentNode.minimumValue);
    mergedSegmentNode.frequencyCount = 0;

    if (leftSegmentNode.minimumValue == mergedSegmentNode.minimumValue)
    {
        mergedSegmentNode.frequencyCount += leftSegmentNode.frequencyCount;
    }
    if (rightSegmentNode.minimumValue == mergedSegmentNode.minimumValue)
    {
        mergedSegmentNode.frequencyCount += rightSegmentNode.frequencyCount;
    }
    return mergedSegmentNode;
}

// Function to build the segment tree
void buildSegmentTree(int nodeIndex, int leftBound, int rightBound)
{
    if (leftBound == rightBound)
    {
        segmentTree[nodeIndex].minimumValue = inputArray[leftBound];
        segmentTree[nodeIndex].frequencyCount = 1;
        return;
    }
    int middleIndex = (leftBound + rightBound) / 2;
    int leftChildIndex = 2 * nodeIndex;
    int rightChildIndex = 2 * nodeIndex + 1;

    buildSegmentTree(leftChildIndex, leftBound, middleIndex);
    buildSegmentTree(rightChildIndex, middleIndex + 1, rightBound);

    segmentTree[nodeIndex] = mergeSegmentTreeNodes(segmentTree[leftChildIndex], segmentTree[rightChildIndex]);
}

// Function to update a value in the segment tree
void updateSegmentTree(int nodeIndex, int leftBound, int rightBound, int updatePosition, int newValue)
{
    if (updatePosition < leftBound || updatePosition > rightBound)
        return;
    if (leftBound == rightBound)
    {
        segmentTree[nodeIndex].minimumValue = newValue;
        segmentTree[nodeIndex].frequencyCount = 1;
        return;
    }
    int middleIndex = (leftBound + rightBound) / 2;
    int leftChildIndex = 2 * nodeIndex;
    int rightChildIndex = 2 * nodeIndex + 1;

    updateSegmentTree(leftChildIndex, leftBound, middleIndex, updatePosition, newValue);
    updateSegmentTree(rightChildIndex, middleIndex + 1, rightBound, updatePosition, newValue);

    segmentTree[nodeIndex] = mergeSegmentTreeNodes(segmentTree[leftChildIndex], segmentTree[rightChildIndex]);
}

// Function to perform range queries in the segment tree
SegmentTreeNode querySegmentTree(int nodeIndex, int leftBound, int rightBound, int queryLeft, int queryRight)
{
    if (rightBound < queryLeft || queryRight < leftBound)
        return {INF, 1};
    if (leftBound >= queryLeft && rightBound <= queryRight)
    {
        return segmentTree[nodeIndex];
    }
    int middleIndex = (leftBound + rightBound) / 2;
    int leftChildIndex = 2 * nodeIndex;
    int rightChildIndex = 2 * nodeIndex + 1;

    return mergeSegmentTreeNodes(
        querySegmentTree(leftChildIndex, leftBound, middleIndex, queryLeft, queryRight),
        querySegmentTree(rightChildIndex, middleIndex + 1, rightBound, queryLeft, queryRight));
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int arraySize, numberOfQueries;
    cin >> arraySize >> numberOfQueries;
    for (int index = 1; index <= arraySize; index++)
    {
        cin >> inputArray[index];
    }
    buildSegmentTree(1, 1, arraySize);

    while (numberOfQueries--)
    {
        int queryType;
        cin >> queryType;
        if (queryType == 1)
        {
            int updateIndex, newValue;
            cin >> updateIndex >> newValue;
            ++updateIndex;
            updateSegmentTree(1, 1, arraySize, updateIndex, newValue);
        }
        else
        {
            int leftRange, rightRange;
            cin >> leftRange >> rightRange;
            --rightRange;

            ++leftRange;
            ++rightRange;

            SegmentTreeNode queryResult = querySegmentTree(1, 1, arraySize, leftRange, rightRange);
            cout << queryResult.minimumValue << ' ' << queryResult.frequencyCount << '\n';
        }
    }
    return 0;
}
