#include <iostream>

using namespace std;

int partition(int a[], int i, int j)
{
    int x = a[j];
    int p = i;
    for (int t = i; t < j; t++) {
        if (a[t] <= x) {
            int temp = a[t];
            a[t] = a[p];
            a[p] = temp;
            p++;
        }
    }
    int temp = a[j];
    a[j] = a[p];
    a[p] = temp;
    return p;
}

int select(int a[], int order, int len)
{
    int i, j, r;
    i = 0;
    j = len - 1;
    while (1) {
		if (i == j)
			return a[i];
        r = partition(a, i, j);
        if (r == order)
            return a[r];
        if (r < order) {
            i = r+1;
            continue;
        }
        else if (r > order) {
            j = r-1;
            continue;
        }
    }
}


int main()
{
    int a[] = { 1,3,2,6,5,8,7,4 };
    int r = select(a, 4, 8);
    cout << r << endl;
    return 0;
}
