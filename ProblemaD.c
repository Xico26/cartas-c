#include <stdio.h>
#include <wchar.h>
#include <stdlib.h> 
#include "header.h"

void geraPossibs (wchar_t mao[100], wchar_t jogadaAnt[100] ,int jogadas[10000][L][C], int *numJogadas) {
    ConjCartas *cmao = (ConjCartas *)malloc(sizeof(ConjCartas));
    analisaLinha(cmao, mao);
    ConjCartas *cant = (ConjCartas *)malloc(sizeof(ConjCartas));
    analisaLinha(cant, jogadaAnt);
    int naiM = getNaipe(cant->maiorCarta);
    int valM = getValor(cant->maiorCarta);
    if (cant->tipoConj == 1) { // CONJUNTOS
        copiaUsaveis(cmao->cartas, cant, jogadas, cant->numCartas, 1, numJogadas, naiM, valM, valM, cant->numCartas);
        if (contaReis(cant) == cant->numCartas) {
            if (cant->numCartas == 1) {
                copiaUsaveis(cmao->cartas, cant, jogadas, 4, 1, numJogadas, naiM, valM, 0, 4);
                copiaUsaveis(cmao->cartas, cant, jogadas, 2, 3, numJogadas, naiM, valM, 0, 6);
            }
            if (cant->numCartas == 2) {
                copiaUsaveis(cmao->cartas, cant, jogadas, 2, 4, numJogadas, naiM, valM, 0, 8);
            }
            if (cant->numCartas == 3) {
                copiaUsaveis(cmao->cartas, cant, jogadas, 2, 5, numJogadas, naiM, valM, 0, 10);
            }
        }
    } else if (cant->tipoConj == 2) { // DUPLAS SEQUENCIAS
        copiaUsaveis(cmao->cartas, cant, jogadas, 2, cant->numCartas / 2, numJogadas, naiM, valM, valM - (cant->numCartas / 2) + 1, cant->numCartas);
    } else if (cant->tipoConj == 3) { // SEQUENCIAS
        copiaUsaveis(cmao->cartas, cant, jogadas, 1, cant->numCartas, numJogadas, naiM, valM, valM - cant->numCartas + 1, cant->numCartas);
    }
    free(cmao);
    free(cant);
}

int geraUsaveisConj (int mao[L][C], int usaveis[L][C], int naiM, int valM, int f, int c, ConjCartas *cant) {
    int nCopiado = 0;
    for (; f < 14; f++) {
        int nai = 0;
        if (f == valM) {
            if (c == 1) {
                nCopiado += geraUsaveisConj1(mao, usaveis, naiM, valM, f);
                return nCopiado;
            } else if (c > 1) {
                int valAnt = 0;
                for (int i = 0; i < 4; i++) {
                    if (cant->cartas[i][f] == 1) {
                        valAnt += i;
                    }
                }
                int coloc = 0;
                int val = 0;
                for (; nai < 4; nai++) {
                    if (mao[nai][f] == 1 && coloc <= c && (val + nai >= valAnt || nai == 0 || val + nai == valAnt - 1)) {
                        usaveis[nai][f] = 1;
                        nCopiado++;
                        coloc++;
                        val += nai;
                    }
                }
                if (mao[naiM][f] == 1) {
                    usaveis[naiM][f] = 1;   
                }
            }
        } else {
            nCopiado += geraUsaveis(mao, usaveis, f);
        }
    }
    return nCopiado;
}

int geraUsaveisConj1 (int mao[L][C], int usaveis[L][C], int naiM, int valM, int f) {
    int nCopiado = 0;
    for (; f < 14; f++) {
        if (f == valM) {
            int nai = naiM + 1;
            for (; nai < 4; nai++) {
                if (mao[nai][f] == 1) {
                    usaveis[nai][f] = 1;
                    nCopiado++;
                }
            }
        } else {
            nCopiado += geraUsaveis(mao, usaveis, f);
        }
    }
    return nCopiado;
}

// COPIA COLUNAS A PARTIR DA MAIOR PARA A SEQ -> CARTAS QUE POSSO USAR NA JOGADA
// c: cartas por valor, s: n de figuras diferentes
int geraUsaveis (int mao[L][C], int usaveis[L][C], int f) {
    int nCopiado = 0;
    for (; f < 14; f++) {
        int nai = 0;
        for (; nai < 4; nai++) {
            if (mao[nai][f] == 1) {
                nCopiado++;
                usaveis[nai][f] = 1;
            }
        }
    }
    return nCopiado;
}

void geraCartasPorFig (int usaveis[L][C], int cartasPorFig[14]) {
    for (int i = 0; i < C; i++) {
        for (int j = 0; j < L; j++) {
            if (usaveis[j][i] == 1) {
                cartasPorFig[i]++;
            }
        }
    }
}

void trataUsaveisDS (int usaveis[L][C], int naiM, int valM, int s, int f, int excl[4], ConjCartas *cant) {
    if (f == valM - s + 1) {
        int coloc = 0;
        int val = 0;
        int valAnt = 0;
        int ult1 = 0;
        for (int i = 0; i < 4; i++) {
            if (cant->cartas[i][valM] == 1) {
                valAnt += i;
            }
        }
        for (int i = 0; i < 4; i++) {
            if (usaveis[i][valM] == 1) {
                val += i;
                coloc++;
                ult1 = i;
            }
        }
        if (val <= valAnt && ult1 <= naiM) {
            for (int i = 0; i < 4; i++) {
                if (usaveis[i][valM] == 1) {
                    usaveis[i][valM] = 0;
                    excl[i] = 1;
                }
            }
        }
    } else {
        for (int i = 0; i < 4; i++) {
            if (excl[i] == 1 && usaveis[i][valM] != 1) {
                usaveis[i][valM] = 1;
                excl[i] = 0;
            }
        }
    }
}

void trataUsaveis (int usaveis[L][C], int naiM, int valM, int s, int c, int f, int excl[4], ConjCartas *cant) {
    if (c == 2) {
        trataUsaveisDS(usaveis, naiM, valM, s, f, excl, cant);
    } else {
        if (f == valM - s + 1) {
            for (int i = 0; i < naiM+1; i++) {
                if (usaveis[i][valM] == 1) {
                    usaveis[i][valM] = 0;
                    excl[i] = 1;
                }
            }
        } else {
            for (int i = 0; i < 4; i++) {
                if (excl[i] == 1 && usaveis[i][valM] != 1) {
                    usaveis[i][valM] = 1;
                    excl[i] = 0;
                }
            }
        }
    }
}

void copiaUsaveis (int mao[L][C], ConjCartas *cant, int jogadas[][L][C], int c, int s, int *numJogadas, int naiM, int valM, int f, int tamMax) {
    int usaveis[L][C];
    if (f < 0) {
        f = 0;
    }
    int nCopiado;
    resetMatriz(usaveis);
    if (cant == NULL) {
        nCopiado = geraUsaveis(mao, usaveis, f);
    } else {
        if (cant->tipoConj == 1) { 
            nCopiado = geraUsaveisConj(mao, usaveis, naiM, valM, f, c, cant);
        } else {
            nCopiado = geraUsaveis(mao, usaveis, f);
        }
    }
    if (nCopiado == 0) {
        return;
    }
    int cartasPorFig[14] = {0};
    geraCartasPorFig(usaveis, cartasPorFig);
    int excl[4] = {0};
    for (; f < 14; f++) {
        if (cant != NULL) {
            if (cant->tipoConj != 1) {
                trataUsaveis(usaveis, naiM, valM, s, c, f, excl, cant);
            }
        }
        int jogadaAtual[L][C];
        resetMatriz(jogadaAtual);
        int myS = 0;
        geraJogadas(usaveis, c, s, f, tamMax, 0, cartasPorFig, jogadas, jogadaAtual, numJogadas, &myS);
    }
}

void caso1 (int usaveis[L][C], int v, int s, int tamMax, int tamAtual, int cartasPorFig[14], int jogadas[][L][C], int jogadaAtual[L][C], int *nJ, int *myS) {
    for (int i = 0; i < 4; i++) {
        int x = geraColuna(usaveis, v, 1, i, jogadaAtual);
        if (x < 1) {
            continue;
        }
        (*myS)++;
        if (v+1 <= 14 && *myS <= s) {
            tamAtual += x;
            geraJogadas(usaveis, 1, s, v+1, tamMax, tamAtual, cartasPorFig,jogadas, jogadaAtual, nJ, myS);
            tamAtual -= x;
        }
    }
}

void caso2 (int usaveis[L][C], int v, int s, int tamMax, int tamAtual, int cartasPorFig[14], int jogadas[][L][C], int jogadaAtual[L][C], int *nJ, int *myS) {
    for (int i = 0; i < 6; i++) {
        int x = geraColuna(usaveis, v, 2, i, jogadaAtual);
        if (x < 2) {
            continue;
        }
        (*myS)++;
        if (v+1 <= 14 && *myS <= s) {
            tamAtual += x;
            geraJogadas(usaveis, 2, s, v+1, tamMax, tamAtual, cartasPorFig,jogadas, jogadaAtual, nJ, myS);
            tamAtual -= x;
        }
    }
}

void caso3 (int usaveis[L][C], int v, int s, int tamMax, int tamAtual, int cartasPorFig[14], int jogadas[][L][C], int jogadaAtual[L][C], int *nJ, int *myS) {
    for (int i = 0; i < 4; i++) {
        int x = geraColuna(usaveis, v, 3, i, jogadaAtual);
        if (x < 3) {
            continue;
        }
        (*myS)++;
        if (v+1 <= 14 && *myS <= s) {
            tamAtual += x;
            geraJogadas(usaveis, 3, s, v+1, tamMax, tamAtual, cartasPorFig,jogadas, jogadaAtual, nJ, myS);
            tamAtual -= x;
        }
    }
}

void casoCT (int usaveis[L][C], int v, int c, int s, int tamMax, int tamAtual, int cartasPorFig[14], int jogadas[][L][C], int jogadaAtual[L][C], int *nJ, int *myS) {
    for (int i = 0; i < 4; i++) {
        jogadaAtual[i][v] = usaveis[i][v];
        if (usaveis[i][v] == 1) {
            tamAtual++;
        }
    }
    (*myS)++;
    if (v+1 <= 14 && *myS <= s) {
        geraJogadas(usaveis, c, s, v+1, tamMax, tamAtual, cartasPorFig, jogadas, jogadaAtual, nJ, myS);
    }
}

int geraJogadas (int usaveis[L][C], int c, int s, int v, int tamMax, int tamAtual, int cartasPorFig[14], int jogadas[][L][C], int jogadaAtual[L][C], int *nJ, int *myS) {
    if (tamAtual >= tamMax) {
        if (contaElemsMatrix(jogadaAtual) != 0) {
            copiaM(jogadaAtual, jogadas, *nJ);
            (*nJ)++;
            (*myS) = 0;
        }
        return 1;
    }
    if (cartasPorFig[v] > c) {
        if (c == 1) {
            caso1(usaveis, v, s, tamMax, tamAtual, cartasPorFig, jogadas, jogadaAtual, nJ, myS);
        } else if (c == 2) {
            caso2(usaveis, v, s, tamMax, tamAtual, cartasPorFig, jogadas, jogadaAtual, nJ, myS);
        } else if (c == 3) {
            caso3(usaveis, v, s, tamMax, tamAtual, cartasPorFig, jogadas, jogadaAtual, nJ, myS);
        }
    } else if (cartasPorFig[v] == 0) {
        return 0;
    } else {
        casoCT(usaveis, v, c, s, tamMax, tamAtual, cartasPorFig, jogadas, jogadaAtual, nJ, myS);
    }
    return 0;
}

// COPIA DA SEQ PARA O ARRAY DAS JOGADAS
void copiaM (int a[L][C], int jogadas[][L][C], int n) {
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < C; j++) {
            jogadas[n][i][j] = a[i][j];
        }
    }
}

int gerac1 (int possiveis[L][C], int fig, int i, int jogada[L][C]) {
    int comb1[4][4] = {{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};
    int numAdd = 0;
    for (int j = 0; j < 4; j++) {
        if (comb1[i][j] == 1 && possiveis[j][fig] == 1) {
            jogada[j][fig] = 1;
            numAdd++;
        } else if (comb1[i][j] == 0) {
            jogada[j][fig] = 0;
        }
    }
    return numAdd;
}

int gerac2 (int possiveis[L][C], int fig, int i, int jogada[L][C]) {
    int comb2[6][4] = {{1,1,0,0},{1,0,1,0},{1,0,0,1},{0,1,1,0}, {0,1,0,1}, {0,0,1,1}};
    int numAdd = 0;
    for (int j = 0; j < 4; j++) {
        if (comb2[i][j] == 1 && possiveis[j][fig] == 1) {
            jogada[j][fig] = 1;
            numAdd++;
        } else if (comb2[i][j] == 0) {
            jogada[j][fig] = 0;
        }
    }
    return numAdd;
}

int gerac3 (int possiveis[L][C], int fig, int i, int jogada[L][C]) {
    int comb3[4][4] = {{1,1,1,0},{1,1,0,1},{1,0,1,1},{0,1,1,1}};
    int numAdd = 0;
    for (int j = 0; j < 4; j++) {
        if (comb3[i][j] == 1 && possiveis[j][fig] == 1) {
            jogada[j][fig] = 1;
            numAdd++;
        } else if (comb3[i][j] == 0) {
            jogada[j][fig] = 0;
        }
    }
    return numAdd;
}

int geraColuna (int possiveis[L][C], int fig, int c, int i, int jogada[L][C]) {
    int numAdd = 0;
    if (c == 1) {
        numAdd = gerac1 (possiveis, fig, i, jogada);
    } else if (c == 2) {
        numAdd = gerac2 (possiveis, fig, i, jogada);
    } else if (c == 3) {
        numAdd = gerac3 (possiveis, fig, i, jogada);
    } else {
        jogada[0][fig] = 1;
        jogada[1][fig] = 1;
        jogada[2][fig] = 1;
        jogada[3][fig] = 1;
        numAdd = numAdd + 4;
    }
    return numAdd;
}