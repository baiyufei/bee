#include <iostream>

int merge(int a[], int p, int m, int q)
{
	int len_l = m - p + 1;
	int len_r = q - m;
	int tars = len_l;
	int *l = new int[len_l];
	int *r = new int[len_r];
	for (int i = 0; i < len_l; i++) {
		l[i] = a[p + i];
	}
	for (int i = 0; i < len_r; i++) {
		r[i] = a[m + 1 + i];
	}

	int i = 0, j = 0;
	int sum = 0;
	int k = p;

	for (k = p; k < q + 1; k++) {
		if (i == len_l) {
			a[k] = r[j++];
		}
		else if (j == len_r) {
			a[k] = l[i++];
		}
		else if (l[i] <= r[j]) {
			a[k] = l[i++];
			tars--;
		}
		else if (l[i] > r[j]) {
			a[k] = r[j++];
			sum += tars;
		}
	}

	delete[] l;
	delete[] r;

	return sum;
}

int merge_sort(int a[], int p, int q)
{
	if (p == q) {
		return 0;
	}
	int m = (p + q) / 2;
	int sum = 0;
	sum = sum + merge_sort(a, p, m);
	sum = sum + merge_sort(a, m + 1, q);
	sum = sum + merge(a, p, m, q);
	return sum;
}

int main()
{
	int a[] = { 2,3,8,6,1 };
	int ret = merge_sort(a, 0, 4);
	std::cout << ret << std::endl;
	return 0;
}
