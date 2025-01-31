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
#include "../headers/file_reader.h"
#include "../headers/patricia.h"
#include "../headers/hash.h"
#include "../headers/busca_hash.h"
#include "../headers/busca_patricia.h"
#include "../headers/menu.h"
#include "../headers/contadores.h"


/*--------------------------------------Funções de visualização no main----------------------------------------------------------------*/
void mostrar_menu(ListaArquivos **lista_arquivos, IndiceInvertidoHash *indice_hash, Patricia *arvore_patricia, int *id_doc, int *idDocPat) {
    int escolha;
    int num_termos;

    while (1) {
        printf("---------------------------------------------------\n");
        printf("Menu:\n");
        printf("1. Receber arquivo de entrada\n");
        printf("2. Construir índices invertidos HASH\n");
        printf("3. Construir índices invertidos PATRÍCIA\n");
        printf("4. Imprimir índices invertidos HASH\n");
        printf("5. Imprimir índices invertidos PATRÍCIA\n");
        printf("6. Realizar buscas na HASH\n");
        printf("7. Realizar buscas na PATRÍCIA\n");
        printf("8. Comparação de inserção de termos HASH e PATRICIA\n");
        printf("10.Comparação de consulta de termos HASH e PATRICIA \n");
        printf("11. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &escolha);
        printf("---------------------------------------------------\n");

        if (escolha == 1) {
            *lista_arquivos = ler_lista_arquivos("entrada.txt");
            if (*lista_arquivos) {
                printf("Arquivo de entrada lido com sucesso.\n");
            } else {
                printf("Falha ao ler o arquivo de entrada.\n");
            }
        } else if (escolha == 2) {
            if (*lista_arquivos) {
                construir_indices_invertidos(*lista_arquivos, indice_hash, id_doc);
                printf("Índices invertidos da HASH construídos com sucesso.\n");
            } else {
                printf("Primeiro importe o arquivo de entrada.\n");
            }
        } else if (escolha == 3) {
            if (*lista_arquivos) {
                *arvore_patricia = criar_arvore_patricia();
                
                construir_indices_invertidos_patricia(*lista_arquivos, arvore_patricia, idDocPat);
                printf("Índices invertidos da PATRÍCIA construídos com sucesso.\n");
            } else {
                printf("Primeiro importe o arquivo de entrada.\n");
            }
        } else if (escolha == 4) {
            if (indice_hash->tamanho > 0) {
                printf("---------------------------------------------------\n");
                printf("                        HASH                       \n");
                imprimir_indices_invertidos(indice_hash);
                printf("---------------------------------------------------\n");
            } else {
                printf("Primeiro construa os índices invertidos.\n");
            }
        } else if (escolha == 5) {
            if (*arvore_patricia) {
                printf("---------------------------------------------------\n");
                printf("                    PATRÍCIA                       \n");
                imprimirPatriciaOrdenada(*arvore_patricia);
                printf("---------------------------------------------------\n");
            } else {
                printf("Primeiro construa os índices invertidos.\n");
            }
        } else if (escolha == 6) {
            if (indice_hash->tamanho > 0) {
                printf("Digite o número de ingredientes de busca: ");
                scanf("%d", &num_termos);
                char **ingredientes = (char **)malloc(num_termos * sizeof(char *));
                for (int i = 0; i < num_termos; i++) {
                    ingredientes[i] = (char *)malloc(256 * sizeof(char));
                    printf("Digite o ingrediente %d: ", i + 1);
                    scanf(" %[^\n]s", ingredientes[i]);
                }

                buscar_e_calcular_relevancia(indice_hash, (const char **)ingredientes, num_termos, *lista_arquivos);

                for (int i = 0; i < num_termos; i++) {
                    free(ingredientes[i]);
                }
                free(ingredientes);
            } else {
                printf("Primeiro construa os índices invertidos.\n");
            }
        } else if (escolha == 7) {
            if (*arvore_patricia) {
                printf("Digite o número de termos de busca: ");
                scanf("%d", &num_termos);
                char **termos_busca = (char **)malloc(num_termos * sizeof(char *));
                for (int i = 0; i < num_termos; i++) {
                    termos_busca[i] = (char *)malloc(256 * sizeof(char));
                    printf("Digite o termo %d: ", i + 1);
                    scanf(" %[^\n]", termos_busca[i]);
                }

                buscar_e_calcular_relevancia_patricia(&(*arvore_patricia), (const char **)termos_busca, num_termos, *lista_arquivos);

                for (int i = 0; i < num_termos; i++) {
                    free(termos_busca[i]);
                }
                free(termos_busca);
            } else {
                printf("Primeiro construa os índices invertidos PATRÍCIA.\n");
            }
        } else if (escolha == 8){
            printf("Número de comparações na inserção (Patricia): %d\n", comparacoes_insercao_patricia);
            printf("Número de comparações na inserção (Hash): %d\n", comparacoes_insercao_hash);
        }else if(escolha == 9){
            printf("Número de comparações na consulta (Hash): %d\n", comparacoes_consulta_hash);
            printf("Número de comparações na consulta (Patricia): %d\n", comparacoes_consulta_patricia);

        } else if (escolha == 10) {
            printf("Saindo...\n");
            break;
        } else {
            printf("Opção inválida. Tente novamente.\n");
        }
    }
}