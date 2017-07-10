#include <iostream>

void selection_sort(int a[], int length)
{
    for (int i = 0; i < length; ++i) {
        int min = i;
        for (int j = i; j < length; j++) {
            if (a[j] < a[min]) {
                min = j;
            }
        }
        int temp = a[i];
        a[i] = a[min];
        a[min] = temp;
    }
}

int main()
{
    int a[5] = {3, 7, 4, 5, 1};
    selection_sort(a, 5);
    for (int i = 0; i < 5; i++)
    {
        std::cout << a[i] << std::endl;
    }
    return 0;
}
