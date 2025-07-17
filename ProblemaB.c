#include <stdio.h>
#include <wchar.h>
#include <stdlib.h> 
#include "header.h"

void processaInputs (wchar_t input[][1][100], int n) {
    int tipos[n];
    int nums[n];
    ConjCartas mao[n];
    ConjCartas *c = (ConjCartas *)malloc(sizeof(ConjCartas));
    for (int i = 0; i < n; i++) {
        analisaLinha(c, input[i][0]);
        mao[i] = *c;
        tipos[i] = c->tipoConj;
        nums[i] = c->numCartas;
    }
    /* wprintf(L"Teste %d\n", nTeste); */
    if (elemsIguais(tipos, n) && elemsIguais(nums, n)) {
        qsort(mao, n, sizeof(ConjCartas), cmpfunc);
        printMao(mao, n);
    } else {
        /* wprintf(L"Combinações não iguais!\n"); */
    }
}

int elemsIguais (int arr[], int n) {
    int curr = arr[0];
    for (int i = 0; i < n; i++) {
        if (arr[i] != curr) {
            return 0;
        }
    }
    return 1;
}

void printMao (ConjCartas c[], int n) {
    for (int i = 0; i < n; i++) {
        printCartasMatrixOrd(c[i].cartas);
    }    
}