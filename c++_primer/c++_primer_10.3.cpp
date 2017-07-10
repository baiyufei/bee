#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

int foo_10_3(const vector<int> &v)
{
    return accumulate(v.cbegin(), v.cend(), 0);
}

int test(vector<int> &v)
{
    auto it = back_inserter(v);
    *it = 10;
    it++;
    it++;
    it++;
    it++;
    //cout << *it << endl;
    *it = 11;
    it++;
    it++;
    *it = 12;
    auto it2 = v.rbegin();
    cout << *it2 << endl;
    it2++;
    cout << *it2 << endl;

    it2++;
    cout << *it2 << endl;
    return 0;
}

int main()
{
    vector<int> vt = {1, 2, 3, 4, 5};
    //cout << foo_10_3(vt) << endl;
    test(vt);
    return 0;
}
