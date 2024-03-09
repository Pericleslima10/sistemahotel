#include "hospedagem.h"
#include "reserva.h"
#include "quartos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void check_in_cliente()
{
    // Implementação para o check-in do cliente
    // Deve perguntar por informações e atualizar os registros de hospedagem e de quarto
    printf("Realizando check-in do cliente.\n");
    int codigoReserva;
    Hospedagem hospedagem;

    printf("Digite o código da reserva para check-in: ");
    scanf("%d", &codigoReserva);
    getchar(); // Limpa buffer de entrada

    // Função fictícia - implementar de acordo com a lógica de negócios
   int i = buscaReserva(codigoReserva);
   FILE *arquivo = fopen("hospedagens.csv", "a");

    if (i == 1)
    {

        printf("Check-in realizado com sucesso!\n");
        fprintf(arquivo, "%d;%s;%s;%s;%s;%f\n", hospedagem.id_reserva, hospedagem.cpf_cliente, hospedagem.data_check_in, "", hospedagem.status, 0.0);                 
    }
    else
    {
        printf("Reserva não encontrada ou já finalizada.\n");
    }
}

void check_out_cliente()
{
    // Implementação para o check-out do cliente
    // Deve calcular o valor total da estadia, atualizar o status do quarto e finalizar a hospedagem
    printf("Realizando check-out do cliente.\n");
}

void buscar_hospedagens_cliente()
{
    // Implementação para buscar as hospedagens de um cliente
    // Deve pedir o CPF do cliente e mostrar todas as hospedagens relacionadas
    printf("Buscando hospedagens do cliente.\n");
}

void menu_hospedagem()
{
    int opcao;
    do
    {
        printf("\nMenu de Hospedagem\n");
        printf("1. Check-in de cliente\n");
        printf("2. Check-out de cliente\n");
        printf("3. Buscar hospedagens do cliente\n");
        printf("9. Voltar para o menu principal\n");
        printf("Selecione uma opção: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao)
        {
        case 1:
            check_in_cliente();
            break;
        case 2:
            check_out_cliente();
            break;
        case 3:
            buscar_hospedagens_cliente();
            break;
        case 9:
            printf("Retornando ao menu principal...\n");
            break;
        default:
            printf("Opção inválida, por favor tente novamente.\n");
        }
    } while (opcao != 9);
}

int buscaReserva(int codigoReserva)
{
    FILE *arquivo = fopen("reservas.csv", "r");
    if (!arquivo)
    {
        printf("Arquivo reservas.csv não pode ser aberto.\n");
        return 0;
    }

    char linha[256];
    int reservaEncontrada = 0;

    while (fgets(linha, sizeof(linha), arquivo))
    {
        int codigo;
        char cpf[14]; // Tamanho do CPF com espaço para o terminador nulo
        Hospedagem hospedagem;
        // Supõe que o CPF está na segunda coluna e o código da reserva na primeira
        if (sscanf(linha, "%d;%14[^;];", &codigo, cpf) == 2)
        {
            if (codigo == codigoReserva)
            {
                reservaEncontrada = 1;
                strcpy(hospedagem.cpf_cliente, cpf);
                strcpy(hospedagem.status, "Ativa");
                hospedagem.id_reserva = codigo;
                hospedagem.data_check_in = hoje();
                break;
            }
        }
    }

    fclose(arquivo);
    return reservaEncontrada;
}

Quarto buscaQuartoPorId(int codigoQuarto)
{

    Quarto quarto;
    return quarto;
}