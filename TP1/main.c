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
#include <string.h>
#include "headers/file_reader.h"
#include "headers/hash.h"
#include "headers/patricia.h"
#include "headers/menu.h"
#include "headers/contadores.h" 


//contadores globais para comparações nas estruturas
int comparacoes_insercao_patricia = 0;
int comparacoes_consulta_patricia = 0;
int comparacoes_insercao_hash = 0;
int comparacoes_consulta_hash = 0;
int main() {

    ListaArquivos *lista_arquivos = NULL;
    IndiceInvertidoHash *indice_hash = criar_tabela_hash(100);
    Patricia arvore_patricia = criar_arvore_patricia();
    int id_doc = 0;
    int idDocPat = 0; 
    mostrar_menu(&lista_arquivos, indice_hash, &arvore_patricia, &id_doc, &idDocPat);
    liberar_lista_arquivos(lista_arquivos);
    liberar_tabela_hash(indice_hash);
    free(arvore_patricia);

    return 0;
}
