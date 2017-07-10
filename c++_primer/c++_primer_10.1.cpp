#include <iostream>
#include <vector>

using namespace std;

int count(vector<int>::iterator begin, vector<int>::iterator end, int value)
{
    int ret = 0;
    for (auto iter = begin; iter != end; iter++) {
        if (*iter == value) {
            ret++;
        }
    }
    return ret;
}

int main()
{
    vector<int> test = { 1, 2, 3, 1, 1, 5, 6, 8, 2 };
    for (int i = 0; i < 8; i++) {
        int c = count(test.begin(), test.end(), i);
        cout << "the count of " << i << " is " << c << endl;
    }
    return 0;
}
