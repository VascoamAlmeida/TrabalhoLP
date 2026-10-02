/* 
 * @File:   clientes.h
 *          Vasco Almeida
 *
 */

#ifndef CLIENTES_H
#define CLIENTES_H

typedef struct Encomendas Encomendas;

#ifdef __cplusplus
extern "C" {
#endif

#define ERRO_CLIENTE_NAO_EXISTE "O cliente não existe na lista.\n"
#define ERRO_LISTA_VAZIA        "A lista de clientes está vazia.\n"
#define ERRO_LISTA_CHEIA        "A lista de clientes está cheia.\n"
#define ERRO_CLIENTE_EXISTE     "O codigo de cliente já se encontra atribuído.\n"
#define CLIENTE_NAO_ENCOMENDA   "Este Cliente não tem encomendas.\n"

    //===================VARIAVIS PARA CRIACAO DOS CLIENTES=====================

#define MIN_COD_CLIENTE           1
#define MAX_COD_CLIENTE           999999
#define MSG_OBTER_COD_CLIENTE     "Insira um codigo de cliente: "

#define MAX_NOME_CLIENTE          50

#define MSG_OBTER_NOME            "Insira o nome do cliente: "

#define MIN_NIF_CLIENTE           0
#define OBTER_NIF_CLIENTE         "Insira o NIF do cliente: "
#define MAX_NIF_CLIENTE           999999999

#define OBTER_COUNTRY_CLIENTE     "Insira o pais do cliente: "
#define MAX_COUNTRY_CLIENTE       50

#define OBTER_MORADA_CLIENTE      "Insira a morada do cliente: "
#define MAX_MORADA_CLIENTE        100

#define NUM_INICIAL_CLIENTE       1

#define MAX_CLIENTES 200


    //===========================STRUCK PARA CLIENTE============================

    /**
     * @struct Cliente
     * Estrutura de dados do cliente
     */
    typedef struct {
        int cod;
        char nome[MAX_NOME_CLIENTE ];
        int nif;
        char pais[MAX_COUNTRY_CLIENTE];
        char morada[MAX_MORADA_CLIENTE];
        char atividade;
    } Cliente;

    //==========================================================================

    /**
     * @struct Clientes
     * Estrutura de dados do contador de clientes
     */
    typedef struct {
        int contador, numClientes, tamanhoArray;
        Cliente *clientes;
    } Clientes;

    int gestao_clientes();
    int opcao_cliente();
    int opcao_encomenda();
    void inserir_clientes(Clientes *clientes);
    void procurar_clientes(Clientes clientes);
    void listar_clientes(Clientes clientes);
    void imprimir_cliente(Cliente cliente);
    void atualizar_clientes(Clientes *clientes);
    void remover_clientes(Clientes *clientes, Encomendas *encomendas);
    void mudanca_dados_cliente(Cliente *cliente);
    int verificacao_procurar_cliente(Clientes clientes, int codigo);
    int inserir_dados_cliente(Clientes *clientes);
    void apagar_dados_cliente(Cliente *cliente);
    void expandir_clientes(Clientes *clientes);
    void carregar_clientes(Clientes *clientes, char *ficheiro);
    void guardar_clientes(Clientes *clientes, char *ficheiro);





#ifdef __cplusplus
}
#endif

#endif /* CLIENTES_H */

