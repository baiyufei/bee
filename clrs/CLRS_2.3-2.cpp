#include <iostream>

void merge(int A[], int p, int q, int r)
{
	int len_l = q - p + 1;
	int len_r = r - q;

	int *L = new int[len_l];
	int *R = new int[len_r];

	for (int i = 0; i < len_l; i++) {
		L[i] = A[p + i];
	}
	for (int i = 0; i < len_r; i++) {
		R[i] = A[q + i + 1];
	}

	int i = 0, j = 0, k = p;
	while (i < len_l || j < len_r) {
		if (i == len_l) {
			A[k] = R[j++];
		}
		else if (j == len_r) {
			A[k] = L[i++];
		}
		else if (R[j] < L[i]) {
			A[k] = R[j++];
		}
		else if (L[i] < R[j]) {
			A[k] = L[i++];
		}
		k++;
	}
	delete L;
	delete R;
}

void merge_sort(int A[], int p, int q)
{
	if (p < q) {
		int t = (p + q) / 2;
		merge_sort(A, p, t);
		merge_sort(A, t + 1, q);
		merge(A, p, t, q);
	}
}

int main()
{
	int nums[] = { 3,41,52,26,38,57,9,49 };
	merge_sort(nums, 0, 7);
	for (int i = 0; i < 8; i++) {
		std::cout << nums[i] << std::endl;
	}
	return 0;
}
