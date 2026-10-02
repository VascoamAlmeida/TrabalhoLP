/* 
 * @File:   strings.h
 *          Vasco Almeida
 *
 */
#ifndef STRINGS_H
#define STRINGS_H

#ifdef __cplusplus
extern "C" {
#endif

#define SEPARACAO "====================================\n"
#define VALOR_INVALIDO      "O valor inserido é inválido."

#define ERROR  "====================================\n" \
               "OPÇCAO INVALIDA!\n" \
               "====================================\n"

#define LOGIN_MSG "====================================\n" \
                  "Indique o perfil:\n"\
                  ">>Cliente - 1\n"\
                  ">>Administrador - 2\n"\
                  ">>SAIR - 0\n" \
                  "====================================\n"

#define ADMIN_OPCOES "\n====================================\n" \
                     "Indique a opcao:\n" \
                     "1-Gestao Produtos\n" \
                     "2-Gestao Materiais\n" \
                     "3-Gestao Encomendas\n" \
                     "4-Gestao Clientes\n" \
                     "5-Gestao Producao\n" \
                     "0-SAIR\n" \
                     "====================================\n" 

    
#define GESTAO_PRODUTOS "\n====================================\n" \
                        "1 - Criar Produto\n" \
                        "2 - Ver Produto\n" \
                        "3 - Listar Produto\n" \
                        "4 - Atualizar Produto\n" \
                        "5 - Remover Produto\n" \
                        "6 - Guardar Produto\n" \
                        "0 - Sair\n" \
                        "====================================\n"

#define GESTAO_MATERIAIS  "\n====================================\n" \
                          "1 - Criar Material\n" \
                          "2 - Ver Material\n" \
                          "3 - Listar Material\n" \
                          "4 - Atualizar Material\n" \
                          "5 - Remover Material\n" \
                          "6 - Guardar Material\n" \
                          "0 - Sair\n" \
                          "====================================\n"
    
#define GESTAO_CLIENTE    "=====================================\n" \
                          "1 - Criar Cliente\n" \
                          "2 - Ver Perfil Cliente\n" \
                          "3 - Listar Clientes\n" \
                          "4 - Atualizar Cliente\n" \
                          "5 - Eliminar Cliente\n" \
                          "6 - Guardar Dados de Clientes\n" \
                          "0 - SAIR\n" \
                          "=====================================\n"

#define GESTAO_ENCOMENDAS "\n====================================\n" \
                          "1 - Ver Encomenda\n" \
                          "2 - Listar Encomenda\n" \
                          "3 - Terminar Encomenda\n" \
                          "4 - Guardar Encomenda\n" \
                          "0 - Sair\n" \
                          "====================================\n"
    
#define CLIENTE_OPCOES   "\n====================================\n"\
                         "Escolha opção:\n"\
                         "1 - Cliente Existente\n"\
                         "2 - Criar Cliente\n" \
                         "0 - SAIR\n" \
                         "====================================\n"
    
#define CLIENTE_ENCOMENDA  "\n====================================\n"\
                           "1 - Fazer encomendas\n"\
                           "2 - Ver encomendas\n"\
                           "0 - SAIR\n"\
                           "====================================\n"
    
#define ADMIN_ENCOMENDA "\n====================================\n" \
                        "1 - Ver todas encomendas\n" \
                        "2 - Ver as encomendas entregues\n" \
                        "3 - Ver as encomendas por entregar\n" \
                        "0 - SAIR\n" \
                        "====================================\n"

#ifdef __cplusplus
}
#endif

#endif /* STRINGS_H */

