#include <stdio.h>
#include <wchar.h>
#include <stdlib.h> 
#include "header.h"

void analisaJogada (wchar_t mao[100], wchar_t jogadasAnt[][1][100], wchar_t jogada[100], int nJogadas) {
    /* wprintf(L"Teste %d\n", nTeste); */
    ConjCartas *cmao = (ConjCartas *)malloc(sizeof(ConjCartas));
    analisaLinha(cmao, mao);
    wchar_t passo[] = L"PASSO\n";
    if (wcscmp(jogada, passo) == 0) {
        printCartasMatrixOrd(cmao->cartas);
        return;
    }
    ConjCartas *cjog = (ConjCartas *)malloc(sizeof(ConjCartas));
    analisaLinha(cjog, jogada);
    if (cjog->tipoConj != 0 && nJogadas == 0) {
        efetuaJogada(cjog, cmao);
    } else if (cjog->numCartas == 1 && nJogadas != 0) {
        if (jogadaValida(cjog, jogadasAnt, nJogadas)) {
            efetuaJogada(cjog, cmao);
        } else {
            printCartasMatrixOrd(cmao->cartas);
        }
    } else if (cjog->tipoConj != 0 && nJogadas != 0) {
        if (jogadaValida(cjog, jogadasAnt, nJogadas)) {
            efetuaJogada(cjog, cmao);
        } else {
            printCartasMatrixOrd(cmao->cartas);
        }   
    } else {
        printCartasMatrixOrd(cmao->cartas);
    }
}

void efetuaJogada (ConjCartas *cjog, ConjCartas *cmao) {
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < C; j++) {
            if (cmao->cartas[i][j] == 1) {
                if (cjog->cartas[i][j] == 1) {
                    cmao->cartas[i][j] = 0;
                }
            }
        }
    }
    printCartasMatrixOrd(cmao->cartas);
}

int determinaUltima (wchar_t jogadasAnt[][1][100], int nJogadas) {
    wchar_t passo[] = L"PASSO";
    wchar_t passoN[] = L"PASSO\n";
    if (wcscmp(jogadasAnt[nJogadas-1][0], passo) == 0 || wcscmp(jogadasAnt[nJogadas-1][0], passoN) == 0) {
        if (wcscmp(jogadasAnt[nJogadas-2][0], passo) == 0 || wcscmp(jogadasAnt[nJogadas-2][0], passoN) == 0) {
            if (wcscmp(jogadasAnt[nJogadas-3][0], passo) == 0 || wcscmp(jogadasAnt[nJogadas-3][0], passoN) == 0) {
                return 0;
            } else {
                return 3;
            }
        } else {
            return 2;
        }   
    } else {
        return 1;
    }
}

int jogadaValida (ConjCartas *cjog, wchar_t jogadasAnt[][1][100], int nJogadas) {
    ConjCartas *ultima = (ConjCartas *)malloc(sizeof(ConjCartas));
    int res = determinaUltima(jogadasAnt, nJogadas);
    if (res == 1) {
        analisaLinha(ultima, jogadasAnt[nJogadas-1][0]);
    } else if (res == 2) {
        analisaLinha(ultima, jogadasAnt[nJogadas-2][0]);
    } else if (res == 3) {
        analisaLinha(ultima, jogadasAnt[nJogadas-3][0]);
    } else if (res == 0) {
        free(ultima);
        return 1;
    }
    int reisUltima = contaReis(ultima);
    if (reisUltima == ultima->numCartas) {
        if (reisUltima == 1) {
            if (cjog->tipoConj == 1 && cjog->numCartas == 4) {
                return 1;
            } else if (cjog->tipoConj == 2 && cjog->numCartas == 6) {
                return 1;
            }
        } else if (reisUltima == 2 && cjog->tipoConj == 2 && cjog->numCartas == 8) {
            return 1;
        } else if (reisUltima == 3 && cjog->tipoConj == 2 && cjog->numCartas == 10) {
            return 1;
        } else {
            return 0;
        }
    }
    if (cjog->numCartas == ultima->numCartas && cjog->tipoConj == ultima->tipoConj) {
        if (comparaCartas(cjog->maiorCarta, ultima->maiorCarta) > 0) {
            return 1;
        }
    }
    free(ultima);
    return 0;
}

int contaReis (ConjCartas *ultima) {
    int nReis = 0;
    for (int i = 0; i < L; i++) {
        if (ultima->cartas[i][13] == 1) {
            nReis++;
        }
    }
    return nReis;
}