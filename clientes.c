/* 
 * @file:   clientes.c
 *          Vasco Almeida
 * @brief várias funções relativas aos clientes
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "strings.h"
#include "clientes.h"
#include "input.h"
#include "produtos.h"
#include "encomendas.h"

/**
 * Função que apresenta todas as opções dos clientes
 * 
 * 1- Criar cliente
 * 2- Ver cliente
 * 3- Listar clientes
 * 4- Atualizar cliente
 * 5- Remover cliente
 * 6- Guardar cliente
 * 7- Sair
 * @return return valor escolhido pelo utilizador
 */
int gestao_clientes() {
    int opcao;
    opcao = leitura_menu(GESTAO_CLIENTE, 0, 6);
    return opcao;
}

/**
 * Função que apresenta todas as opções do cliente
 * 
 * 1- Cliente existente
 * 2- Criar cliente
 * 0- Sair
 * @return return valor escolhido pelo utilizador
 */
int opcao_cliente() {
    int opcao;
    opcao = leitura_menu(CLIENTE_OPCOES, 0, 2);
    return opcao;
}

/**
 * Função que apresenta todas as opções do cliente
 * 
 * 1- Criar encomenda
 * 2- Ver encomenda
 * 0- Sair
 * @return 
 */
int opcao_encomenda() {
    int opcao;
    opcao = leitura_menu(CLIENTE_ENCOMENDA, 0, 2);
    return opcao;
}

/**
 * Função que verifica se existe o cliente na estrura e se a lista se encontra 
 * cheia
 * 
 * @param clientes estrutura de dados de Clientes
 */
void inserir_clientes(Clientes *clientes) {
    if (clientes->contador == clientes->tamanhoArray) {
        expandir_clientes(clientes);
    }
    if (clientes->contador < MAX_CLIENTES) {
        if (inserir_dados_cliente(clientes) == -1) {
            puts(ERRO_CLIENTE_EXISTE);
        }
    }
}

/**
 * Função que verifica se existe o código pedido
 * 
 * @param clientes estrutura de dados de Clientes
 * @param codigo código do cliente a procurar
 * @return se o codigo já existe ou não
 */
int verificacao_procurar_cliente(Clientes clientes, int codigo) {
    int i;
    for (i = 0; i < clientes.contador; i++) {
        if (clientes.clientes[i].cod == codigo) {
            return i;
        }
    }
    return -1;
}

/**
 * Função para inserir os dados do novo cliente
 *  
 * @param clientes estrutura de dados de Clientes
 * @return aumenta o número de clientes na estrutura ou erro se o código do 
 * cliente já existir
 */
int inserir_dados_cliente(Clientes *clientes) {
    int codigo;

    printf(MSG_OBTER_COD_CLIENTE);
    scanf("%d", &codigo);
    cleanInputBuffer();

    if (verificacao_procurar_cliente(*clientes, codigo) == -1) {

        clientes->clientes[clientes->contador].cod = codigo;

        lerString(clientes->clientes[clientes->contador].nome,
                MAX_NOME_CLIENTE, MSG_OBTER_NOME);
        clientes->clientes[clientes->contador].nif = obterInt
                (MIN_NIF_CLIENTE, MAX_NIF_CLIENTE, OBTER_NIF_CLIENTE);
        lerString(clientes->clientes[clientes->contador].pais,
                MAX_COUNTRY_CLIENTE, OBTER_COUNTRY_CLIENTE);
        lerString(clientes->clientes[clientes->contador].morada,
                MAX_MORADA_CLIENTE, OBTER_MORADA_CLIENTE);
        clientes->clientes[clientes->contador].atividade = 'A';
        return clientes->contador++;
    }
    return -1;
}

/**
 * Função que imprime o cliente na ecrã
 * 
 * @param cliente estrutura de dados de Clientes 
 */
void imprimir_cliente(Cliente cliente) {
    printf("\nCodigo: %d Nome: %s NIF: %d Pais: %s Morada: %s Estado: %s\n",
            cliente.cod,
            cliente.nome,
            cliente.nif,
            cliente.pais,
            cliente.morada,
            cliente.atividade == 'D' ? "Inativo" : "Ativo");
    printf(SEPARACAO);
}

/**
 * Função que lista todos os clientes que existem na estrutura
 * 
 * @param clientes estrutura de dados de Clientes
 */
void listar_clientes(Clientes clientes) {
    if (clientes.contador > 0) {
        int i;
        for (i = 0; i < clientes.contador; i++) {
            imprimir_cliente(clientes.clientes[i]);
        }
    } else {
        puts(ERRO_LISTA_VAZIA);
    }
}

/**
 * Função que com o código procura o cliente e verifica se existe ou não
 * 
 * @param clientes estrutura de dados de Clientes
 */
void procurar_clientes(Clientes clientes) {
    int codigo = verificacao_procurar_cliente(clientes, obterInt
            (MIN_COD_CLIENTE, MAX_COD_CLIENTE, MSG_OBTER_COD_CLIENTE));

    if (codigo != -1) {
        imprimir_cliente(clientes.clientes[codigo]);
    } else {
        puts(ERRO_CLIENTE_NAO_EXISTE);
    }
}

/**
 * Função que permite mudar os dados de um cliente
 * 
 * @param cliente estrutura de dados de Clientes
 */
void mudanca_dados_cliente(Cliente *cliente) {
    lerString((*cliente).nome, MAX_NOME_CLIENTE, MSG_OBTER_NOME);
    (*cliente).nif = obterInt(MIN_NIF_CLIENTE, MAX_NIF_CLIENTE, OBTER_NIF_CLIENTE);
    lerString((*cliente).pais, MAX_COUNTRY_CLIENTE, OBTER_COUNTRY_CLIENTE);
    lerString((*cliente).morada, MAX_MORADA_CLIENTE, OBTER_MORADA_CLIENTE);
}

/**
 * Função que pede o código e verifica se o código existe ou não para atualizar
 *  o cliente
 * 
 * @param clientes estrutura de dados de Clientes
 */
void atualizar_clientes(Clientes *clientes) {
    int codigo = verificacao_procurar_cliente(*clientes, obterInt
            (MIN_COD_CLIENTE, MAX_COD_CLIENTE, MSG_OBTER_COD_CLIENTE));

    if (codigo != -1) {
        mudanca_dados_cliente(&(*clientes).clientes[codigo]);
    } else {
        puts(ERRO_CLIENTE_NAO_EXISTE);
    }
}

/**
 * Função que pede o código do cliente verifica se existe e se existir apaga
 *  o mesmo
 * 
 * @param clientes estrutura de dados de Clientes
 */
void remover_clientes(Clientes *clientes, Encomendas *encomendas) {
    int i, codigo = verificacao_procurar_cliente(*clientes,
            obterInt(MIN_COD_CLIENTE, MAX_COD_CLIENTE, MSG_OBTER_COD_CLIENTE));

    if (codigo == -1) {
        puts(ERRO_CLIENTE_NAO_EXISTE);
        return;
    }

    if (cliente_tem_encomendas(encomendas, clientes->clientes[codigo].cod)) {
        clientes->clientes[codigo].atividade = 'D';
        printf("O cliente possui encomendas e foi alterado para inativo.\n");
        return;
    }

    for (i = codigo; i < clientes->contador - 1; i++) {
        clientes->clientes[i] = clientes->clientes[i + 1];
    }

    if (clientes->contador > 0) {
        apagar_dados_cliente(&clientes->clientes[clientes->contador - 1]);
        clientes->contador--;
    }
}

/**
 * Função que torna todos os dados do cliente a zero ou vazio
 * 
 * @param cliente estrutura de dados de Clientes
 */
void apagar_dados_cliente(Cliente *cliente) {
    cliente->cod = 0;
    strncpy(cliente->nome, "", MAX_NOME_CLIENTE);
    cliente->nif = 0;
    strncpy(cliente->pais, "", MAX_COUNTRY_CLIENTE);
    strncpy(cliente->morada, "", MAX_MORADA_CLIENTE);
    cliente->atividade = 'D';
}

/**
 * Função que permite aumentar a quantidade de clientes
 * 
 * @param clientes estrutura de dados de Clientes
 */
void expandir_clientes(Clientes *clientes) {
    if (clientes->contador >= clientes->tamanhoArray) {
        clientes->tamanhoArray = clientes->contador + 20;
        clientes->clientes = (Cliente *) realloc(clientes->clientes,
                clientes->tamanhoArray * sizeof (Cliente));
    }
}

/**
 * Função que permite carregar o ficheiro onde os clientes estão guardados
 * 
 * @param clientes estrutura de dados de Clientes
 * @param ficheiro onde os clientes estão gravados
 */
void carregar_clientes(Clientes *clientes, char *ficheiro) {
    int i;
    FILE *fp = fopen(ficheiro, "rb");

    clientes->contador = 0;
    clientes->numClientes = 0;
    clientes->tamanhoArray = 20;
    clientes->clientes = (Cliente *) malloc(clientes->tamanhoArray * sizeof (Cliente));

    if (clientes->clientes == NULL) {
        exit(EXIT_FAILURE);
    }

    if (fp != NULL) {
        if (fread(&clientes->contador, sizeof (int), 1, fp) == 1 && clientes->contador > 0) {
            if (clientes->contador >= clientes->tamanhoArray) {
                clientes->tamanhoArray = clientes->contador + 20;
                Cliente *temp = (Cliente *) realloc(clientes->clientes,
                        clientes->tamanhoArray * sizeof (Cliente));
                if (temp == NULL) {
                    fclose(fp);
                    free(clientes->clientes);
                    exit(EXIT_FAILURE);
                }
                clientes->clientes = temp;
            }

            for (i = 0; i < clientes->contador; i++) {
                if (fread(&clientes->clientes[i], sizeof (Cliente), 1, fp) != 1) {
                    clientes->contador = i;
                    break;
                }
                if (clientes->clientes[i].atividade != 'A' &&
                        clientes->clientes[i].atividade != 'D') {
                    clientes->clientes[i].atividade = 'A';
                }
            }
            clientes->numClientes = clientes->contador;
        }
        fclose(fp);
    }
}

/**
 * Função que permite guardar os clientes feitos no seu ficheiro
 * 
 * @param clientes estrutura de dados de Clientes
 * @param ficheiro onde os clientes estão gravados
 */
void guardar_clientes(Clientes *clientes, char *ficheiro) {
    int i;

    FILE *fp = fopen(ficheiro, "wb");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }

    fwrite(&clientes->contador, sizeof (int), 1, fp);

    for (i = 0; i < clientes->contador; i++) {
        fwrite(&clientes->clientes[i], sizeof (Cliente), 1, fp);
    }

    fclose(fp);
}
