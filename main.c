#include "hospedagem.h"
#include "tempo.h"
#include "cliente.h"
#include "quartos.h"
#include "reserva.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM 2

int main() {
    int opcao;

    do {
        printf("\nMENU\n");
        printf("1. Reservas\n");
        printf("2. Clientes\n");
        printf("3. Hospedagem\n");
        printf("4. Quartos\n");
        printf("9. Sair\n");
        printf("Opção: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
               reservas();
                break;
            case 2:
                //listarQuartos();
                clientes();
                break;
            case 3:
                menu_hospedagem();
                break;
            case 4:
                //listarQuartos();
               quartos();
                break;
            case 9:
                printf("Encerrando o programa...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 9);

    return 0;
}


