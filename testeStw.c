#include <stdio.h>
#include <string.h>

#define MAX 1000

int tamanho = 0;
int tamanho2 = 0;

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

Sumario sumario[MAX];
Texto texto[MAX];
Stopwords stopwords[MAX];

void preencher(Texto *texto);
void stw(Stopwords *stopwords);
void mostrar(Texto *texto, Stopwords *stopwords);
void removerStopWords(Texto *texto, Stopwords *stopwords);
void preencherSemRepetir(Texto *texto, Sumario *sumario);

int main() {


    preencher(texto);
    stw(stopwords);
	mostrar(texto, stopwords);
    removerStopWords(texto, stopwords);
    //mostrar(texto, stopwords);
    preencherSemRepetir(texto, sumario);

    int i;

    printf("Palavras sem repetir:\n");
    for(i = 0; i < tamanho; i++){
        if(strcmp(texto[i].palavra, "") != 0){
     	    printf("%s ", texto[i].palavra);
        }
    }

    printf("\n\nSumario:\n");
    for(i = 0; i < tamanho; i++){
        if(strcmp(sumario[i].palavra, "") != 0){
     	    printf("%s\n", sumario[i].palavra);
        }
    }

    printf("\n\n");


    
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
    file = fopen("stopwords.txt","r");

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
  
    int l = 0;

    for(j = 0; j < tamanho; j++){
        if(strcmp(texto[j].palavra, "") != 0){
            strcpy(sumario[l].palavra, texto[j].palavra);
            l++;
        } 
    }
}


