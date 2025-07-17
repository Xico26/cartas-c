#include <stdio.h>
#include <wchar.h>
#include <stdlib.h>
#include <time.h> 
#include "header.h"

void imprimeValida (wchar_t mao[100], wchar_t jogadasAnt[][1][100], int nAnt) {
    int jogadas[10000][L][C];
    int numJogadas = 0;
    ConjCartas *cmao = (ConjCartas *)malloc(sizeof(ConjCartas));
    analisaLinha(cmao, mao);
    if (nAnt == 0) {
        geraQualquer(cmao, jogadas, &numJogadas);
    } else if (determinaUltima(jogadasAnt, nAnt) == 1 && (nAnt - 1) >= 0) {
        geraPossibs(mao, jogadasAnt[nAnt-1][0], jogadas, &numJogadas);
    } else if (determinaUltima(jogadasAnt, nAnt) == 2 && (nAnt - 2) >= 0) {
        geraPossibs(mao, jogadasAnt[nAnt-2][0], jogadas, &numJogadas);
    } else if (determinaUltima(jogadasAnt, nAnt) == 3 && (nAnt - 3) >= 0) {
        geraPossibs(mao, jogadasAnt[nAnt-3][0], jogadas, &numJogadas);
    } else if (determinaUltima(jogadasAnt, nAnt) == 0) {
        geraQualquer(cmao, jogadas, &numJogadas);
    }
    int x = imprimeJogada(jogadas, &numJogadas, jogadasAnt, nAnt);
    if (x == 0) {
        wprintf(L"PASSO\n");
    }
    free(cmao);
}

int imprimeJogada(int jogadas[][L][C], int *nJ, int jogadasAnt[][1][100], int nAnt) {
    int imp = 0;
    for (int i = 0; i < *nJ; i++) {
        if (contaElemsMatrix(jogadas[i]) != 0) {
            wchar_t str[100];
            matrixToLinha(jogadas[i], str);
            ConjCartas *cjog = (ConjCartas *)malloc(sizeof(ConjCartas));
            analisaLinha(cjog, str);
            if (nAnt == 0) {
                imp++;
                printCartasMatrixOrd(jogadas[i]);
                free(cjog);
                return imp;
            } else {
                if (jogadaValida(cjog, jogadasAnt, nAnt)) {
                    imp++;
                    printCartasMatrixOrd(jogadas[i]);
                    free(cjog);
                    return imp;
                }
            }
            
        }
    }
    return imp;
}

void geraQualquer (ConjCartas *cmao, int jogadas[][L][C], int *nJ) {
    // DS
    int i = cmao->numCartas;
    while (*nJ < 1 && i >= 6) {
        copiaUsaveis(cmao->cartas, NULL, jogadas, 2, i / 2, nJ, 13, -1, 0, i);
        i--;
    }
    // SEQ
    int j = cmao->numCartas;
    while (*nJ < 1 && j >= 3) {
        copiaUsaveis(cmao->cartas, NULL, jogadas, 1, j, nJ, 13, -1, 0, j);
        j--;
    }
    // CONJ
    int k = cmao->numCartas;
    while (*nJ < 1 && k > 0) {
        copiaUsaveis(cmao->cartas, NULL, jogadas, k, 1, nJ, 13, -1, 0, k);
        k--;
    }
}