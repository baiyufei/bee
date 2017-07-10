#include <iostream>

int binary_search(int a[], int len, int tar)
{
	int i = 0;
	int j = len - 1;
    while (i <= j) {
        int m = (i + j) / 2;
        if (a[m] == tar) {
            return m;
        }
        else if (a[m] > tar) {
            j = m - 1;
        }
        else if (a[m] < tar) {
            i = m + 1;
        }
    }
    return -1;
}

int main()
{
    int a[] = { 1, 3, 5, 7, 9, 10 };
    int b[] = { 1, 2, 6, 8, 9 };
    int ret;
    for (int i = 0; i < 6; i++) {
        ret = binary_search(a, 6, a[i]);
        std::cout << ret << std::endl;
    }
    for (int i = 0; i < 5; i++) {
        ret = binary_search(b, 5, b[i]);
        std::cout << ret << std::endl;
    }
    ret = binary_search(b, 5, -1);
    std::cout << ret << std::endl;
    ret = binary_search(b, 5, 3);
    std::cout << ret << std::endl;

	return 0;
}
