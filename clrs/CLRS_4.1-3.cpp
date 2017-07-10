#include <iostream>

int find_cross_max_subarray(const int a[], int& left, int mid, int& right)
{
    int sum = 0;
    int max = a[mid];
    int l = mid;
    int r = mid + 1;
    for (int i = mid; i >= left; i--) {
        sum += a[i];
        if (sum > max) {
            l = i;
            max = sum;
        }
    }
    int max_r = a[mid + 1];
    sum = 0;
    for (int i = mid + 1; i <= right; i++) {
        sum += a[i];
        if (sum > max_r) {
            r = i;
            max_r = sum;
        }
    }
    left = l;
    right = r;
    return max + max_r;
}

int find_max_subarray(const int a[], int& left, int& right)
{
    if (left == right) {
        return a[left];
    }
    int mid = (left + right) / 2;
    int l[3], r[3], m[3];
    l[0] = left;
    r[0] = mid;
    m[0] = find_max_subarray(a, l[0], r[0]);
    l[1] = mid + 1;
    r[1] = right;
    m[1] = find_max_subarray(a, l[1], r[1]);
    l[2] = left;
    r[2] = right;
    m[2] = find_cross_max_subarray(a, l[2], mid, r[2]);

    if (m[0] > m[1] && m[1] >= m[2]) {
        left = l[0];
        right = l[1];
        return m[0];
    }
    else if (m[1] > m[0] && m[0] >= m[2]) {
        left = l[1];
        right = r[1];
        return m[1];
    }
    else {
        left = l[2];
        right = r[2];
        return m[2];
    }
}

int main()
{
    int array[] = { 13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7 };
    int l, r;
    l = 0;
    r = sizeof(array)/4 - 1;
    find_max_subarray(array, l, r);

    for (int i = l; i <= r; i++) {
        std::cout << array[i] << std::endl;
    }

    return 0;
}
