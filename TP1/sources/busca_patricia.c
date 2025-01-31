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

#include <stdio.h>
#include <stdlib.h>
#include <math.h> 
#include <string.h>
#include "../headers/file_reader.h"
#include "../headers/patricia.h"
#include "../headers/busca_patricia.h"


/*--------------------------------------Funções De Busca na PATRICIA----------------------------------------------------------------*/
// Calcula o TF
double calcular_tfpatricia(int frequencia, int total_termos) {
    if (total_termos == 0) {
        return 0.0; // Evita divisão por zero
    }
    return (double)frequencia / total_termos;
}
// Calcula o IDF
double calcular_idfpatricia(int num_documentos, int documentos_contendo_termo) {
    if (documentos_contendo_termo == 0) {
        return log((double)num_documentos + 1); // Ajuste para evitar log(0)
    }
    return log((double)num_documentos / (documentos_contendo_termo + 1) + 1);
}
// Calcula o TF-IDF
double calcular_tf_idfpatricia(double tf, double idf) {
    return tf * idf;
}
// Calcula a relevância de um documento
double calcular_relevanciapatricia(int total_termos_documento, double *tf_idfs, int num_termos) {
    double soma = 0;
    for (int i = 0; i < num_termos; i++) {
        soma += tf_idfs[i];
    }
    if (total_termos_documento == 0) {
        return 0.0; // Evita divisão por zero
    }
    return soma / total_termos_documento;
}
// Função para comparar dois documentos com base na relevância
int comparar_relevanciapatricia(const void *a, const void *b) {
    int index_a = *(const int *)a;
    int index_b = *(const int *)b;
    
    if (relevancias_global[index_a] < relevancias_global[index_b]) return 1;
    if (relevancias_global[index_a] > relevancias_global[index_b]) return -1;
    return 0;
}
// Função para calucular e após bucar com base nas relevâncias 
void buscar_e_calcular_relevancia_patricia(Patricia *arvore, const char **termos, int num_termos, ListaArquivos *lista_arquivos) {
    // Atualizar o total de termos antes de realizar a busca e cálculo
    contar_total_termos(lista_arquivos);

    int num_documentos = lista_arquivos->cont_arquivos;
    double *relevancias = (double *)calloc(num_documentos, sizeof(double));
    int *documentos_indices = (int *)malloc(num_documentos * sizeof(int));
    
    // Armazenar a referência global de relevâncias
    relevancias_global = relevancias;

    for (int i = 0; i < num_documentos; i++) {
        documentos_indices[i] = i; // Inicializar com o índice do documento
        double *tf_idfs = (double *)calloc(num_termos, sizeof(double));// Alocação tf_idfs

        for (int j = 0; j < num_termos; j++) {
            tipoPalavra *palavra_indexada = pesquisaPatricia((char *)termos[j], *arvore);
            if (palavra_indexada) {
                // Encontrou a palavra na árvore PATRICIA
                int frequencias = 0; // Frequência no documento específico
                for (int k = 0; k < palavra_indexada->num_ocorrencias; k++) {
                    if (palavra_indexada->cont_ocorrencias[k].idDoc_pat == i) {
                        frequencias += palavra_indexada->cont_ocorrencias[k].qtde_pat;
                    }
                }

                double tf = calcular_tfpatricia(frequencias, lista_arquivos->total_termos[i]);
                double idf = calcular_idfpatricia(num_documentos, palavra_indexada->num_ocorrencias);
                tf_idfs[j] = calcular_tf_idfpatricia(tf, idf);
            }
        }

        relevancias[i] = calcular_relevanciapatricia(lista_arquivos->total_termos[i], tf_idfs, num_termos);
        free(tf_idfs); // Liberar memória alocada
    }

    // Ordenar os documentos com base na relevância
    qsort(documentos_indices, num_documentos, sizeof(int), comparar_relevanciapatricia);

    // Exibir os documentos em ordem decrescente de relevância
    for (int i = 0; i < num_documentos; i++) {
        int index = documentos_indices[i];
        printf("------------------------------------------\n");
        printf("Documento %d\nRelevância: %.3f\n", index + 1, relevancias[index]);
    }

    free(relevancias);
    free(documentos_indices);
}