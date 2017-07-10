#include <iostream>

int brute_find_max_subarray(const int a[], const int length,
    int& left, int& right)
{
    int max_value = a[0];
    left = 0;
    right = 0;

    for (int i = 0; i < length; i++) {
        int s_sum = 0;
        for (int j = i; j < length; j++) {
            s_sum += a[j];
            if (s_sum > max_value) {
                left = i;
                right = j;
                max_value = s_sum;
            }
        }
    }
    return max_value;
}

int main()
{
    int array[] = { 13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7 };
    int l, r;
    brute_find_max_subarray(array, sizeof(array) / 4, l, r);

    for (int i = l; i <= r; i++) {
        std::cout << array[i] << std::endl;
    }

    return 0;
}
