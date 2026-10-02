/* 
 * @File:   main.c
 *          Vasco Almeida
 * 
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

#define CLIENTES_DB_FILE  "clientes.bin"
#define PRODUTOS_DB_FILE "produtos.bin"
#define ENCOMENDAS_DB_FILE "encomendas.bin"
#define MATERIAIS_DB_FILE "materiais.bin"

Clientes clientes;
Produtos produtos;
Cliente cliente;
Materiais materiais;
Encomendas encomendas;
Encomenda encomenda;

/**
 * Função que carrega os quatro ficheiros externos e entra no menu principal
 * 
 * @return sai do programa
 */
int main() {
    carregar_clientes(&clientes, CLIENTES_DB_FILE);
    carregar_produtos(&produtos, PRODUTOS_DB_FILE);
    carregar_materiais(&materiais, MATERIAIS_DB_FILE);
    carregar_encomendas(&encomendas, ENCOMENDAS_DB_FILE);

    menu_principal();

    return (EXIT_SUCCESS);
}

/**
 * Função que apresenta as opções do administrador
 * 
 * 1- Gestão produtos
 * 2- Gestão materiais
 * 3- Gestão encomendas
 * 4- Gestão clientes
 * 0- Sair do administrador
 */
void menu_admin() {
    int opcao, valor, opc;
    do {
        opcao = leitura_menu(ADMIN_OPCOES, 0, 5);
        switch (opcao) {
            case 0:
                break;
            case 1:
                do {
                    valor = gestao_produtos();

                    printf("Produtos: %d\n", produtos.contador);
                    switch (valor) {
                        case 1:
                            //CRIAR PRODUTO
                            inserir_produtos(&produtos);
                            break;
                        case 2:
                            //PROCURAR PRODUTO
                            procurar_produtos(&produtos);
                            break;
                        case 3:
                            //LISTAR OS PRODUTOS
                            listar_produtos(&produtos);
                            break;
                        case 4:
                            //EDITAR PRODUTOS
                            atualizar_produtos(&produtos);
                            break;
                        case 5:
                            //ELIMINAR PRODUTOS
                            remover_produtos(&produtos, &encomendas);
                            break;
                        case 6:
                            //GUARDAR PRODUTOS
                            guardar_produtos(&produtos, PRODUTOS_DB_FILE);
                            break;
                        case 0:
                            break;
                    }
                } while (valor != 0);
                break;

            case 2:
                do {
                    valor = gestao_materiais();

                    printf("Materiais: %d\n", materiais.contador);
                    switch (valor) {
                        case 1:
                            //CRIAR MATERIAIS
                            inserir_materiais(&materiais);
                            break;
                        case 2:
                            //PROCURAR MATERIAIS
                            procurar_materiais(&materiais);
                            break;
                        case 3:
                            //LISTAR OS MATERIAIS
                            listar_materiais(&materiais);
                            break;
                        case 4:
                            //EDITAR MATERIAIS
                            atualizar_materiais(&materiais);
                            break;
                        case 5:
                            //ELIMINAR MATERIAIS
                            remover_materiais(&materiais);
                            break;
                        case 6:
                            //GUARDAR MATERIAIS
                            guardar_materiais(&materiais, MATERIAIS_DB_FILE);
                            break;
                        case 0:
                            break;
                    }
                } while (valor != 0);
                break;
            case 3:
                do {
                    valor = gestao_encomendas();
                    switch (valor) {
                        case 1:
                            //PROCURA ENCOMENDAS
                            procurar_encomendas(&encomendas, &produtos);
                            break;
                        case 2:
                            do {
                                opc = encomenda_admin();
                                switch (opc) {
                                    case 1:
                                        //LISTA TODAS AS ENCOMENDAS PARA O ADMIN 
                                        listar_encomendas(&encomendas, &produtos);
                                        break;
                                    case 2:
                                        //LISTA TODAS AS ENCOMENDAS ENTREGUES
                                        //AO ADMINISTRADOR
                                        listar_encomendas_terminadas
                                                (&encomendas, &produtos);
                                        break;
                                    case 3:
                                        //LISTA TODAS AS ENCOMENDAS POR ENTREGAR
                                        //AO ADMINISTRADOR
                                        listar_encomendas_por_terminar
                                                (&encomendas, &produtos);
                                        break;
                                    case 0:
                                        break;
                                }
                            } while (opc != 0);
                            break;
                        case 3:
                            //ATUALIZA AS ENCOMENDAS
                            atualizar_encomendas(&encomendas);
                            break;
                        case 4:
                            //GUARDA EM FICHEIRO AS ENCOMENDAS
                            guardar_encomendas(&encomendas, ENCOMENDAS_DB_FILE);
                            break;
                        case 0:
                            break;
                    }
                } while (valor != 0);
                break;
            case 4:
                do {
                    valor = gestao_clientes();
                    printf("Clientes: %d\n", clientes.contador);

                    switch (valor) {
                        case 0:
                            break;
                        case 1:
                            //CRIAR NOVO CLIENTE
                            inserir_clientes(&clientes);
                            break;
                        case 2:
                            //PROCURAR CLIENTE
                            procurar_clientes(clientes);
                            break;
                        case 3:
                            //LISTAR OS CLIENTES
                            listar_clientes(clientes);
                            break;
                        case 4:
                            //EDITAR CLIENTES
                            atualizar_clientes(&clientes);
                            break;
                        case 5:
                            //ELIMINAR CLIENTES
                            remover_clientes(&clientes, &encomendas);
                            break;
                        case 6:
                            //GUARDAR DADOS CLIENTE
                            guardar_clientes(&clientes, CLIENTES_DB_FILE);
                            break;
                    }
                } while (valor != 0);
                break;
            case 5:
                gestao_producao(&encomendas, &produtos, &materiais);
                break;
        }
    } while (opcao != 0);
}

/**
 * Função onde apresenta as várias opções do cliente
 * 
 * @return Sai do menu de cliente
 */
int menu_cliente() {
    int codigo, opcao1, opcao2;
    opcao1 = opcao_cliente();
    switch (opcao1) {
        case 0:
            break;
        case 1:
        {
            codigo = obterInt(MIN_COD_CLIENTE, MAX_COD_CLIENTE, 
                    MSG_OBTER_COD_CLIENTE);

            int indice_cliente = verificacao_procurar_cliente(clientes, codigo);
            if (indice_cliente != -1 && clientes.clientes[indice_cliente].atividade != 'D') {
                opcao2 = opcao_encomenda();

                switch (opcao2) {
                    case 0:
                        break;
                    case 1:
                        //PERMITE INSERIR ENCOMENDA NOVA
                        inserir_encomendas(&encomendas, &produtos, codigo);
                        //GUARDA ENCOMENDA EM FICHEIRO
                        guardar_encomendas(&encomendas, ENCOMENDAS_DB_FILE);
                        break;
                    case 2:
                        //LISTA TODAS AS ENCOMENDAS DO CLIENTE
                        listar_encomendas_cliente(&encomendas, &produtos, codigo);
                        break;
                }
            } else if (indice_cliente != -1) {
                printf("Este cliente encontra-se inativo.\n");
            } else {
                printf(ERRO_CLIENTE_NAO_EXISTE);
            }
            break;
        }
        case 2:
        {
            //PERMITE INSERIR NOVO CLIENTE
            inserir_clientes(&clientes);
            //GUARDA O NOVO CLIENTE
            guardar_clientes(&clientes, CLIENTES_DB_FILE);
            break;
        }
        default:
        {
            printf(ERROR);
            break;
        }
    }
    return 0;
}

/**
 * Função que permite escolher na consola se es administrador ou cliente
 * 
 */
void menu_principal() {
    int perfil;
    do {
        perfil = leitura_menu(LOGIN_MSG, 0, 2);
        switch (perfil) {
            case 0:
                break;
            case 1:
                //MENU CORRESPONDENTE AO CLIENTE
                menu_cliente();
                break;
            case 2:
                //MENU CORRESPONDENTE AO ADMINISTRADOR
                menu_admin();
                break;
            default:
                printf(ERROR);
        }
    } while (perfil != 0);
}
