/* 
 * @File:   materiais.h
 *          Vasco Almeida
 *
 */
#ifndef MATERIAIS_H
#define MATERIAIS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "strings.h"
#include "clientes.h"
#include "input.h"
#include "produtos.h"

#define MATERIAL_NAO_EXISTE      "O Material nao existe!\n"
#define LISTA_MATERIAl_VAZIA     "A lista de materiais está vazia.\n"

    int gestao_materiais();
    int inserir_materiais(Materiais *materiais);
    void expandir_materiais(Materiais *materiais);
    void carregar_materiais(Materiais *materiais, char *ficheiro);
    void guardar_materiais(Materiais *materiais, char *ficheiro);
    void remover_materiais(Materiais *materiais);
    void mudanca_dados_materiais(Material *material);
    void atualizar_materiais(Materiais *materiais);
    void listar_materiais(Materiais *materiais);
    void imprimir_materiais(Material *material);
    void procurar_materiais(Materiais *materiais);
    int verificacao_procurar_material(Materiais *materiais, int codigo);
    int inserir_materiais(Materiais *materiais);
    int inserir_material(Materiais *materiais);

#ifdef __cplusplus
}
#endif

#endif /* MATERIAIS_H */

