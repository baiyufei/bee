#include <iostream>

int find_max_subarray(const int a[], const int length, int& left, int& right)
{
    int m1 = 0;
    int m2 = 0;
    int l1 = -1;
    int l2 = -1;
    int r1 = -1;

    for (int j = 0; j < length; j++) {
        m2 += a[j];

        if (a[j] >= m2) {
            l2 = j;
            m2 = a[j];
        }

        if (m2 > m1) {
            l1 = l2;
            r1 = j;
            m1 = m2;
        }
    }

    if (m2 > m1) {
        left = l2;
        right = length - 1;
        return m2;
    }
    else {
        left = l1;
        right = r1;
        return m1;
    }
}

int main()
{
    //int array[] = { 13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7 };
	int array[] = { -1, -1, -1, -1 };
    int l = 0, r = 0;
    int len = sizeof(array) / 4;
    find_max_subarray(array, len, l, r);

	if (l > 0) {
		for (int i = l; i <= r; i++) {
			std::cout << array[i] << std::endl;
		}
	}
    

    return 0;
}
