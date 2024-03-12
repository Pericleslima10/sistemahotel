
#include <stdio.h>
#ifndef RESERVA_H_INCLUDED
#define RESERVA_H_INCLUDED

typedef struct {
    int codigo_reserva;
    char cpf_reserva[12];
    int data_checkin;
    int data_checkout;
    char tipo_quarto[6];
    int codigo_quarto;
} Reserva;

void carregarClientes();
void criarArquivoReservas();
void verificarCpf();
void fazerReserva();
void mostrarQuartos();
void cancelarReserva();
void buscarReservas();
void reservas();
#endif 