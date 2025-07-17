#include <stdio.h>
#include <wchar.h>
#include <assert.h>
#include <locale.h>
#include <stdlib.h>
#include "header.h"

int main () {
    setlocale(LC_CTYPE, "C.UTF-8");
    // Numero de jogadas
    /* int nTestes;
    assert(wscanf(L"%d ", &nTestes) == 1); */
    // PROBLEMA A
    /* for (int i = 0; i < nTestes; i++) {
        wchar_t linha[100];
        assert(fgetws(linha, 100, stdin));
        ConjCartas *c = (ConjCartas *)malloc(sizeof(ConjCartas));
        analisaLinha(c, linha);
    } */
    // PROBLEMA B
    /* for (int i = 0; i < nTestes; i++) {
        int m;
        assert(wscanf(L"%d ", &m) == 1);
        wchar_t input[m][1][100];
        for (int j = 0; j < m; j++) {
            wchar_t linha[100];
            assert(fgetws(linha, 100, stdin));
            wcscpy(input[j][0], linha);
        }
        processaInputs(input, m, i+1);
    } */
    // PROBLEMA C
    /* for (int i = 0; i < nTestes; i++) {
        int nJogadas; 
        assert(wscanf(L"%d ", &nJogadas) == 1);
        wchar_t mao[100];
        assert(fgetws(mao, 100, stdin));
        wchar_t jogadasAnt[nJogadas][1][100];
        for (int j = 0; j < nJogadas; j++) {
            wchar_t linha[100];
            assert(fgetws(linha, 100, stdin));
            wcscpy(jogadasAnt[j][0], linha);
        }
        wchar_t jogada[100];
        assert(fgetws(jogada, 100, stdin));
        analisaJogada(mao, jogadasAnt, jogada, nJogadas, i+1);
    } */
    // PROBLEMA D
    /* for (int i = 0; i < nTestes; i++) {
        wchar_t linha[100];
        assert(fgetws(linha, 100, stdin));
        wchar_t mao[100];
        assert(fgetws(mao, 100, stdin));
        geraPossibs(mao, linha, i+1);
    } */
    int nAnt;
    assert(wscanf(L"%d ", &nAnt) == 1);
    wchar_t mao[100];
    assert(fgetws(mao, 100, stdin));
    wchar_t jogadasAnt[nAnt][1][100];
    for (int j = 0; j < nAnt; j++) {
        wchar_t linha[100];
        assert(fgetws(linha, 100, stdin));
        wcscpy(jogadasAnt[j][0], linha);
    }
    imprimeValida(mao, jogadasAnt, nAnt);
}