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

void preencher(Texto *texto, char *arq[]);
void stw(Stopwords *stopwords, char *arqStp[]);
void mostrar(Texto *texto, Stopwords *stopwords);
void removerStopWords(Texto *texto, Stopwords *stopwords);
void output(Texto *texto, char *saida[]);

int main(int tipo, char *arq[], int quantidade, char *arqStp[], char *saida[]) {


    preencher(texto, arq);
    stw(stopwords, arqStp);
	//mostrar(texto, stopwords);
    removerStopWords(texto, stopwords);
    //mostrar(texto, stopwords);
    output(texto, saida);

    
    return 0;
}

void preencher(Texto *texto, char *arq[]){
    FILE *file;
    file = fopen(arq,"r");

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

void stw(Stopwords *stopwords, char *arqStp[]){
    FILE *file;
    file = fopen(arqStp,"r");

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
    for(i = 0; i < tamanho; i++){
     	printf("%s ", texto[i].palavra);
    }
    for(i = 0; i < tamanho2; i++){
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

void output(Texto *texto, char *saida[]){
    FILE *out;

    out = fopen(saida,"w");

    if(out){
        int i;

        for(i = 0; i < MAX; i++){
            fprintf(out,"%s\n",texto[i].palavra);
        }

        fclose(out);
    } else{
        printf("Arquivo nao criado!\n");
    }
}

