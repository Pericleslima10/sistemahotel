
#include <stdio.h>
#ifndef QUARTOS_H_INCLUDED
#define QUARTOS_H_INCLUDED


typedef struct {
    int codigo_quarto;
    int camas_solteiro;
    int camas_casal;
    char tipo_quarto[6];
    double preco_diaria;
    char status[1];
} Quarto;
void quartos();
void criarArquivoq();
void novoquarto();
void alteraquarto();
void deletarQuarto();

#endif 