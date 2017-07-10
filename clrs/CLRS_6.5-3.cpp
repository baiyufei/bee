#include <iostream>
#include <vector>
using namespace std;

void min_heapify(vector<int>& v, int i)
{
    int smallest;
    while (1) {
        unsigned int l = 2 * i + 1;
        unsigned int r = 2 * i + 2;
        unsigned int size = v.size();
        if (l < size && v[l] < v[i])
            smallest = l;
        else
            smallest = i;
        if (r < size && v[r] < v[smallest])
            smallest = r;
        if (smallest != i) {
            int temp  = v[i];
            v[i] = v[smallest];
            v[smallest] = temp;
            i = smallest;
        }
        else
            return;
    }
}

int heap_minimum(vector<int> &v) {
    return v[0];
}

int heap_extract_min(vector<int> &v)
{
    if (v.empty()) {
        exit(1);
    }
    int min = v[0];
    v[0] = v[v.size()-1];
    v.pop_back();
    min_heapify(v, 0);
    return min;
}

int heap_decrease_key(vector<int> &v, int i , int k)
{
    if (k > v[i]) {
        exit(1);
    }
	v[i] = k;

    while (i > 0) {
        int parent = (i-1)/2;
        if (v[parent] > v[i]) {
            int temp = v[i];
            v[i] = v[parent];
            v[parent] = temp;
            i = parent;
        }
        else {
            break;
        }
    }

    return 0;
}

int min_heap_insert(vector<int> &v, int k)
{
    v.push_back(k+1);
    heap_decrease_key(v, v.size()-1, k);
    return 0;
}

void vector_show(vector<int> &v) {
    for (auto i = v.begin(); i!= v.end(); i++) {
        cout << *i << " ";
    }
    cout << endl;
}

int main()
{
    vector<int> v = {1, 2, 3, 4, 5, 6, 7, 9, 10};
    heap_extract_min(v);
    vector_show(v);
    min_heap_insert(v, 8);
    vector_show(v);

    return 0;
}
