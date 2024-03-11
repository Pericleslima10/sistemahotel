
#include <stdio.h>
#ifndef CLIENTE_H_INCLUDED
#define CLIENTE_H_INCLUDED

typedef struct {
    char nome_cliente[50];
    char cpf_cliente[13];
    int data_nasc;
    int idade_cliente;
    char endereco[100];
    char cidade[100];
    char estado[2];
} Cliente;

void clientes();
void novocliente();
void criarArquivo();
void alterarcliente();
void removercliente();

#endif 