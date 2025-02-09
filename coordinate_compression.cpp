#include <bits/stdc++.h>
using namespace std;
/*
 Coordinate compression - were compressing the indexes with smaller number with smaller indices and larger numbers with bigger indices
in order to maitain the relative order of the values.

*/

vector<int> compress_coordinates(vector<int> &values)
{
    vector<int> sorted_values = values;

    sort(sorted_values.begin(), sorted_values.end());
    sorted_values.erase(unique(sorted_values.begin(), sorted_values.end()), sorted_values.end());

    unordered_map<int, int> compressed_map;
    for (int i = 0; i < sorted_values.size(); i++)
    {
        compressed_map[sorted_values[i]] = i;
    }

    vector<int> compressed_values;
    for (int value : values)
    {
        compressed_values.push_back(compressed_map[value]);
    }

    return compressed_values;
}

int main()
{
    vector<int> values = {100, 200, 1000, 500, 100, 200};
    vector<int> compressed = compress_coordinates(values);

    for (int val : compressed)
    {
        cout << val << " ";
    }
    cout << endl;

    return 0;
}
