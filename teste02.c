#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 1000

int tamanho = 0;
int tamanho2 = 0;

int arq = 0, org = 0, suma = 0;

typedef struct{
    int quantidade;    
    char palavra[50];
} Sumario;

typedef struct{
    char palavra[50];
} Texto;

typedef struct{
    char plv[50];
} Stopwords;

typedef struct{
    char palavra[50];
} Origem;

Sumario sumario[MAX];
Texto texto[MAX];
Stopwords stopwords[MAX];
Origem origem[MAX];

void preencher(Texto *texto);
void stw(Stopwords *stopwords);
void mostrar(Texto *texto, Stopwords *stopwords);
void removerStopWords(Texto *texto, Stopwords *stopwords);
void preencherSemRepetir(Texto *texto, Sumario *sumario);
void token(Texto *texto, Sumario *sumario);
void eliminar(Texto *texto);
void copiar(Texto *texto, Origem *origem);
void comparacao(Sumario *sumario, Origem *origem);
void ordenar(Sumario *sumario);

int main() {


    preencher(texto);
    stw(stopwords);
	mostrar(texto, stopwords);
    copiar(texto, origem);
    removerStopWords(texto, stopwords);
    eliminar(texto);
    preencherSemRepetir(texto, sumario);
    comparacao(sumario, origem);
	
    printf("\n\n\nTexto sem repeticoes:\n");
    int i;

    for(i = 0; i < tamanho; i++){
        if(strcmp(texto[i].palavra, "") != 0){
     	    printf("%s ", texto[i].palavra);
        }
    }


    printf("\n\n\nSumario:\n");
    for(i = 0; i < tamanho; i++){
        if(strcmp(sumario[i].palavra, "") != 0){
     	    printf("%s %d\n", sumario[i].palavra, sumario[i].quantidade);
        }
    }

    printf("\n\n");

    ordenar(sumario);

    printf("Ordenado pela quantidade:\n");
    for(i = 0; i < tamanho; i++){
        if(strcmp(sumario[i].palavra, "") != 0){
     	    printf("%s %d\n", sumario[i].palavra, sumario[i].quantidade);
        }
    }
    
    return 0;
}

void preencher(Texto *texto){
    FILE *file;
    file = fopen("testetrab2.txt","r");

    if(file){

        int i;
        for(i = 0; i < MAX; i++){
            fscanf(file,"%s",texto[tamanho].palavra);
            tamanho++;
        }

        fclose(file);
    } else{
        printf("Arquivo nao encontrado!\n");
    }
}

void stw(Stopwords *stopwords){
    FILE *file;
    file = fopen("stopow2.txt","r");

    if(file){

        int i;
        for(i = 0; i < MAX; i++){
            fscanf(file,"%s",stopwords[tamanho2].plv);
            tamanho2++;
        }

        fclose(file);
    } else{
        printf("Arquivo nao encontrado!\n");
    }
}

void mostrar(Texto *texto, Stopwords *stopwords){
    int i;

    printf("Palavras:\n");
    for(i = 0; i < tamanho; i++){
        if(strcmp(texto[i].palavra, "") != 0){
     	    printf("%s ", texto[i].palavra);
        }
    }

    printf("\n\nStopwords:\n");
    for(i = 0; i < tamanho2; i++){
        if(strcmp(stopwords[i].plv, "") != 0){
     	    printf("%s ", stopwords[i].plv);
        }
    }

    printf("\n\n");
}

void removerStopWords(Texto *texto, Stopwords *stopwords){
    int i, j;

    for(i = 0; i < MAX; i++){
        for(j = 0; j < MAX; j++){
            if(strcmp(texto[i].palavra, stopwords[j].plv) == 0){
                strcpy(texto[i].palavra, "");
            }
        }
    }

    
}

void preencherSemRepetir(Texto *texto, Sumario *sumario){
    int i, j;

    for(i = 0; i < tamanho; i++){
        for(j = 0; j < i; j++){
            if(strcmp(texto[j].palavra, texto[i].palavra) == 0){
                strcpy(texto[j].palavra, "");
            }
        }
    }

    //int l = 0;

    for(j = 0; j < tamanho; j++){
        if(strcmp(texto[j].palavra, "") != 0){
            strcpy(sumario[suma].palavra, texto[j].palavra);
            sumario[suma].quantidade = 0;
            suma++;
        } 
    }
}


void token(Texto *texto, Sumario *sumario){
    char *pt;

    int i;

    for(i = 0; i < MAX; i++){
        pt = strtok(texto[i].palavra, "!, .;?");

        while(pt){
            strcpy(sumario[i].palavra, pt);
            pt = strtok(NULL, "!, .;?");
        }
    }
}

void eliminar(Texto *texto){
    int i;

    for(i = 0; i < tamanho; i++){
        if(texto[i].palavra == ',' || texto[i].palavra == '.'){
            strcpy(texto[i].palavra, "");
        }
    }
}

void comparacao(Sumario *sumario, Origem *origem){
    int i, j;

    for(i = 0; i < suma; i++){
        for(j = 0; j < tamanho; j++){
            if(strcmp(sumario[i].palavra, origem[j].palavra) == 0){
                sumario[i].quantidade++;
            }
        }
    }
}

void copiar(Texto *texto, Origem *origem){
    int i;

    for(i = 0; i < tamanho; i++){
        strcpy(origem[i].palavra, texto[i].palavra);
    }
}

void ordenar(Sumario *sumario){
    int i, j;
    int quant;
    char auxPalavra[50];

    for(i = 1; i < tamanho; i++){
        quant = sumario[i].quantidade;
        strcpy(auxPalavra, sumario[i].palavra);

        j = i - 1;
        while((j >= 0) && quant > sumario[j].quantidade){
            sumario[j + 1].quantidade = sumario[j].quantidade;
            strcpy(sumario[j + 1].palavra, sumario[j].palavra);

            j--;
        }

        sumario[j + 1].quantidade = quant;
        strcpy(sumario[j + 1].palavra, auxPalavra);
    }
}

