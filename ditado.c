#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct aluno{
    int id;
    float nota;
    char palavra[20];
    int **mat;
};

typedef struct aluno ALUNO;

ALUNO aluno[5];

int QTD_ALUNOS = 5;

int PRIMEIRO_ALUNO = 0;
int SEGUNDO_ALUNO  = 1;
int TERCEIRO_ALUNO = 2;
int QUARTO_ALUNO   = 3;
int QUINTO_ALUNO   = 4;

void imprime_matriz(int pos_aluno, char palavra_padrao[20]){

    int i, j;
    int linhas, colunas;

    linhas = strlen(aluno[pos_aluno].palavra) + 2;

    colunas = strlen(palavra_padrao) + 2;

    printf("+-----------------------------------------------------------+\n");

    for(i=0;i<linhas;i++){
        for(j=0;j<colunas;j++){
            printf("| %3d ", aluno[pos_aluno].mat[i][j]);
        }
        printf("|\n");
        printf("+-----------------------------------------------------------+\n");
    }

}

void salva_matriz_aluno(int **mat, int pos_aluno, char palavra_padrao[20]){

    int i, j;
    int linhas, colunas;

    colunas = strlen(palavra_padrao) + 2;

    linhas = strlen(aluno[pos_aluno].palavra) + 2;

    aluno[pos_aluno].mat = (int**)malloc(linhas * sizeof(int*));

    for(i=0;i<linhas;i++){
        aluno[pos_aluno].mat[i] = (int*)malloc(colunas * sizeof(int*));
    }

    for(i=0;i<linhas;i++){
        for(j=0;j<colunas;j++){
            aluno[pos_aluno].mat[i][j] = mat[i][j];
        }
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

void desaloca_matriz(int **mat, int linhas){

    int i;

    for(i=0;i<linhas;i++){
        free(mat[i]);
    }

    free(mat);
    
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

void mostra_resultado(){

    int i;
    float maior_nota;
    int count;

    maior_nota = aluno[PRIMEIRO_ALUNO].nota;

    for(i=1;i<QTD_ALUNOS;i++){
        if(aluno[i].nota > maior_nota){
            maior_nota = aluno[i].nota;
        }
    }

    if(maior_nota == 0){
        return;
    }

    printf("%.1f\n", maior_nota);

    count = 0;

    for(i=0;i<QTD_ALUNOS;i++){
        if(aluno[i].nota == maior_nota){
            if(count > 0){
                printf(" ");
            }

            printf("%d", (i + 1));
            count++;
        }
    }

    printf("\n");

}

void inicializa_matriz_aluno(){

    int i;

    for(i=0;i<QTD_ALUNOS;i++){
        //free(aluno[i].mat);
        aluno[i].mat = NULL;
    }

}

void calculo_distancia(char palavra_padrao[20]){

    int i, j, k;
    int qtd_letras_palavra_padrao, qtd_letras_palavra_aluno;
    int **mat;
    int indicador, diagonal_superior, diagonal_inferior, diagonal_central;
    int menor;
    int alguem_acertou;
    float nota[QTD_ALUNOS];

    alguem_acertou = 0;

    for(i=0;i<QTD_ALUNOS;i++){
        nota[i] = 0;
    }

    for(k=0;k<QTD_ALUNOS;k++){

        qtd_letras_palavra_padrao = strlen(palavra_padrao) + 2;

        qtd_letras_palavra_aluno = strlen(aluno[k].palavra) + 2;

        mat = aloca_matriz(mat, qtd_letras_palavra_aluno, qtd_letras_palavra_padrao);
        mat = inicializa_matriz(mat, qtd_letras_palavra_aluno, qtd_letras_palavra_padrao);

        // ATRIBUICAO DAS STRINGS PARA A MATRIZ
        for(i=2;i<qtd_letras_palavra_aluno;i++){
            mat[i][0] = aluno[k].palavra[i-2];
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

        // VERIFICA SE O ALUNO ACERTOU A PALAVRA
        if(mat[qtd_letras_palavra_aluno-1][qtd_letras_palavra_padrao-1] == 0){
            //aluno[k].nota += 1;
            nota[k] = 1;
            alguem_acertou = 1;
        }
        
        salva_matriz_aluno(mat, k, palavra_padrao);
        desaloca_matriz(mat, qtd_letras_palavra_aluno);
    }

    //CASO ALGUM ALUNO TENHA ACERTADO, ATRIBUÍMOS AS NOTAS DE CADA UM
    if(alguem_acertou == 1){
        for(i=0;i<QTD_ALUNOS;i++){
            aluno[i].nota += nota[i];
        }
    }

    // CASO NENHUM ALUNO TENHA ACERTADO TODA A PALAVRA
    if(alguem_acertou == 0){

        qtd_letras_palavra_aluno = strlen(aluno[PRIMEIRO_ALUNO].palavra) + 2;
        menor = aluno[PRIMEIRO_ALUNO].mat[qtd_letras_palavra_aluno-1][qtd_letras_palavra_padrao-1];

        for(i=1;i<QTD_ALUNOS;i++){
            qtd_letras_palavra_aluno = strlen(aluno[i].palavra) + 2;

            if(aluno[i].mat[qtd_letras_palavra_aluno-1][qtd_letras_palavra_padrao-1] < menor){
               menor = aluno[i].mat[qtd_letras_palavra_aluno-1][qtd_letras_palavra_padrao-1];
            }
        }

        for(i=0;i<QTD_ALUNOS;i++){
            qtd_letras_palavra_aluno = strlen(aluno[i].palavra) + 2;
            if(aluno[i].mat[qtd_letras_palavra_aluno-1][qtd_letras_palavra_padrao-1] == menor){
                aluno[i].nota += 0.5;
            }
        }
    }

    inicializa_matriz_aluno();

}

void calcula_nota(char palavra_padrao[20]){

    int i;
    int qtd_letras_palavra_padrao, qtd_letras_palavra_aluno;

    qtd_letras_palavra_padrao = strlen(palavra_padrao) + 2;

    for(i=0;i<QTD_ALUNOS;i++){

        qtd_letras_palavra_aluno = strlen(aluno[i].palavra) + 2;

        if(aluno[i].mat[qtd_letras_palavra_aluno][qtd_letras_palavra_padrao] == 0){
            aluno[i].nota += 1;
        }
    }

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

        calculo_distancia(palavra);

    }

    mostra_resultado();

}

int main(){

    ditado();

    return 0;
}