/* 
 * @file:   materiais.c
 *          Vasco Almeida
 * @brief várias funções relativas aos materiais
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "strings.h"
#include "clientes.h"
#include "input.h"
#include "produtos.h"
#include "encomendas.h"
#include "materiais.h"

/**
 * Função que apresenta todas as opções dos materiais
 * 
 * 1- Criar material
 * 2- Ver material
 * 3- Listar material
 * 4- Atualizar material
 * 5- Remover material
 * 6- Guardar material
 * 7- Sair
 * @return return valor escolhido pelo utilizador
 */
int gestao_materiais() {
    int opcao;
    opcao = leitura_menu(GESTAO_MATERIAIS, 0, 6);
    return opcao;
}

/**
 * Função confirmação se existe materiais no sistema ou não
 * 
 * @param materiais estrutura dos materiais
 * @return 
 */
int inserir_materiais(Materiais *materiais) {
    if (materiais->contador >= materiais->tamanho_array) {
        expandir_materiais(materiais);
    }
    if (inserir_material(materiais) == -1) {
        printf("O codigo do material ja existe.\n");
        return -1;
    }
    return 0;
}

/**
 * Função criar materiais no sistema
 * 
 * @param materiais materiais estrutura dos materiais
 * @return 
 */
int inserir_material(Materiais *materiais) {
    int codigo;

    printf(MSG_OBTER_MATERIAL);
    scanf("%d", &codigo);
    cleanInputBuffer();

    if (verificacao_procurar_material(materiais, codigo) == -1) {

        materiais->materiais[materiais->contador].codMaterial = codigo;
        lerString(materiais->materiais[materiais->contador].nome_material,
                MAX_NOME_MATERIAL, MSG_OBTER_NOME_MATERIAL);
        lerString(materiais->materiais[materiais->contador].unidade,
                MAX_UNIDADE_MATERIAL, MSG_UNIDADE_MATERIAL);


        return materiais->contador++;
    }
    return -1;
}

/**
 * Função verifica a procura dos materiais no sistema
 * 
 * @param materiais materiais estrutura dos materiais
 * @param codigo referente ao material
 * @return return -1 se não existir se existir return i
 */
int verificacao_procurar_material(Materiais *materiais, int codigo) {
    int i;
    for (i = 0; i < materiais->contador; i++) {
        if (materiais->materiais[i].codMaterial == codigo) {
            return i;
        }
    }
    return -1;
}

/**
 * Função procura o material no sistema
 * 
 * @param materiais materiais estrutura dos materiais
 */
void procurar_materiais(Materiais *materiais) {
    int codigo, indice_material;
    printf(MSG_OBTER_MATERIAL);
    scanf("%d", &codigo);
    cleanInputBuffer();

    indice_material = verificacao_procurar_material(materiais, codigo);

    if (indice_material != -1) {
        imprimir_materiais(&materiais->materiais[indice_material]);
    } else {
        puts(MATERIAL_NAO_EXISTE);
    }
}

/**
 * Função imprime no ecrã os materiais no sistema
 * 
 * @param material materiais estrutura dos materiais
 */
void imprimir_materiais(Material *material) {
    printf("\nCodigo: %d |Nome: %s |Unidade: %s\n",
            material->codMaterial, material->nome_material, material->unidade);
    printf(SEPARACAO);

}

/**
 * Função lista no ecrã todos os materiais no sistema
 * 
 * @param materiais materiais estrutura dos materiais
 */
void listar_materiais(Materiais *materiais) {
    if (materiais->contador > 0) {
        int i;
        for (i = 0; i < materiais->contador; i++) {
            imprimir_materiais(&materiais->materiais[i]);
        }
    } else {
        puts(LISTA_MATERIAl_VAZIA);
    }
}

/**
 * Função que permite atualizar os materiais do sistema
 * 
 * @param materiais materiais estrutura dos materiais
 */
void atualizar_materiais(Materiais *materiais) {
    int codigo, indice_material;
    printf(MSG_OBTER_MATERIAL);
    scanf("%d", &codigo);
    cleanInputBuffer();
    indice_material = verificacao_procurar_material(materiais, codigo);

    if (indice_material != -1) {
        mudanca_dados_materiais(&materiais->materiais[indice_material]);
    } else {
        puts(MATERIAL_NAO_EXISTE);
    }
}

/**
 * Função que permite a mudança de dados dos materiais
 * 
 * @param material materiais estrutura dos materiais
 */
void mudanca_dados_materiais(Material *material) {

    lerString((*material).nome_material, MAX_NOME_MATERIAL,
            MSG_OBTER_NOME_MATERIAL);
    lerString((*material).unidade, MAX_UNIDADE_MATERIAL, MSG_UNIDADE_MATERIAL);
}

/**
 * Função permite remover materiais do sistema
 * 
 * @param materiais materiais estrutura dos materiais
 */
void remover_materiais(Materiais *materiais) {
    int i, codigo, indice_material;
    printf(MSG_OBTER_MATERIAL);
    scanf("%d", &codigo);
    cleanInputBuffer();
    indice_material = verificacao_procurar_material(materiais, codigo);

    if (indice_material != -1) {
        for (i = indice_material; i < materiais->contador - 1; i++) {
            materiais->materiais[i] = materiais->materiais[i + 1];
        }
        materiais->contador--;
    } else {
        printf(MATERIAL_NAO_EXISTE);
    }
}

/**
 * Função guarda os materiais em ficheiro externo
 * 
 * @param materiais materiais estrutura dos materiais
 * @param ficheiro ficheiro onde estão guardados materiais
 */
void guardar_materiais(Materiais *materiais, char *ficheiro) {
    int i;

    FILE *fp = fopen(ficheiro, "wb");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }

    fwrite(&materiais->contador, sizeof (int), 1, fp);

    for (i = 0; i < materiais->contador; i++) {
        fwrite(&materiais->materiais[i], sizeof (Material), 1, fp);
    }
    fclose(fp);
}

/**
 * Função que carrega os materiais do ficheiro externo
 * 
 * @param materiais materiais estrutura dos materiais
 * @param ficheiro ficheiro onde estão guardados materiais
 */
void carregar_materiais(Materiais *materiais, char *ficheiro) {
    int i;
    FILE *fp = fopen(ficheiro, "rb");

    materiais->contador = 0;
    materiais->tamanho_array = 20;
    materiais->materiais = (Material *) malloc(materiais->tamanho_array * sizeof (Material));

    if (materiais->materiais == NULL) {
        exit(EXIT_FAILURE);
    }

    if (fp != NULL) {
        if (fread(&materiais->contador, sizeof (int), 1, fp) == 1 && materiais->contador > 0) {
            if (materiais->contador >= materiais->tamanho_array) {
                materiais->tamanho_array = materiais->contador + 20;
                Material *temp = (Material *) realloc(materiais->materiais,
                        materiais->tamanho_array * sizeof (Material));
                if (temp == NULL) {
                    fclose(fp);
                    free(materiais->materiais);
                    exit(EXIT_FAILURE);
                }
                materiais->materiais = temp;
            }

            for (i = 0; i < materiais->contador; i++) {
                if (fread(&materiais->materiais[i], sizeof (Material), 1, fp) != 1) {
                    materiais->contador = i;
                    break;
                }
            }
        }
        fclose(fp);
    }
}

/**
 * Função que permite expandir a quantidades de materiais no sistema
 * 
 * @param materiais materiais estrutura dos materiais
 */
void expandir_materiais(Materiais *materiais) {
    if (materiais->contador >= materiais->tamanho_array) {
        materiais->tamanho_array = materiais->contador + 20;
        materiais->materiais = (Material *)
                realloc(materiais->materiais,
                materiais->tamanho_array * sizeof (Material));
    }
}
