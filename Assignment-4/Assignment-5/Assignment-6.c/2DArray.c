#include <stdio.h>

// ---------- (i) Matrix addition — O(n^2) ----------
void addMatrix(int A[][10], int B[][10], int C[][10], int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
}

// ---------- (ii) Matrix multiplication — O(n^3) ----------
void multiplyMatrix(int A[][10], int B[][10], int C[][10], int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n; k++)
                C[i][j] += A[i][k] * B[k][j];
        }
}

// ---------- (iii) Check zero matrix — O(n^2) ----------
int isZeroMatrix(int A[][10], int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (A[i][j] != 0) return 0;
    return 1;
}

// ---------- (iv) Check symmetric matrix — O(n^2) ----------
int isSymmetric(int A[][10], int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (A[i][j] != A[j][i]) return 0;
    return 1;
}

// ---------- (v) Determinant (recursive expansion) — O(n!) ----------
int determinant(int A[][10], int n) {
    if (n == 1) return A[0][0];
    int det = 0, sub[10][10];
    for (int x = 0; x < n; x++) {
        int subi = 0;
        for (int i = 1; i < n; i++) {
            int subj = 0;
            for (int j = 0; j < n; j++) {
                if (j == x) continue;
                sub[subi][subj++] = A[i][j];
            }
            subi++;
        }
        det += (x % 2 == 0 ? 1 : -1) * A[0][x] * determinant(sub, n - 1);
    }
    return det;
}

// ---------- (vi) Transpose in place — O(n^2) ----------
void transpose(int A[][10], int n) {
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++) {
            int temp = A[i][j];
            A[i][j] = A[j][i];
            A[j][i] = temp;
        }
}

// ---------- MAIN ----------
int main() {
    int A[10][10] = {{1, 2}, {3, 4}};
    int B[10][10] = {{5, 6}, {7, 8}};
    int C[10][10];
    int n = 2;

    // Addition
    addMatrix(A, B, C, n);
    printf("Matrix Addition:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) printf("%d ", C[i][j]);
        printf("\n");
    }

    // Multiplication
    multiplyMatrix(A, B, C, n);
    printf("Matrix Multiplication:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) printf("%d ", C[i][j]);
        printf("\n");
    }

    // Zero check
    printf("Is Zero Matrix? %s\n", isZeroMatrix(A, n) ? "Yes" : "No");

    // Symmetry check
    printf("Is Symmetric? %s\n", isSymmetric(A, n) ? "Yes" : "No");

    // Determinant
    printf("Determinant: %d\n", determinant(A, n));

    // Transpose
    transpose(A, n);
    printf("Transpose:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) printf("%d ", A[i][j]);
        printf("\n");
    }

    return 0;
}
