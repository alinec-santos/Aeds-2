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

#ifndef HASH_H
#define HASH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX_DOCS 100

typedef struct {
    int idDoc;
    int quantidade;
} Ocorrencia;

typedef struct NoEntrada {
    Ocorrencia *ocorrencias;
    char *palavra;
    int cont_ocorrencias;
    int capacidade_ocorrencias;
    struct NoEntrada *prox;
    int cont_docs; 
    int *docs; 
} EntradaIndiceInvertido;

typedef struct {
    EntradaIndiceInvertido **tabela;
    int tamanho;
    int capacidade;
} IndiceInvertidoHash;

typedef struct {
    int idDoc;
    double relevancia;
} ResultadoBusca;


/*--------------------------------------Funções Hash----------------------------------------------------------------*/
unsigned int funcao_hash(const char *palavra, int capacidade);
IndiceInvertidoHash *criar_tabela_hash(int capacidade);
void liberar_tabela_hash(IndiceInvertidoHash *tabela_hash);
void adicionar_entrada_hash(IndiceInvertidoHash *hash, EntradaIndiceInvertido *entrada);

/*--------------------------------------Funções Auxiliares----------------------------------------------------------------*/
void remover_ponto_final(char *palavra) ;
int comparar_palavras(const void *a, const void *b) ;

/*--------------------------------------Funções Indice Invertido Hash----------------------------------------------------------------*/
EntradaIndiceInvertido *criar_nova_entrada(const char *palavra);
void atualizar_ocorrencias(EntradaIndiceInvertido *entrada, int quantidade, int idDoc) ;
void inserir_hash(IndiceInvertidoHash *hash, const char *palavra, int idDoc, int quantidade) ;
void construir_indices_invertidos(ListaArquivos *lista_arquivos, IndiceInvertidoHash *indice_hash, int *id_doc);
EntradaIndiceInvertido *buscar_entrada_hash(IndiceInvertidoHash *hash, const char *palavra);
void imprimir_indices_invertidos(IndiceInvertidoHash *indice_hash);

#endif // HASH_H
