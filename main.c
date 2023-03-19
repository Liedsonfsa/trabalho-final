#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 1000

int tamanho = 0;
int tamanho2 = 0;

int suma = 0;

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

void preencher(Texto *texto, char *arq);
void stw(Stopwords *stopwords, const char *arqStp);
void removerStopWords(Texto *texto, Stopwords *stopwords);
void preencherSemRepetir(Texto *texto, Sumario *sumario);
void eliminar(Texto *texto);
void copiar(Texto *texto, Origem *origem);
void comparacao(Sumario *sumario, Origem *origem);
void ordenar(Sumario *sumario);
void salvar(Sumario *sumario, char *sKOaida, int quantidade); 

int main(int argc, char **argv) {

    int n = atoi(argv[1]);
    argc++;

    if(n != 2){
        printf("Nao existe o caminho para arquivo HTML.");
        return 0;
    } else{

        char *arq = argv[2];
        char *stp = argv[4];
        char *saida = argv[5];
        int a = atoi(argv[3]);

        preencher(texto, arq);
        stw(stopwords, stp);
        removerStopWords(texto, stopwords);   
        eliminar(texto);
        copiar(texto, origem);
        preencherSemRepetir(texto, sumario);
        comparacao(sumario, origem);
        ordenar(sumario);    
        salvar(sumario, saida, a);
    }
    return 0;
}     

void preencher(Texto *texto, char *arq){
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

void stw(Stopwords *stopwords,  const char *arqStp){
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

void removerStopWords(Texto *texto, Stopwords *stopwords){
    int i, j;
   
    for(i = 0; i < MAX; i++){
        for(j = 0; j < MAX; j++){
            if(strcasecmp(texto[i].palavra, stopwords[j].plv) == 0){
                strcpy(texto[i].palavra, "");
            }
        }
    }
}

void preencherSemRepetir(Texto *texto, Sumario *sumario){
    int i, j;


    for(i = 0; i < tamanho; i++){
        for(j = 0; j < i; j++){
            if(strcasecmp(texto[j].palavra, texto[i].palavra) == 0){
                strcpy(texto[j].palavra, "");
            }
        }
    }


    for(j = 0; j < tamanho; j++){
        if(strcmp(texto[j].palavra, "") != 0){
            strcpy(sumario[suma].palavra, texto[j].palavra);
            sumario[suma].quantidade = 0;
            suma++;
        } 
    }
}

void eliminar(Texto *texto){
    int i;

    char aux[50];
   
    for(i = 0; i < tamanho; i++){
        strcpy(aux, texto[i].palavra);

        int l = 0;

        int ver = 0;

        while(aux[l] != '\0'){
            if(aux[l] == ',' || aux[l] == '.' || aux[l] == '?' || aux[l]  == '!' || aux[l] == ';'){
                ver = 1;
            }

            l++;
        }

        if(ver){
            aux[l - 1] = '\0';
        }

        strcpy(texto[i].palavra, aux);
        
    }
}

void comparacao(Sumario *sumario, Origem *origem){
    int i, j;
   
    for(i = 0; i < suma; i++){
        for(j = 0; j < tamanho; j++){
            if(strcasecmp(sumario[i].palavra, origem[j].palavra) == 0){
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

void salvar(Sumario *sumario, char *saida, int quantidade){
	int i;

	FILE *file = fopen (saida, "w");
   
    i = 0;

    if(file){
        while ( quantidade-- ) {

            if(sumario[i].quantidade == 0){
                break;
            } else{
                fprintf(file, "%s   %d\n", sumario[i].palavra, sumario[i].quantidade);	 
            }

            i++;  

        }
        fclose(file);
    }
}
