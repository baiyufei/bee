#include <iostream>

int a[5][4] = {
    { 37, 23, 22, 32 },
    { 21, 6, 7, 10 },
    { 53, 34, 30, 31 },
    { 32, 13, 9, 6 },
    { 43, 21, 15, 8 }
};

int b[5][4] = {0};

int main()
{
    for (int i = 0 ; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            if (a[i][j] + a[i+1][j+1] > a[i+1][j] + a[i][j+1]) {
                b[i][j]++;
                b[i+1][j+1]++;
                b[i+1][j]++;
                b[i][j+1]++;
            }
        }
    }

    int max = 0;
    int si = 0;
    int sj = 0;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 4; j++) {
            if (b[i][j] > max) {
                max = b[i][j];
                si = i;
                sj = j;
            }
        }
    }

    std::cout << si << std::endl << sj << std::endl << max;
    return 0;
}
