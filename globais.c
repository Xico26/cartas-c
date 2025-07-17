#include <stdio.h>
#include <wchar.h>
#include "header.h"

#define L 4
#define C 14

int contaElem (wchar_t linha[]) {
    int i = 0;
    while (linha[i] != '\0') {
        i++;
    }
    return i;
}

void terminaLinha (wchar_t linha[], int n) {
    if (linha[n] == '\n') {
        linha[n] = '\0';
    }   
}

int getNaipe (wchar_t carta) {
    int nai = (carta - 0x1F0A1) / 16;
    return nai;
}

int getValor (wchar_t carta) {
    int val = (carta % 16) - 1;
    return val;
}

void resetMatriz(int matrix[L][C]) {
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < C; j++) {
            matrix[i][j] = 0;
        }
    }
}

void inicializaArr (int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = 0;
    } 
}

void printCartasMatrix (int matrix[L][C]) {
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < C; j++) {
            if (matrix[i][j] == 1) {
                wchar_t carta;
                if (i == 0) {
                    carta = 0x1F0A1 + j;
                } else if (i == 1) {
                    carta = 0x1F0B1 + j;
                } else if (i == 2) {
                    carta = 0x1F0C1 + j;
                } else {
                    carta = 0x1F0D1 + j;
                }
                wprintf(L"%lc ", carta);
            }
        }
    }
    wprintf(L"\n");
}

void printCartasMatrixOrd (int matrix[L][C]) {
    int ch = 0;
    wchar_t str[100];
    for (int i = 0; i < C; i++) {
        for (int j = 0; j < L; j++) {
            if (matrix[j][i] == 1) {
                wchar_t carta;
                if (j == 0) {
                    carta = 0x1F0A1 + i;
                } else if (j == 1) {
                    carta = 0x1F0B1 + i;
                } else if (j == 2) {
                    carta = 0x1F0C1 + i;
                } else {
                    carta = 0x1F0D1 + i;
                }
                str[ch] = carta;
                str[ch+1] = ' ';
                ch++;
                ch++;
            }
        }
    }
    if (ch == 0) {
        wprintf(L"\n");
    } else {
        str[ch-1] = '\0';
        wprintf(L"%ls", str);
        wprintf(L"\n");
    }   
}

void matrixToLinha (int matrix[L][C], wchar_t str[100]) {
    int ch = 0;
    for (int i = 0; i < C; i++) {
        for (int j = 0; j < L; j++) {
            if (matrix[j][i] == 1) {
                wchar_t carta;
                if (j == 0) {
                    carta = 0x1F0A1 + i;
                } else if (j == 1) {
                    carta = 0x1F0B1 + i;
                } else if (j == 2) {
                    carta = 0x1F0C1 + i;
                } else {
                    carta = 0x1F0D1 + i;
                }
                str[ch] = carta;
                ch++;
            }
        }
    }
    if (ch == 0) {
        return;
    } else {
        str[ch] = '\0';
    }   
}

void swap (int l[], int i, int j) {
    int tI = l[i];
    l[i] = l[j];
    l[j] = tI;
}

int cmpfunc(const void *a, const void *b) {
    const ConjCartas *m1 = (const ConjCartas *)a;
    const ConjCartas *m2 = (const ConjCartas *)b;
    wchar_t c1 = m1->maiorCarta;
    wchar_t c2 = m2->maiorCarta;
    int v1 = getValor(c1);
    int v2 = getValor(c2);
    int n1 = getNaipe(c1);
    int n2 = getNaipe(c2);
    if ((v1 - v2) == 0) {
        return (n1 - n2);
    }
    return (v1 - v2);
}

int comparaCartas (wchar_t c1, wchar_t c2) {
    int v1 = getValor(c1);
    int v2 = getValor(c2);
    int n1 = getNaipe(c1);
    int n2 = getNaipe(c2);
    if ((v1 - v2) == 0) {
        return (n1 - n2);
    }
    return (v1 - v2);
}

int contaElemsMatrix (int mat[L][C]) {
    int res = 0;
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < C; j++) {
            if (mat[i][j] == 1) {
                res++;
            }
        }
    }
    return res;
}

void printArray (int arr[], int n) {
    wprintf(L"{");
    for (int i = 0; i < n; i++) {
        wprintf(L"%d, ", arr[i]);
    }
    wprintf(L"}\n");
}

void printMatrix(int matrix[L][C]) {
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < C; j++) {
            wprintf(L"%d ", matrix[i][j]);
        }
        wprintf(L"\n");
    }
    wprintf(L"\n");
}

void printLinha (wchar_t linha[]) {
    wprintf(L"Linha: \n");
    for (int i = 0; linha [i] != '\0'; i++) {
        wprintf(L"%lc ", linha[i]);
    }
    wprintf(L"\n");
}