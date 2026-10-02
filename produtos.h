/* 
 * @File:   produtos.h
 *          Vasco Almeida
 *
 */
#ifndef PRODUTOS_H
#define PRODUTOS_H

typedef struct Encomendas Encomendas;

#ifdef __cplusplus
extern "C" {
#endif



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "strings.h"
#include "clientes.h"
#include "input.h"

    //=========================VARIÁVEIS PARA PRODUTO===========================
#define ERRO_PRODUTO_NAO_EXISTE   "O produto não existe na lista.\n"
#define ERRO_PRODUTO_EXISTE     "O codigo do produto já se encontra atribuído.\n"
#define ERRO_LISTA_PRODUTOS_VAZIA    "A lista de produtos está vazia.\n"
#define ERRO_LISTA_PRODUTOS_CHEIA    "A lista de produtos está cheia.\n"
#define QUANTIDADE_PRODUTOS          "Indique quantos produtos vai desejar:\n"

#define MIN_QUANTIDADE_PRODUTO           1
#define MSG_OBTER_QUANTIDADE_PRODUTO     "Indique a quantidade do produto: "

#define MIN_COD_PRODUTO           1
#define MAX_COD_PRODUTO           999999
#define MSG_OBTER_COD_PRODUTO     "Indique o codigo do produto: "

#define MAX_NOME_PRODUTO          50
#define MSG_OBTER_NOME_PRODUTO    "Indique o nome do produto: "

#define NUM_INICIAL_PRODUTO       1

#define MIN_PRECO_PRODUTO 1
#define MSG_OBTER_PRECO_PRODUTO "Insira preço do produto: "
#define MAX_PRECO_PRODUTO   500

#define MAX_PRODUTOS 20

#define MIN_COMPRIMENTO_PRODUTO 10
#define MAX_COMPRIMENTO_PRODUTO 200
#define MSG_OBTER_COMPRIMENTO_PRODUTO "Indique comprimento do produto: "

#define MIN_LARGURA_PRODUTO 10
#define MAX_LARGURA_PRODUTO 160
#define MSG_OBTER_LARGURA_PRODUTO "Indique largura do produto: "


#define MIN_ALTURA_PRODUTO 10
#define MAX_ALTURA_PRODUTO 100
#define MSG_OBTER_ALTURA_PRODUTO "Indique altura do produto: "


#define MIN_COD_MATERIAL         0
#define MAX_COD_MATERIAL         50
#define MSG_OBTER_MATERIAL       "Indique o codigo do material: "

#define MAX_NOME_MATERIAL         50
#define MSG_OBTER_NOME_MATERIAL    "Indique o nome do material: "

#define MIN_QUANTIDADE_MATERIAL           0
#define MAX_QUANTIDADE_MATERIAL           100
#define MSG_OBTER_QUANTIDADE_MATERIAL     "Indique quantidade do material: "


#define MIN_QUANTOS_MATERIAS       0
#define MAX_QUANTOS_MATERIAS       15    
#define MSG_QUANTOS_MATERIAIS      "Indique quantos materiais tem o produto: "
#define MSG_UNIDADE_MATERIAL      "Indique se o material e unico ou em pares: "

#define NUM_DIM 3    
#define MAX_UNIDADE_MATERIAL 5
#define MIN_UNIDADE_MATERIAL 2


    //=========================STRUCTS PARA MATERIAIS===========================

    /**
     * @struct Material
     * Estrutura de dados do material
     */
    typedef struct {
        int codMaterial;
        char nome_material[MAX_NOME_MATERIAL];
        char unidade[MAX_UNIDADE_MATERIAL];
    } Material;

    /**
     * @struct Materiais
     * Estrutura de dados do materiais
     */
    typedef struct {
        int contador;
        Material *materiais;
        int tamanho_array;
    } Materiais;
    //=========================STRUCTS PARA DIMENSOES===========================

    /**
     * @struct Dimensoes
     * Estrutura de dados das dimensoes do produto
     */
    typedef struct {
        int comprimento, largura, altura;
    } Dimensoes;

    //=========================STRUCTS PARA PRODUTO=============================

    /**
     * @struct Produto
     * Estrutura de dados do produtos
     */
    typedef struct {
        int codProduto;
        char nome[MAX_NOME_PRODUTO];
        int preco;
        Dimensoes dimensoes;
        int codmaterial[MAX_QUANTIDADE_MATERIAL];
        int quantidade_material[MAX_QUANTIDADE_MATERIAL];
        int quantidade_mat;
        char atividade;
    } Produto;

    /**
     * @struct Produtos
     * Estrutura de dados do produtos
     */
    typedef struct {
        int contador, numero_produtos, tamanhoArray;
        Produto *produtos;
    } Produtos;
    //==========================================================================


    int gestao_produtos();
    void inserir_produtos(Produtos *produtos);
    int inserir_produto(Produtos *produtos);
    void procurar_produtos(Produtos *produtos);
    void imprimir_produto(Produto *produto);
    void atualizar_produtos(Produtos *produtos);
    void mudanca_dados_produto(Produto *produto);
    void remover_produtos(Produtos *produtos, Encomendas *encomendas);
    void apagar_dados_produto(Produto *produto);
    int verificacao_procurar_produto(Produtos *produtos, int codigo);
    void listar_produtos(Produtos *produtos);
    void expandir_produtos(Produtos *produtos);
    void guardar_produtos(Produtos *produtos, char *ficheiro);
    void carregar_produtos(Produtos *produtos, char *ficheiro);
    void imprimir_produto_cliente(Produto *produto);
    void listar_produtos_cliente(Produtos *produtos);


#ifdef __cplusplus
}
#endif

#endif /* PRODUTOS_H */

