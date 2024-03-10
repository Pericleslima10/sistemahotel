// hospedagem.h

#ifndef HOSPEDAGEM_H_INCLUDED
#define HOSPEDAGEM_H_INCLUDED

#include "tempo.h"
typedef struct {
    int id_reserva;          // Identificação da reserva
    char cpf_cliente[14];    // CPF do cliente, assumindo 13 dígitos + terminador nulo
    DATA data_check_in;      // Data do check-in
    DATA data_check_out;     // Data do check-out
    char status[10];         // Status da hospedagem, por exemplo "Ativa" ou "Finalizada"
    double preco_total;      // Preço total da hospedagem
} Hospedagem;

void check_in_cliente();
void check_out_cliente();
void buscar_hospedagens_cliente();
void menu_hospedagem();
int buscaReserva(int codigoReserva, Hospedagem *hospedagem);
void atualizarStatusQuarto(int codigoQuarto, char novoStatus[2]);
int quantidadeHospedagensCSV();
int obterIdQuarto(int idReserva);
float obterPrecoDiariaQuarto(int idQuarto);
double calcularPrecoTotal(int idReserva, double diaria);
void finalizarHospedagem(int idReserva, double precoTotal);

#endif // HOSPEDAGEM_H_INCLUDED
