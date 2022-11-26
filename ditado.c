#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct aluno{
    int id;
    double nota;
    char palavra[20];
};

typedef struct aluno ALUNO;

ALUNO aluno[5];

int QTD_ALUNOS = 5;

int PRIMEIRO_ALUNO = 0;
int SEGUNDO_ALUNO  = 1;
int TERCEIRO_ALUNO = 2;
int QUARTO_ALUNO   = 3;
int QUINTO_ALUNO   = 4;

void imprime_matriz(int **mat, int linhas, int colunas){

    int i, j;

    printf("+-----------------------------------------------------------------+\n");

    for(i=0;i<linhas;i++){
        for(j=0;j<colunas;j++){
            printf("| %3d ", mat[i][j]);
        }
        printf("|\n");
        printf("+-----------------------------------------------------------------+\n");
    }

}

int ** aloca_matriz(int **mat, int linhas, int colunas){

    int i;

    mat = (int**)malloc(linhas * sizeof(int*));

    for(i=0;i<linhas;i++){
        mat[i] = (int*)malloc(colunas * sizeof(int*));
    }

    return mat;

}

int ** inicializa_matriz(int **mat, int linhas, int colunas){

    int i,j;

    for(i=0;i<linhas;i++){
        for(j=0;j<colunas;j++){
            mat[i][j] = 0;
        }
    }

    return mat;

}

void calculo_distancia(char palavra_padrao[20], char palavra_aluno[20]){

    int i, j;
    int qtd_letras_palavra_padrao, qtd_letras_palavra_aluno;
    int **mat;
    int indicador, diagonal_superior, diagonal_inferior, diagonal_central;
    int menor;

    qtd_letras_palavra_padrao = strlen(palavra_padrao) + 2;

    qtd_letras_palavra_aluno = strlen(palavra_aluno) + 2;

    mat = aloca_matriz(mat, qtd_letras_palavra_aluno, qtd_letras_palavra_padrao);
    mat = inicializa_matriz(mat, qtd_letras_palavra_aluno, qtd_letras_palavra_padrao);

    // ATRIBUICAO DAS STRINGS PARA A MATRIZ
    for(i=2;i<qtd_letras_palavra_aluno;i++){
        mat[i][0] = palavra_aluno[i-2];
    }
    for(j=2;j<qtd_letras_palavra_padrao;j++){
        mat[0][j] = palavra_padrao[j-2];
    }

    // INICIALIZANDO OS VALORES PADRÕES
    for(i=1;i<qtd_letras_palavra_aluno;i++){
        mat[i][1] = i-1;
        for(j=1;j<qtd_letras_palavra_padrao;j++){
            if(i == 1){
                mat[i][j] = j-1;
            }
        }
    }

    // REALIZANDO OS CALCULOS
    for(i=1;i<qtd_letras_palavra_aluno;i++){
        for(j=1;j<qtd_letras_palavra_padrao;j++){
            if(mat[i][0] == mat[0][j]){
                indicador = 0;
            }else{
                indicador = 1;
            }

            diagonal_superior = mat[i-1][j] + 1;
            diagonal_inferior = mat[i][j-1] + 1;
            diagonal_central = mat[i-1][j-1] + indicador;

            // VERIFICAR O MENOR
            if((diagonal_inferior <= diagonal_central) && (diagonal_inferior <= diagonal_superior)){
                mat[i][j] = diagonal_inferior;
            }

            if((diagonal_central <= diagonal_inferior) && (diagonal_central <= diagonal_superior)){
                mat[i][j] = diagonal_central;
            }

            if((diagonal_superior <= diagonal_central) && (diagonal_superior <= diagonal_inferior)){
                mat[i][j] = diagonal_superior;
            }

            if((diagonal_central == diagonal_inferior) && (diagonal_central == diagonal_superior)){
                mat[i][j] = diagonal_central;
            }

        }
    }

    imprime_matriz(mat, qtd_letras_palavra_aluno, qtd_letras_palavra_padrao);

}

void inicializa_alunos(){

    int i;

    for(i=0;i<QTD_ALUNOS;i++){
        aluno[i].id = i;
        aluno[i].nota = 0;
    }

}

int retorna_quantidade_palavras(){

    int qtd;
    int saida_laco;

    saida_laco = 0;

    while(!saida_laco){
        scanf("%d", &qtd);

        if(qtd > 0){
            saida_laco = 1;
        }
    }

    return qtd;

}

void ditado(){

    int qtd_palavras;
    int i;
    char palavra[20];

    inicializa_alunos();

    qtd_palavras = retorna_quantidade_palavras();

    for(i=0;i<qtd_palavras;i++){

        scanf("%s", palavra);

        scanf("%s %s %s %s %s", aluno[PRIMEIRO_ALUNO].palavra,
                                aluno[SEGUNDO_ALUNO].palavra,
                                aluno[TERCEIRO_ALUNO].palavra,
                                aluno[QUARTO_ALUNO].palavra,
                                aluno[QUINTO_ALUNO].palavra);

        calculo_distancia(palavra, aluno[PRIMEIRO_ALUNO].palavra);

    }

}

int main(){

    ditado();

    return 0;
}