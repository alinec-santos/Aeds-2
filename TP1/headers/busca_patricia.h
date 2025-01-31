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


#ifndef BUSCA_PATRICIA_H
#define BUSCA_PATRICIA_H
#include "../headers/patricia.h"
#include "../headers/file_reader.h"
#include  "../headers/busca_hash.h" 



/*------------------------------------------------Funções de busca na Patricia-------------------------------------------------------------------------------*/
double calcular_tfpatrcia(int frequencia, int total_termos);
double calcular_idfpatricia(int num_documentos, int documentos_contendo_termo) ;
double calcular_tf_idfpatricia(double tf, double idf) ;
double calcular_relevanciapatricia(int total_termos_documento, double *tf_idfs, int num_termos) ;
int comparar_relevanciapatricia(const void *a, const void *b) ;
void buscar_e_calcular_relevancia_patricia(Patricia *arvore, const char **termos, int num_termos, ListaArquivos *lista_arquivos) ;


#endif // BUSCA_PATRICIA_H