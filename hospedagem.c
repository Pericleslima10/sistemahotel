#include "hospedagem.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void check_in_cliente()
{
    // Implementação para o check-in do cliente
    // Deve perguntar por informações e atualizar os registros de hospedagem e de quarto
    printf("Realizando check-in do cliente.\n");
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