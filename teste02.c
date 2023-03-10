#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 1000

int tamanho = 0;
int tamanho2 = 0;

int arq = 0;

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
void token(Texto *texto, Sumario *sumario);
void eliminar(Texto *texto);

int main() {


    preencher(texto);
    stw(stopwords);
	mostrar(texto, stopwords);
    removerStopWords(texto, stopwords);
    eliminar(texto);
	mostrar(texto, stopwords);

    //preencherSemRepetir(texto, sumario);

    /*printf("====================================\n");
    int i;
    for(i = 0; i < tamanho; i++){
     	printf("%s ", sumario[i].palavra);
    }*/

    
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
    for(i = 1; i < tamanho; i++){
     	printf("%s ", texto[i].palavra);
    }
    for(i = 1; i < tamanho2; i++){
     	printf("%s ", stopwords[i].plv);
    }
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

    //strcpy(sumario[0].palavra,texto[0].palavra);

    for(i = 1; i < tamanho; i++){
        for(j = 0; j < i; j++){
            if(strcmp(texto[j].palavra, texto[i].palavra) == 0){
                strcpy(sumario[j].palavra, "");
            } 
        }
    }


    for(i = 0; i < j; i++){
        strcpy(sumario[i].palavra, texto[i].palavra);
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
    int i = 0, l = 0;

    while(texto[i].palavra[l] != '\0'){
        if(texto[i].palavra[l] == '\0'){
            i++;
            l = 0;
        }

        if(texto[i].palavra[l] == ',' || texto[i].palavra[l] == '.'){
            strcpy(texto[i].palavra[l], "");
        }

        l++;
    }
}
