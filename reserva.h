
#include <stdio.h>
#ifndef RESERVA_H_INCLUDED
#define RESERVA_H_INCLUDED


typedef struct {
    int codigo_reserva;
    char cpf_reserva[13];
    int data_checkin;
    int data_checkout;
    char tipo_quarto[6];
    int codigo_quarto;
} Reserva;


void carregarClientes();
void criarArquivoReservas();
int gerarNumReserva();
void buscarReserva();
void verificarCpf();
void fazerReserva(char *cpf);
void mostrarQuartos();
void cancelarReserva();
// void buscarReservas();
// void buscarReservaPorCPF() ;
Reserva encontrar_reserva_por_cpf(char cpf[], FILE *file);




void reservas();
#endif 