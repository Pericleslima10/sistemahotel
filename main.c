// Para dividir em .c e .h bastaria criar uma função no .h, e no .c 
// colocar todo o código que tem. Depois apenas seria necessário chamar no main. 
// Isso não seria grande ideia mas ficaria assim:

// matriz.h

// #include <stdio.h>
// #ifndef MATRIZ_H_INCLUDED
// #define MATRIZ_H_INCLUDED

// void programa_matriz();

// #endif // MATRIZ_H_INCLUDED

// matriz.c

// #include "matriz.h"
// void programa_matriz(){
//     //todo o código que tinha no main aqui
// }

// main.c

// #include "matriz.c"
// int main(){
//     programa_matriz();
//     return 0;
// }

#include "cliente.h"
#include "quartos.h"
#include "reserva.h"
#include "hospedagem.h"
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
                //listarQuartos();
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


