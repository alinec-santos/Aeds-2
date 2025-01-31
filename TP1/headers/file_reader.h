/* ------------------------------------------------------------------------------------------------------------------------------------------------------------

    Universidade Federal De Viçosa - Campus Florestal
    Trabalho prático 1 de Algorítimos e estrutura de dados 2
    
    Professora responsável: 
        Glaucia Braga e Silva
        
    Integrantes do Gupo:
        Aline Cristina - 5791
        Luana Tavares  - 5364
        Rafaella Pinheiro - 5363

------------------------------------------------------------------------------------------------------------------------------------------------------------ */

#ifndef FILE_READER_H
#define FILE_READER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int cont_arquivos;
    char **nomes_arquivos;
    int *total_termos;  
} ListaArquivos;

/*--------------------------------------Funções De Manipulaçao de Arquivos----------------------------------------------------------------*/
ListaArquivos* ler_lista_arquivos(const char *nome_arquivo);
void liberar_lista_arquivos(ListaArquivos *lista_arquivos);
char** ler_arquivo_receita(const char *nome_arquivo, int *num_ingredientes, int *num_passos);
void contar_total_termos(ListaArquivos *lista_arquivos);

#endif // FILE_READER_H
