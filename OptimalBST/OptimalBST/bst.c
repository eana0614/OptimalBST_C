#define _CRT_SECURE_NO_DEPRECATE

#include<stdio.h>
#include<stdlib.h>
#include<memory.h>

void runOptimalBST(float* key, float* imaginaryKey, int n);
void printFloatArray(float** arr, int row, int col);
void printIntArray(int** arr, int row, int col);
void initFloatArray(float** e, int row, int);
void initIntArray(int** e, int row, int col);

#define MAX 100000;

int main(void) {

	float p[] = { 0, 0.15, 0.10, 0.05, 0.10, 0.20 };
	float q[] = { 0.05, 0.10, 0.05, 0.05, 0.05, 0.10 };

	printf("[ START ] Optimal BST\n");

	runOptimalBST(p, q, 6);

}

void runOptimalBST(float* key, float* imaginaryKey, int n) {
	float **e, **w;
	int **root;

	e = (float**)malloc(sizeof(n+1) * sizeof(float*));
	w = (float**)malloc(sizeof(n+1) * sizeof(float*));

	for (int i = 0; i < n+1; i++) {
		e[i] = (float*)malloc(sizeof(n) * sizeof(float));
		w[i] = (float*)malloc(sizeof(n) * sizeof(float));
	}


	root = (int**)malloc(sizeof(n) * sizeof(int));
	for (int i = 0; i < n; i++) {
		root[i] = (int*)malloc(sizeof(n) * sizeof(int));
	}

	initFloatArray(e, n + 1, n);
	initFloatArray(w, n + 1, n);
	initIntArray(root, n, n);

	for (int i = 0; i < n; i++) {
		e[i + 1][i] = imaginaryKey[i];
		w[i + 1][i] = imaginaryKey[i];
	}

	for (int l = 0; l < n + 1; l++) {
		for (int i = 1; i < n - l; i++) {
			int j = i + l;

			e[i][j] = MAX;
			w[i][j] = w[i][j - 1] + key[j] + imaginaryKey[j];

			for (int r = i; r < j+1 ; r++) {
				float temp = e[i][r - 1] + e[r + 1][j] + w[i][j];

				if (temp < e[i][j]) {
					e[i][j] = temp;
					root[i][j] = r;
				}
			}
		}
	}

	
	printf("!] E(x) \n");
	printFloatArray(e, n+1, n);

	printf("!] Weight \n");
	printFloatArray(w, n + 1, n);

	printf("!] Root \n");
	printIntArray(root, n, n);

	printf("!] Search Cost = %2.2f\n", e[1][n - 1]);
	
}

void initIntArray(int** e, int row, int col) {

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			e[i][j] = 0;
		}
	}

}

void initFloatArray(float** e, int row, int col) {

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			e[i][j] = 0;
		}
	}

}

void printIntArray(int** arr, int row, int col) {

	for (int i = 1; i < row; i++) {
		for (int j = 1; j < col; j++) {
			printf("   %d", arr[i][j]);
		}

		printf("\n");
	}
	printf("\n");
}
void printFloatArray(float** arr, int row, int col) {

	for (int i = 1; i <row; i++) {
		for (int j = 0; j < col; j++) {
			printf("   %1.2f", arr[i][j]);
		}
		printf("\n");
	}

	printf("\n");
}
