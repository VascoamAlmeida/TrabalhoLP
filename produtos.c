/* 
 * @file:   produtos.c
 *          Vasco Almeida
 * @brief várias funções relativas aos produtos
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
 * Função que apresenta todas as opções dos produtos
 * 
 * 1- Criar produto
 * 2- Ver produto
 * 3- Listar produtos
 * 4- Atualizar produtos
 * 5- Remover produtos
 * 6- Guardar produtos
 * 7- Sair
 * @return return valor escolhido pelo utilizador
 */
int gestao_produtos() {
    int opcao;
    opcao = leitura_menu(GESTAO_PRODUTOS, 0, 6);
    return opcao;
}

/**
 * Função que verifica se o produto existe ou não
 * 
 * @param produtos estrutura dos produtos
 */
void inserir_produtos(Produtos *produtos) {
    if (produtos->contador == produtos->tamanhoArray) {
        expandir_produtos(produtos);
    }
    if (produtos->contador < MAX_PRODUTOS) {
        if (inserir_produto(produtos) == -1) {
            printf(ERRO_PRODUTO_EXISTE);
        }
    }
}

/**
 * Função que permite inserir os dados do produto
 * 
 * @param produtos estrutura dos produtos
 * @return 
 */
int inserir_produto(Produtos *produtos) {
    int i, quantidade_mat;
    int codigo;

    printf(MSG_OBTER_COD_PRODUTO);
    scanf("%d", &codigo);
    cleanInputBuffer();

    if (verificacao_procurar_produto(produtos, codigo) == -1) {

        produtos->produtos[produtos->contador].codProduto = codigo;
        lerString(produtos->produtos[produtos->contador].nome,
                MAX_NOME_PRODUTO, MSG_OBTER_NOME_PRODUTO);
        produtos->produtos[produtos->contador].dimensoes.comprimento =
                obterInt(MIN_COMPRIMENTO_PRODUTO, MAX_COMPRIMENTO_PRODUTO,
                MSG_OBTER_COMPRIMENTO_PRODUTO);
        produtos->produtos[produtos->contador].dimensoes.largura =
                obterInt(MIN_LARGURA_PRODUTO, MAX_LARGURA_PRODUTO,
                MSG_OBTER_LARGURA_PRODUTO);
        produtos->produtos[produtos->contador].dimensoes.altura =
                obterInt(MIN_ALTURA_PRODUTO, MAX_ALTURA_PRODUTO,
                MSG_OBTER_ALTURA_PRODUTO);
        produtos->produtos[produtos->contador].preco =
                obterInt(MIN_PRECO_PRODUTO, MAX_PRECO_PRODUTO,
                MSG_OBTER_PRECO_PRODUTO);
        produtos->produtos[produtos->contador].quantidade_mat =
                quantidade_mat = obterInt(MIN_QUANTOS_MATERIAS,
                MAX_QUANTOS_MATERIAS, MSG_QUANTOS_MATERIAIS);

        for (i = 0; i < quantidade_mat; i++) {
            produtos->produtos[produtos->contador].codmaterial[i] =
                    obterInt(MIN_COD_MATERIAL, MAX_COD_MATERIAL,
                    MSG_OBTER_MATERIAL);
            produtos->produtos[produtos->contador].quantidade_material[i] =
                    obterInt(1, MAX_QUANTIDADE_MATERIAL,
                    MSG_OBTER_QUANTIDADE_MATERIAL);
        }

        produtos->produtos[produtos->contador].atividade = 'A';

        return produtos->contador++;
    }
    return -1;
}

/**
 * Função que verifica a procura do produto
 * 
 * @param produtos estrutura dos produtos
 * @param codigo codigo do produto pedido
 * @return return -1 se não existe produto return i se existe produto
 */
int verificacao_procurar_produto(Produtos *produtos, int codigo) {
    int i;
    for (i = 0; i < produtos->contador; i++) {
        if (produtos->produtos[i].codProduto == codigo) {
            return i;
        }
    }
    return -1;
}

/**
 * Função que procura produto pedido pelo utilizador
 * 
 * @param produtos estrutura dos produtos
 */
void procurar_produtos(Produtos *produtos) {
    int codigo, indice_produto;
    printf(MSG_OBTER_COD_PRODUTO);
    scanf("%d", &codigo);
    cleanInputBuffer();
    indice_produto = verificacao_procurar_produto(produtos, codigo);

    if (indice_produto != -1) {
        imprimir_produto(&produtos->produtos[indice_produto]);
    } else {
        puts(ERRO_PRODUTO_NAO_EXISTE);
    }
}

/**
 * Função que imprime produto pedido no ecrã
 * 
 * @param produto estrutura dos produtos
 */
void imprimir_produto(Produto *produto) {
    printf("\nCodigo: %d |Nome: %s |Dimensoes: %dx%dx%d |Preço: %dEuros |Estado: %s\n",
            produto->codProduto, produto->nome, produto->dimensoes.comprimento,
            produto->dimensoes.largura, produto->dimensoes.altura,
            produto->preco, produto->atividade == 'D' ? "Inativo" : "Ativo");
    printf(SEPARACAO);

}

/**
 * Função que lista todos os produtos do sistema
 * 
 * @param produtos estrutura dos produtos
 */
void listar_produtos(Produtos *produtos) {
    if (produtos->contador > 0) {
        int i;
        for (i = 0; i < produtos->contador; i++) {
            imprimir_produto(&produtos->produtos[i]);
        }
    } else {
        puts(ERRO_LISTA_PRODUTOS_VAZIA);
    }
}

/**
 * Função que atualiza produto pedido pelo utilizador
 * 
 * @param produtos estrutura dos produtos
 */
void atualizar_produtos(Produtos *produtos) {
    int codigo, indice_produto;
    printf(MSG_OBTER_COD_PRODUTO);
    scanf("%d", &codigo);
    cleanInputBuffer();
    indice_produto = verificacao_procurar_produto(produtos, codigo);

    if (indice_produto != -1) {
        mudanca_dados_produto(&produtos->produtos[indice_produto]);
    } else {
        puts(ERRO_PRODUTO_NAO_EXISTE);
    }
}

/**
 * Função que permite mudar os dados do produto
 * 
 * @param produto estrutura dos produtos
 */
void mudanca_dados_produto(Produto *produto) {
    lerString((*produto).nome, MAX_NOME_PRODUTO, MSG_OBTER_NOME_PRODUTO);
    (*produto).dimensoes.comprimento = obterInt(MIN_COMPRIMENTO_PRODUTO,
            MAX_COMPRIMENTO_PRODUTO, MSG_OBTER_COMPRIMENTO_PRODUTO);
    (*produto).dimensoes.largura = obterInt(MIN_LARGURA_PRODUTO,
            MAX_LARGURA_PRODUTO, MSG_OBTER_LARGURA_PRODUTO);
    (*produto).dimensoes.altura = obterInt(MIN_ALTURA_PRODUTO,
            MAX_ALTURA_PRODUTO, MSG_OBTER_ALTURA_PRODUTO);
    (*produto).preco = obterInt(MIN_PRECO_PRODUTO,
            MAX_PRECO_PRODUTO, MSG_OBTER_PRECO_PRODUTO);

}

/**
 * Função que permite remover produto do sistema
 * 
 * @param produtos estrutura dos produtos
 */
void remover_produtos(Produtos *produtos, Encomendas *encomendas) {
    int i, codigo, indice_produto;
    printf(MSG_OBTER_COD_PRODUTO);
    scanf("%d", &codigo);
    cleanInputBuffer();
    indice_produto = verificacao_procurar_produto(produtos, codigo);

    if (indice_produto == -1) {
        puts(ERRO_PRODUTO_NAO_EXISTE);
        return;
    }

    if (produto_tem_encomendas(encomendas, codigo)) {
        apagar_dados_produto(&produtos->produtos[indice_produto]);
        printf("O produto possui encomendas e foi alterado para inativo.\n");
        return;
    }

    for (i = indice_produto; i < produtos->contador - 1; i++) {
        produtos->produtos[i] = produtos->produtos[i + 1];
    }
    produtos->contador--;
}

/**
 * Função que faz com que o produto fique desativado no sistema
 * 
 * @param produto estrutura dos produtos
 */
void apagar_dados_produto(Produto *produto) {
    produto->atividade = 'D';
}

/**
 * Função que guarda os produtos em ficheiro externo
 * 
 * @param produtos estrutura dos produtos
 * @param ficheiro ficheiro externo que contém os produtos
 */
void guardar_produtos(Produtos *produtos, char *ficheiro) {
    int i;

    FILE *fp = fopen(ficheiro, "wb");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }

    fwrite(&produtos->contador, sizeof (int), 1, fp);

    for (i = 0; i < produtos->contador; i++) {
        fwrite(&produtos->produtos[i], sizeof (Produto), 1, fp);
    }

    fclose(fp);
}

/**
 * Função que carrega produtos de ficheiro externo
 * 
 * @param produtos estrutura dos produtos
 * @param ficheiro ficheiro externo que contém os produtos
 */
void carregar_produtos(Produtos *produtos, char *ficheiro) {
    typedef struct {
        int codProduto;
        char nome[MAX_NOME_PRODUTO];
        int preco;
        Dimensoes dimensoes;
        int codmaterial[MAX_QUANTIDADE_MATERIAL];
        int quantidade_mat;
        char atividade;
    } ProdutoLegacy;

    int i, j;
    long tamanho_ficheiro = 0;
    FILE *fp = fopen(ficheiro, "rb");

    produtos->contador = 0;
    produtos->numero_produtos = 0;
    produtos->tamanhoArray = 20;
    produtos->produtos = (Produto *) malloc(produtos->tamanhoArray * sizeof (Produto));

    if (produtos->produtos == NULL) {
        exit(EXIT_FAILURE);
    }

    if (fp != NULL) {
        fseek(fp, 0, SEEK_END);
        tamanho_ficheiro = ftell(fp);
        rewind(fp);

        if (fread(&produtos->contador, sizeof (int), 1, fp) == 1 && produtos->contador > 0) {
            int formato_antigo = tamanho_ficheiro ==
                    (long) sizeof (int) + (long) produtos->contador * (long) sizeof (ProdutoLegacy);

            if (produtos->contador >= produtos->tamanhoArray) {
                produtos->tamanhoArray = produtos->contador + 20;
                Produto *temp = (Produto *) realloc(produtos->produtos,
                        produtos->tamanhoArray * sizeof (Produto));
                if (temp == NULL) {
                    fclose(fp);
                    free(produtos->produtos);
                    exit(EXIT_FAILURE);
                }
                produtos->produtos = temp;
            }

            for (i = 0; i < produtos->contador; i++) {
                if (formato_antigo) {
                    ProdutoLegacy antigo;
                    if (fread(&antigo, sizeof (ProdutoLegacy), 1, fp) != 1) {
                        produtos->contador = i;
                        break;
                    }
                    memset(&produtos->produtos[i], 0, sizeof (Produto));
                    produtos->produtos[i].codProduto = antigo.codProduto;
                    strncpy(produtos->produtos[i].nome, antigo.nome, MAX_NOME_PRODUTO);
                    produtos->produtos[i].nome[MAX_NOME_PRODUTO - 1] = '\0';
                    produtos->produtos[i].preco = antigo.preco;
                    produtos->produtos[i].dimensoes = antigo.dimensoes;
                    produtos->produtos[i].quantidade_mat = antigo.quantidade_mat;
                    produtos->produtos[i].atividade =
                            antigo.atividade == 'D' ? 'D' : 'A';
                    for (j = 0; j < antigo.quantidade_mat &&
                            j < MAX_QUANTIDADE_MATERIAL; j++) {
                        produtos->produtos[i].codmaterial[j] = antigo.codmaterial[j];
                        produtos->produtos[i].quantidade_material[j] = 1;
                    }
                } else if (fread(&produtos->produtos[i], sizeof (Produto), 1, fp) != 1) {
                    produtos->contador = i;
                    break;
                } else {
                    if (produtos->produtos[i].atividade != 'A' &&
                            produtos->produtos[i].atividade != 'D') {
                        produtos->produtos[i].atividade = 'A';
                    }
                    for (j = 0; j < produtos->produtos[i].quantidade_mat &&
                            j < MAX_QUANTIDADE_MATERIAL; j++) {
                        if (produtos->produtos[i].quantidade_material[j] <= 0) {
                            produtos->produtos[i].quantidade_material[j] = 1;
                        }
                    }
                }
            }
            produtos->numero_produtos = produtos->contador;
        }
        fclose(fp);
    }
}

/**
 * Função que permite ao cliente imprimir produto pretendido
 * 
 * @param produto estrutura dos produtos
 */
void imprimir_produto_cliente(Produto *produto) {
    printf("\nCodigo: %d |Nome: %s |Dimensoes: %dx%dx%d |Preço: %dEuros\n",
            produto->codProduto, produto->nome, produto->dimensoes.comprimento,
            produto->dimensoes.largura, produto->dimensoes.altura,
            produto->preco);
    printf(SEPARACAO);

}

/**
 * Função que permite o cliente listar os produtos que tem disponiveis
 * 
 * @param produtos estrutura dos produtos
 */
void listar_produtos_cliente(Produtos *produtos) {
    if (produtos->contador > 0) {
        int i, encontrados = 0;
        for (i = 0; i < produtos->contador; i++) {
            if (produtos->produtos[i].atividade != 'D') {
                imprimir_produto_cliente(&produtos->produtos[i]);
                encontrados++;
            }
        }
        if (encontrados == 0) {
            puts(ERRO_LISTA_PRODUTOS_VAZIA);
        }
    } else {
        puts(ERRO_LISTA_PRODUTOS_VAZIA);
    }
}

/**
 * Função que expande a quantidade de produtos no sistema
 * 
 * @param produtos estrutura dos produtos
 */
void expandir_produtos(Produtos *produtos) {
    if (produtos->contador >= produtos->tamanhoArray) {
        produtos->tamanhoArray = produtos->contador + 20;
        produtos->produtos = (Produto *) realloc(produtos->produtos,
                produtos->tamanhoArray * sizeof (Produto));
    }
}
