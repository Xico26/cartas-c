#include <stdio.h>
#include <wchar.h>
#include <stdlib.h> 
#include "header.h"

#define L 4
#define C 14

void analisaLinha (ConjCartas *c, wchar_t linha[]) {
    // Length linha
    int l = contaElem(linha);
    terminaLinha(linha, l-1);
    l = contaElem(linha);
    c->numCartas = l;
    // Preenche Matriz (Cartas)
    resetMatriz(c->cartas);
    for (int i = 0; i < l; i++) {
        wchar_t carta;
        carta = linha[i];
        /* wprintf(L"Carta: %lc\n", carta); */
        int nai = getNaipe(carta);
        int val = getValor(carta);
        c->cartas[nai][val] = 1;
    }
    // Maior Carta
    c->maiorCarta = maiorCarta(c->cartas);
    // Tipo Conjunto
    determinaTipo(c);
    // Conta Figuras
    contaFigs(c);
}

void determinaTipo (ConjCartas *c) {
    if (isConjunto(c->cartas, c->numCartas)) {
        c->tipoConj = 1;
        /* wprintf(L"conjunto com %d cartas onde a carta mais alta é %lc\n", c->numCartas, c->maiorCarta); */
    } else if (isDuplaSeq(c->cartas, c->numCartas)) {
        c->tipoConj = 2;
        /* wprintf(L"dupla sequência com %d cartas onde a carta mais alta é %lc\n", c->numCartas/2, c->maiorCarta); */
    } else if (isSequencia(c->cartas, c->numCartas)) {
        c->tipoConj = 3;
        /* wprintf(L"sequência com %d cartas onde a carta mais alta é %lc\n", c->numCartas, c->maiorCarta); */
    } else {
        c->tipoConj = 0;
        /* wprintf(L"Nada!\n"); */
    }
}

void contaFigs(ConjCartas *c) {
    inicializaArr(c->nFiguras, 14);
    for (int i = 0; i < C; i++) {
        for (int j = 0; j < L; j++) {
            if (c->cartas[j][i] == 1) {
                c->nFiguras[i]++;
            }
        }
    }
}

wchar_t converteCarta (int n, int v) {
    wchar_t carta;
    if (n == 0) {
        carta = 0x1F0A1 + v;
    } else if (n == 1) {
        carta = 0x1F0B1 + v;
    } else if (n == 2) {
        carta = 0x1F0C1 + v;
    } else {
        carta = 0x1F0D1 + v;
    }
    return carta;
}

wchar_t maiorCarta (int cartas[L][C]) {
    wchar_t carta = 0x1F0A0;
    for (int i = C-1; i >= 0; i--) {
        for (int j = L-1; j >= 0; j--) {
            if (cartas[j][i] == 1) {
                carta = converteCarta(j, i);
                return carta;
            }
        }
    }
    return carta;
}



int verifNaipe (int cartas[L][C], int l, int v) {
    int r = 1;
    for (int i = l; i < L; i++) {
        if (cartas[i][v] == 1) {
            r++;
        }
    }
    if (r > 1) {
        return 1;
    }
    return 0;
}

int isConjunto (int cartas[L][C], int n) {
    if (n > 4) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }
    int r = 1;
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < C; j++) {
            if (cartas[i][j] == 1) {
                if (verifNaipe(cartas, i+1, j)) {
                    r++;
                }
            }
        }
    }
    if (r == n) {
        return 1;
    }
    return 0;
}

int isConsecutivo (int cartas[L][C], int v) {
    for (int i = 0; i < L; i++) {
        if (cartas[i][v+1] == 1 && v+1 < 14) {
            return 1;
        }
    }
    return 0;
}

int isSequencia (int cartas[L][C], int n) {
    if (n < 3) {
        return 0;
    }
    int r = 1;
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < C; j++) {
            if (cartas[i][j] == 1) {
                if (isConsecutivo(cartas, j)) {
                    r++;
                }
            }
        }
    }
    if (r > 2 && r == n) {
        return 1;
    }
    return 0;
}

int verifPar (int cartas[L][C], int l, int v) {
    for (int i = l; i < L; i++) {
        if (cartas[i][v] == 1) {
            return 1;
        }
    }
    return 0;
}

int isDuplaSeq (int cartas[L][C], int n) {
    int pares = 0;
    if (n < 6) {
        return 0;
    }
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < C; j++) {
            if (cartas[i][j] == 1) {
                if (verifPar(cartas, i+1, j)) {
                    pares++;
                }
            }
        }
    }
    if (pares >= 3) {
        return 1;
    }
    return 0;
}