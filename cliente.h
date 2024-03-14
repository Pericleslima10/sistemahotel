
#include <stdio.h>
#ifndef CLIENTE_H_INCLUDED
#define CLIENTE_H_INCLUDED

typedef struct {
    char nome_cliente[50];
    char cpf_cliente[13];
    char data_nasc[11];
    int idade_cliente;
    char endereco[100];
    char cidade[100];
    char estado[3];
} Cliente;

void clientes();
void novocliente();
void criarArquivo();
void alterarcliente();
void removercliente();

#endif 