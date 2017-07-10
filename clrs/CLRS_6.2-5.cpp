#include <iostream>
#include <vector>
using namespace std;

void max_heapify(vector<int>& v, int i)
{
    int largest;
    while (1) {
        unsigned int l = 2 * i + 1;
        unsigned int r = 2 * i + 2;
        unsigned int size = v.size();
        if (l < size && v[l] > v[i])
            largest = l;
        else
            largest = i;
        if (r < size && v[r] > v[largest])
            largest = r;
        if (largest != i) {
            int temp  = v[i];
            v[i] = v[largest];
            v[largest] = temp;
            i = largest;
        }
        else
            return;
    }
}

int main()
{
    vector<int> v = {16, 4, 10, 14, 7, 9, 3, 2, 8, 1};
    max_heapify(v, 1);
    for (auto i = v.begin(); i!= v.end(); i++) {
        cout << *i << endl;
    }
    return 0;
}
