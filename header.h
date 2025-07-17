#define L 4
#define C 14

typedef struct conjuntoCartas {
    int numCartas;
    int tipoConj;
    wchar_t maiorCarta;
    int nFiguras[14];
    int cartas[4][14]; //Naipes x Figuras
} ConjCartas;

typedef struct jogada {
    int jogada[L][C];
    struct jogada *prox;
} *JogadasPossibs;

/* 
TIPOS CONJUNTO
0: Nada
1: Conjunto
2: Dupla Sequência
3: Sequência
 */

// A

void analisaLinha (ConjCartas *c, wchar_t linha[]);

void determinaTipo (ConjCartas *c);

void contaFigs(ConjCartas *c);

int verifNaipe (int cartas[L][C], int l, int v);

int isConjunto (int cartas[L][C], int n);

int isConsecutivo (int cartas[L][C], int v);

wchar_t converteCarta (int n, int v);

wchar_t maiorCarta (int cartas[L][C]);

int isSequencia (int cartas[L][C], int n);

int verifPar (int cartas[L][C], int l, int v);

int isDuplaSeq (int cartas[L][C], int n);

// B

void processaInputs (wchar_t input[][1][100], int n);

int elemsIguais (int arr[], int n);

void printMao (ConjCartas c[], int n);

// C

void analisaJogada (wchar_t mao[100], wchar_t jogadasAnt[][1][100], wchar_t jogada[100], int n);

void efetuaJogada (ConjCartas *cjog, ConjCartas *cmao);

int determinaUltima (wchar_t jogadasAnt[][1][100], int nJogadas);

int jogadaValida (ConjCartas *cjog, wchar_t jogadasAnt[][1][100], int nJogadas);

int contaReis (ConjCartas *ultima);

// D

void geraPossibs (wchar_t mao[100], wchar_t jogadaAnt[100], int jogadas[10000][L][C], int *numJogadas);

int geraUsaveisConj (int mao[L][C], int usaveis[L][C], int naiM, int valM, int f, int c, ConjCartas *cant);

int geraUsaveisConj1 (int mao[L][C], int usaveis[L][C], int naiM, int valM, int f);

int geraUsaveis (int mao[L][C], int usaveis[L][C], int f);

void geraCartasPorFig (int usaveis[L][C], int cartasPorFig[14]);

void trataUsaveisDS (int usaveis[L][C], int naiM, int valM, int s, int f, int excl[4], ConjCartas *cant);

void trataUsaveis (int usaveis[L][C], int naiM, int valM, int s, int c, int f, int excl[4], ConjCartas *cant);

void copiaUsaveis (int mao[L][C], ConjCartas *cant, int jogadas[][L][C], int c, int s, int *numJogadas, int naiM, int valM, int f, int tamMax);

void copiaM (int a[L][C], int jogadas[][L][C], int n);

void caso1 (int usaveis[L][C], int v, int s, int tamMax, int tamAtual, int cartasPorFig[14], int jogadas[][L][C], int jogadaAtual[L][C], int *nJ, int *myS);

void caso2 (int usaveis[L][C], int v, int s, int tamMax, int tamAtual, int cartasPorFig[14], int jogadas[][L][C], int jogadaAtual[L][C], int *nJ, int *myS);

void caso3 (int usaveis[L][C], int v, int s, int tamMax, int tamAtual, int cartasPorFig[14], int jogadas[][L][C], int jogadaAtual[L][C], int *nJ, int *myS);

void casoCT (int usaveis[L][C], int v, int c, int s, int tamMax, int tamAtual, int cartasPorFig[14], int jogadas[][L][C], int jogadaAtual[L][C], int *nJ, int *myS);

int geraJogadas (int usaveis[L][C], int c, int s, int v, int tamMax, int tamAtual, int cartasPorFig[14], int jogadas[][L][C], int jogadaAtual[L][C], int *nJ, int *myS);

int gerac1 (int possiveis[L][C], int fig, int i, int jogada[L][C]);

int gerac2 (int possiveis[L][C], int fig, int i, int jogada[L][C]);

int gerac3 (int possiveis[L][C], int fig, int i, int jogada[L][C]);

int geraColuna (int possiveis[L][C], int fig, int c, int i, int jogada[L][C]);

// E

void imprimeValida (wchar_t mao[100], wchar_t jogadasAnt[][1][100], int nAnt);

int imprimeJogada(int jogadas[][L][C], int *nJ, int jogadasAnt[][1][100], int nAnt);

void geraQualquer (ConjCartas *cmao, int jogadas[][L][C], int *nJ);

// GLOBAIS

int contaElem (wchar_t linha[]);

void terminaLinha (wchar_t linha[], int n);

int getNaipe (wchar_t carta);

int getValor (wchar_t carta);

void resetMatriz(int matrix[L][C]);

void inicializaArr (int arr[], int n);

void printCartasMatrix (int matrix[L][C]);

void printCartasMatrixOrd (int matrix[L][C]);

int cmpfunc(const void *a, const void *b);

int comparaCartas (wchar_t c1, wchar_t c2);

int contaElemsMatrix (int mat[L][C]);

void printLinha (wchar_t linha[]);

void printMatrix(int matrix[L][C]);

void printArray (int arr[], int n);

void matrixToLinha (int matrix[L][C], wchar_t str[100]);